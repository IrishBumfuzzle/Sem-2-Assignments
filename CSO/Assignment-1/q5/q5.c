#include <stdio.h>

void prod(long long n, long long a[], long long b[]);

int main()
{
    long long n;
    scanf("%lld", &n);
    long long a[n], b[n];
    for (long long i = 0; i < n; i++)
    {
        scanf("%lld", &a[i]);
    }
    prod(n, a, b);
    for (long long i = 0; i < n; i++)
    {
        printf("%lld ", b[i]);
    }
}
