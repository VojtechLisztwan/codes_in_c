#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>


void printArray(int pole[], int n){
    printf("Pole je [");
    for (int i = 0; i < n-1; i++){
        printf("%d, ", pole[i]);
    }
    printf("%d ", pole[n-1]);
    

    printf("]\n");
}
int *index2dto1d(int *m, int row, int col, int row_lenght){
    return m+col+row*row_lenght;
}
void printMatrix(int *matrix, int rows,int columns){//ulozene za sebou
    for (int i = 0; i < rows; i++){
        printf("| ");
        for (int j = 0; j < columns; j++){
            printf(" %d ", *index2dto1d(matrix, i, j, rows));
        }
        printf(" |\n");    
    }
    
}
int dotProduct(int *vec1, int *vec2, int len){
    int val =0;
    for (int j = 0; j < len; j++){
        val += vec1[j]*vec2[j];
    }
    return val;

}
void mmv(int *m, int *vec1, int *result, int rows, int cols){
    int *tmp;
    for(int i=0; i<rows; i++){
        
        result[i]=dotProduct(index2dto1d(m, i, 0, cols), vec1, cols);
    }
}






void allocate_memory_without_return(int **pointer,unsigned long len){
    *pointer = malloc(len);
    if(*pointer==NULL){
        fprintf(stderr, "Cannot alocate %lu bytes", len);
        exit(-1);
    }
}

void free_memory(int **pointer){
    if(*pointer!=NULL){
        free(*pointer);
        *pointer = NULL;
    }
}




int main() {
    int val=0;
    int rows = 3;
    int cols = 3;
    
    int *vec1 = NULL;
    int *m = NULL;
    int *result = NULL;

    allocate_memory_without_return(&vec1, cols*sizeof(int));
    allocate_memory_without_return(&m, rows*cols*sizeof(int));
    allocate_memory_without_return(&result, cols*sizeof(int));


    for (int i = 0; i < rows; i++){
        for (int j = 0; j < cols; j++){

            *index2dto1d(m, i, j, rows)=val;
            val++;
        }  
    }

    val=0;
    for (int j = 0; j < cols; j++){
        vec1[j] = val;
        val++;
    }
    printf("Matrix\n");
    printMatrix(m, rows,cols);
    printf("\n\nVector1\n");
    printMatrix(vec1, 1,3);
    printf("\n\nResult after multiplying\n");
    mmv(m, vec1, result, rows, cols);
    printMatrix(result, 1, 3);
    free_memory(*m);
    free_memory(*vec1);
    free_memory(*result);
    //printArray(pole1,sizeof(pole1)/sizeof(int));
    //printMatrix(&matrix,3,3);
    return 0;
}
