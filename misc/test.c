#include<string.h>
#include<stdio.h>
int main(void){
    int i[2] = {1,11};
    int j = 0;
    printf("%p,%p,%p,%p",&i[1],i+1,((void*)i)+1,((void*)i)+sizeof(int));
    memcpy(&j, i+1,sizeof(int));
    printf("\n%d,%d",i[1],j);
}