#ifndef MEDIAN_H
#define MEDIAN_H

typedef struct Median 
{
    float* arr;
    float** ptArr;
    unsigned int size;
    unsigned int cnt;
} median;

extern median Median;

extern float MedianFilter(median* this,float in);
extern void MedianInit(median* this, float* arr,float** ptArr, unsigned int n);
#endif
