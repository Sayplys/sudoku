#include <stdio.h>
#include "../game/sudoku.h"

#define COLOR_RED   "\033[31m"
#define COLOR_GREEN   "\033[32m"
#define COLOR_YELLOW    "\033[33m"
#define RESET   "\033[0m"

void printSudoku(int** table, int selectedRow, int selectedColumn){
    for (int row = 0; row < SIZE; row++) {
        for (int col = 0; col < SIZE; col++) {
            if (col % 3 == 0 && col != 0)
                printf("| ");
            
            int field = row * 9 + col;
            int mapArea = fixedFieldMap[field / BITS_PER_UINT];
            if(selectedRow != row || selectedColumn != col){
              if((mapArea | (1 << field)) == mapArea)
                printf(COLOR_YELLOW "%2d " RESET, table[row][col]);
              else printf("%2d ", table[row][col]);
            }
            else
              if((mapArea | (1 << field)) == mapArea)
                printf(COLOR_RED "%2d " RESET, table[row][col]);
              else printf(COLOR_GREEN "%2d " RESET, table[row][col]);
 
        }
        printf("\n");
        if ((row + 1) % 3 == 0 && row != SIZE - 1) {
            for (int i = 0; i < SIZE + 2; i++)
                printf("---");
            printf("\n");
        }
    }
}

void printWinMenu(){
  printf("Congratulations you found a solution!!!");
  printf("Press r to restart or q to quit?");
}
