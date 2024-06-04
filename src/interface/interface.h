#ifndef INTERFACE
#define interface

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


void configureTerminal(struct termios *originalTermios);
void resetTerminal(struct termios *originalTermios);
int HandleInput(int *selectedRow, int *selectedCol);


#endif // INTERFACE
