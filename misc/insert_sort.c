#include<stdio.h>
#include<string.h>
#include<time.h>
#include<stdlib.h>

#define MAX_LEN 20


void print(int* pArray, int size, char* s){
    printf("%s\n", s);
    for(int i = 0; i < size; ++i)
        printf("%d,",pArray[i]);
    printf("\n");
}

void sort_insert(int *pArray, int size){
    for(int i = 1; i < size; ++i){
        int key = pArray[i];
        int j = i - 1;
        for(; j > -1 && pArray[j] > key; --j){
            pArray[j+1] = pArray[j];
        }
        pArray[j+1] = key;
    }
}


int main(void){
	int arr[MAX_LEN];
	memset(arr, 0, sizeof(arr));
	srand(time(0));
	for(int i = 0; i < MAX_LEN;++i){
        arr[i] = rand()%20;
    }
    print(arr, MAX_LEN, "array before insert is:");
    sort_insert(arr, MAX_LEN);
    print(arr, MAX_LEN, "array after insert is:");
}

	