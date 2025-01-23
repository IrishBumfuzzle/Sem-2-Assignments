#include <stdio.h>
#include <stdlib.h>
#include "functions.h"

int main()
{
    char oper[40];
    scanf("%s", oper);

    if (oper[0] == 'T')
    {
        int n, m, k;
        scanf("%d %d %d", &n, &m, &k);

        RowPtr mat = createMatrix();
        for (int i = 0; i < k; i++)
        {
            int row, col, val;
            scanf("%d %d %d", &row, &col, &val);
            addToMatix(mat, val, row, col);
        }

        RowPtr transposed = matrixTranspose(mat);
        printf("%d\n", k);
        printMatrix(transposed);

        freeMatrix(transposed);
        freeMatrix(mat);
    }
    else if (oper[0] == 'A')
    {
        int n, m, k1, k2;
        scanf("%d %d %d %d", &n, &m, &k1, &k2);

        RowPtr mat1 = createMatrix();
        RowPtr last = mat1;
        for (int i = 0; i < k1; i++)
        {
            int row, col, val;
            scanf("%d %d %d", &row, &col, &val);
            last = addToMatix(last, val, row, col);
        }

        RowPtr mat2 = createMatrix();
        last = mat2;
        for (int i = 0; i < k2; i++)
        {
            int row, col, val;
            scanf("%d %d %d", &row, &col, &val);
            last = addToMatix(last, val, row, col);
        }

        int count = 0;
        RowPtr added = addMatrices(mat1, mat2, &count);
        printf("%d\n", count);
        printMatrix(added);

        freeMatrix(added);
        freeMatrix(mat1);
        freeMatrix(mat2);
    }
}