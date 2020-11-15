// manage the physical frames
#include <stdio.h>
#include <stdlib.h>
#include "phyframes.h"

int phyInit(int size) {

    PF.size = size;
    PF.length = 1;
    PF.stack = (int *)malloc(size * sizeof(int));
    for(int i = 0; i < size; i++) {
        PF.stack[i] = 0;
    }
    pageFaultCount = 0;
    return 0;
}


int fetch(struct phyFrames *pf, int ind, int pageTableSize) {
    
    int frameInd;
    if(pageTable[ind] ==  -1){
        pageFaultCount++;
        if(pf->length < pf->size) {
            frameInd = putNew(pf);
        } else {
            frameInd = rmLRU(pf, pageTableSize);
        }
    } else {
        frameInd = pageTable[ind];
        mvFront(pf, frameInd);
    }
    pageTable[ind] = frameInd;
    return frameInd;
}

int putNew(struct phyFrames *pf) {
    for (int i = pf->length; i > 1; i--) {
        pf->stack[i] = pf->stack[i-1];
    }
    pf->stack[1] = pf->length++;
    return pf->stack[1];
}

int rmLRU(struct phyFrames *pf, int pageTableSize) {
    int frameInd = pf->stack[pf->length - 1];

    for (int i = 0; i < pageTableSize; i++) {
        if(pageTable[i] == frameInd) {
            pageTable[i] = -1;
            break;
        }
    }
    
    for (int i = pf->size - 1; i > 1; i--) {
        pf->stack[i] = pf->stack[i - 1];
    }
    pf->stack[1] = frameInd;
    return frameInd;
}

int mvFront(struct phyFrames *pf, int frameInd) {
    for (int i = 1; i < pf->length; i++) {
        if (pf->stack[i] == frameInd) {
            for (int j = i; j > 1; j--) {
                pf->stack[j] = pf->stack[j - 1];
            }
            pf->stack[1] = frameInd;
            return 0;
        }
    }
    return -1;
}

int printFrame(struct phyFrames *pf) {
    printf("stack list: ");
    for (int i = 0; i < pf->length; i++) {
        printf("%d", pf->stack[i]);
        if(i < pf->length - 1) {
            printf("->");
        }
    }
    printf("\n");
    return 0;
}