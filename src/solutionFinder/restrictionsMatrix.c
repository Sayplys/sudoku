#include <math.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct Node Node;
typedef struct CollumnNode CollumnNode;

struct Node {
  Node* up;
  Node* down;
  Node* left;
  Node* right;
  CollumnNode* collumn;
};

struct CollumnNode {
  Node self;
  int index;
};

void addNodeToCollumn(Node** lastRowNode, CollumnNode** currentCollumnNode, int collumn) {
  CollumnNode* startNode = *currentCollumnNode; // To detect cycles
  do {
    *currentCollumnNode = (*currentCollumnNode)->self.right->collumn;
    if (*currentCollumnNode == startNode){
      fprintf(stderr, "Memory allocation failed\n");
      return;
    }
  }while ((*currentCollumnNode)->index != collumn);

  Node* newNode = (Node*)malloc(sizeof(Node));
  if (newNode == NULL) {
    fprintf(stderr, "Memory allocation failed\n");
    exit(EXIT_FAILURE);
  }

  newNode->up = (*currentCollumnNode)->self.up;
  (*currentCollumnNode)->self.up->down = newNode;
  (*currentCollumnNode)->self.up = newNode;
  newNode->down = &(*currentCollumnNode)->self;
  newNode->collumn = (*currentCollumnNode);

  if (*lastRowNode != NULL) {
    newNode->right = (*lastRowNode)->right;
      (*lastRowNode)->right->left = newNode;
      (*lastRowNode)->right = newNode;
      newNode->left = *lastRowNode;
    }else {
      newNode->right = newNode;
      newNode->left = newNode;
    }

  *lastRowNode = newNode;
}

CollumnNode* createRestrictionsMatrix(int** sudoku, int sudokuSize) {
  CollumnNode* header = (CollumnNode*)malloc(sizeof(CollumnNode));
  if(header == NULL) {
    fprintf(stderr, "Memory allocation failed\n");
    exit(EXIT_FAILURE);
  }

  header->self.up = &header->self;
  header->self.down = &header->self;
  header->self.left = &header->self;
  header->self.right = &header->self;
  header->self.collumn = header;
  header->index = -1;

  CollumnNode* lastCreated = header;

  for (int i = 0; i < 3 * sudokuSize * sudokuSize; i++) {
    CollumnNode* newCollumn = (CollumnNode*)malloc(sizeof(CollumnNode));
    if (newCollumn == NULL) {
      fprintf(stderr, "Memory allocation failed\n");
      exit(EXIT_FAILURE);
    }

    newCollumn->self.up = &newCollumn->self;
    newCollumn->self.down = &newCollumn->self;
    newCollumn->self.left = &lastCreated->self;
    lastCreated->self.right = &newCollumn->self;
    newCollumn->self.right = &header->self;
    header->self.left = &newCollumn->self;
    newCollumn->self.collumn = newCollumn;
    newCollumn->index = i;
    lastCreated = newCollumn;
  }

  for (int row = 0; row < sudokuSize; row++) {
    for (int col = 0; col < sudokuSize; col++) {
      int area = floor((float)row / 3) * 3 + floor((float)col / 3);
      if (sudoku[row][col] == 0) {
        for (int i = 0; i < sudokuSize; i++) {
          CollumnNode* currentCollumnNode = header;
          Node* lastAddNode = NULL;

          addNodeToCollumn(&lastAddNode, &currentCollumnNode, col + (i * sudokuSize));
          addNodeToCollumn(&lastAddNode, &currentCollumnNode, row + (i * sudokuSize) + sudokuSize * sudokuSize);
          addNodeToCollumn(&lastAddNode, &currentCollumnNode, area + (i * sudokuSize) + 2 * sudokuSize * sudokuSize);
        }
      }else {
        CollumnNode* currentCollumnNode = header;
        Node* lastAddNode = NULL;
        int i = sudoku[row][col] - 1;
        addNodeToCollumn(&lastAddNode, &currentCollumnNode, col + (i * sudokuSize));
        addNodeToCollumn(&lastAddNode, &currentCollumnNode, row + (i * sudokuSize) + sudokuSize * sudokuSize);
        addNodeToCollumn(&lastAddNode, &currentCollumnNode, area + (i * sudokuSize) + 2 * sudokuSize * sudokuSize);
      }
    }
  }

  return header;
}

