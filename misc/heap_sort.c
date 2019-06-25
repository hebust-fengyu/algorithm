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



void max_heap(int* pArray, int size, int index){
    int large;
    int left = (index+1)*2-1;
    int right = (index+1)*2;
    if(left < size && pArray[left] > pArray[index])
        large = left;
    else large = index;
    if(right < size && pArray[right] > pArray[large])
        large = right;
    if(large!=index){
        int tmp = pArray[large];
        pArray[large]=pArray[index];
        pArray[index]=tmp;
        max_heap(pArray, size, large);
    }
}


void build_heap(int* pArray, int size){
    for(int i  = size / 2 - 1; i >= 0; --i){
        max_heap(pArray, size, i);
    }
}


void sort_heap(int* pArray, int size){
    build_heap(pArray, size);
    while(size){
        int tmp = pArray[0];
        pArray[0]=pArray[size-1];
        pArray[size-1]=tmp;
        max_heap(pArray, --size, 0);
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
		
		
