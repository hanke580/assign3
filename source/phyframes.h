#include <stdio.h>
#include "pagetable.h"

struct phyFrames {
    int size;
    int length;
    int *stack;
} PF;

int stack[8];

int pageFaultCount;

int phyInit();

int fetch(struct phyFrames *pf, int ind);

int putNew(struct phyFrames *pf);

int rmLRU(struct phyFrames *pf);

int mvFront(struct phyFrames *pf, int frameInd);

int printFrame(struct phyFrames *pf);
