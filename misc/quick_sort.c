#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_LEN 20

void print(int *arr, char *str)
{
    printf("%s\n", str);
    for (int i = 0; i < MAX_LEN; ++i)
    {
        printf("%d,", arr[i]);
    }
    printf("\n");
}

void change_value(int *pArray, int src, int dst)
{
    int tmp = pArray[src];
    pArray[src] = pArray[dst];
    pArray[dst] = tmp;
}

int separation(int *pArray, int beg, int end)
{
    int index = beg;
    while (beg < end)
    {
        if (pArray[beg] < pArray[end])
        {
            change_value(pArray, index++, beg);
        }
        ++beg;
    }
    change_value(pArray, index, end);
    return index;
}

void quick_sort(int *pArray, int beg, int end)
{
    if (beg < end)
    {
        int sep = separation(pArray, beg, end);
        quick_sort(pArray, beg, sep-1);
        quick_sort(pArray, sep + 1, end);
    }
}

int main(void)
{
    int array[MAX_LEN] = {0};
    srand(time(0));
    for (int i = 0; i < MAX_LEN; ++i)
    {
        array[i] = rand() / (RAND_MAX / 100);
    }
    print(array, "before the quick_sort is :");
    quick_sort(array, 0, MAX_LEN - 1);
    print(array, "after the quick_sort is :");
}