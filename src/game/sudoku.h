#ifndef SUDOKU
#define SUDOKU

#define SIZE 9
#define BITS_PER_UINT (sizeof(uint) * 8)

#include <stdbool.h>
#include <stdlib.h>

extern int** sudokuTable;
extern uint* fixedFieldMap;
extern int difficulty;

bool verifyFieldValue(int value, int row, int col);
void createSudoku();
bool addValue(int value, int row, int col);
bool removeValue(int row, int col);
bool checkWin();

#endif // SUDOKU
