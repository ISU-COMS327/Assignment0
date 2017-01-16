# Assignment0

## The Game of Life

### Description
Run the `make` command in this directory to generate the executable file. The executable will be named `main`.
Running `make clean` will remove all executables.

You can run this program by entering the command `./main` in your shell. This program takes
numbers as command line args. There *must* be an even number of numbers passed in. This is
because each tuple of numbers represents coordinates that the game will initialize as a 
live cell for this game. The game setting is a torus with dimensions 80x24.

### Examples

Here are some example inputs:

The following command will prodcue a *glider* and *lightweight space ship*
which travel around the torus multiple times before colliding.
`./main 2 1 2 3 3 4 4 4 5 1 5 4 6 2 6 3 6 4 15 0 16 1 14 2 15 2 16 2`

The following command will produce a *glider gun* which eventually destroys itself.
`./main 1 5 2 5 1 6 2 6 11 5 11 6 11 7 12 4 12 8 13 3 13 9 14 3 14 9 15 6 16 4 16 8 17 5 17 6 17 7 18 6 21 3 21 4 21 5 22 3 22 4 22 5 23 2 23 6 25 1 25 2 25 6 25 7 35 3 35 4 36 3 36 4`

