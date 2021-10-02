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
    /*
     * 寻找最值元素的索引
     * order = SMALL_TO_BIG = 1时， 寻找最小值，
     * order = BIG_TO_SMALL =-1时， 寻找最大值。
     */
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
        //找到最值元素游标j，并将其元素与当前游标的元素交换
        size_t j = FindBest(pArray,i,end,order,compareCallback);
        Swap(pArray,i,j);
    }
}

void InsertSort(
        void** pArray,
        size_t begin,
        size_t end,
        int order,
        int(*compareCallback)(void* pA, void* pB)
        ){
    for(size_t i = begin+1; i<=end; i++){//遍历无序区
        void* p = pArray[i];//缓存无序区首值
        for(size_t j = begin; j<i; j++){//遍历有序区
            if(order*compareCallback(p,pArray[j]) == 1){
                if(j == i-1){//如果插入到有序区末尾，即无操作（有序区末尾和无序区起始重叠）
                    break;
                }
                continue;//continue直到不符合比较条件，即找到插入位置的次一索引
            }
            //找到插入位置的次一索引后
            for(size_t k = i; k>j;k--){//移动有序区
                pArray[k] = pArray[k-1];
            }
            pArray[j] = p;//插入缓存的值
            break;//无序区的下一个值
        }
    }
}