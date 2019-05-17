#include<stdio.h>
#include<stdlib.h>
#include<math.h>


#define MAX_SIZE 10

void print(int* pArray, int size, char* c){
	printf("%s",c);
	for(int i = 0; i < size; ++i){
		printf("%d,",pArray[i]);
	}
}


int get_max_index(int* pArray, int size){
	int index = 0;
	for(int i = 1; i < size; ++i){
		if(pArray[i] > pArray[index])
			index = i;
	}
	return index;
}


void sort_bubble(int* pArray, int size){
	int tmp, tmp_index;
	for(;size;--size){
		tmp_index = get_max_index(pArray,size);
		tmp = pArray[tmp_index];
		pArray[tmp_index] = pArray[size - 1];
		pArray[size - 1] = tmp;
	}
}
		

int main(void){
	int array[MAX_SIZE];
	srand(100);
	for(int i = 0; i < MAX_SIZE; ++i){
		array[i] = rand() * 100 / RAND_MAX;
	}
	print(array, MAX_SIZE, "before sort_bubble is:\n");
	sort_bubble(array, MAX_SIZE);
	print(array, MAX_SIZE, "after sort_bubble is: \n");
}
	