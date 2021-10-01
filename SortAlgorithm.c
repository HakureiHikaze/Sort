//
// Created by Hikaze on 2021/9/30 20:49.
// 
//

#include "SortAlgorithm.h"
/**
 * @brief 内部函数，交换数组两索引确定的元素
 * @param pArray 数组指针
 * @param a 索引A
 * @param b 索引B
 */
void Swap(void** pArray, size_t a, size_t b){
    void* pBuffer = pArray[a];
    pArray[a] = pArray[b];
    pArray[b] = pBuffer;
}

size_t FindBest(void** pArray,
                size_t begin,
                size_t end,
                int order,
                int (*compareCallback)(void*,void *)
                ){
    void* p = pArray[begin];
    size_t rtn = begin;
    for(size_t i = begin+1; i<=end; i++){
        if(order * compareCallback(p, pArray[i]) == 1){
            p = pArray[i];
            rtn = i;
        }
    }
    return rtn;
}

void BubbleSort(
        void** pArray,
        size_t begin,
        size_t end,
        int order,
        int(*compareCallback)(void*,void*)
        ){
    if(begin == end)return;
    while (true) {
        //x为数组发生交换的次数，循环后为0表示无交换，即数组正序
        size_t x = 0;
        for (size_t j = begin; j < end; j++) {
            //order标识数组排序大小方向，若为1则不取相反数
            if (order * compareCallback(pArray[j], pArray[j + 1]) == 1) {
                Swap(pArray, j, j + 1);
                x++;
            }
        }
        if(!x) break;
    }
}

void SelectSort(
        void** pArray,
        size_t begin,
        size_t end,
        int order,
        int(*compareCallback)(void*,void*)
        ){
    if(begin == end)return;
    for(size_t i = begin; i<end; i++){
        size_t j = FindBest(pArray,i,end,order,compareCallback);
        Swap(pArray,i,j);
    }
}