# Word Search Puzzle Solver

## Overview

This is a C program that reads a square word search puzzle from a file and allows the user to search for a word within the puzzle. If the word is found, the program displays the path of the word in the grid.

This project was developed in collaboration with Aravind Balasubramaniam.

## Features

* Reads a word search puzzle grid from a file.
* Accepts a word input from the user.
* Converts the word to uppercase to ensure case-insensitive matching.
* Searches for the word in all 8 directions (horizontal, vertical, and diagonals).
* Supports reverse direction searching.
* Prints the puzzle and a visual representation of the search path if the word is found.

## How to Compile

Use `gcc` to compile the program:

```bash
g++ -std=c++11 -o wordsearch wordsearch.c
```

## How to Run

Run the program by providing a puzzle file as an argument:

```bash
./wordsearch puzzle.txt
```

The program will then prompt you to enter the word you wish to search.

### Input File Format

* The first line should contain an integer `N` — the size of the NxN puzzle.
* The following `N` lines should contain `N` characters each (separated by spaces), representing the puzzle grid.

**Example (`puzzle.txt`):**

```
4
A B C D
E F G H
I J K L
M N O P
```

### Sample Interaction

```
$ ./wordsearch puzzle.txt
Enter the word to search: FJK

Printing puzzle before search:
A B C D
E F G H
I J K L
M N O P

Word found!
Printing the search path:
0 0 0 0
0 1 2 3
0 0 0 0
0 0 0 0
```

## Code Structure

* `printPuzzle`: Prints the grid.
* `searchPuzzle`: Main logic to handle word searching and path printing.
* `capitalize`: Converts the word to uppercase.
* `initializePath`: Initializes the path grid to zero.
* `findFirstLetter`: Finds the starting location of the word's first character.
* `checkAdjacent`, `checkAdjacentReverse`: Searches for the rest of the word in forward and reverse directions.
* `outlinePath`, `restartPath`, `printPath`: Handle path tracking and output.

## Limitations

* Only one occurrence of the word is tracked at a time.
* Words longer than 20 characters are not supported without modifying the code.

## License

This project is for educational purposes.

---
