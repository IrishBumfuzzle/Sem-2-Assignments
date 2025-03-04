#include <stdio.h>

long long diff(long long n, long long a[]);

int main()
{
    long long n;
    scanf("%lld", &n);
    long long a[n];
    for(long long i = 0; i < n; i++)
    {
        scanf("%lld", &a[i]);
    }
    long long di = diff(n, a);
    printf("%lld\n", di);
    
}
