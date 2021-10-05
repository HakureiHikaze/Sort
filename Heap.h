//
// Created by Hikaze on 2021/10/5 12:14.
// 
//

#pragma once
#include "Vector.h"

typedef Vector Heap;
extern void printInt(void* I);
extern Heap* HeapInit(
        Vector* vector,
        int order,
        int(*compareCallback)(void* pA, void* pB)
        );


extern void HeapAdjust(
        Heap* heap,
        int order,
        int(*compareCallback)(void* pA, void* pB)
        );
extern void HeapSwapElement(Heap*, size_t, size_t);