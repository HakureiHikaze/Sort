//
// Created by Hikaze on 2021/9/30 9:12.
// 
//

#include "Vector.h"

#define ASSERT(x) if(!x)exit(-1) //伪断言，不符合条件则退出

Vector* VectorInit(){
    Vector* pRtn = (Vector*) calloc(1, sizeof(Vector));
    ASSERT(pRtn);
    return pRtn;
}

void VectorFree(Vector* vector){
    if(vector){
        if(vector->capacity){
            free(vector->pArray);
        }
    }
    free(vector);
}

void VectorPushBack(Vector *vector, void *pData) {
    ASSERT(vector);//空检测
    if(!vector->capacity){
        vector->pArray = (void**) calloc(8, sizeof(void*));
        vector->capacity = 8;
    }
    //已用空间==可用空间时表示满，扩增
    if (vector->size == vector->capacity) {
        //重分配空间
        void **pNew = (void **) realloc(vector->pArray, 2 * vector->capacity * sizeof(void *));
        ASSERT(pNew);//空检测
        vector->pArray = pNew;
        vector->capacity *= 2;
    }
    vector->pArray[vector->size] = pData;
    vector->size++;
}

void VectorSort(
        Vector * vector,
        size_t begin,
        size_t end,
        int order,
        int (*compareCallback)(void* pA, void* pB),
        void(*sortCallback)(
                void** pArray,
                size_t begin,
                size_t end,
                int order,
                int (*compareCallback)(void* pA, void* pB))
                ){
    sortCallback(vector->pArray,begin,end, order,compareCallback);
}

void VectorDebugPrint(Vector * vector, void(*printCallback)(void*)){
    ASSERT(vector);//空检测
    printf_s("Vector:  \t0x%p\n", vector);
    printf_s("Array:   \t0x%p\n", vector->pArray);
    printf_s("Size:    \t%d\n", vector->size);
    printf_s("Capacity:\t%d\n\n", vector->capacity);
    for(size_t i = 0; i<vector->size; i++){
        if(!(i%8)) printf_s("\n");
        printCallback(vector->pArray[i]);
    }
}