#ifndef DLXSUDOKU
#define DLXSUDOKU

typedef struct Node Node;
typedef struct ColumnNode ColumnNode;

struct Node {
  Node* up;
  Node* down;
  Node* left;
  Node* right;
  ColumnNode* column;
};

struct ColumnNode {
  Node self;
  int index;
  int size;
};

ColumnNode* createRestrictionsMatrix(int** sudoku, int sudokuSize);
void freeRestrictionsMatrix(ColumnNode* header);
int** findSolution(int** sudoku, int sudokuSize);

#endif //DLXSUDOKU
