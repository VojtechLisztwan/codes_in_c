#include <stdio.h>
#include <stdlib.h>


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
int abs(int a){
    if(a<0) return a*-1;
    return a;
}



int main(){
    unsigned long vals;
    scanf("%li ", &vals);
    long *array = NULL;
    allocate_memory_without_return((void *) &array, sizeof(long)*vals);    
    for (unsigned long i = 0; i < vals; i++){
        scanf("%lu ", array+i);
    }
    long max=array[0], min=array[0];
    for (unsigned long i = 0; i < vals; i++){
        //printf("%d \n", array[i]);
        if(max<array[i]); max = array[i];
        if(min>array[i]); min = array[i];
    }
    for (unsigned long i = 0; i < vals; i++){
        printf("%li ", array[i]-min);
        printf("%li ", max-min);
        printf("%li ", max);
        printf("%li ", min);
        printf("%g \n", (double)(array[i]-min)/(max-min));
        
    }
    
}