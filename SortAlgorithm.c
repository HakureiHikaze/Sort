//
// Created by Hikaze on 2021/9/30 20:49.
// 
//

#include "SortAlgorithm.h"
#include "Vector.h"
#include "Heap.h"
#include <math.h>

// Forward declarations for internal functions
size_t MergeSort_(
        void** pArray,
        size_t begin,
        size_t end,
        int order,
        int(*compareCallback)(void* pA, void* pB)
        );

void heapify(void** pArray, size_t base, size_t n, size_t i, int order,
            int(*compareCallback)(void* pA, void* pB));
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
        void* key = pArray[i];//缓存无序区当前值
        size_t j = i;
        
        // Move elements that are greater/smaller than key one position ahead
        while(j > begin && order * compareCallback(pArray[j-1], key) == 1){
            pArray[j] = pArray[j-1];
            j--;
        }
        pArray[j] = key;//插入缓存的值到正确位置
    }
}

size_t Partition(
        void** pArray,
        size_t low,
        size_t high,
        int order,
        int(*compareCallback)(void* pA, void* pB)
        ){
    //printf("Calling Partition(...), Low:\t%lld,\tHigh:\t%lld.\n", low,high);
    //fflush(stdout);
    void* pPivot =pArray[low];
    while(low < high){
        while(low< high && (order*compareCallback(pPivot, pArray[high]) == -1)){
            high--;
        }
        Swap(pArray, low, high);
        while(low< high && (order*compareCallback(pPivot, pArray[low]) == 1)){
        low++;
        }
        Swap(pArray, low, high);
    }
    return low;
}

void QuickSort(
        void** pArray,
        size_t begin,
        size_t end,
        int order,
        int(*compareCallback)(void* pA, void* pB)
        ){
    if(begin < end){
        size_t pivotIndex = Partition(pArray,begin,end,order,compareCallback);
        if(pivotIndex > begin) QuickSort(pArray,begin,pivotIndex-1,order,compareCallback);
        if(pivotIndex < end) QuickSort(pArray,pivotIndex+1, end,order,compareCallback);
    }
}

void MergeSort(
        void** pArray,
        size_t begin,
        size_t end,
        int order,
        int(*compareCallback)(void* pA, void* pB)
        ){
    MergeSort_(pArray,begin,end,order,compareCallback);
}

size_t MergeSort_(
        void** pArray,
        size_t begin,
        size_t end,
        int order,
        int(*compareCallback)(void* pA, void* pB)
        ){
#ifdef DEBUG_HIKAZE
    printf("MergeSort called:\npArray:\t%p\tbegin:\t%zu\tend:\t%zu\n",pArray,begin,end);
    fflush(stdout);
#endif
    if(begin == end){
        return 1;
    }
    size_t length = end-begin+1;
    size_t preLength = MergeSort_(pArray,begin,begin+(end-begin)/2,order,compareCallback);
    size_t postLength = MergeSort_(pArray,begin+(end-begin)/2+1, end,order,compareCallback);
    void** pBuffer = (void**) calloc(length, sizeof(void*));
    size_t i=0, j=0;
    while(i<preLength &&j<postLength){
        if(order * compareCallback(pArray[begin+i], pArray[begin+preLength+j]) == -1){
            pBuffer[i+j] = pArray[begin+i];
            i++;
            continue;
        }
        pBuffer[i+j] = pArray[begin+preLength+j];
        j++;
    }
    while(i < preLength){
        pBuffer[i+j] = pArray[begin+i];
        i++;
    }
    while(j < postLength){
        pBuffer[i+j] = pArray[begin+preLength+j];
        j++;
    }
    for(size_t k = 0; k<length;k++){
        pArray[begin+k] = pBuffer[k];
    }
    free(pBuffer);
    return length;
}

void HeapSort(
        void** pArray,
        size_t begin,
        size_t end,
        int order,
        int(*compareCallback)(void* pA, void* pB)
        ){
    size_t length = end - begin + 1;
    if(length <= 1) return;
    
    // Build heap (rearrange array) - use opposite order for heapify to get correct sort order
    for(size_t i = length / 2; i > 0; i--) {
        heapify(pArray, begin, length, begin + i - 1, -order, compareCallback);
    }
    
    // One by one extract an element from heap
    for(size_t i = length; i > 1; i--) {
        // Move current root to end
        Swap(pArray, begin, begin + i - 1);
        
        // Call heapify on the reduced heap
        heapify(pArray, begin, i - 1, begin, -order, compareCallback);
    }
}

// Helper function to heapify a subtree rooted with node i
void heapify(void** pArray, size_t base, size_t n, size_t i, int order,
            int(*compareCallback)(void* pA, void* pB)) {
    size_t target = i; // Initialize largest/smallest as root
    size_t left = base + 2 * (i - base) + 1; // left = 2*i + 1
    size_t right = base + 2 * (i - base) + 2; // right = 2*i + 2
    
    // If left child is larger/smaller than root
    if (left < base + n && order * compareCallback(pArray[target], pArray[left]) == 1) {
        target = left;
    }
    
    // If right child is larger/smaller than target so far
    if (right < base + n && order * compareCallback(pArray[target], pArray[right]) == 1) {
        target = right;
    }
    
    // If target is not root
    if (target != i) {
        Swap(pArray, i, target);
        
        // Recursively heapify the affected sub-tree
        heapify(pArray, base, n, target, order, compareCallback);
    }
}