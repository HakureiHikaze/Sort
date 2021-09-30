//
// Created by Hikaze on 2021/9/30 20:49.
// 
//

#pragma once
#include <stdlib.h>
#include <stdbool.h>
/**
 * @brief 冒泡排序(含两端)
 * @param pArray 数组指针
 * @param begin 起始索引
 * @param end 结束索引
 * @param order 从大到小排序或从小到大排序，宏：BIG_TO_SMALL, SMALL_TO_BIG
 * @param compareCallback 比较回调函数，若参数0 > 参数1则返回true，原型: bool(*)(void*, void*)
 */
extern void BubbleSort(
        void** pArray,
        size_t begin,
        size_t end,
        int order,
        int(*compareCallback)(void* pA, void* pB)
        );