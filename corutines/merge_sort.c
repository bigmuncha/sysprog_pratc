#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define SIZE 10000

void merge_sort(int *A, int size)
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

    merge_sort(array, SIZE);

    for(int i =0; i < SIZE-1; i++){
        printf("%d ", array[i]);
        if (array[i] > array[i+1]){
            puts("ERROR");
            exit(1);
        }
    }

    return 0;
}
