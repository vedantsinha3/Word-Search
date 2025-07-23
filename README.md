# Word-Search
Word Search Puzzle Solver
Overview
This is a C program that reads a square word search puzzle from a file and allows the user to search for a word within the puzzle. If the word is found, the program displays the path of the word in the grid.

This project was developed in collaboration with Aravind Balasubramaniam.

Features
Reads a word search puzzle grid from a file.

Accepts a word input from the user.

Converts the word to uppercase to ensure case-insensitive matching.

Searches for the word in all 8 directions (horizontal, vertical, and diagonals).

Supports reverse direction searching.

Prints the puzzle and a visual representation of the search path if the word is found.

How to Compile
Use gcc to compile the program:

bash
Copy
Edit
g++ -std=c++11 -o wordsearch wordsearch.c
How to Run
Run the program by providing a puzzle file as an argument:

bash
Copy
Edit
./wordsearch puzzle.txt
The program will then prompt you to enter the word you wish to search.
