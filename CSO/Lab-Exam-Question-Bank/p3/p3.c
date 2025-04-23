#include <stdio.h>
#include <stdlib.h>

long long score(char s[]);

int main(){
    char s[150];
    scanf("%s", s);
    long long result = score(s);
    printf("%lld\n", result);
}   
