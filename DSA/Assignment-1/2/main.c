#include <stdio.h>
#include <stdlib.h>

void mergeSort(int start, int end, int *arr)
{
    if (start == end)
        return;

    int middle = (start + end) / 2;
    mergeSort(start, middle, arr);
    mergeSort(middle + 1, end, arr);

    int l1 = start;
    int l2 = middle + 1;
    int newArray[end - start + 1];
    int index = 0;

    while (l2 <= end || l1 <= middle)
    {
        if (l2 <= end && l1 <= middle)
        {
            newArray[index] = arr[l1] > arr[l2] ? arr[l2] : arr[l1];
            arr[l1] > arr[l2] ? l2++ : l1++;
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

int main()
{
    int n, l, temp;
    scanf("%d %d", &n, &l);
    int *arr = (int *)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++)
    {
        scanf("%d %d", &arr[i], &temp);
    }

    mergeSort(0, n - 1, arr);
    int end = arr[0] + l;
    int remove = 0;

    for (int i = 1; i < n; i++)
    {
        // printf("%d %d\n", arr[i], end);
        if (arr[i] < end)
        {
            remove++;
        }
        else
        {
            end = arr[i] + l;
        }
    }

    printf("%d", n - remove);

    free(arr);
}