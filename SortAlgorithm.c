//
// Created by Hikaze on 2021/9/30 20:49.
// 
//

#include "SortAlgorithm.h"

void Swap(void** pArray, size_t a, size_t b){
    void* pBuffer = pArray[a];
    pArray[a] = pArray[b];
    pArray[b] = pBuffer;
}

void BubbleSort(
        void** pArray,
        size_t begin,
        size_t end,
        int order,
        int(*compareCallback)(void* pA, void* pB)
        ){
    while (true) {
        size_t x = 0;
        for (size_t j = begin; j < end - 1; j++) {
            if (order * compareCallback(pArray[j], pArray[j + 1]) == 1) {
                Swap(pArray, j, j + 1);
                x++;
            }
        }
        if(!x) break;
    }
}