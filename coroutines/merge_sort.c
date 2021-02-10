#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


/*временная функция*/
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

/*обычное слияние*/
void merge(int *A, int l, int mid, int r){
    int massize = r-l+1;
    if(massize <=1){
        massize = 3;
    }

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
/*сортировка слиянием кормен стайл*/
void merge_sort(int *A,int l, int r){
    if(l < r){
        int mid = (l+r)/2;
        merge_sort(A,l, mid);
        merge_sort(A, mid+1, r);
        merge(A,l,mid,r);
    }
}

/*слияние отсортированных файлов в ресулт.тхт*/
void merge_files(int **Array,int *size_arrays,int len_size_arrays){

    FILE *file;
    file = fopen("result.txt", "w");

    size_t result_size=0;

    /*вычисление конечного размера */
    for(int i=0;i<len_size_arrays;i++){
        result_size+=size_arrays[i];
    }
    int *result_array = (int *) malloc(sizeof(int *)* result_size);


    /*заполение массива отсортированными массивами*/
    for(int i=0, index =0; i < len_size_arrays; i++){
        for(int j=0;j < size_arrays[i]; j++){
            result_array[index] = Array[i][j];
            index++;
        }
    }

    /*cлияние отсортированных массивов в нормальный отсортированный массив*/
    int mid=0, right=size_arrays[0];
    for(int i=0; i< len_size_arrays-1;i++){
        mid+=size_arrays[i];
        right+= size_arrays[i+1];
        merge(result_array,0,mid-1,right-1);
    }
    /*запись результата*/
    for(int i=0; i < result_size; i++){
        fprintf(file,"%d ",result_array[i]);
    }
    free(result_array);
    fclose(file);

}

void sort_files(int argc,char *argv[]){

    if(argc < 2){
        perror("input files");
        exit(1);
    }

    int num_files = argc-1;
    int **array;
    int size_arrays[num_files];
    FILE *fdarr[num_files];

    for(int i=0; i < num_files;i++){
        /*открываю файл*/
        if((fdarr[i]= fopen(argv[i+1], "r")) == NULL){
            perror("FILE");
            exit(1);
        }
        /*считаю количество элементов*/
        int number;
        for(int j=0; fscanf(fdarr[i],"%d",&number)!=EOF; j++){
            size_arrays[i] = j;
        }
        /*смещаю офсет в начало*/
        if(fseek(fdarr[i],0,SEEK_SET)!= 0){
            perror("fseeek");
            exit(1);
        }
    }
    /*выделяю память под все файлы*/
    array = (int **)malloc(sizeof(int*) *num_files);
    for(int i =0; i < num_files; i++){
        array[i] =(int *) malloc(size_arrays[i]*sizeof(int*));
    }

    /*сортирую каждый файл отдельно*/
    for(int i =0 ; i< num_files; i++){

        int num;
        /*закидываю содержимое файла в массив*/
        for(int j=0;fscanf(fdarr[i], "%d", &num)!= EOF;j++){
            array[i][j] = num;
        }
        /*сортировка массива*/
        merge_sort(array[i],0,size_arrays[i]-1);

        /*закрытие фала и последующее открытие с опцией w для перезаписи*/
        fclose(fdarr[i]);
        if((fdarr[i]= fopen(argv[i+1], "w")) == NULL ){
            perror("FILE2");
            exit(1);
        }
        /*запись в файл*/
        for(int j=0; j < size_arrays[i]; j++){
            fprintf(fdarr[i], "%d ", array[i][j]);
        }
        /*закрытие файлов*/
        fclose(fdarr[i]);
        //free(array[i]);
    }
    merge_files(array, size_arrays,num_files);
    /*освобождение памяти*/
    for(int i=0; i<num_files;i++){
        free(array[i]);
    }
    free(array);
}

int main(int argc, char *argv[]) {

    sort_files(argc,argv);

    return 0;
}
