#include <stdio.h>
#include <stdlib.h>

long long find(long long arr[], long long start, long long end, long long val);

int main(){
    long long n;
    scanf("%lld", &n);

    long long arr[n];
    for (long long i = 0; i < n; i++){
        scanf("%lld", &arr[i]);
    }
    long long val;
    scanf("%lld", &val);
    long long ans = find(arr, 0, n, val);
    printf("%lld", ans);
}