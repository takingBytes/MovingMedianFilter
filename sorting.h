#ifndef SORT_H
#define SORT_H

typedef enum {BUBBLE, INSERTION, SHELL} SortType;
extern void SortPtBufferInit(float *bufferUnsorted,float **ptBufferSorted,unsigned int size);
extern unsigned int SortPt(float** ptBufferSorted,SortType type, unsigned int n);
#endif
