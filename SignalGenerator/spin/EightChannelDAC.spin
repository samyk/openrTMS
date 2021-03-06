''┌─────────────────────────────────────────────────────────┐
''│ Eight Channel DAC for four MCP4922 DACs                 │
''│ Author: Tobias Schaefer                                 │
''│ Copyright (c) 2010                                      │
''│ Licence: GNU General Public License version 3.0 (GPLv3) │
''└─────────────────────────────────────────────────────────┘

' Use of this file:

' OBJ
'   dac : "EightChannelDAC"


' The vaiables in the main program have to be in the following order:

'  long dac_status
'  long dac_pinCS
'  long dac_pinSCK
'  long dac_pinD0
'  long dac_pinD1
'  long dac_pinD2
'  long dac_pinD3
'  long dac_pinLOAD
'  long dac_value[8]

' setup all the dac_pins
' then start the object with:

' dac.start(@dac_status)

' whenever dac_status != 0 the object copies the
' 8 dac values and then sets dac_status back to 0.
' Afterwards the values are transmitted.
' If dac_status == 0 the values of dac_value may
' be changed. 


VAR
  long  cog

PUB Start(statusPtr) : okay

    pinSetCS :=  |< long[statusPtr+4]
    pinSetSCK :=  |< long[statusPtr+8]
    pinD0 := |< long[statusPtr+12]
    pinD1 := |< long[statusPtr+16]
    pinD2 := |< long[statusPtr+20]
    pinD3 := |< long[statusPtr+24]
    pinSetLOAD := |< long[statusPtr+28]

    pinClearCS := !pinSetCS
    pinClearSCK := !pinSetSCK
    pinClearLOAD := !pinSetLOAD
    
    Stop
    okay := cog := cognew(@entry, statusPtr) + 1
    
PUB Stop
  if cog
    cogstop(cog~ - 1)

DAT           org




entry         
'             

              ' Setup direction pins towards the DAC converters
              mov temp, pinSetCS
              or temp, pinSetSCK
              or temp, pinD0
              or temp, pinD1
              or temp, pinD2
              or temp, pinD3
              or temp, pinSetLOAD
              mov dira, temp

              ' Set CS and LOAD high (they are inverted)
              mov temp, pinSetCS
              or temp, pinSetLOAD
              mov outa, temp


loop
              ' prepare the buffers
              mov buffer0, transmitCommand
              mov buffer1, transmitCommand
              mov buffer2, transmitCommand
              mov buffer3, transmitCommand

              ' prepare the address to point towars the dac_values
              mov address, par 
              add address, #32 ' address of dac_value[0]
              
              ' Wait for the status to be != 0
waitstatus
              rdlong  temp, par   wz
              if_z  jmp     #waitstatus

              ' Get the dac_values and put them into the buffers
              ' Note that between two hub commands (rdlong) 2 extra
              ' instructions can be executed without speed loss.

              rdlong buffervalue0, address ' get dac_value[0]
              and buffervalue0, maskFor12Bit ' make the value to 12 bit
              
              add address, #4 ' address of dac_value[1]
              rdlong buffervalue1, address ' get dac_value[1]
              and buffervalue1, maskFor12Bit ' make the value to 12 bit

              add address, #4 ' address of dac_value[2]
              rdlong buffervalue2, address ' get dac_value[2]
              and buffervalue2, maskFor12Bit ' make the value to 12 bit

              add address, #4 ' address of dac_value[3]
              rdlong buffervalue3, address ' get dac_value[3]
              and buffervalue3, maskFor12Bit ' make the value to 12 bit

              add address, #4 ' address of dac_value[4]
              rdlong buffervalue4, address ' get dac_value[4]
              and buffervalue4, maskFor12Bit ' make the value to 12 bit

              add address, #4 ' address of dac_value[5]
              rdlong buffervalue5, address ' get dac_value[5]
              and buffervalue5, maskFor12Bit ' make the value to 12 bit

              add address, #4 ' address of dac_value[6]
              rdlong buffervalue6, address ' get dac_value[6]
              and buffervalue6, maskFor12Bit ' make the value to 12 bit

              add address, #4 ' address of dac_value[7]
              rdlong buffervalue7, address ' get dac_value[7]
              and buffervalue7, maskFor12Bit ' make the value to 12 bit


              ' Set the status to 0, so other objects can change the values
              wrlong zero, par

              shl buffervalue0, #16       ' shift up value0 to fit into buffer0 DataA
              shl buffervalue2, #16       ' shift up value2 to fit into buffer1 DataA
              shl buffervalue4, #16       ' shift up value4 to fit into buffer2 DataA
              shl buffervalue6, #16       ' shift up value6 to fit into buffer3 DataA
                            
              or buffer0, buffervalue0    ' put value0 it into the buffer0 DataA
              or buffer0, buffervalue1    ' put value1 it into the buffer0 DataB
              or buffer1, buffervalue2    ' put value2 it into the buffer1 DataA
              or buffer1, buffervalue3    ' put value3 it into the buffer1 DataB
              or buffer2, buffervalue4    ' put value4 it into the buffer2 DataA
              or buffer2, buffervalue5    ' put value5 it into the buffer2 DataB
              or buffer3, buffervalue6    ' put value6 it into the buffer3 DataA
              or buffer3, buffervalue7    ' put value7 it into the buffer3 DataB
                             
              ' Write out the upper 16 bit, MSB first:

              'Set CS low = only LOAD is high
              mov outa, pinSetLOAD
                 
              mov temp2,#16 ' Loop 16 times
loopTransmitA
              ' Setup the output pins
              mov outa, pinSetLOAD ' only LOAD is high
              
              shl buffer0,#1  wc ' Shift buffer0 one bit to the left the MSB is written into the carrybit (wc).
        if_C  or outa, pinD0  ' If the carrybit is one, set D0 to 1. 
              
              shl buffer1,#1  wc ' Shift buffer1 one bit to the left the MSB is written into the carrybit (wc).
        if_C  or outa, pinD1  ' If the carrybit is one, set D1 to 1. 

              shl buffer2,#1  wc ' Shift buffer2 one bit to the left the MSB is written into the carrybit (wc).
        if_C  or outa, pinD2  ' If the carrybit is one, set D2 to 1.

              shl buffer3,#1  wc ' Shift buffer3 one bit to the left the MSB is written into the carrybit (wc).
        if_C  or outa, pinD3  ' If the carrybit is one, set D3 to 1. 

              or outa, pinSetSCK     ' clock high
              and outa, pinClearSCK  ' clock low
        
              sub temp2, #1  wz  ' Subtract 1 from temp2 and set the zerobit if temp2 is zero.
        if_nz jmp #loopTransmitA ' If temp2 not zero loop again.

              or outa, pinSetCS     ' CS high

              and outa, pinClearCS  ' CS low

              ' Write out the lower 16 bit, MSB first:
              
              mov temp2,#16 ' Loop 16 times              
loopTransmitB
              ' Setup the output pins
              mov outa, pinSetLOAD ' only LOAD is high
              
              shl buffer0,#1  wc ' Shift buffer0 one bit to the left the MSB is written into the carrybit (wc).
        if_C  or outa, pinD0  ' If the carrybit is one, set D0 to 1. 
              
              shl buffer1,#1  wc ' Shift buffer1 one bit to the left the MSB is written into the carrybit (wc).
        if_C  or outa, pinD1  ' If the carrybit is one, set D1 to 1. 

              shl buffer2,#1  wc ' Shift buffer2 one bit to the left the MSB is written into the carrybit (wc).
        if_C  or outa, pinD2  ' If the carrybit is one, set D2 to 1. 

              shl buffer3,#1  wc ' Shift buffer3 one bit to the left the MSB is written into the carrybit (wc).
        if_C  or outa, pinD3  ' If the carrybit is one, set D3 to 1. 

              or outa, pinSetSCK     ' clock high
              and outa, pinClearSCK  ' clock low
        
              sub temp2, #1  wz  ' Subtract 1 from temp2 and set the zerobit if temp2 is zero.
        if_nz jmp #loopTransmitB ' If temp2 not zero loop again.

              or outa, pinSetCS     ' CS high

              and outa, pinClearLOAD  ' LOAD low
              nop                     ' Wait for 50 ns, because LOAD has to be low for 100 ns.
              or outa, pinSetLOAD     ' LOAD high

              ' Thats it, back to waiting for status != 0.
              jmp     #loop


' ########################### Assembly variables ###########################


zero           long    0                 

' toA unbufferedMode 1xGain OutputEnable 12BitDataA toB unbufferedMode 1xGain OutputEnable 12BitDataB  
transmitCommand  long %0011_000000000000_1011_000000000000

' temporary variables
temp           long    0 
temp2          long    0


maskFor12Bit   long    %1111_1111_1111
address        long    0

'Pin definitions
pinSetCS       long 0
pinSetSCK      long 0
pinD0          long 0
pinD1          long 0
pinD2          long 0
pinD3          long 0
pinSetLOAD     long 0

pinClearCS     long 0
pinClearSCK    long 0
pinClearLOAD   long 0

buffer0        res 1
buffer1        res 1
buffer2        res 1
buffer3        res 1

buffervalue0   res 1
buffervalue1   res 1
buffervalue2   res 1
buffervalue3   res 1
buffervalue4   res 1
buffervalue5   res 1
buffervalue6   res 1
buffervalue7   res 1
