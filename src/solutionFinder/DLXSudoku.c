#include "DLXSudoku.h"
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void DLXSudoku(ColumnNode* restrictionsHeader, int size, int** solution, bool* founded);

ColumnNode* findColumn(ColumnNode* restrictionsHeader);
void saveSolution(Node* rowNode, int** solution, int sudokuSize);
void coverColumn(ColumnNode* column);
void uncoverColumn(ColumnNode* column);

int** findSolution(int** sudoku, int sudokuSize){
  printf("Seaching for solution...\n");
  int** solution = (int**)malloc(sizeof(int**) * sudokuSize);
  for(int i = 0; i < sudokuSize; i++)
    solution[i] = (int*)calloc(sizeof(int), sudokuSize);
  
  ColumnNode* restrictionsHeader = createRestrictionsMatrix(sudoku, sudokuSize);

  bool solutionFounded = false;
  DLXSudoku(restrictionsHeader, sudokuSize, solution, &solutionFounded);
  return solution;
}

void DLXSudoku(ColumnNode* restrictionsHeader, int size, int** solution, bool* solutionFound){
  if(restrictionsHeader->self.right->column == restrictionsHeader){
    printf("Solution found\n");
    *solutionFound = true;
    return;
  }

  ColumnNode* column = findColumn(restrictionsHeader);
  coverColumn(column);

  Node* currentColRow = column->self.down;
  while(currentColRow != &column->self){
    if(!(*solutionFound))
      saveSolution(currentColRow, solution, size);
    
    Node* rowNode = currentColRow -> right;
    while(rowNode != currentColRow){
      coverColumn(rowNode->column);
      rowNode = rowNode -> right;
    }
    
    if(!(*solutionFound))
      DLXSudoku(restrictionsHeader, size, solution, solutionFound);

    rowNode = currentColRow->left;
    while(rowNode != currentColRow){
      uncoverColumn(rowNode->column);
      rowNode = rowNode->left;
    }

    currentColRow = currentColRow -> down;
  }
  uncoverColumn(column);
}

ColumnNode* findColumn(ColumnNode* restrictionsHeader){
  ColumnNode* choice = NULL;
  int number = 9999999;
  
  ColumnNode* column = restrictionsHeader->self.right->column;
  while(column != restrictionsHeader){
    if(column->size < number){
      choice = column;
      number = choice->size;
    }
    column = column->self.right->column;
  }

  return choice;
}

void saveSolution(Node* rowNode, int** solution, int sudokuSize){
  int row = 0, col = 0, num = 0;
  Node* node = rowNode;
  do{
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
  }while(node != rowNode);
  int area = (row/(int)sqrt(sudokuSize)) * (int)sqrt(sudokuSize) + col/(int)sqrt(sudokuSize);

  solution[row][col] = num;
}

void coverColumn(ColumnNode* column){
  column->self.right->left = column->self.left;
  column->self.left->right = column->self.right;
  
  Node* colRow = column->self.down;
  while(colRow != &column->self){
    Node* rowNode = colRow->right;
    while(rowNode != colRow){
      rowNode->down->up = rowNode->up;
      rowNode->up->down = rowNode->down;
      rowNode->column->size--;
      rowNode = rowNode->right;
    }


    colRow = colRow->down;
  }
  
}

void uncoverColumn(ColumnNode* column){
  Node* colRow = column->self.up;
  while(colRow != &column->self){
    Node* rowNode = colRow->left;
    while(rowNode != colRow){
      rowNode->column->size++;
      rowNode->down->up = rowNode;
      rowNode->up->down = rowNode;
      rowNode = rowNode->left;
    }


    colRow = colRow->up;
  }
  
  column->self.right->left = &column->self;
  column->self.left->right = &column->self;
}

