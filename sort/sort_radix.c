#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>


#define MAX_LEN 30

#define MAX_RADIX 10


void sort_value(int arr[], int dst[]) {
	int index_arr[RAND_MAX] = { 0 };
	int tmp_arr[MAX_LEN];
	memcpy(tmp_arr, arr, MAX_LEN * sizeof(int));
	for (int i = 0; i < MAX_LEN; ++i) {
		index_arr[dst[i]] += 1;
	}
	for (int i = 1; i < MAX_LEN; ++i) {
		index_arr[i] += index_arr[i - 1];
	}
	for (int i = MAX_LEN; i; --i) {
		arr[index_arr[dst[i - 1]] - 1] = tmp_arr[i - 1];
		index_arr[dst[i - 1]] -= 1;
	}
}

void set_radix_value(int arr[],int dst[], int len) {
	int tmp_arr[MAX_LEN] = { 0 };
	int div = pow(10, len);
	int inter;
	memcpy(tmp_arr, arr, MAX_LEN * sizeof(int));
	for (int i = 0; i < MAX_LEN; ++i) {
		inter = arr[i];
		inter /= div;
		dst[i] = inter % 10;
	}
}

void print(int arr[], char *c) {
	printf("%s\n", c);
	for (int i = 0; i < MAX_LEN; ++i) {
		printf("%d,", arr[i]);
	}
	printf("\n");
}

int get_max_value(int arr[]) {
	int tmp = arr[0];
	for (int i = 1; i < MAX_LEN; ++i) {
		if (arr[i] > tmp) tmp = arr[i];
	}
	return tmp;
}

int get_radix(int arr[]) {
	int tmp = get_max_value(arr);
	int len = 0;
	for (; tmp; ++len, tmp /= 10);
	return len;
}

void sort_radix(int arr[]) {
	int arr_radix[MAX_LEN] = { 0 };
	int radix_len = get_radix(arr);
	for (int i = 0; i < radix_len; ++i) {
		set_radix_value(arr, arr_radix, i);
		sort_value(arr, arr_radix);
	}
	
}


int main(void) {
	srand(time(0));
	int array[MAX_LEN] = { 0 };
	for (int i = 0; i < MAX_LEN; ++i) {
		array[i] = rand() / (RAND_MAX / 1000);
	}
	print(array, "before sort_radix is:");
	sort_radix(array);
	print(array, "after sort_radix is:");
	return 0;
}