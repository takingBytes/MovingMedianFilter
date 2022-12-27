#include <stdbool.h>
#include <stdio.h>
#include "sorting.h"
#include "median.h"

extern void MedianInit(median* this, float* buffer,float** ptBufferSorted, unsigned int size)
{
    if ((buffer == NULL)||(ptBufferSorted == NULL)||(size == 0))
    {
        return;
    }

    SortPtBufferInit(buffer,ptBufferSorted,size);
    this->buffer=buffer;
    this->ptBufferSorted=ptBufferSorted;
    this->size=size;
    this->index=0;
}

extern float MedianFilter(median* this,float input)
{
    float filteredOutput= 0;
    unsigned int middleIndex = 0;

    this->buffer[this->index] = input;
    this->index = (this->index + 1) % this->size;

    middleIndex = this->size / 2;
    this->iterationCount = SortPt(this->ptBufferSorted,SHELL, this->size);

    if (this->size % 2) 
    {
        filteredOutput = *this->ptBufferSorted[middleIndex];
    } else 
    {
        filteredOutput= (*this->ptBufferSorted[middleIndex] + *this->ptBufferSorted[middleIndex - 1]) / 2;
    }
    return filteredOutput;
}

extern unsigned int MedianLastIterationCountGet(median* this)
{
    return this->iterationCount;
}