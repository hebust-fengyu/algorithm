#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include <string.h>
#include <limits.h>

#define MAX_LEN 30

void print(int arr[], char *c)
{
    printf("%s\n", c);
    for (int i = 0; i < MAX_LEN; ++i)
    {
        printf("%d,", arr[i]);
    }
    printf("\n");
}

/*
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
*/

void merge(int *pArray, int beg, int sep, int end)
{
    int fir = sep - beg + 1;
    int second = end - sep;

    int *fir_arr = (int *)malloc(sizeof(int) * (fir + 1));
    int *second_arr = (int *)malloc(sizeof(int) * (second + 1));
    // for (int i = 0; i < fir; ++i)
    // {
    //     fir_arr[i] = pArray[beg + i];
    // }
    // for (int i = 0; i< second; ++i)
    // {
    //     second_arr[i] = pArray[sep + i + 1];
    // }
    memcpy(fir_arr, pArray + beg, fir*sizeof(int));
    memcpy(second_arr, pArray + (sep + 1), second*sizeof(int));

    fir_arr[fir] = INT_MAX;
    second_arr[second] = INT_MAX;
    int fir_index = 0, sec_index = 0;
    for (int i = beg; i <= end; ++i)
    {
        pArray[i] = fir_arr[fir_index] < second_arr[sec_index] ? fir_arr[fir_index++] : second_arr[sec_index++];
    }

    free(fir_arr);
    free(second_arr);
}

void sort_merge(int *pArray, int beg, int end)
{
    if (beg < end)
    {
        int sep = (beg + end) / 2;
        sort_merge(pArray, beg, sep);
        sort_merge(pArray, sep + 1, end);
        merge(pArray, beg, sep, end);
    }
}

int main(void)
{
    srand(time(0));
    int array[MAX_LEN] = {0};
    for (int i = 0; i < MAX_LEN; ++i)
    {
        array[i] = rand() / (RAND_MAX / 100);
    }
    print(array, "before sort_merge is:");
    sort_merge(array, 0, MAX_LEN - 1);
    print(array, "after sort_merge is:");
    return 0;
}
