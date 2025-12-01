#include <stdlib.h>
#include <stdio.h>
#include "array.h"

void array_init(Array *self, int capacity, int element_size){
    self->capacity = capacity;
    self->element_size = element_size;
    self->count = 0;
    self->data = malloc(capacity*element_size);
    
}

void array_free(Array *self){
    for (int i = 0; i < self->count; i++){
        free(self->data[i]);
    }
    self->count = 0;
    self->element_size=0;
    self->capacity=0;
    free(self->data);    
}

void* array_push(Array* self){
    void *result = malloc(self->element_size);
    if(self->count == self->capacity){
        self->capacity*=2;
        self->data = realloc(self->data, self->capacity);
    }
    self->data[self->count] = result;
    self->count++;

    return result;
}

void* array_get(Array* self, int i){
    return self->data[i];
}

int array_count(Array* self){
    return self->count;
}