#ifndef MEDIAN_H
#define MEDIAN_H

typedef struct Median 
{
    float* buffer;
    float** ptBufferSorted;
    unsigned int size;
    unsigned int index;
    unsigned int iterationCount;
    unsigned int initialKnuthGap;
} median;

extern median Median;

extern void MedianInit(median* this, float* buffer,float** ptBufferSorted, unsigned int size);
extern float MedianFilter(median* this,float input);
extern unsigned int MedianIterationGet(median* this);

#endif