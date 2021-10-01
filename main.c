#include <stdio.h>
#include "Vector.h"
#include "SortAlgorithm.h"
#include <time.h>

extern void printInt(void* I);
extern int compareInt(void* a, void* b);

int main() {
    clock_t start, end;
    Vector * vector = VectorInit();
    Vector * test;
    for(int i = 5000; i<=50000;i+=5000){
        test = VectorInit();
        for(size_t j = 1; j<=i;j++){
            VectorPushBack(test, (void*)j);
        }
        start = clock();
        VectorSort(test,0,i-1,BIG_TO_SMALL,compareInt,SelectSort);
        end = clock();
        //VectorDebugPrint(test, printInt);
        VectorFree(test);
        printf_s("Sorted %d elements, spent %ld\n",i, end-start);
    }
    return 0;
}

void printInt(void* I){
    printf_s("%ld\t",I);
}

int compareInt(void* a, void* b){
    if(((size_t)a>(size_t)b))return 1;
    else return -1;
}