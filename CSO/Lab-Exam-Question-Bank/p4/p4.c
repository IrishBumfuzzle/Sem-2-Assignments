#include <stdio.h>
#include <stdlib.h>

long long summation(long long (*a)[], long long n, long long m);

int main(){
    long long n, m;
    scanf("%lld %lld", &n, &m);
    long long a[n][m];
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            scanf("%lld", &a[i][j]);
        }
    }
    long long result = summation(a, n, m);
    printf("%lld", result);
}
