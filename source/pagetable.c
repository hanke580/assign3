// all functions that manages the page table for the process. 

#include "pagetable.h"

int ptInit() {
    for (int i = 0; i < PAGE_TABLE_SIZE; i++) {
        pageTable[i] = -1;
    }
    return 0;
}

