Commandline options:

SDLLife -r N -c N -z N -i <filename> -o <filename> -s

r   number of rows - height (ignored if -i is specified)
c   number of columns - width (ignored if -i is specified)
z   cell size (in pixels)

i   the filename of a properly formatted file

o   the filename to output the grid to when saved (out_grid.txt)

s   step: if specified, will do a half step instead 
    of a full step ( shows intermediate steps )


File format:
N1,N2,C1,C2<newline>
[Cell data: N1 cells long]<newline>
[Cell data: N1 cells long]<newline>
.
.
.
[N2 rows of cells]<newline>
<EOF>

N1: Number of columns in the grid (width)
N2: Number of rows in the grid (height)
C1: Character for a cell that is alive
C2: Character for dead cells (all other cell will be ignored)

<newline> *must* be \n (0A hex), single character
<EOF> may be on the next line


Keys:

Space:       Unpause for a single frame
Right arrow: Unpause while held
Return:      Unpause until pressed again

Up,plus,period:   FPS up
Down,minus,comma: FPS down

e: Toggle edit mode
h: Toggle step mode full/half
c: Switch colour scheme
s: Save to file
r: Reset grid
x: Invert grid

Patterns:
0: Clear grid
1: Pattern 1 ( checkerboard )
2: Pattern 2 ( horizontal lines )
3: Pattern 3 ( diagonal lines )
7: Pattern 7 ( invert grid )
8: Pattern 8 ( randomized #1 )
9: Pattern 9 ( randomized #2 )
