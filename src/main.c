#include <stdlib.h>
#include <unistd.h>
#include <termios.h>

#include "./game/sudoku.h"
#include "./interface/interface.h"

int main() {
    int difficulty = 1; // Adjust difficulty as needed
    int selectedRow = 0;
    int selectedCol = 0;
    createSudoku();
    bool hasChange = true;
    bool isPlaying = true;
    struct termios originalTermios;

    
    configureTerminal(&originalTermios);
    while(1){
      if(hasChange){
        system("clear");
        printSudoku(sudokuTable, selectedRow, selectedCol);
        if(showWin()){
          isPlaying = false;
          printWinMenu();
        }
      }

      hasChange = HandleInput(sudokuTable, &selectedRow, &selectedCol, isPlaying);
      if(!hasChange && !isPlaying){
        break;
      }
    }
    resetTerminal(&originalTermios);

    // Free allocated memory
    for (int row = 0; row < SIZE; row++)
        free(sudokuTable[row]);
    free(sudokuTable);
    free(fixedFieldMap);

    return 0;
}
