#include "../game/sudoku.h"

void selectFieldByArrow(char* input,int* currentRow, int* currentCol){
  if(input[0] == '\033')
    if(input[3] == '\0' && input[1] == '[')
      switch (input[2]){
        case 'A': // UP
          if (*currentRow > 0)
            (*currentRow)--;
          break;
        case 'B': // DOWN
          if(*currentRow < SIZE - 1)
            (*currentRow)++;
          break;
        case 'C': // RIGHT
          if(*currentCol < SIZE - 1)
            (*currentCol)++;
          break;
        case 'D': // Left
          if(*currentCol > 0)
            (*currentCol)--;
          break;
    }
}
