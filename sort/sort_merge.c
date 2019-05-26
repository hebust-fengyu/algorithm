#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<assert.h>
#include<string.h>

#define MAX_LEN 30


void print(int arr[], char *c){
    printf("%s\n", c);
    for(int i = 0; i < MAX_LEN; ++i){
        printf("%d,", arr[i]);
    }
    printf("\n");
}

int sort_merge(int arr[], int beg, int end){
    assert(beg <= end);
    if(end - beg == 1) return 0;
	int mid = (beg + end) / 2;
    sort_merge(arr, beg, mid);
    sort_merge(arr, mid, end);
    int *parr = (int *)malloc(sizeof(int) * (end - beg));
    memset(parr, 0, sizeof(int) * (end - beg));
    const int sep = mid, begin = beg;
    int index = 0;
    while(beg < sep && mid < end){
        if(arr[beg] < arr[mid]){
            parr[index++] = arr[beg++];
        }
        else{
            parr[index++] = arr[mid++];
        }
    }
    while(beg < sep){
        parr[index++] = arr[beg++];
    }
    while(mid < end){
        parr[index++] = arr[mid++];
    }
    memmove(&arr[begin], parr, sizeof(int) * (end - begin));    
}


int main(void){
    srand(time(0));
    int array[MAX_LEN] = {0};
    for(int i = 0; i < MAX_LEN; ++i){
        array[i] = rand() / (RAND_MAX / 100);
    }
    print(array, "before sort_merge is:");
    sort_merge(array, 0, MAX_LEN);
    print(array, "after sort_merge is:");
}