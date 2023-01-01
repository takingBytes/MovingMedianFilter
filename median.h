#ifndef MEDIAN_H
#define MEDIAN_H

typedef struct Median 
{
    float* buffer;
    float** ptBufferSorted;
    uint8_t size;
    uint8_t index;
    uint8_t iterationCount;
    uint8_t initialKnuthGap;
    bool init;
} median;

extern median Median;

extern void MedianInit(median* this, float* buffer,float** ptBufferSorted, uint16_t size);
extern float MedianFilter(median* this,float input);
extern uint8_t MedianIterationGet(median* this);

#endif