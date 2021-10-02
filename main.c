#include <stdio.h>
#include "Vector.h"
#include "SortAlgorithm.h"
#include <time.h>

extern void printInt(void* I);
extern int compareInt(void* a, void* b);
#define DEBUG
int main() {
    clock_t start, end;
    Vector * vector = VectorInit();
    Vector * vector1 = VectorInit();
    for(size_t i =0; i<10; i++){
        VectorPushBack(vector,(void*)i);
    }
    for(size_t i =100; i<=135; i++){
        VectorPushBack(vector1,(void*)i);
    }
    VectorInsertVector(vector,2,vector1);
    VectorDebugPrint(vector,printInt);
    Vector * test;

    for(int i = 12800; i<12800;i+=400){
        test = VectorInit();
        for(size_t j = 1; j<=i;j++){
            VectorPushBack(test, (void*)rand());
        }
        start = clock();
        VectorSort(test,0,i-1,BIG_TO_SMALL,compareInt,InsertSort);
        end = clock();
        //VectorDebugPrint(test, printInt);
        VectorFree(test);
        printf_s("Sorted %d elements, spent %ld\n",i, end-start);
        fflush(stdout);
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