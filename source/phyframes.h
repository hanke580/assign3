#include <stdio.h>
#include "pagetable.h"

struct phyFrames {
    int size;
    int length;
    struct phyNode* head;
    struct phyNode* tail;
} PF;

struct phyNode {
    int ind;
    struct phyNode *pre;
    struct phyNode *next;
};

int pageFaultCount;

int phyInit(int size);

int fetch(struct phyFrames *pf, int ind, int pageTableSize);

int putNew(struct phyFrames *pf);

int rmLRU(struct phyFrames *pf, int pageTableSize);

int mvFront(struct phyFrames *pf, int frameInd);
