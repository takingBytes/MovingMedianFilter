#ifndef SORT_H
#define SORT_H

typedef enum {BUBBLE, INSERTION, SHELL} Sorter;
extern void SortPtBufferInit(float *bufferUnsorted,float **ptBufferSorted,unsigned int size);
extern unsigned int SortPt(float** ptBufferSorted,Sorter type, unsigned int n);
#endif
