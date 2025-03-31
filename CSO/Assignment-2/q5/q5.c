#include <stdio.h>
#include <stdlib.h>

short peak(short *nums, long long n);

int main(){
    long long n;
    scanf("%lld", &n);
    short *arr = (short *)malloc(n * sizeof(short));
    for(int i = 0; i < n; i++){
        scanf("%hd", &arr[i]);
    }
    short result = peak(arr, n);
    printf("%hd\n", result);
}