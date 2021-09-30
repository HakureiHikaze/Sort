//
// Created by Hikaze on 2021/9/30 9:12.
// 
//

#include "Vector.h"

#define ASSERT(x) if(!x)exit(-1) //伪断言，不符合条件则退出

void VectorPushBack(Vector *vector, void *pData) {
    ASSERT(vector);//空检测
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