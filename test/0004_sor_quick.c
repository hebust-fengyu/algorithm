#include<stdio.h>
#include<stdlib.h>
#include<time.h>


#define MAX_LEN 20

void print(int *arr, char *str){
    printf("%s\n", str);
    for(int i = 0; i < MAX_LEN; ++i){
        printf("%d,",arr[i]);
    }
    printf("\n");
}

int partition(int *arr, int beg, int end){
    int i = beg - 1;
    int x = arr[end - 1];
    int tmp;
    while(beg < end){
        if(arr[beg] < x){
            tmp = arr[beg];
            arr[beg] = arr[++i];
            arr[i] = tmp;
        }
        ++beg;
    }
    tmp = arr[++i];
    arr[i] = arr[end - 1];
    arr[end - 1] = tmp;
    return i;
}



void quick_sort(int *arr, int beg, int end){
    int index = 0;
    if(beg < end){
        index = partition(arr, beg, end);
        quick_sort(arr, beg, index);
        quick_sort(arr, index + 1, end);
    }
}


int main(void){
    int array[MAX_LEN] = {0};
    srand(time(0));
    for(int i = 0; i < MAX_LEN; ++i){
        array[i] = rand() / (RAND_MAX / 100);
    }
    print(array, "before the quick_sort is :");
    quick_sort(array, 0, MAX_LEN);
    print(array, "after the quick_sort is :");

}