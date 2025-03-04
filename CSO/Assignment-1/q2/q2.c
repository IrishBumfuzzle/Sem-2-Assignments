#include <stdio.h>

void rot_by_two(long long n, long long a[], long long new[]);

int main()
{
    long long n;
    scanf("%lld", &n);
    long long a[n];
    for (long long i = 0; i < n; i++)
    {
        scanf("%lld", &a[i]);
    }
    long long new[n];

    rot_by_two(n, a, new);
    for(long long i = 0; i < n; i++)
    {
        printf("%lld ", new[i]);
    }
}
