#include <stdio.h>
#include <termios.h>
#include <unistd.h>

#include "interface.h"

void configureTerminal(struct termios *originalTermios){
  struct termios newTermios;

  tcgetattr(STDIN_FILENO, originalTermios);
  newTermios = *originalTermios;
  newTermios.c_lflag &= ~(ICANON | ECHO);
  tcsetattr(STDIN_FILENO, TCSANOW, &newTermios);
}

void resetTerminal(struct termios *originalTermios){
  tcsetattr(STDIN_FILENO, TCSANOW, originalTermios);
}

bool gameListener(int **table, int *currentRow, int *currentCol){
  char input[4];
  fgets(input, 4 , stdin);
  if(selectFieldByArrow(input, currentRow, currentCol))
    return true;
  else if(inputValue(table, *input, *currentRow, *currentCol))
    return true;
  else if(input[0] == 's'){
    showSolution();
    return true;
  }

  return false;
}

bool HandleInput(int **table, int *currentRow, int *currentCol, bool* isPlaying){

  if(*isPlaying)
    return gameListener(table, currentRow, currentCol);
  else{
    char input = getc(stdin);
    if(input == 'r'){
      restartGame();
      *isPlaying = true;
      return true;
    }
    if(input == 'q')
      return false;
  }

  return false;
}

