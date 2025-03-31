#include <stdio.h>
#include <stdlib.h>

void marks(long long *input, long long *ans, long long n);

int main(){
    long long n;
    scanf("%lld", &n);
    long long *input = (long long *)malloc(n * sizeof(long long));
    long long *ans = (long long *)malloc(n * sizeof(long long));
    for(long long i = 0; i < n; i++){
        scanf("%lld", &input[i]);
    }
    marks(input, ans, n);
    for(long long i = 0; i < n; i++){
        printf("%lld ", ans[i]);
    }
    printf("\n");
}