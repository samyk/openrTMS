''***************************************
''*  VGA Text 16x16 v1.0                *
''*  Author: Chip Gracey                *
''*  Modified by: Tobias Schaefer       *
''*  Copyright (c) 2006 Parallax, Inc.  *
''*  See end of file for terms of use.  *
''***************************************

' Modified to separate the vga object from this file to make it available for graphic overlay.

CON

  cols = 32
  rows = 15

  screensize = cols * rows * 2
  lastrow = cols * rows - cols

  
VAR

  long  col, row, color, flag
  
  word  screen[screensize]
  long  colors[8 * 2]
 

PUB start

'' Start terminal - starts a cog
'' returns false if no cog available
''
'' requires at least 80MHz system clock

  setcolors(@palette)
  out(0)

PUB GetScreenPtr : ptr
  ptr := @screen

PUB GetColorsPtr : ptr
  ptr := @colors

PUB str(stringptr)

'' Print a zero-terminated string

  repeat strsize(stringptr)
    out(byte[stringptr++])


PUB dec(value) | i

'' Print a decimal number

  if value < 0
    -value
    out("-")

  i := 1_000_000_000

  repeat 10
    if value => i
      out(value / i + "0")
      value //= i
      result~~
    elseif result or i == 1
      out("0")
    i /= 10


PUB hex(value, digits)

'' Print a hexadecimal number

  value <<= (8 - digits) << 2
  repeat digits
    out(lookupz((value <-= 4) & $F : "0".."9", "A".."F"))


PUB bin(value, digits)

'' Print a binary number

  value <<= 32 - digits
  repeat digits
    out((value <-= 1) & 1 + "0")


PUB out(c) | i, k

'' Output a character
''
''     $00 = clear screen
''     $01 = home
''     $08 = backspace
''     $09 = tab (8 spaces per)
''     $0A = set X position (X follows)
''     $0B = set Y position (Y follows)
''     $0C = set color (color follows)
''     $0D = return
''  others = printable characters

  case flag
    $00: case c
           $00: wordfill(@screen, $0220, screensize)
                col := row := 0
           $01: col := row := 0
           $08: if col
                  col--
           $09: repeat
                  print(" ")
                while col & 7
           $0A..$0C: flag := c
                     return
           $0D: newline
           other: print(c)
    $0A: col := c // cols
    $0B: row := c // rows
    $0C: color := c & 7
  flag := 0


PUB setcolors(colorptr) | i, fore, back

'' Override default color palette
'' colorptr must point to a list of up to 8 colors
'' arranged as follows (where r, g, b are 0..3):
''
''               fore   back
''               ------------
'' palette  byte %%rgb, %%rgb     'color 0
''          byte %%rgb, %%rgb     'color 1
''          byte %%rgb, %%rgb     'color 2
''          ...

  repeat i from 0 to 7
    fore := byte[colorptr][i << 1] << 2
    back := byte[colorptr][i << 1 + 1] << 2
    colors[i << 1]     := fore << 24 + back << 16 + fore << 8 + back
    colors[i << 1 + 1] := fore << 24 + fore << 16 + back << 8 + back


PRI print(c)

  screen[row * cols * 2 + col +    0] := (color << 1 + c & 1) << 10 + $200 + c & $FE
  screen[row * cols * 2 + col + cols] := (color << 1 + c & 1) << 10 + $201 + c & $FE
  if ++col == cols
    newline


PRI newline | i

  col := 0
  if ++row == rows
    row--
    wordmove(@screen, @screen[cols*2], lastrow*2)   'scroll lines
    wordfill(@screen[lastrow*2], $220, cols*2)      'clear new line


DAT

                        '        fore   back
                        '         RGB    RGB
palette                 byte    %%333, %%001    '0    white / dark blue
                        byte    %%330, %%110    '1   yellow / brown
                        byte    %%202, %%000    '2  magenta / black
                        byte    %%111, %%333    '3     grey / white
                        byte    %%033, %%011    '4     cyan / dark cyan
                        byte    %%020, %%232    '5    green / gray-green
                        byte    %%100, %%311    '6      red / pink
                        byte    %%033, %%003    '7     cyan / blue

{{
┌──────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────┐
│                                                   TERMS OF USE: MIT License                                                  │                                                            
├──────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────┤
│Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation    │ 
│files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy,    │
│modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software│
│is furnished to do so, subject to the following conditions:                                                                   │
│                                                                                                                              │
│The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.│
│                                                                                                                              │
│THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE          │
│WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR         │
│COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,   │
│ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.                         │
└──────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────┘
}}                        