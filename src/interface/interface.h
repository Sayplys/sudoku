#ifndef INTERFACE
#define interface

#include <stdbool.h>
#include <termios.h>

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
void printWinMenu();


bool selectFieldByArrow(char* input,int* currentRow, int* currentCol);
bool inputValue(int ** table, char input, int selectedRow, int selectedCol);
bool showWin();
void restartGame();
void showSolution();


void configureTerminal(struct termios *originalTermios);
void resetTerminal(struct termios *originalTermios);
bool HandleInput(int** table, int *selectedRow, int *selectedCol, bool* isPlaying);


#endif // INTERFACE
