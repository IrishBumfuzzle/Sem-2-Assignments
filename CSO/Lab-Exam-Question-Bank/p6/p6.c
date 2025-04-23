#include <stdio.h>
#include <stdlib.h>

long long duplicate(long long arr[], long long n);

int main(){
    long long n;
    scanf("%lld", &n);

    long long arr[n];
    for (long long i = 0; i < n; i++){
        scanf("%lld", &arr[i]);
    }
    long long result = duplicate(arr, n);
    if(result == 1){
        printf("TRUE");
    }
    else{
        printf("FALSE");
    }

}