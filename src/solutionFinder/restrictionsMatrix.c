#include "DLXSudoku.h"
#include <math.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

void printMatrix(ColumnNode* header, int sudokuSize);

bool addColumnNode(ColumnNode* header, int index){
  ColumnNode* column = (ColumnNode*)malloc(sizeof(ColumnNode));
  if(column == NULL){
    fprintf(stderr, "It wasn's possible allocate memory... exiting...");
    exit(EXIT_FAILURE);
  }

  column->self.up = &column->self;
  column->self.down = &column->self;
  column->self.right = &header->self;
  column->self.left = header->self.left;
  header->self.left->right = &column->self;
  header->self.left = &column->self;
  
  column->index = index;
  column->size = 0;
  column->self.column = column;

  return true;
}

bool addRowNode(ColumnNode* header, int columnIndex, Node** leftNode) {
    Node* node = (Node*)malloc(sizeof(Node));
    if (node == NULL) {
        fprintf(stderr, "It wasn't possible to allocate memory... exiting...");
        exit(EXIT_FAILURE);
    }

    ColumnNode* column = (ColumnNode*)header->self.right->column;
    while (column != header) {
        if (column->index == columnIndex) {
            break;
        }
        column = (ColumnNode*)column->self.right->column;
    }

    if (column == header) {
        free(node);
        return false;
    }

    node->down = &column->self;
    node->up = column->self.up;
    column->self.up->down = node;
    column->self.up = node;

    if (*leftNode == NULL) {
        node->left = node;
        node->right = node;
    } else {
        node->left = *leftNode;
        node->right = (*leftNode)->right;
        (*leftNode)->right->left = node;
        (*leftNode)->right = node;
    }
    
    *leftNode = node;
    node->column = column;

    column->size++;
    return true;
}

bool createRow(int row, int col, int num, int sudokuSize, ColumnNode* header){
  Node* addedNode = NULL;
          
  int field = row * sudokuSize + col;
  if(!addRowNode(header, field, &addedNode)) return false;
          
  int colNum = sudokuSize * sudokuSize + col * sudokuSize + num;
  if(!addRowNode(header, colNum, &addedNode)) return false;
          
  int rowNum = 2 * sudokuSize * sudokuSize + row * sudokuSize + num;
  if(!addRowNode(header, rowNum, &addedNode)) return false;

  int area = 3 * sudokuSize * sudokuSize +
    ((row/(int)sqrt(sudokuSize)) * (int)sqrt(sudokuSize) + col/(int)sqrt(sudokuSize)) 
    * sudokuSize + num;
  if(!addRowNode(header, area, &addedNode)) return false;

  return true;
}

ColumnNode* createRestrictionsMatrix(int** sodoku, int sudokuSize){
  ColumnNode* header = (ColumnNode*)malloc(sizeof(ColumnNode));
  if(header == NULL){
    fprintf(stderr, "It wasn's possible allocate memory... exiting...\n");
    exit(EXIT_FAILURE);
  }
 
  header->self.left = &header->self;
  header->self.right = &header->self;
  header->index = -1;
  header->self.column = header;


  for(int i = 0; i < sudokuSize*sudokuSize*3 + sudokuSize*sudokuSize; i++){
    if(!addColumnNode(header, i)){
      fprintf(stderr, "Failed to add column %d... exiting...\n", i);
      exit(EXIT_FAILURE);
    };
  }

  for(int row = 0; row < sudokuSize; row++){
    for(int col = 0; col < sudokuSize; col++){
      if(sodoku[row][col] == 0){
        for(int num = 0; num < sudokuSize; num++){
          if(!createRow(row, col, num, sudokuSize, header)){
            fprintf(
                stderr, 
                "Failed to add row for cell %d %d with num %d... exiting...\n", 
                row, col, num);
            exit(EXIT_FAILURE);
          }

        }
      }
      else{
        int num = sodoku[row][col] - 1;
        if(!createRow(row, col, num, sudokuSize, header)){
            fprintf(
                stderr, 
                "Failed to add row for cell %d %d with num %d... exiting...", 
                row, col, num
                );
        exit(EXIT_FAILURE);
        }
      }
    }
  }

  return header;
}

void freeRestrictionsMatrix(ColumnNode* header){
  ColumnNode* column = header->self.right->column;
  while(column != header){
    Node* columnRow = column->self.down;
    while(columnRow != &column->self){
      Node* tempRow = columnRow;
      columnRow = column->self.down;
      free(tempRow);
    }
    ColumnNode* tempColumn = column;
    column = column->self.right->column;
    header->self.right = &column->self;
    free(column);
  }
}

void printMatrix(ColumnNode* header, int sudokuSize) {
  ColumnNode* colNode = (ColumnNode*)header->self.right;
    while(colNode->index < sudokuSize*sudokuSize){
      printf("\nField %d\n", colNode->index);
      Node* rowNode = colNode->self.down;
      while(rowNode != &colNode->self){
        Node* node = rowNode->right;
        int row = 0, col = 0, num = 0;
        while(node != rowNode){
          if(node->column->index >= sudokuSize * sudokuSize 
            && node->column->index < 2 * sudokuSize * sudokuSize){
            col = (node->column->index - sudokuSize*sudokuSize) / sudokuSize;
            num = ((node->column->index - sudokuSize*sudokuSize) % sudokuSize) + 1;
          }
          else if(node->column->index >= 2 * sudokuSize * sudokuSize 
                && node->column->index < 3 * sudokuSize * sudokuSize){
            row = (node->column->index - 2 * sudokuSize*sudokuSize) / sudokuSize;
          }
          
          node = node->right;
        }
        printf("[%d][%d] = [%d]\n", row, col, num);
        rowNode = rowNode->down;
      }
      
      colNode = (ColumnNode*)colNode->self.right->column;
    }
}

/*void testCreateRestrictionsMatrix() {
    int sudokuSize = 4;
    int** sudoku = (int**)malloc(sudokuSize * sizeof(int*));
    for (int i = 0; i < sudokuSize; i++) {
        sudoku[i] = (int*)malloc(sudokuSize * sizeof(int));
    }

    // Sample 4x4 Sudoku puzzle
    int sampleSudoku[4][4] = {
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0}
    };

    for (int i = 0; i < sudokuSize; i++) {
        for (int j = 0; j < sudokuSize; j++) {
            sudoku[i][j] = sampleSudoku[i][j];
        }
    }

    ColumnNode* header = createRestrictionsMatrix(sudoku, sudokuSize);
    printMatrix(header, sudokuSize);

    // Free allocated memory
    for (int i = 0; i < sudokuSize; i++) {
        free(sudoku[i]);
    }
    free(sudoku);
}

int main() {
    testCreateRestrictionsMatrix();
    return 0;
}*/
