#include <stdio.h>
#include <stdlib.h>

long long rotation(long long n, long long d);

int main(){
    int n, d;
    scanf("%d %d", &n, &d);
    long long result = rotation(n, d);
    if(result == 1){
        printf("TRUE\n");
    }
    else{
        printf("FALSE\n");
    }

}