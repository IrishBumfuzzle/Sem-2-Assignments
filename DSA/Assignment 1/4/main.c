#include <stdio.h>
#include <stdlib.h>
#include "functions.h"

int main()
{
    int n;
    scanf("%d", &n);
    PtrNode Head = NULL;

    for (int i = 0; i < n; i++)
    {
        char operation[40];
        scanf("%s", operation);

        if (operation[4] == '1')
        {
            int num;
            scanf("%d", &num);

            if (Head != NULL)
            {
                Head = Insert(Head, num);
            }
            else
            {
                Head = (PtrNode)malloc(sizeof(Node));
                Head->Element = num;
                Head->NextNode = Head;
                Head->PrevNode = Head;
            }
        }
        else if (operation[4] == '2')
        {
            int num;
            scanf("%d", &num);

            PtrNode temp = Find(Head, num);
            Head = temp != NULL ? temp : Head;
        }
        else if (operation[4] == '3')
        {
            Print(Head);
        }
    }

    PtrNode temp = Head;
    do
    {
        PtrNode temp2 = temp;
        temp = temp->NextNode;
        free(temp2);
    } while (temp != Head);
}