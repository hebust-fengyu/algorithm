#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>


#define MAX_LEN 30

#define MAX_RADIX 10



void print(int arr[], char *c) {
	printf("%s\n", c);
	for (int i = 0; i < MAX_LEN; ++i) {
		printf("%d,", arr[i]);
	}
	printf("\n");
}

int max_value(int* pArray, int size){
    int max = pArray[0];
    for(int i = 1; i < size;++i)
        max = pArray[i] > max ? pArray[i]:max;
    return max;
}

int get_len(int num){
    if(num == 0) return 1;
    int index = 0;
    while(num){
        num/=10;
        ++index;
    }
    return index;
}

void set_value(int* arr, int num){
    int i = 0;
    while(num){
        arr[i++] = num%10;
        nums/=10;
    }
}

void sort(int* pArray, int** arr, i){
    for(int i = 0; i < size; ++i){
        
    }
}

void sort_radix(int* pArray, int size){
    if(size==0)return;
    int max = max_value(pArray, size);
    int len = get_len(max);
    int* arr[size] = (int*[size])malloc(sizeof(int)*len*size);
    memset(arr, 0, sizeof(int)*len*size);
    for(int i = 0; i < size; ++i){
        set_value(arr[i], pArray[i]);
    }
    for(int i=0;i < len;++i){
        sort(pArray, arr, i);
    }
}

int main(void) {
	srand(time(0));
	int array[MAX_LEN] = { 0 };
	for (int i = 0; i < MAX_LEN; ++i) {
		array[i] = rand() / (RAND_MAX / 1000);
	}
	print(array, "before sort_radix is:");
	sort_radix(array, MAX_LEN);
	print(array, "after sort_radix is:");
	return 0;
}