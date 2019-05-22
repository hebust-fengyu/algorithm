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

void sort_count(int arr[]){
    int index[RANDOM_RAGNE] = {0};
    int tmp_arr[ARR_MAX_LEN];
    memcpy(tmp_arr, arr, sizeof(int) * ARR_MAX_LEN);

    for(int i = 0; i < ARR_MAX_LEN; ++i){
        index[arr[i]] += 1;
    }
    for(int i = 1; i < RANDOM_RAGNE; ++i){
        index[i] += index[i - 1];
    }
    for(int i = ARR_MAX_LEN; i; --i){
        arr[index[tmp_arr[i - 1]] - 1] = tmp_arr[i - 1];
        index[tmp_arr[i - 1]] -= 1;
    }
}




int main(void){
    int array[ARR_MAX_LEN];
    srand(time(0));
    for(int i = 0; i < ARR_MAX_LEN; ++i){
        array[i] = rand() / (RAND_MAX / RANDOM_RAGNE);
    }
    print(array, "before sort_count is:");
    sort_count(array);
    print(array, "after sort_count is:");
}
