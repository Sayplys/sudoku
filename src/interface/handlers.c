#include <stdio.h>

#include "../game/sudoku.h"

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

bool addInputValue(int** table, char input, int selectedRow, int selectedCol){
  if('1' <= input && input <= '9'){
    return addValue(table, (input + 1) % '1', selectedRow, selectedCol);
  }

  return false;
}
