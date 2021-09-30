//
// Created by Hikaze on 2021/9/30 9:12.
// 
//

#pragma once
#include "stdlib.h"
#include "stdbool.h"
typedef struct Vector_{
    void* p;
    size_t size;
}Vector;


/**
 * @brief 矢量追加一个元素
 * @param vector 矢量指针
 * @param pData 数据指针
 */
extern void VectorPushBack(Vector * vector, void* pData);
extern void* VectorPopBack(Vector * vector);
/**
 * @brief 在矢量中指定索引的元素后插入元素
 * @param vector 矢量指针
 * @param index 索引，取值范围[-1,size-1]
 * @param pData 数据指针
 */
extern void VectorInsertElement(Vector * vector, size_t index, void* pData);
/**
 * @brief 在矢量中指定索引的元素后插入矢量
 * @param vector 矢量指针
 * @param index 索引
 * @param pVector 插入的矢量的指针
 */
extern void VectorInsertVector(Vector * vector, size_t index, Vector* pVector);
/**
 * @brief 对矢量指定索引间的元素（含两端）排序
 * @param vector 矢量指针
 * @param begin 起始索引
 * @param end 结束索引
 * @param compareCallback 比较回调函数，若参数0大于参数1则返回true，原型: bool(*)(void*, void*)
 * @param sortCallback 排序回调函数，原型: void(*)(Vector*, size_t,size_t,bool(*)(void*, void*))
 */
extern void VectorSort(
        Vector * vector,
        size_t begin,
        size_t end,
        bool (*compareCallback)(void* pA, void* pB),
        void(*sortCallback)(
                Vector * vector,
                size_t begin,
                size_t end,
                bool (*compareCallback)(void* pA, void* pB))
        );
/**
 * @brief 测试输出
 * @param vector 矢量指针
 */
extern void VectorDebugPrint(Vector * vector);