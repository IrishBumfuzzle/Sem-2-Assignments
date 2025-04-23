#include <stdio.h>
#include <stdlib.h>

void wave(long long a[], long long n);

int main(){
    long long n;
    scanf("%lld", &n);
    long long a[n];
    for (long long i = 0; i < n; i++){
        scanf("%lld", &a[i]);
    }
    wave(a, n);
    for (long long i = 0; i < n; i++){
        printf("%lld ", a[i]);
    }
}