#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>


#define MAX_LEN 30
#define BUCKET_LEN 10

typedef struct tag_bucket
{
    float val;
    struct tag_bucket *next;
}bucket;

typedef struct tag_bk_header{
    bucket *head;
}bk_header;

void print(float *arr, char *c);
void sort_bucket(float *arr);
int make_bucket(float val, int pos, bk_header pbk[]);

int main(void){
    srand(time(0));
    float array[MAX_LEN] = {0};
    for(int i = 0; i < MAX_LEN; ++i){
        array[i] =(float) rand() / RAND_MAX;
    }
    print(array, "before sort_bucket is:");
    sort_bucket(array);
    print(array, "after sort_bucket is:");
}


void sort_bucket(float *arr){
	bk_header bk_array[BUCKET_LEN];
	for (int i = 0; i < BUCKET_LEN; ++i) {
		bk_array[i].head = NULL;
	}
    bucket *tmp;
    int index = 0;
    for(int i = 0; i < MAX_LEN; ++i){
        make_bucket(arr[i], floor(arr[i] * 10), bk_array);
    }
    for(int i = 0; i < BUCKET_LEN; ++i){
        tmp = bk_array[i].head;
        while(tmp){
			printf("%d,",index);
            arr[index++] = tmp->val;
            tmp = tmp->next;
        }   
    }
}

void print(float *arr, char *c){
    printf("%s\n", c);
    for(int i = 0; i < MAX_LEN; ++i){
        printf("%f,", arr[i]);
    }
    printf("\n");
}

int make_bucket(float val, int pos, bk_header pbk[]){
    if(pbk[pos].head == NULL){
        pbk[pos].head = (bucket *)malloc(sizeof(bucket));
        pbk[pos].head->val = val;
		pbk[pos].head->next = NULL;
    }
    else{
        bucket *tmp;
        tmp = pbk[pos].head;
        if(pbk[pos].head->val >= val){
            pbk[pos].head = (bucket *)malloc(sizeof(bucket));
            pbk[pos].head->val = val;
            pbk[pos].head->next = tmp;
        }
        else{
            bucket *bk_tmp = tmp;
            while(bk_tmp->next){
                if(bk_tmp->next->val >= val){
                    tmp = bk_tmp->next;
                    bk_tmp->next = (bucket *)malloc(sizeof(bucket));
                    bk_tmp->next->val = val;
                    bk_tmp->next->next = tmp;
                    return 0;
                }
                bk_tmp = bk_tmp->next;
            }
			bk_tmp->next = (bucket*)malloc(sizeof(bucket));
			bk_tmp->next->val = val;
			bk_tmp->next->next = NULL;
        }
    }
    return 0;
}