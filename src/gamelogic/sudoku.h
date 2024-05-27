#ifndef SUDOKU
#define SUDOKU

#define SIZE 9

int** verifyFieldValue(int** table, int value, int row, int col);
int** createSudoku(int difficulty);

#endif // SUDOKU
