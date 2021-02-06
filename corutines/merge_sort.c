#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define SIZE 10000

void bubble_sort(int *A, int size)
{
    for(int i = 0; i < size -1; i++){
        for(int j = 0; j < size-i-1;j++){
            if(A[j] > A[j+1]){
                int temp = A[j];
                A[j] = A[j+1];
                A[j+1] = temp;
            }
        }
    }
}

void merge(int *A, int mid, int l,int r){

    int start, final, j;
    int massize = r-l+1;
    if(massize <=1){
        massize = 3;
    }

    start = l;
    final = mid+1;

    int *temparray = malloc(massize * sizeof(int));
/*
    for(int i =0; i < r-l+1; i++){
        if((start <=mid) && ((final> r) || (A[start] < A[final]))){
            temparray[i] = A[start];
            start++;
        } else{
            temparray[i] = A[final];
            final++;
        }

    }
*/
    for(int i =0,first = l,second=mid+1;i < r-l + 1; i++){
        if(second > r){
            temparray[i] = A[first];
            first++;
        }else if(first >mid){
            temparray[i] = A[second];
            second++;
        }else if(A[first] < A[second]){
            temparray[i] = A[first];
            first++;
        }else{
            temparray[i] = A[second];
            second++;
        }
    }
/*
    printf("%d %d %d   ",l,mid , r);
    for(int i =0; i < r-l+1; i++){
        printf("%d ",temparray[i]);
    }
    puts("\n");
*/

    for(int i = 0, f=l; i < r-l+1; i++, f++){
        A[f] = temparray[i];
    }
    free(temparray);

}

void merge_sort(int *A,int l, int r){
    if(l < r){
        int mid = (l+r)/2;
        merge_sort(A,l, mid);
        merge_sort(A, mid+1, r);
        merge(A,mid,l,r);
    }
}


int *array;


int main(int argc, char *argv[]) {

    array = malloc(SIZE * sizeof(int));

    if(argc < 2){
        perror("input files");
        exit(1);
    }

    int num;
    FILE *file = fopen(argv[1], "r");


    for(int i=0;fscanf(file, "%d", &num)!= EOF;i++){
        array[i] = num;
    }

  //  int garray[] = {9,2,3,1,8,77,90};

    merge_sort(array,0,SIZE -1);

    for(int i =0; i < SIZE-1; i++){
    //    printf("%d ", array[i]);
        if (array[i] > array[i+1]){
            puts("ERROR");
            exit(1);
        }
    }

    fclose(file);

    file = fopen("result.txt", "w");
    for (int i =0; i<SIZE; i++) {
        fprintf(file, "%d ",array[i]);
    }

    fclose(file);
    return 0;
}
