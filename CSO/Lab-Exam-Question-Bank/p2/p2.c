#include <stdio.h>
#include <stdlib.h>

long long palin(char number[]);

int main(){
    char number[50];
    scanf("%s", number);
    if(palin(number)){
        printf("TRUE\n");
    } else {
        printf("FALSE\n");
    }
}