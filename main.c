#include <stdio.h>
#include "Vector.h"
#include "SortAlgorithm.h"

extern void printInt(void* I);
extern int compareInt(void* a, void* b);

int main() {
    Vector * vector = VectorInit();
    for(size_t i = 500; i>=1; i--){
        VectorPushBack(vector, (void*)i);
    }
    VectorSort(vector, 0, 500, SMALL_TO_BIG, compareInt, BubbleSort);
    VectorDebugPrint(vector, printInt);
    VectorFree(vector);
    return 0;
}

void printInt(void* I){
    printf_s("%ld\t",I);
}

int compareInt(void* a, void* b){
    if(((size_t)a>(size_t)b))return 1;
    else return -1;
}