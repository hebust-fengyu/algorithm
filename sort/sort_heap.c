#include<stdio.h>
#include<stdlib.h>
#include<math.h>


#define MAX_LEN 20



void print(int* pArray, int size, char* c){
	printf("%s",c);
	for(int i = 0; i < size; ++i){
		printf("%d,",pArray[i]);
	}
}

void max_heap(int *pArray, int index, int size){
	int left_index = (index + 1) * 2 - 1;
	int right_index = (index + 1) * 2;
	int large;
	if(left_index < size && pArray[index] < pArray[left_index]){
		large = left_index;
	}
	else{
		large = index;
	}
	if(right_index < size && pArray[large] < pArray[right_index]){
		large = right_index;
	}
	
	if(large != index){
		int tmp = pArray[large];
		pArray[large] = pArray[index];
		pArray[index] = tmp;
		max_heap(pArray, large, size);
	}
}



void build_max_heap(int* pArray, int max){
	for(int i = ceil(max) / 2 - 1; i >= 0 ; --i){
		max_heap(pArray, i, max);
	}
}

void sort_heap(int* pArray, int max){
	int tmp = 0;
	build_max_heap(pArray, max);
	for(; max; ){
		tmp = pArray[0];
		pArray[0] = pArray[max-1];
		pArray[max-1] = tmp;
		max_heap(pArray, 0, --max);
	}
}




int main(void){
	int array[MAX_LEN];
	srand(100);
	for(int i = 0; i < MAX_LEN; ++i){
		array[i] = rand() * 100 / RAND_MAX;
	}
	print(array, MAX_LEN, "before sortheap is:\n");
	sort_heap(array, MAX_LEN);
	print(array, MAX_LEN, "\nafter sort_heap is:\n");
}
		
		
