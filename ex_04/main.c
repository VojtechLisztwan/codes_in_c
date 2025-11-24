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

int main() {
    int pole1[]={1,12,15,8,87};
    int matrix[3][3]={
        {3,5,6},
        {1,4,8},
        {7,8,9}
    };

    int val=0;
    int rows = 3;
    int cols = 3;
    int *m = malloc(sizeof(int)*rows*cols);
    int *vec1 = malloc(sizeof(int)*cols);
    int *result = malloc(sizeof(int)*cols);
    for (int i = 0; i < rows; i++){
        for (int j = 0; j < cols; j++){

            *index2dto1d(m, i, j, rows)=val;
            val++;
        }  
    }
    printMatrix(m, rows,cols);
    printf("\n\n");
    mmv(m, vec1, result, rows, cols);
    printMatrix(result, rows, 1);
    free(m);

    //printArray(pole1,sizeof(pole1)/sizeof(int));
    //printMatrix(&matrix,3,3);
    return 0;
}
