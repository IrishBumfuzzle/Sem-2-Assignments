#include <stdio.h>
#include <stdlib.h>

int powerCalc(int num, int power) { return power == 0 ? 1 : powerCalc(num * num, power - 1); }

int makeString(char str[], char character, int countOfCharacter)
{
    str[0] = character;
    int numOfDigits = 0;
    int count = countOfCharacter;
    while (count > 0)
    {
        count /= 10;
        numOfDigits++;
    }
    for (int i = numOfDigits; i > 0; i--)
    {
        str[i] = countOfCharacter % 10 + '0';
        countOfCharacter /= 10;
    }
    str[numOfDigits + 1] = '\0';
    return numOfDigits + 1;
}

int concatStrings(char *str1, char *str2, int len1, int len2)
{
    for (int i = len1; i < len1 + len2 + 1; i++)
    {
        str1[i] = str2[i - len1];
    }
    return len1 + len2;
}

void reverseString(char *str, int length)
{
    int ahead = 0, back = length - 1;

    while (ahead < back)
    {
        char temp = str[ahead];
        str[ahead] = str[back];
        str[back] = temp;
        ahead++;
        back--;
    }
}

char *compressString(char *str, int length)
{
    char curr = str[0];
    int count = 1;
    char *compressed = (char *)malloc(2 * (length + 1) * sizeof(char));
    int compressedLen = 0;
    compressed[0] = '\0';

    for (int i = 1; i < length; i++)
    {
        if (str[i] == curr)
        {
            count++;
        }
        else
        {
            char new_str[100];
            int len = makeString(new_str, curr, count);
            compressedLen = concatStrings(compressed, new_str, compressedLen, len);
            curr = str[i];
            count = 1;
        }
    }
    char new_str[100];
    int len = makeString(new_str, curr, count);
    compressedLen = concatStrings(compressed, new_str, compressedLen, len);

    return compressed;
}

int *uniqueElements(int *arr, int length)
{
    int *unique = (int *)malloc(1 * sizeof(int));
    int count = 0;

    for (int i = 0; i < length; i++)
    {
        int j = 0;
        for (j = 0; j < count; j++)
        {
            if (arr[i] == unique[j])
            {
                break;
            }
        }

        if (j == count)
        {
            unique = (int *)realloc(unique, (count + 1) * sizeof(int));
            unique[count] = arr[i];
            count++;
        }
    }

    for (int i = 0; i < count; i++)
    {
        printf("%d ", unique[i]);
    }
    printf("\n");

    return unique;
}

int **transpose(int **matrix, int NumRow, int NumCol)
{
    int **new_matrix = (int **)malloc(NumCol * sizeof(int *));
    for (int i = 0; i < NumCol; i++)
    {
        new_matrix[i] = (int *)malloc(NumRow * sizeof(int));
    }

    for (int i = 0; i < NumRow; i++)
    {
        for (int j = 0; j < NumCol; j++)
        {
            new_matrix[j][i] = matrix[i][j];
        }
    }

    return new_matrix;
}