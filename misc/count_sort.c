#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>


#define ARR_MAX_LEN 40
#define RANDOM_RAGNE 30


void print(int arr[], char *c){
    printf("%s\n",c);
    for(int i = 0; i < ARR_MAX_LEN; ++i){
        printf("%d,", arr[i]);
    }
    printf("\n");
}

int max_value(int* pArray, int max_size){
    int max = pArray[0];
    for(int i =1;i < max_size;++i)
        max = pArray[i] > max ? pArray[i] : max;
    return max; 
}


void sort_count(int* pArray, int size){
    if(size == 0) return;
    int max = max_value(pArray, size);
    int* count_arr = (int*)malloc(sizeof(int)*(max+1));
    int* tmp_arr = (int*)malloc(sizeof(int)*size);
    memcpy(tmp_arr, pArray, sizeof(int)*size);
    memset(count_arr, 0, sizeof(int)*(max+1));
    for(int i=0; i<size;++i){
        count_arr[pArray[i]]+=1;
    }
    for(int i =0;i<max+1;++i){
        count_arr[i+1]+=count_arr[i];
    }
    for(int i = 0;i<size;++i){
        pArray[count_arr[tmp_arr[i]]-1] =tmp_arr[i];
        count_arr[tmp_arr[i]]-=1; 
    }
}



int main(void){
    int array[ARR_MAX_LEN];
    srand(time(0));
    for(int i = 0; i < ARR_MAX_LEN; ++i){
        array[i] = rand() / (RAND_MAX / RANDOM_RAGNE);
    }
    print(array, "before sort_count is:");
    sort_count(array, ARR_MAX_LEN);
    print(array, "after sort_count is:");
}
