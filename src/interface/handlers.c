#include "../game/sudoku.h"
#include "interface.h"
#include "../solutionFinder/DLXSudoku.h"
#include <stdlib.h>
#include <unistd.h>

bool selectFieldByArrow(char* input,int* currentRow, int* currentCol){
  if(input[0] == '\033')
    if(input[3] == '\0' && input[1] == '['){
      switch (input[2]){
        case 'A': // UP
          if (*currentRow > 0){
            (*currentRow)--;
            return true;
          }
          return false;
        case 'B': // DOWN
          if(*currentRow < SIZE - 1){
            (*currentRow)++;
            return true;
          }
          return false;
        case 'C': // RIGHT
          if(*currentCol < SIZE - 1){
            (*currentCol)++;
            return true;
          }
          return false;
        case 'D': // Left
          if(*currentCol > 0){
            (*currentCol)--;
            return true;
          }
          return false;
    }
  }

  return false;
}

bool inputValue(int** table, char input, int selectedRow, int selectedCol){
  if('1' <= input && input <= '9'){
    return addValue((input + 1) % '1', selectedRow, selectedCol);
  }else if(input == '0'){
    return removeValue(selectedRow, selectedCol);
  }

  return false;
}

bool showWin(){
  if(checkWin() == true){
    return true;
  }
  
  return false;
}

void restartGame(){
  createSudoku();
}

void showSolution(){
  int** solution = findSolution(sudokuTable, SIZE);
  for(int i = 0; i < SIZE; i++)
    for(int j = 0; j < SIZE; j++)
      sudokuTable[i][j] = solution[i][j];
  free(solution);
  sleep(1);
}
