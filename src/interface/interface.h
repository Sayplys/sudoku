#ifndef INTERFACE
#define interface

#include <stdbool.h>

typedef enum InputType{
  ARROW,
  COORD,
  VALUE,
  NONE,
}InputType;

typedef struct SKInput{
  InputType type;
  char* input;
}SKInput;


void printSudoku(int** table, int selectedRow, int selectedCol);
int selectFieldByArrow(char* input,int* currentRow, int* currentCol);
int addInputValue(int ** table, char input, int selectedRow, int selectedCol);


void configureTerminal(struct termios *originalTermios);
void resetTerminal(struct termios *originalTermios);
bool HandleInput(int** table, int *selectedRow, int *selectedCol);


#endif // INTERFACE
