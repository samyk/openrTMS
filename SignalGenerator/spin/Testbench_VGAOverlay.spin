''┌────────────────────────────┐
''│ Testbench for VGA Overlay  │
''│ Author: Tobias Schaefer    │
''│ Copyright (c) 2010         │
''└────────────────────────────┘

CON

'' Board used:
  board_V09 = true              '' Open rTMS Board Version 0.9
  board_V10 = false             '' Open rTMS Board Version 1.0 or Parallax Demo board


  _clkmode = xtal1 + pll16x
  _xinfreq = 5_000_000

  '' for doublebuffering 1.) graphics -> bitmap 2.) bitmap -> screen
  bitmap_base = $6000
  graphics_base = $7000 
  
OBJ

 vga    : "VGA"
 text   : "TextDriver16x32"
 gr     : "Graphics"

VAR
  
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

  
PUB Start | i,j,textptr,dx,dy


  longmove(@vga_status, @vga_params, vga#paramcount)
  vga_pins := (16 & board_V10) | %000_111
  vga_screen := text.getScreenPtr
  vga_colors := text.getColorsPtr
  vga_rate := clkfreq >> 2
  textptr := text.getScreenPtr

  vga.start(@vga_status)
  text.start


  'start and setup graphics
  gr.start
  gr.setup(9, 6, 72, 48, bitmap_base)
  

  text.out(0)
  text.out(1)
  text.str(string($C,1,"   Testbench Graphics Overlay   "))
  text.str(string($C,7,"                │               "))
  text.str(string($C,7,"  This tests    │ Fancy font:   "))
  text.str(string($C,7,"  the overlay   │     ┌┐      "))
  text.str(string($C,7,"  of text and   │     │ 1µF  "))
  text.str(string($C,7,"  graphics.     │     └┘      "))
  text.str(string($C,7,"  Inside the    │    10kΩ       "))
  text.str(string($C,7,"  box is a 144x │          2πf  "))
  text.str(string($C,7,"  96 pixel ┌────┴────┐          "))
  text.str(string($C,7,"  graphics │         │          "))
  text.str(string($C,7,"───────────┤         ├──────────"))
  text.str(string($C,7,"  area.    │         │          "))
  text.str(string($C,7,"  0,0 is in└────┬────┘          "))
  text.str(string($C,7,"  the center of │               "))
  text.str(string($C,7,"  the box.      │              " ))


  'Graphic overlay
  repeat dx from 0 to 8
    repeat dy from 0 to 2
      word[textptr][(dy+9) * text#cols + dx+12] := graphics_base >> 6 + dy*2 + dx*6  + (0<<10)


  i := 0
  j := 0
  repeat
    i := (i + 10) & $1fff
    j := (j - 7 ) & $1fff

    gr.clear
    gr.colorwidth(3,1)
    gr.plot(0,0)

    gr.vec(0, 0, $100, i, @vecdef)
    gr.vec(0, 0, $07f, j, @vecdef)                                      
                              
    gr.copy(graphics_base)    
  
   
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


vecdef                  word    $4000+$2000/3*0 'triangle
                        word    50
                        word    $8000+$2000/3*1+1
                        word    50
                        word    $8000+$2000/3*2-1
                        word    50
                        word    $8000+$2000/3*0
                        word    50
                        word    0
                        