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


void merge_files(int **Array){
    FILE *file;
    file = fopen("result.txt", "w");

}

void sort_files(int argc,char *argv[]){

    if(argc < 2){
        perror("input files");
        exit(1);
    }

    int **array;

    array = (int **)malloc(sizeof(int*) * 20);

    for(int i =0; i < 20; i++){
        array[i] =(int *) malloc(20000*sizeof(int*));
    }

    FILE *fdarr[argc];

    for(int i =0 ; i< argc-1; i++){
        if((fdarr[i]= fopen(argv[i+1], "r")) == NULL){
            perror("FILE");
            exit(1);
        }

        int num;

        for(int j=0;fscanf(fdarr[i], "%d", &num)!= EOF;j++){
            array[i][j] = num;
        }
        merge_sort(array[i],0,SIZE-1);




        fclose(fdarr[i]);



        if((fdarr[i]= fopen(argv[i+1], "w")) == NULL ){
            perror("FILE2");
            exit(1);
        }
        if(fseek(fdarr[i],0,SEEK_SET)!= 0){
            perror("fseeek");
            exit(1);
        }




        for(int j=0; j < SIZE; j++){
            fprintf(fdarr[i], "%d ", array[i][j]);
        }

        fclose(fdarr[i]);
        free(array[i]);
    }


}

void temp_sort_files(int argc,char *argv[]){

    if(argc < 2){
        perror("input files");
        exit(1);
    }
    int **array;

    array = malloc(argc* sizeof(int));
    for(int i =0; i < argc-1; i++){
        array[i] = malloc(SIZE*sizeof(int));
    }

    FILE *fdarr[argc];


    if((fdarr[1]= fopen(argv[1], "r")) == NULL){
        perror("FILE");
        exit(1);
    }
    int num;

    for(int j=0;fscanf(fdarr[1], "%d", &num)!= EOF;j++){
        array[1][j] = num;
    }

    merge_sort(array[1],0,SIZE-1);


    fclose(fdarr[1]);

    if((fdarr[1]= fopen(argv[1], "w")) == NULL){
        perror("FILE");
        exit(1);
    }

    if(fseek(fdarr[1],0,SEEK_SET)!= 0){
            perror("fseeek");
            exit(1);
        }

    for(int j=0; j <SIZE; j++){
            fprintf(fdarr[1], "%d ", array[1][j]);
        }


    for(int i =0; i < SIZE-1; i++){
        printf("%d ", array[1][i]);
        if (array[1][i] > array[1][i+1]){
            puts("ERROR");
            exit(1);
        }
    }


        fclose(fdarr[1]);




}


int main(int argc, char *argv[]) {

    sort_files(argc,argv);

    return 0;
}
