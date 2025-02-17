typedef struct Node *NodePtr;
typedef struct Row *RowPtr;

typedef struct Row
{
    int rowNumber;
    NodePtr firstNode;
    RowPtr nextRow;
} Row;

typedef struct Node
{
    int value;
    int columnNumber;
    NodePtr next;
} Node;

typedef struct
{
    int row;
    int col;
    int val;
} Element;

RowPtr createMatrix();
RowPtr addToMatix(RowPtr head, int val, int row, int col);
void printMatrix(RowPtr head);
void freeMatrix(RowPtr head);
RowPtr matrixTranspose(RowPtr head);
RowPtr addMatrices(RowPtr mat1, RowPtr mat2, int *count);
void mergeSort(int start, int end, Element *arr);
