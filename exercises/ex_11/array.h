#ifndef _ARRAY_H
#define _ARRAY_H

typedef struct {
    void **data;
    int capacity;
    int count;
    int element_size;
}Array;

void array_init(Array *self, int capacity, int element_size);
void array_free(Array *self);
void* array_push(Array* self);
void* array_get(Array* self, int i);
int array_count(Array* self);

#endif