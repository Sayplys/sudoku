#include "./game/sudoku.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

void printSudoku(int** table) {
    for (int row = 0; row < SIZE; row++) {
        for (int col = 0; col < SIZE; col++) {
            if (col % 3 == 0 && col != 0)
                printf("| ");
            printf("%2d ", table[row][col]);
        }
        printf("\n");
        if ((row + 1) % 3 == 0 && row != SIZE - 1) {
            for (int i = 0; i < SIZE + 2; i++)
                printf("---");
            printf("\n");
        }
    }
}

int main() {
    int difficulty = 1; // Adjust difficulty as needed
    int** sudoku = createSudoku(difficulty);
    printSudoku(sudoku);

    sleep(1);
    if(!addValue(sudoku, 3, 5, 6))
      printf("\n It is not possible add 3 in {5,6}");
    
    printf("\n");
    printSudoku(sudoku);

    sleep(1);
    removeValue(sudoku, 5,6);
    printf("\n");
    printSudoku(sudoku);

    // Free allocated memory
    for (int row = 0; row < SIZE; row++)
        free(sudoku[row]);
    free(sudoku);

    return 0;
}
