#include <stdio.h>
#include <stdlib.h>
#include "functions.h"

RowPtr createMatrix()
{
    RowPtr head = (RowPtr)malloc(sizeof(Row));
    head->rowNumber = 0;
    head->firstNode = NULL;
    head->nextRow = NULL;
    return head;
}

void mergeSort(int start, int end, Element *arr)
{
    if (start == end)
        return;

    int middle = (start + end) / 2;
    mergeSort(start, middle, arr);
    mergeSort(middle + 1, end, arr);

    int l1 = start;
    int l2 = middle + 1;
    Element newArray[end - start + 1];
    int index = 0;

    while (l2 <= end || l1 <= middle)
    {
        if (l2 <= end && l1 <= middle)
        {
            // newArray[index] = arr[l1] > arr[l2] ? arr[l2] : arr[l1];
            // arr[l1] > arr[l2] ? l2++ : l1++;
            if (arr[l1].row < arr[l2].row || (arr[l1].row == arr[l2].row && arr[l1].col < arr[l2].col))
            {
                newArray[index] = arr[l1++];
            }
            else
            {
                newArray[index] = arr[l2++];
            }
            index++;
        }
        else if (l2 <= end)
        {
            newArray[index++] = arr[l2++];
        }
        else if (l1 <= middle)
            newArray[index++] = arr[l1++];
    }
    for (int i = 0; i < index; i++)
        arr[start + i] = newArray[i];

    return;
}

RowPtr addToMatix(RowPtr head, int val, int row, int col)
{
    RowPtr currentRow = head;
    while (currentRow->rowNumber != row)
    {
        if (currentRow->nextRow == NULL)
        {
            currentRow->nextRow = (RowPtr)malloc(sizeof(Row));
            currentRow->nextRow->rowNumber = row;
            currentRow->nextRow->firstNode = NULL;
            currentRow->nextRow->nextRow = NULL;
            currentRow = currentRow->nextRow;
            break;
        }
        currentRow = currentRow->nextRow;
    }

    NodePtr currentNode = currentRow->firstNode;
    if (currentNode == NULL)
    {
        currentRow->firstNode = (NodePtr)malloc(sizeof(Node));
        currentRow->firstNode->value = val;
        currentRow->firstNode->columnNumber = col;
        currentRow->firstNode->next = NULL;
    }
    else
    {
        while (currentNode->next != NULL)
            currentNode = currentNode->next;

        currentNode->next = (NodePtr)malloc(sizeof(Node));
        currentNode->next->value = val;
        currentNode->next->columnNumber = col;
        currentNode->next->next = NULL;
    }

    return currentRow;
}

void printMatrix(RowPtr head)
{
    RowPtr currentRow = head;
    Element *arr = malloc(sizeof(Element) * 1000000);
    int index = 0;
    while (currentRow != NULL)
    {
        NodePtr currentNode = currentRow->firstNode;
        while (currentNode != NULL)
        {
            // printf("%d %d %d\n", currentRow->rowNumber, currentNode->columnNumber, currentNode->value);
            arr[index].row = currentRow->rowNumber;
            arr[index].col = currentNode->columnNumber;
            arr[index++].val = currentNode->value;
            currentNode = currentNode->next;
        }
        currentRow = currentRow->nextRow;
    }
    mergeSort(0, index - 1, arr);
    for (int i = 0; i < index; i++)
    {
        printf("%d %d %d\n", arr[i].row, arr[i].col, arr[i].val);
    }
    free(arr);
}

void freeMatrix(RowPtr head)
{
    RowPtr currentRow = head;
    while (currentRow != NULL)
    {
        NodePtr currentNode = currentRow->firstNode;
        while (currentNode != NULL)
        {
            NodePtr temp = currentNode;
            currentNode = currentNode->next;
            free(temp);
        }
        RowPtr temp = currentRow;
        currentRow = currentRow->nextRow;
        free(temp);
    }
}

RowPtr matrixTranspose(RowPtr head)
{
    RowPtr transposedMatrix = createMatrix();
    RowPtr currentRow = head;
    while (currentRow != NULL)
    {
        NodePtr currentNode = currentRow->firstNode;
        while (currentNode != NULL)
        {
            addToMatix(transposedMatrix, currentNode->value, currentNode->columnNumber, currentRow->rowNumber);
            currentNode = currentNode->next;
        }
        currentRow = currentRow->nextRow;
    }
    return transposedMatrix;
}

RowPtr addMatrices(RowPtr mat1, RowPtr mat2, int *count)
{
    RowPtr result = createMatrix();
    RowPtr result_curr = result;
    RowPtr currentRow1 = mat1;
    RowPtr currentRow2 = mat2;
    while (currentRow1 != NULL && currentRow2 != NULL)
    {
        if (currentRow1->rowNumber == currentRow2->rowNumber)
        {
            NodePtr currNode1 = currentRow1->firstNode;
            NodePtr currNode2 = currentRow2->firstNode;

            while (currNode1 != NULL && currNode2 != NULL)
            {
                if (currNode1->columnNumber == currNode2->columnNumber)
                {
                    if (currNode1->value + currNode2->value != 0)
                    {
                        result_curr = addToMatix(result_curr, currNode1->value + currNode2->value, currentRow1->rowNumber, currNode1->columnNumber);
                        (*count)++;
                    }
                    currNode1 = currNode1->next;
                    currNode2 = currNode2->next;
                }
                else if (currNode1->columnNumber < currNode2->columnNumber)
                {
                    result_curr = addToMatix(result_curr, currNode1->value, currentRow1->rowNumber, currNode1->columnNumber);
                    (*count)++;
                    currNode1 = currNode1->next;
                }
                else
                {
                    result_curr = addToMatix(result_curr, currNode2->value, currentRow2->rowNumber, currNode2->columnNumber);
                    (*count)++;
                    currNode2 = currNode2->next;
                }
            }

            if (currNode1 != NULL)
            {
                while (currNode1 != NULL)
                {
                    result_curr = addToMatix(result_curr, currNode1->value, currentRow1->rowNumber, currNode1->columnNumber);
                    (*count)++;
                    currNode1 = currNode1->next;
                }
            }
            else if (currNode2 != NULL)
            {
                while (currNode2 != NULL)
                {
                    result_curr = addToMatix(result_curr, currNode2->value, currentRow2->rowNumber, currNode2->columnNumber);
                    (*count)++;
                    currNode2 = currNode2->next;
                }
            }

            currentRow1 = currentRow1->nextRow;
            currentRow2 = currentRow2->nextRow;
        }

        else if (currentRow1->rowNumber < currentRow2->rowNumber)
        {
            NodePtr currNode1 = currentRow1->firstNode;
            while (currNode1 != NULL)
            {
                result_curr = addToMatix(result_curr, currNode1->value, currentRow1->rowNumber, currNode1->columnNumber);
                (*count)++;
                currNode1 = currNode1->next;
            }

            currentRow1 = currentRow1->nextRow;
        }
        else
        {
            NodePtr currNode2 = currentRow2->firstNode;
            while (currNode2 != NULL)
            {
                result_curr = addToMatix(result_curr, currNode2->value, currentRow2->rowNumber, currNode2->columnNumber);
                (*count)++;
                currNode2 = currNode2->next;
            }

            currentRow2 = currentRow2->nextRow;
        }
    }
    if (currentRow1 != NULL)
    {
        while (currentRow1 != NULL)
        {
            NodePtr currNode1 = currentRow1->firstNode;
            while (currNode1 != NULL)
            {
                result_curr = addToMatix(result_curr, currNode1->value, currentRow1->rowNumber, currNode1->columnNumber);
                (*count)++;
                currNode1 = currNode1->next;
            }
            currentRow1 = currentRow1->nextRow;
        }
    }
    else if (currentRow2 != NULL)
    {
        while (currentRow2 != NULL)
        {
            NodePtr currNode2 = currentRow2->firstNode;
            while (currNode2 != NULL)
            {
                result_curr = addToMatix(result_curr, currNode2->value, currentRow2->rowNumber, currNode2->columnNumber);
                (*count)++;
                currNode2 = currNode2->next;
            }
            currentRow2 = currentRow2->nextRow;
        }
    }

    return result;
}