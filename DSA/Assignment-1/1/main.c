#include <stdio.h>
#include <stdlib.h>

int cmpfunc(const void *a, const void *b)
{
    return *(int *)a > *(int *)b;
}

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
    int n;
    scanf("%d", &n);
    int *arr = (int *)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &arr[i]);
    }
    int dist;
    scanf("%d", &dist);

    int min_diff = __INT_MAX__;
    int a, b;

    mergeSort(0, n - 1, arr);

    int ahead = 0, back = n - 1;
    while (ahead < back)
    {
        if (abs(dist - (arr[ahead] + arr[back])) < min_diff)
        {
            min_diff = abs(dist - (arr[ahead] + arr[back]));
            a = arr[ahead];
            b = arr[back];
        }
        else if (abs(dist - (arr[ahead] + arr[back])) == min_diff)
        {
            if (abs(arr[ahead] - arr[back]) < abs(a - b))
            {
                a = arr[ahead];
                b = arr[back];
            }
        }
        if (arr[ahead] + arr[back] < dist)
        {
            ahead++;
        }
        else if (arr[ahead] + arr[back] > dist)
        {
            back--;
        }
        else
        {
            ahead++;
            back--;
        }
    }

    printf("%d %d", a, b);
    free(arr);
}