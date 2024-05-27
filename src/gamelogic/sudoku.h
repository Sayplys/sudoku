#ifndef SUDOKU
#define SUDOKU

#define SIZE 9

#include <stdbool.h>

bool verifyFieldValue(int** table, int value, int row, int col);
int** createSudoku(int difficulty);
bool addValue(int** table, int value, int row, int col);
bool removeValue(int** table, int row, int col);

#endif // SUDOKU
