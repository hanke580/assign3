// manage the physical frames
#include <stdio.h>
#include <stdlib.h>
#include "phyframes.h"

int phyInit(int size) {

    PF.size = size;
    PF.length = 1;
    PF.head = (struct phyNode*)malloc(sizeof(struct phyNode));
    PF.tail = PF.head;
    PF.head->ind = 0;
    PF.head->next = NULL;
    PF.head->pre = NULL;
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

struct phyNode* del(struct phyFrames *pf, struct phyNode *cur) {
    if(cur == pf->tail) {
        pf->tail = cur->pre;
    }
    struct phyNode *pre = cur->pre;
    struct phyNode *next = cur->next;
    if(pre)
        pre->next = next;
    if(next)
        next->pre = pre;
    cur->pre = NULL;
    cur->next = NULL;
    return cur;
}

int insert(struct phyFrames *pf, struct phyNode* cur) {
    cur->next = pf->head->next;
    cur->pre = pf->head;
    if(pf->head->next){
        pf->head->next->pre = cur;
    } else {
        pf->tail = cur;
    }
    pf->head->next = cur;
    return 0;
}

int putNew(struct phyFrames *pf) {
    struct phyNode* cur = (struct phyNode*)malloc(sizeof(struct phyNode));
    insert(pf, cur);
    cur->ind = pf->length++;
    return cur->ind;
}

int rmLRU(struct phyFrames *pf, int pageTableSize) {
    int frameInd = pf->tail->ind;
    for (int i = 0; i < pageTableSize; i++) {
        if(pageTable[i] == frameInd) {
            pageTable[i] = -1;
            break;
        }
    }
    struct phyNode* cur = del(pf, pf->tail);
    insert(pf, cur);
    return frameInd;
}

int mvFront(struct phyFrames *pf, int frameInd) {

    // 1: Find cur
    struct phyNode* cur = pf->head;
    while(cur && cur->ind!=frameInd){
        cur = cur->next;
    }
    if(cur == NULL) {
        printf("wrong frame ID\n");
        return -1;
    }
    del(pf, cur);
    insert(pf, cur);
    return 0;
}
