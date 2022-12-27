#ifndef MEDIAN_H
#define MEDIAN_H

typedef struct Median 
{
    float* buffer;
    float** ptBufferSorted;
    unsigned int size;
    unsigned int index;
    unsigned int iterationCount;
} median;

extern median Median;

extern float MedianFilter(median* this,float input);
extern void MedianInit(median* this, float* buffer,float** ptBufferSorted, unsigned int size);
extern unsigned int MedianLastIterationCountGet(median* this);
#endif
