#include <stdio.h>
#include <stdlib.h>

long long majority(long long* arr, long long n);

int main(){
    long long n;
    scanf("%lld", &n);

    long long* arr = malloc(n * sizeof(long long));
    for(int i = 0; i < n; i++){
        scanf("%lld", &arr[i]);
    }

    long long result = majority(arr, n);
    printf("%lld\n", result);
    free(arr);
}