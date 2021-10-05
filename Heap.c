//
// Created by Hikaze on 2021/10/5 12:14.
// 
//

#include "Heap.h"

Heap* HeapInit(Vector* vector){
    Heap* p = VectorInit();
    p->pArray = (void**) calloc(vector->capacity, sizeof(void*));
    for(size_t i = 0; i< vector->size;i++){
        p->pArray[i] = vector->pArray[i];
    }
    p->capacity = vector->capacity;
    p->size = vector->size;

    return p;
}