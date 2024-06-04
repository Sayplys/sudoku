#ifndef SUDOKU
#define SUDOKU

#define SIZE 9
#define BITS_PER_UINT (sizeof(uint) * 8)

#include <stdbool.h>
#include <stdlib.h>

extern int** sudokuTable;
extern uint* fixedFieldMap;

bool verifyFieldValue(int value, int row, int col);
void createSudoku(int difficulty);
bool addValue(int value, int row, int col);
bool removeValue(int row, int col);

#endif // SUDOKU
