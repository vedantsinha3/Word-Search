// worked with Aravind Balasubramaniam

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Declarations of the two functions you will implement
// Feel free to declare any helper functions or global variables
void printPuzzle(char** arr);
void searchPuzzle(char** arr, char* word);
void capitalize(char* word);
void initializePath();
void findFirstLetter(char** arr, char* word, int currentX, int currentY);
void outlinePath(int currentX, int currentY);
void restartPath();
void printPath();
void checkAdjacent(char** arr, char* word, int currentX, int currentY);
void checkAdjacentReverse(char** arr, char* word, int currentX, int currentY);
int bSize;
int** searchPath;
int currentX = -1;
int currentY = -1;
int initialX = 0;
int initialY = 0;
int isFound = 0;
int moveCounter = 0;

// Main function, DO NOT MODIFY 	
int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <puzzle file name>\n", argv[0]);
        return 2;
    }
    int i, j;
    FILE *fptr;

    // Open file for reading puzzle
    fptr = fopen(argv[1], "r");
    if (fptr == NULL) {
        printf("Cannot Open Puzzle File!\n");
        return 0;
    }

    // Read the size of the puzzle block
    fscanf(fptr, "%d\n", &bSize);
    
    // Allocate space for the puzzle block and the word to be searched
    char **block = (char**)malloc(bSize * sizeof(char*));
    char *word = (char*)malloc(20 * sizeof(char));

    // Read puzzle block into 2D arrays
    for(i = 0; i < bSize; i++) {
        *(block + i) = (char*)malloc(bSize * sizeof(char));
        for (j = 0; j < bSize - 1; ++j) {
            fscanf(fptr, "%c ", *(block + i) + j);            
        }
        fscanf(fptr, "%c \n", *(block + i) + j);
    }
    fclose(fptr);

    printf("Enter the word to search: ");
    scanf("%s", word);
    
    // Print out original puzzle grid
    printf("\nPrinting puzzle before search:\n");
    printPuzzle(block);
    
    // Call searchPuzzle to the word in the puzzle
    searchPuzzle(block, word);
    
    return 0;
}

void printPuzzle(char** arr) {
	// This function will print out the complete puzzle grid (arr). 
    // It must produce the output in the SAME format as the samples 
    // in the instructions.
    // Your implementation here...
    for (int i = 0; i < bSize; i++){ 
		for (int j = 0; j < bSize; j++){
			printf("%c ", *(*(arr + i) + j));
		}
		printf("\n");
	}
    printf("\n");

}

void capitalize(char* word){// change the word to upper case
    char* ptr = word; // Pointer to iterate over the characters in the word
    while (*ptr != '\0') { // Loop until the end of the string
        if (*ptr >= 'a' && *ptr <= 'z') { // Check if the character is lowercase
            *ptr = *ptr - 32; // Convert to uppercase by subtracting 32 (ASCII difference)
        }
        ptr++; // Move to the next character
    }
   }


void searchPuzzle(char** arr, char* word) {
    // This function checks if arr contains the search word. If the 
    // word appears in arr, it will print out a message and the path 
    // as shown in the sample runs. If not isFound, it will print a 
    // different message as shown in the sample runs.
    // Your implementation here...
    capitalize(word); // turns word into uppercase
    initializePath(); // sets search path to zeros
    findFirstLetter(arr, word, currentX, currentY); // finds the first letter in the puzzle
    if (isFound == 0){
        printf("Word is not found!\n");
    } else {
        printf("Word found!\n");
        printPath();
    }
}

void findFirstLetter(char** arr, char* word, int currentX, int currentY) {
    if (currentX == -1 && currentY == -1) { 
        char** rowPtr = arr; //current row pointer
        while (*rowPtr != NULL) {
            char* colPtr = *rowPtr; //points to current collumn
            while (*colPtr != '\0') {
                if (*colPtr == *word) {
                    initialX = colPtr - *rowPtr;
                    initialY = rowPtr - arr;
                    currentX = initialX;
                    currentY = initialY;
                    isFound++;
                    break;
                }
                colPtr++;
            }
            if (isFound != 0)
                break;
            rowPtr++;
        }
    } else {
        char** rowPtr = arr + currentY;
        char* colPtr = *rowPtr + currentX + 1;
        while (*rowPtr != NULL) {
            while (*colPtr != '\0') { // end of string
                if (*colPtr == *word) {
                    initialX = colPtr - *rowPtr; //column index
                    initialY = rowPtr - arr; //row index 
                    currentX = initialX;
                    currentY = initialY;
                    isFound++;
                    break;
                }
                colPtr++;
            }
            if (isFound != 0)
                break;
            rowPtr++; // Next row
            colPtr = *rowPtr; //Reset col to next row 
        }
    }

    if (isFound != 0 && *word == *(*(arr + initialY) + initialX)) {
        outlinePath(currentX, currentY);
        checkAdjacent(arr, word, currentX, currentY);
    } else {
        isFound = 0;
    }
}

void initializePath(){ // setting up the search path as 0's
    // Allocate memory for the search path rows
    searchPath = (int**)malloc(sizeof(int*) * bSize);
    
    // Iterate over each row of the search path
    for (int i = 0; i < bSize; i++) {
        // Allocate memory for the entire row of the search path
        *(searchPath + i) = (int*)malloc(sizeof(int) * bSize);
        
        // Set the entire row to zero using memset
        memset(*(searchPath + i), 0, sizeof(int) * bSize);
    }
}

void restartPath() {
    int** pathPtr = searchPath;
    while (pathPtr - searchPath < bSize) { // Iterate over rows of the search path
        int* rowPtr = *pathPtr;
        while (rowPtr - *pathPtr < bSize) {
            *rowPtr = 0; 
            rowPtr++;
        }
        pathPtr++;
    }
    isFound = 0;
    moveCounter = 0;
    currentX = initialX;
    currentY = initialY;
}

void outlinePath(int currentX, int currentY) {
    int sum = *((*(searchPath + currentY)) + currentX);
    int temp = 1;
    moveCounter++;
    while (temp < sum) {
        temp *= 10;
    }
    if (temp > sum) {
        sum = temp * moveCounter + sum;
    }
    *((*(searchPath + currentY)) + currentX) = sum;
}


void printPath() {
    printf("Printing the search path:\n");
    int** pathPtr = searchPath;
    while (pathPtr - searchPath < bSize) {
        int* rowPtr = *pathPtr;
        while (rowPtr - *pathPtr < bSize) {
            int num = *rowPtr;
            if (num < 10)
                printf("%d       ", num);
            else if (num < 100)
                printf("%d      ", num);
            else if (num < 1000)
                printf("%d     ", num);
            else if (num < 10000)
                printf("%d    ", num);
            else if (num < 100000)
                printf("%d   ", num);
            else if (num < 1000000)
                printf("%d  ", num);
            else if (num < 10000000)
                printf("%d ", num);
            else
                printf("%d", num);
            rowPtr++;
        }
        printf("\n");
        pathPtr++;
    }
    printf("\n");
}

void checkDirection(char** arr, char* word, int* currentX, int* currentY, int x_offset, int y_offset) {
    if (*currentX + x_offset >= 0 && *currentY + y_offset >= 0 && *currentX + x_offset < bSize && *currentY + y_offset < bSize && *(word + moveCounter) != '\0') {
        if (*(word + moveCounter) == *(*(arr + (*currentY + y_offset)) + (*currentX + x_offset))) {
            *currentX += x_offset;
            *currentY += y_offset;
            outlinePath(*currentX, *currentY);
            checkAdjacent(arr, word, *currentX, *currentY);
        }
    }
}

void checkAdjacent(char** arr, char* word, int currentX, int currentY) {
    checkDirection(arr, word, &currentX, &currentY, -1, -1);
    checkDirection(arr, word, &currentX, &currentY, 0, -1);
    checkDirection(arr, word, &currentX, &currentY, 1, -1);
    checkDirection(arr, word, &currentX, &currentY, 1, 0);
    checkDirection(arr, word, &currentX, &currentY, 1, 1);
    checkDirection(arr, word, &currentX, &currentY, 0, 1);
    checkDirection(arr, word, &currentX, &currentY, -1, 1);
    checkDirection(arr, word, &currentX, &currentY, -1, 0);
    
    if (*(word + moveCounter) != '\0') {
        restartPath();
        currentX = initialX;
        currentY = initialY;
        outlinePath(currentX, currentY);
        checkAdjacentReverse(arr, word, currentX, currentY);
    } else {
        isFound = 1;
    }
}
void checkDirectionReverse(char** arr, char* word, int* currentX, int* currentY, int x_offset, int y_offset) {
    if (*currentX + x_offset >= 0 && *currentY + y_offset >= 0 && *currentX + x_offset < bSize && *currentY + y_offset < bSize && *(word + moveCounter) != '\0') {
        if (*(word + moveCounter) == *(*(arr + (*currentY + y_offset)) + (*currentX + x_offset))) {
            *currentX += x_offset;
            *currentY += y_offset;
            outlinePath(*currentX, *currentY);
            checkAdjacentReverse(arr, word, *currentX, *currentY);
        }
    }
}
void checkAdjacentReverse(char** arr, char* word, int currentX, int currentY) {
    checkDirectionReverse(arr, word, &currentX, &currentY, -1, 0);
    checkDirectionReverse(arr, word, &currentX, &currentY, -1, 1);
    checkDirectionReverse(arr, word, &currentX, &currentY, 0, 1);
    checkDirectionReverse(arr, word, &currentX, &currentY, 1, 1);
    checkDirectionReverse(arr, word, &currentX, &currentY, 1, 0);
    checkDirectionReverse(arr, word, &currentX, &currentY, 1, -1);
    checkDirectionReverse(arr, word, &currentX, &currentY, 0, -1);
    checkDirectionReverse(arr, word, &currentX, &currentY, -1, -1);
    
    if (*(word + moveCounter) != '\0') {
        restartPath();
        currentX = initialX;
        currentY = initialY;
        findFirstLetter(arr, word, currentX, currentY);
    } else {
        isFound = 1;
    }
}