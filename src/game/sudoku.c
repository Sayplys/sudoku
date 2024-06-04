#include <time.h>
#include <stdbool.h>
#include <stdio.h>

#include "sudoku.h"

uint* fixedFieldMap = NULL;

bool verifyFieldValue(int** table, int value, int row, int col){
  int field = row * 9 + col;
  int mapArea = fixedFieldMap[field / BITS_PER_UINT];
  if((mapArea | (1 << field)) == mapArea)
    return false;

  for(int i = 0; i < SIZE; i++)
    if(i != row && table[i][col] == value)
      return false;

  for(int j = 0; j < SIZE; j++)
    if(j != col && table[row][j] == value)
      return false;

  int startRow = row / 3 * 3;
  int startCol = col / 3 * 3;

  for(int i = 0; i < 3; i++)
    for(int j = 0; j < 3; j++)
      if(startRow + i != row && startCol + j != col &&
          table[startRow + i][startCol + j] == value)
        return false;
      

  return true;
}

int** createSudoku(int difficult){
  fixedFieldMap = calloc(((SIZE * SIZE  + BITS_PER_UINT - 1) / BITS_PER_UINT), sizeof(uint));
  int** table = (int**)calloc(SIZE, sizeof(int*));
  for(int row = 0; row < SIZE; row++) 
    table[row] = (int*)calloc(SIZE, sizeof(int));
  
  srand(time(NULL));

  for(int row = 0; row < SIZE; row++){
    for(int col = 0; col < SIZE; col++){
      int randNum = rand() % (9 * 3 * difficult);
      if( randNum < 9 && randNum > 0){
        bool canAdd = verifyFieldValue(table, randNum, row, col);
        if(canAdd){
          table[row][col] = randNum;
          int field = row * 9 + col;
          fixedFieldMap[field / BITS_PER_UINT] |= (1 << field);
        }
      }
    }
  }


  return table;
}

bool addValue(int** table, int value, int row, int col){
  if(verifyFieldValue(table, value, row, col)){
    table[row][col] = value;
    return true;
  }
  return false;
}

bool removeValue(int** table, int row, int col){
  int field = row * 9 + col;
  int mapArea = fixedFieldMap[field / BITS_PER_UINT];
  if((mapArea | (1 << field)) == mapArea)
    return false;
  table[row][col] = 0;
  return true;
}
