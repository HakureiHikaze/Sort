#include <stdio.h>
#include "Vector.h"
#include "SortAlgorithm.h"
#include <time.h>

extern void printInt(void* I);
extern int compareInt(void* a, void* b);
#define DEBUG
int main() {
    clock_t start, end;
    Vector * test;
    for(int i = 100000000; i<=100000000;i+=10000000){
        test = VectorInit();
        for(size_t j = 1; j<=i;j++){
            unsigned long i3 = rand();
            unsigned long i4 = rand();
            if(j%4567345 == 0)VectorPushBack(test,(void*)j);
            else VectorPushBack(test, (void*)(i3<<16 + i4));
        }
        start = clock();
        VectorSort(test,0,i-1,BIG_TO_SMALL,compareInt,MergeSort);
        end = clock();
        //VectorDebugPrint(test, printInt);
        VectorFree(test);
        printf_s("Sorted %d elements, spent %ld\n",i, end-start);
        fflush(stdout);
    }
    return 0;
}

void printInt(void* I){
    printf_s("%u\t",I);
}

int compareInt(void* a, void* b){
    if(((size_t)a>(size_t)b))return 1;
    else return -1;
}