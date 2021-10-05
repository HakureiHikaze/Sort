//
// Created by Hikaze on 2021/10/5 12:14.
// 
//

#include "Heap.h"

void Adjust_(
        Heap* heap,
        size_t root,
        int order,
        int(*compareCallback)(void* pA, void* pB)
        );

Heap* HeapInit(
        Vector* vector,
        int order,
        int(*compareCallback)(void* pA, void* pB)
        ){
    Heap* p = VectorInit();
    p->pArray = (void**) calloc(vector->capacity, sizeof(void*));
    for(size_t i = 0; i< vector->size;i++){
        p->pArray[i] = vector->pArray[i];
    }
    p->capacity = vector->capacity;
    p->size = vector->size;
    HeapAdjust(p, order, compareCallback);
    return p;
}

void HeapAdjust(
        Heap* heap,
        int order,
        int(*compareCallback)(void* pA, void* pB)
        ){
    for(size_t i = ((heap->size-1)/2)+1; i>0;){
        i--;
        Adjust_(heap, i, order, compareCallback);
    }
}

void Adjust_(
        Heap* heap,
        size_t root,
        int order,
        int(*compareCallback)(void* pA, void* pB)
        ){
    if(root*2+1<heap->size) {
        if (order * compareCallback(heap->pArray[root], heap->pArray[root * 2 + 1]) == 1) {
            HeapSwapElement(heap,root, root*2+1);
        }
        Adjust_(heap, root * 2 + 1, order, compareCallback);
    }
    if(root*2+2<heap->size) {
        if (order * compareCallback(heap->pArray[root], heap->pArray[root * 2 + 2]) == 1) {
            HeapSwapElement(heap,root, root*2+2);
        }
        Adjust_(heap, root * 2 + 2, order, compareCallback);
    }
}

void HeapSwapElement(Heap* heap, size_t a, size_t b){
    void* p = heap->pArray[a];
    heap->pArray[a] = heap->pArray[b];
    heap->pArray[b] = p;
}