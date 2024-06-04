#include <stdlib.h>
#include <unistd.h>
#include <termios.h>

#include "./game/sudoku.h"
#include "./interface/interface.h"


int main() {
    int difficulty = 1; // Adjust difficulty as needed
    int selectedRow = 0;
    int selectedCol = 0;
    int** sudoku = createSudoku(difficulty);
    bool hasChange = true;
    struct termios originalTermios;

    configureTerminal(&originalTermios);
    while(1){
      if(hasChange){
        system("clear");
        printSudoku(sudoku, selectedRow, selectedCol);
      }

      hasChange = HandleInput(sudoku, &selectedRow, &selectedCol);
    }
    resetTerminal(&originalTermios);

    // Free allocated memory
    for (int row = 0; row < SIZE; row++)
        free(sudoku[row]);
    free(sudoku);

    return 0;
}
