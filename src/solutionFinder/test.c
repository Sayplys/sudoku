#include "DLXSudoku.h"
#include <stdio.h>
#include <stdlib.h>

// Function prototypes
int** createSudoku(int size);
void printSudoku(int** sudoku, int size);
void freeSudoku(int** sudoku, int size);

int main() {
    // Example Sudoku puzzle (0 represents empty cells)
    int size = 9;
    int** sudoku = createSudoku(size);

    // Fill in some sample values for testing
    int exampleSudoku[9][9] = {
        {5, 3, 0, 0, 7, 0, 0, 0, 0},
        {6, 0, 0, 1, 9, 5, 0, 0, 0},
        {0, 9, 8, 0, 0, 0, 0, 6, 0},
        {8, 0, 0, 0, 6, 0, 0, 0, 3},
        {4, 0, 0, 8, 0, 3, 0, 0, 1},
        {7, 0, 0, 0, 2, 0, 0, 0, 6},
        {0, 6, 0, 0, 0, 0, 2, 8, 0},
        {0, 0, 0, 4, 1, 9, 0, 0, 5},
        {0, 0, 0, 0, 8, 0, 0, 7, 9}
    };

    // Copy example Sudoku to the dynamically allocated array
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            sudoku[i][j] = exampleSudoku[i][j];
        }
    }

    // Print the initial Sudoku puzzle
    printf("Initial Sudoku puzzle:\n");
    printSudoku(sudoku, size);

    // Find the solution
    int** solution = findSolutions(sudoku, size);

    // Print the solution
    if (solution != NULL) {
        printf("\nSolved Sudoku puzzle:\n");
        printSudoku(solution, size);
        freeSudoku(solution, size);
    } else {
        printf("\nNo solution found.\n");
    }

    // Free the allocated memory
    freeSudoku(sudoku, size);

    return 0;
}

int** createSudoku(int size) {
    int** sudoku = (int**)malloc(size * sizeof(int*));
    for (int i = 0; i < size; i++) {
        sudoku[i] = (int*)malloc(size * sizeof(int));
        for (int j = 0; j < size; j++) {
            sudoku[i][j] = 0;
        }
    }
    return sudoku;
}

void printSudoku(int** sudoku, int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            printf("%d ", sudoku[i][j]);
        }
        printf("\n");
    }
}

void freeSudoku(int** sudoku, int size) {
    for (int i = 0; i < size; i++) {
        free(sudoku[i]);
    }
    free(sudoku);
}

