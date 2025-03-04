#include <stdio.h>

long long calc(long long n, long long a[]);

int main()
{
    long long n;
    scanf("%lld", &n);
    long long a[3*n+1];
    for (long long i = 0; i < 3*n+1; i++)
    {
        scanf("%lld", &a[i]);
    }
    printf("%lld", calc(3*n+1, a));
}
