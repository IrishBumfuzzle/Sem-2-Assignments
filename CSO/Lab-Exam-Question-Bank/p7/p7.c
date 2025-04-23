#include <stdio.h>
#include <stdlib.h>

long long special(long long a);
long long factorial(long long n);

int main(){
    long long a;
    scanf("%lld", &a);

    long long result = special(a);
    if(result == 0){
        printf("FALSE");
    } else {
        printf("TRUE");
    }
}
