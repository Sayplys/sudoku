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

bool HandleInput(int **table, int *currentRow, int *currentCol){
  SKInput skinput;

  char input[4];
  fgets(input, 4 , stdin);
  if(selectFieldByArrow(input, currentRow, currentCol))
    return true;
  else if(addInputValue(table, *input, *currentRow, *currentCol))
    return true;
  else if('0' < input[0] && input[1] < '9' &&
          '0' < input[0] && input[1] < '9')
    return true;
  
  return false;
}

