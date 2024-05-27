#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

#define SIZE 9

bool validateNum(int** table, int value, int row, int col){
  for(int i = 0; i < SIZE; i++)
    if(table[i][col] == value)
      return false;

  for(int j = 0; j < SIZE; j++)
    if(table[row][j] == value)
      return false;

  int startRow = row / 3 * 3;
  int startCol = col / 3 * 3;

  for(int i = 0; i < 3; i++)
    for(int j = 3; j < 3; j++)
      if(table[startRow + i][startCol + j] == value)
        return false;
      

  return true;
}

int** createSudoku(int difficult){
  int** table = (int**)calloc(SIZE, sizeof(int*));
  for(int row = 0; row < SIZE; row++) 
    table[row] = (int*)calloc(SIZE, sizeof(int));
  
  srand(time(NULL));

  for(int row = 0; row < SIZE; row++){
    for(int col = 0; col < SIZE; col++){
      int randNum = rand() % (9 * 3 * difficult);
      if( randNum < 9 && randNum > 0){
        bool canAdd = validateNum(table, randNum, row, col);
        if(canAdd)
          table[row][col] = randNum;
      }
    }
  }


  return table;
}

void printSudoku(int** table) {
    for (int row = 0; row < SIZE; row++) {
        for (int col = 0; col < SIZE; col++) {
            if (col % 3 == 0 && col != 0)
                printf("| ");
            printf("%2d ", table[row][col]);
        }
        printf("\n");
        if ((row + 1) % 3 == 0 && row != SIZE - 1) {
            for (int i = 0; i < SIZE + 2; i++)
                printf("---");
            printf("\n");
        }
    }
}

int main() {
    int difficulty = 1; // Adjust difficulty as needed
    int** sudoku = createSudoku(difficulty);
    printSudoku(sudoku);

    // Free allocated memory
    for (int row = 0; row < SIZE; row++)
        free(sudoku[row]);
    free(sudoku);

    return 0;
}
