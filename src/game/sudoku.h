#ifndef SUDOKU
#define SUDOKU

#define SIZE 9
#define BITS_PER_UINT (sizeof(uint) * 8)

#include <stdbool.h>
#include <stdlib.h>

extern uint* fixedFieldMap;

bool verifyFieldValue(int** table, int value, int row, int col);
int** createSudoku(int difficulty);
bool addValue(int** table, int value, int row, int col);
bool removeValue(int** table, int row, int col);

#endif // SUDOKU
