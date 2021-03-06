'' firmware_openrtms_h09_20130202
'' This is the main firmware for the Open-rTMS projects hardware.
'' h09 = Hardware version 0.9 (the first board released by this project).
'' p1 = Protocol version 1. If the protocol changes essentially it will become P2.  
''
'' Author: Tobias Schaefer
'' Created: 02.02.2013
'' Copyright: (C) 2013 Tobias Schaefer <tobiassch@users.sourceforge.net>   
'' License: GNU General Public License version 3.0 (GPLv3)
 
CON


'' Board used:
  board_H09 = true              '' Open rTMS Board version 0.9
  board_H10 = false             '' Open rTMS Board version 1.0 or the Parallax demo board


'' Init the oscillator and the PLL
  _clkmode = xtal1 + pll16x     
  _xinfreq = 5_000_000          ' 5 MHz XTAL and 16x PLL = 80 MHz for the main CLK


'' Pins for the analog comparator
  AC_ch0 = (20 & board_H09)
  AC_ch1 = (21 & board_H09)
  AC_ch2 = (18 & board_H09)
  AC_ch3 = (19 & board_H09)
  AC_ch4 = (13 & board_H09)
  AC_ch5 = (14 & board_H09)
  AC_ch6 = (11 & board_H09)
  AC_ch7 = (12 & board_H09)


  LED_pin = (23 & board_H09)

  
'' Enumeration for states of the communication state machine.
'' It tells the machine where the cursor is.
  #0, COM_Idle, COM_OnCommand, COM_OnNumber, COM_OnText, COM_OnWhiteSpace, COM_OnEqualSign                      
  

'' Enumeration of internal variables
  #0, var_VERBOSE, var_CHANNEL_COUNT, var_LED, var_count
  ' With the auto numeration var_count ist set to the number of variables.
  
'' Memory area for doublebufferd graphics:
'' The Graphics object operates on the bitmap.
'' When it is finished the whole bitmap is copied onto the screen (into graphics base.)
'' The area graphics_base is mapped into the middle of the screen.
''  bitmap_base = $6000
''  graphics_base = $7000 
  
OBJ

  vga   : "VGA"                                         ' Graphics driver
  text  : "TextDriver16x32"                             ' Text output module
  dac   : "EightChannelDAC"                             ' Driver for the DACs
  com   : "Parallax Serial Terminal"                    ' Serial communication object


VAR
' Variables to hold the VGA config:  
  long  vga_status    '0/1/2 = off/visible/invisible      read-only   (21 longs)
  long  vga_enable    '0/non-0 = off/on                   write-only
  long  vga_pins      '%pppttt = pins                     write-only
  long  vga_mode      '%tihv = tile,interlace,hpol,vpol   write-only
  long  vga_screen    'pointer to screen (words)          write-only
  long  vga_colors    'pointer to colors (longs)          write-only            
  long  vga_ht        'horizontal tiles                   write-only
  long  vga_vt        'vertical tiles                     write-only
  long  vga_hx        'horizontal tile expansion          write-only
  long  vga_vx        'vertical tile expansion            write-only
  long  vga_ho        'horizontal offset                  write-only
  long  vga_vo        'vertical offset                    write-only
  long  vga_hd        'horizontal display ticks           write-only
  long  vga_hf        'horizontal front porch ticks       write-only
  long  vga_hs        'horizontal sync ticks              write-only
  long  vga_hb        'horizontal back porch ticks        write-only
  long  vga_vd        'vertical display lines             write-only
  long  vga_vf        'vertical front porch lines         write-only
  long  vga_vs        'vertical sync lines                write-only
  long  vga_vb        'vertical back porch lines          write-only
  long  vga_rate      'tick rate (Hz)                     write-only

' Variables for the comunication protocol
  byte  com_command
  byte  com_char[129]
  byte  com_charcount
  long  com_number[16]
  byte  com_numbercount
  byte  com_state

' Variables for the DAC
  long dac_status
  long dac_pinCS
  long dac_pinSCK
  long dac_pinD0
  long dac_pinD1
  long dac_pinD2
  long dac_pinD3
  long dac_pinLOAD
  long dac_value[8]

' State of the voltage comparators
  byte ac_state[8]
  
' Internal variables that can be read and written from the COM interface.
  long var_value[var_count]

  
PUB Main | i,j,textptr,oldstate,c

' Start the COM module
' --------------------
  com.start(115200)
  
' Start the graphics adapter
' --------------------------  
  longmove(@vga_status, @vga_params, vga#paramcount)    ' Copy the default parameters from below
  vga_pins := (0 & board_H09) | (16 & board_H10) | %000_111  ' Set the output pins.
  textptr := text.getScreenPtr                          ' Get a pointer to the memory area of the graphics adapter. 
  vga_screen := textptr                                 ' Connect the memory area provided by the text object to the graphics adapter.
  vga_colors := text.getColorsPtr                       ' Connect the color map as well.
  vga_rate := clkfreq >> 2                              ' Link the graphics adapter to the CPU clock speed.
  vga.start(@vga_status)                                ' Start it with the options defined.

' Init the text output
' ---------------------
  text.start                                            ' Init the text generator (does not need a extra core, just a bunch of functions in a file).

' Start the DAC driver
' --------------------

' Set the DACs to 0 volt.
  repeat i from 0 to 7
    dac_value[i] := 2048
  
  dac_status  := 1
  dac_pinCS   := (board_H09 & 17) | (board_H10 &  0)
  dac_pinSCK  := (board_H09 & 10) | (board_H10 &  0)
  dac_pinD0   := (board_H09 & 22) | (board_H10 &  0)
  dac_pinD1   := (board_H09 & 16) | (board_H10 &  0)
  dac_pinD2   := (board_H09 &  9) | (board_H10 &  0)
  dac_pinD3   := (board_H09 &  8) | (board_H10 &  0)
  dac_pinLOAD := (board_H09 & 15) | (board_H10 &  0)

  dac.start(@dac_status)

  DIRA[LED_pin] := 1
  
' Init the text displayed
  text.out(0) ' Clear screen
  text.out(1) ' Home the cursor
  
  text.str(string($C,1,"   Open-rTMS Signal Generator   "))
  text.str(string($C,4,"┌┤ DAC- and Comparator-Values ├┐"))
  text.str(string($C,4,"│C0= 0000 U0= 0 C4= 0000 U4= 0 │"))
  text.str(string($C,4,"│C1= 0000 U1= 0 C5= 0000 U5= 0 │"))
  text.str(string($C,4,"│C2= 0000 U2= 0 C6= 0000 U6= 0 │"))
  text.str(string($C,4,"│C3= 0000 U3= 0 C7= 0000 U7= 0 │"))
  text.str(string($C,4,"└──────────────────────────────┘"))
  text.str(string($C,7,"┌───────────┤ COM ├────────────┐"))
  text.str(string($C,7,"│ Command:                     │"))
  text.str(string($C,7,"│                              │"))
  text.str(string($C,7,"│                              │"))
  text.str(string($C,7,"│                              │"))
  text.str(string($C,7,"│ Variables:                   │"))
  text.str(string($C,7,"│ VERBOSE = 1                  │"))
  text.str(string($C,7,"└──────────────────────────────"))

  com_state := 0                 ' Variable for communication state machine.
  com_command := 0
  
'' Init the internal variables
'' ---------------------------
  var_value[var_VERBOSE] := 1
  var_value[var_LED] := 0
  var_value[var_CHANNEL_COUNT] := 8

repeat

  ' Read the states of the voltage comparators
  ac_state[0] := INA[AC_ch0]
  ac_state[1] := INA[AC_ch1]
  ac_state[2] := INA[AC_ch2]
  ac_state[3] := INA[AC_ch3]
  ac_state[4] := INA[AC_ch4]
  ac_state[5] := INA[AC_ch5]
  ac_state[6] := INA[AC_ch6]
  ac_state[7] := INA[AC_ch7]

  ' Check, if signals were send over the serial connection.
  repeat com.rxcount
    c := com.CharIn
          
    'Communication state machine
    oldstate := com_state
    case com_state
      COM_Idle:
        if var_value[var_VERBOSE]
          text.str(string($A,11,$B,8))
          text.out(c)

        ' Check for a command, that is known
        if lookdown(c: "V","C","U","G","S","Z","F","R","D") > 0
          com_state := COM_OnCommand
          com_command := c
          com_charcount := 0
          com_numbercount := -1
        else
          com.str(string($D,"?",$D))
          text.str(string($A,2,$B,9,"Command not found!           "))
      COM_OnCommand:
        if (c=>"a" and c=<"z") or (c=>"A" and c=<"Z") or c == "_"
          
        elseif c == "="
          com_state := COM_OnEqualSign
        elseif c=>"0" and c=<"9"
          com_state := COM_OnNumber
        else
          com_state := COM_OnWhiteSpace
          
      COM_OnNumber, COM_OnText, COM_OnWhiteSpace, COM_OnEqualSign:
        if (c=>"a" and c=<"z") or (c=>"A" and c=<"Z") or c == "_"
          com_state := COM_OnText          
        elseif c == "="
          com_state := COM_OnEqualSign
        elseif c=>"0" and c=<"9"
          com_state := COM_OnNumber
        else
          com_state := COM_OnWhiteSpace

    if c == 13
      com_state := COM_Idle 

      
    ' Collect data
    case com_state
      COM_OnNumber:
        if com_state <> oldstate and com_numbercount <> 15
          com_numbercount ++
          com_number[com_numbercount] := 0
        com_number[com_numbercount] *= 10
        com_number[com_numbercount] += c-"0"
      COM_OnText:
        if com_charcount < 127
          com_char[com_charcount] := c
          com_char[com_charcount+1] := 0
          com_charcount ++

    ' Processing the commands
    case com_command
      "C":
        if com_state <> COM_OnNumber and com_numbercount == 1
          if com_number[0] < 8
            dac_value[com_number[0]] := com_number[1] <# 4095
          com_numbercount := -1
        if c == 13
          dac_status := 1
          if var_value[var_VERBOSE]
            text.str(string($A,2,$B,9,"Values sent to the DACs!     "))
      
      "V":
        if com_state == COM_Idle
          com.str(string("firmware_openrtms_h09_20130202",$d))
          if var_value[var_VERBOSE]
            text.str(string($A,2,$B,9,"Firmware version sent!       "))
               
      "U":
        if com_state == COM_Idle
          repeat i from 0 to 7
            com.Char("0"+ac_state[i])          
          com.Char($d)
          if var_value[var_VERBOSE]
            text.str(string($A,2,$B,9,"Comparator state sent!       "))
        
      "G":
        if com_state == COM_Idle
          i := var_count
          if strcomp(@com_char,string("VERBOSE"))
            i := var_VERBOSE
          if strcomp(@com_char,string("CHANNEL_COUNT"))
            i := var_CHANNEL_COUNT
          if strcomp(@com_char,string("LED"))
            i := var_LED
          if i == var_count
            com.Char("?")
            if var_value[var_VERBOSE]
              text.str(string($A,2,$B,13,"Unknown variable!            "))
          else
            com.Dec(var_value[i])            
            if var_value[var_VERBOSE]
              text.str(string($A,2,$B,13,"                             "))
              text.str(string($A,2,$B,13))
              text.str(@com_char)
              text.str(string(" = "))
              text.dec(var_value[i])
              text.str(string($A,2,$B,9,"Value sent!                  "))

                       
          com.Char($d)
   
      "S":
        if com_state == COM_Idle
          i := var_count
          if strcomp(@com_char,string("VERBOSE"))
            i := var_VERBOSE
          if strcomp(@com_char,string("LED"))
            i := var_LED
          if i == var_count
            com.Char("?")
            if var_value[var_VERBOSE]
              text.str(string($A,2,$B,13,"Unknown variable!            "))
          else
            if com_numbercount => 0      ' numbercount = 0 means 1 number on pos 0
              var_value[i] := com_number[0]

              if var_value[var_VERBOSE] or i == var_VERBOSE
                text.str(string($A,2,$B,13,"                             "))
                text.str(string($A,2,$B,13))
                text.str(@com_char)
                text.str(string(" = "))
                text.dec(var_value[i])
                text.str(string($A,2,$B,9,"Value changed!               "))
              if i == var_verbose and com_number[0] == 0
                text.str(string($A,2,$B,9,"Verbosing disabled!          "))
                       
          com.Char($d)
          
      "Z":
        if com_state == COM_Idle
          var_value[var_LED] := 0
          repeat i from 0 to 7
            dac_value[i] := 2048
          dac_status := 1
          if var_value[var_VERBOSE]
            text.str(string($A,2,$B,9,"All outputs set to zero!     "))

      "F":
        if com_state == COM_Idle
          if var_value[var_VERBOSE]
            text.str(string($A,2,$B,9,"No functions implemented!    "))

      "R":
        if com_state == COM_Idle
          com.str(string("1",$d))
          if var_value[var_VERBOSE]
            text.str(string($A,2,$B,9,"System is ready!             "))

      "D":
        if com_state == COM_Idle
          com.str(string($d))
          if var_value[var_VERBOSE]
            text.str(string($A,2,$B,9,"No debugging output...       "))

    if c == 13
      com_command := 0
    
  OUTA[LED_pin] := var_value[var_LED]
    
  text.str(string($c,4))  
  repeat i from 0 to 3
    text.str(string($a,5,$b))
    text.out(i+2)
    deczero(dac_value[i],4)
    text.str(string($a,20,$b))
    text.out(i+2)
    deczero(dac_value[i+4],4)
    text.str(string($a,14,$b))
    text.out(i+2)
    text.out("0"+ac_state[i])
    text.str(string($a,29,$b))
    text.out(i+2)
    text.out("0"+ac_state[i+4])

  text.str(string($c,7))

PUB deczero(value,digits) | i,c


  c:=1
  i := value
  repeat while i => 10
    c++
    i/=10
  repeat digits-c
    text.out("0") 
  text.dec(value)
   
DAT

vga_params              long    0               'status
                        long    1               'enable
                        long    0               'pins
                        long    %1000           'mode
                        long    0               'videobase
                        long    0               'colorbase
                        long    text#cols       'ht
                        long    text#rows       'vt
                        long    1               'hx
                        long    1               'vx
                        long    0               'ho
                        long    0               'vo
                        long    512             'hd
                        long    10              'hf
                        long    75              'hs
                        long    43              'hb
                        long    480             'vd
                        long    11              'vf
                        long    2               'vs
                        long    31              'vb
                        long    0               'rate