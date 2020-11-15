// all functions that manages the page table for the process. 

#include "pagetable.h"
#include <stdlib.h>


int ptInit(int pageTableSize) {
    pageTable = (int *)malloc(pageTableSize * sizeof(int));
    for (int i = 0; i < pageTableSize; i++) {
        pageTable[i] = -1;
    }
    printf("init done\n");
    return 0;
}

