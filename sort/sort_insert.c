#include<stdio.h>
#include<stdlib.h>
#include<math.h>

#define MAX_LEN 20

void print(int* pArray, int size, char* c){
	printf("%s\n", c);
	for(int i = 0; i < size; ++i){
		printf("%d,",pArray[i]);
	}
}

void change_array(int* pArray, int begin, int end){
	int tmp = pArray[end];
	for(int i = end; i != begin; --i){
		pArray[i] = pArray[i - 1];
	}
	pArray[begin] = tmp;
}
	



void insert(int *pArray, int size, int index){
	for(int i = 0; i < index; ++i){
		if(pArray[i] < pArray[index]) change_array(pArray, i, index);
	}
}


void sort_insert(int* pArray, int size){
	for(int i = 1; i < size; ++i){
		insert(pArray, size, i);
	}
}
		


int main(void){
	int array[MAX_LEN];
	srand(10);
	for(int i = 0; i < MAX_LEN; ++i){
		array[i] = rand() * 100 / RAND_MAX;
	}
	print(array, MAX_LEN, "before sort_insert is:\n");
	sort_insert(array, MAX_LEN);
	print(array, MAX_LEN, "after sort_insert is:\n");
}
	