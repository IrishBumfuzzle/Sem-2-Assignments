#include <stdio.h>
#include <stdlib.h>
#include "functions.h"

int main()
{
    char input[100];
    int num;
    scanf("%d", &num);

    for (int i = 0; i < num; i++)
    {
        scanf("%s", input);

        if (input[4] == '1')
        {
            int len;
            scanf("%d", &len);
            char *str = (char *)malloc((len + 1) * sizeof(char));
            scanf("%s", str);
            reverseString(str, len);
            printf("%s\n", str);
            free(str);
        }
        else if (input[4] == '2')
        {
            int len;
            scanf("%d", &len);
            char *str = (char *)malloc((len + 1) * sizeof(char));
            scanf("%s", str);
            char *compressed = compressString(str, len);
            printf("%s\n", compressed);
            free(str);
            free(compressed);
        }

        else if (input[4] == '3')
        {
            int len;
            scanf("%d", &len);
            int *arr = (int *)malloc(len * sizeof(int));
            for (int j = 0; j < len; j++)
            {
                scanf("%d", &arr[j]);
            }
            int *unique = uniqueElements(arr, len);
            free(arr);
            free(unique);
        }
        else if (input[4] == '4')
        {
            int NumRow, NumCol;
            scanf("%d %d", &NumRow, &NumCol);
            int **matrix = (int **)malloc(NumRow * sizeof(int *));
            for (int j = 0; j < NumRow; j++)
            {
                matrix[j] = (int *)malloc(NumCol * sizeof(int));
                for (int k = 0; k < NumCol; k++)
                {
                    scanf("%d", &matrix[j][k]);
                }
            }
            int **transposed = transpose(matrix, NumRow, NumCol);
            for (int j = 0; j < NumCol; j++)
            {
                for (int k = 0; k < NumRow; k++)
                {
                    printf("%d ", transposed[j][k]);
                }
                free(transposed[j]);
                printf("\n");
            }
            free(transposed);
            for (int j = 0; j < NumRow; j++)
            {
                free(matrix[j]);
            }
            free(matrix);
        }
    }
}