#include <stdio.h>
#include <stdlib.h>

long long comb(long long n, long long r);

int main()
{
    long long n, r;
    scanf("%lld", &n);
    scanf("%lld", &r);
    long long result = comb(n, r);
    printf("%lld\n", result);
}