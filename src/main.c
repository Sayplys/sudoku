#include <stdlib.h>
#include <unistd.h>
#include <termios.h>

#include "./game/sudoku.h"
#include "./interface/interface.h"

int main() {
    int difficulty = 1; // Adjust difficulty as needed
    int selectedRow = 0;
    int selectedCol = 0;
    createSudoku(difficulty);
    bool hasChange = true;
    struct termios originalTermios;

    
    configureTerminal(&originalTermios);
    while(1){
      if(hasChange){
        system("clear");
        printSudoku(sudokuTable, selectedRow, selectedCol);
      }

      hasChange = HandleInput(sudokuTable, &selectedRow, &selectedCol);
    }
    resetTerminal(&originalTermios);

    // Free allocated memory
    for (int row = 0; row < SIZE; row++)
        free(sudokuTable[row]);
    free(sudokuTable);
    free(fixedFieldMap);

    return 0;
}
