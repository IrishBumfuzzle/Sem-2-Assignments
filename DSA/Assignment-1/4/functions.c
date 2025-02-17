#include <stdio.h>
#include <stdlib.h>
#include "functions.h"

PtrNode Insert(PtrNode Head, int num)
{
    PtrNode temp = (PtrNode)malloc(sizeof(Node));
    temp->Element = num;

    temp->NextNode = Head;
    temp->PrevNode = Head->PrevNode;

    Head->PrevNode->NextNode = temp;
    Head->PrevNode = temp;

    return temp;
}

PtrNode Find(PtrNode Head, int num)
{
    if (Head == NULL)
        return NULL;
    PtrNode curr = Head;
    do
    {
        if (curr->Element == num)
        {
            if (curr == Head)
                return Head;
            curr->PrevNode->NextNode = curr->NextNode;
            curr->NextNode->PrevNode = curr->PrevNode;

            curr->NextNode = Head;
            curr->PrevNode = Head->PrevNode;

            Head->PrevNode->NextNode = curr;
            Head->PrevNode = curr;

            return curr;
        }
        curr = curr->NextNode;
    } while (curr != Head);
    return NULL;
}

void Print(PtrNode Head)
{
    if (Head == NULL)
        return;
    PtrNode curr = Head;
    do
    {
        printf("%d ", curr->Element);
        curr = curr->NextNode;
    } while (curr != Head);
    printf("\n");
}