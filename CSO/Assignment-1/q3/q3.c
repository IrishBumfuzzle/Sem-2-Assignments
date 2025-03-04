#include <stdio.h>
#include <string.h>

long long palin(long long n, char str[]);

int main()
{
    char str[1000];
    scanf("%s", str);

    long long r = palin(strlen(str), str);
    printf("%lld\n", r);
}
