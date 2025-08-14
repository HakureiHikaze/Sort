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
    size_t largest = root;
    size_t left = root * 2 + 1;
    size_t right = root * 2 + 2;
    
    // Find the largest/smallest among root and its children
    if (left < heap->size && order * compareCallback(heap->pArray[largest], heap->pArray[left]) == 1) {
        largest = left;
    }
    
    if (right < heap->size && order * compareCallback(heap->pArray[largest], heap->pArray[right]) == 1) {
        largest = right;
    }
    
    // If root is not the largest/smallest, swap and continue heapifying
    if (largest != root) {
        HeapSwapElement(heap, root, largest);
        Adjust_(heap, largest, order, compareCallback);
    }
}

void HeapSwapElement(Heap* heap, size_t a, size_t b){
    void* p = heap->pArray[a];
    heap->pArray[a] = heap->pArray[b];
    heap->pArray[b] = p;
}