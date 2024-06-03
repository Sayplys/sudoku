#include "./game/sudoku.h"
#include "./interface/interface.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int main() {
    int difficulty = 1; // Adjust difficulty as needed
    int selectedRow = 0;
    int selectedCol = 0;
    int** sudoku = createSudoku(difficulty);
    char arrowInput[4];

    while(1){
      printf("\e[1;1H\e[2J");
      printSudoku(sudoku, selectedRow, selectedCol);
      
      fgets(arrowInput, 4, stdin);
      selectFieldByArrow(arrowInput, &selectedRow, &selectedCol);
      while ( getchar() != '\n' );

      if(arrowInput[0] == '0')break;
    }

    // Free allocated memory
    for (int row = 0; row < SIZE; row++)
        free(sudoku[row]);
    free(sudoku);

    return 0;
}
