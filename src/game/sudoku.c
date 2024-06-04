#include <time.h>
#include <stdbool.h>
#include <stdio.h>

#include "sudoku.h"

uint* fixedFieldMap = NULL;
int** sudokuTable = NULL;

bool verifyFieldValue(int value, int row, int col){
  int field = row * 9 + col;
  int mapArea = fixedFieldMap[field / BITS_PER_UINT];
  if((mapArea | (1 << field)) == mapArea)
    return false;

  for(int i = 0; i < SIZE; i++)
    if(i != row && sudokuTable[i][col] == value)
      return false;

  for(int j = 0; j < SIZE; j++)
    if(j != col && sudokuTable[row][j] == value)
      return false;

  int startRow = row / 3 * 3;
  int startCol = col / 3 * 3;

  for(int i = 0; i < 3; i++)
    for(int j = 0; j < 3; j++)
      if(startRow + i != row && startCol + j != col &&
          sudokuTable[startRow + i][startCol + j] == value)
        return false;
      

  return true;
}

void createSudoku(int difficult){
  fixedFieldMap = calloc(((SIZE * SIZE  + BITS_PER_UINT - 1) / BITS_PER_UINT), sizeof(uint));
  sudokuTable = (int**)calloc(SIZE, sizeof(int*));
  for(int row = 0; row < SIZE; row++) 
    sudokuTable[row] = (int*)calloc(SIZE, sizeof(int));
  
  srand(time(NULL));

  for(int row = 0; row < SIZE; row++){
    for(int col = 0; col < SIZE; col++){
      int randNum = rand() % (9 * 3 * difficult);
      if( randNum < 9 && randNum > 0){
        bool canAdd = verifyFieldValue(randNum, row, col);
        if(canAdd){
          sudokuTable[row][col] = randNum;
          int field = row * 9 + col;
          fixedFieldMap[field / BITS_PER_UINT] |= (1 << field);
        }
      }
    }
  }
}

bool addValue(int value, int row, int col){
  if(verifyFieldValue(value, row, col)){
    sudokuTable[row][col] = value;
    return true;
  }
  return false;
}

bool removeValue(int row, int col){
  int field = row * 9 + col;
  int mapArea = fixedFieldMap[field / BITS_PER_UINT];
  if((mapArea | (1 << field)) == mapArea)
    return false;
  sudokuTable[row][col] = 0;
  return true;
}
