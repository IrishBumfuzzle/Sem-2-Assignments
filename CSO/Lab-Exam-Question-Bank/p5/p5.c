#include <stdio.h>
#include <stdlib.h>

void unique(long long arr[], long long n, long long result[], long long *size);

int main(){
    int n;
    scanf("%d", &n);

    long long arr[n];
    long long result[n];
    long long size = 0;
    for(int i = 0; i < n; i++){
        scanf("%lld", &arr[i]);
    }
    unique(arr, n, result, &size);
    for(int i = 0; i < size; i++){
        printf("%lld ", result[i]);
    }
}