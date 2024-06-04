#include "../game/sudoku.h"

int selectFieldByArrow(char* input,int* currentRow, int* currentCol){
  if(input[0] == '\033')
    if(input[3] == '\0' && input[1] == '['){
      switch (input[2]){
        case 'A': // UP
          if (*currentRow > 0){
            (*currentRow)--;
            return 1;
          }
          return 0;
        case 'B': // DOWN
          if(*currentRow < SIZE - 1){
            (*currentRow)++;
            return 1;
          }
          return 0;
        case 'C': // RIGHT
          if(*currentCol < SIZE - 1){
            (*currentCol)++;
            return 1;
          }
          return 0;
        case 'D': // Left
          if(*currentCol > 0){
            (*currentCol)--;
            return 1;
          }
          return 0;
    }
  }

  return 0;
}
