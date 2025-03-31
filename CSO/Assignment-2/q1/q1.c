#include <stdio.h>
#include <stdlib.h>

long long int subarray_sum(long long *arr, long long n);

int main()
{
    long long n;
    scanf("%d", &n);
    long long *arr = malloc(sizeof(long long) * n);
    for (int i = 0; i < n; i++)
    {
        scanf("%lld", &arr[i]);
    }

    long long result = subarray_sum(arr, n);

    printf("%lld\n", result);
    free(arr);
}