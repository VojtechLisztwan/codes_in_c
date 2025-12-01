#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "array.h"
#include "array.h"

int main() {
    Array ints;
    array_init(&ints, 10, sizeof(int));
    *(int *)array_push(&ints)=1;
    *(int *)array_push(&ints)=5;
    *(int *)array_push(&ints)=6;
    *(int *)array_push(&ints)=7;

    for (int i = 0; i < ints.count; i++){
        printf("%d: %d\n", i, *(int*)array_get(&ints, i));
    }
    
    array_free(&ints);
    return 0;
}
