#include <stdio.h>
#include <stdlib.h>

void doSomething(long long arr[], int n);

int main(){
    int n;
    scanf("%d", &n);
    long long arr[n+1];
    doSomething(arr, n);
    for(int i = 1; i <= n; i++){
        printf("%lld ", arr[i]);
    }
}