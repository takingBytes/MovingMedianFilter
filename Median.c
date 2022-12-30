#include <stdbool.h>
#include <stdio.h>
#include "median.h"

static void MedianBufferClear(median* this);
static void MedianBufferShellSort(median* this);
static void MedianBufferInit(median* this);
static float MedianValueGet(median* this);

static void SwapPtPt(float **a, float **b);
static void MedianSortingGapInit(median* this);

extern void MedianInit(median* this, float* buffer,float** ptBufferSorted, unsigned int size)
{
    if ((buffer == NULL)||(ptBufferSorted == NULL)||(size == 0))
        return;
    
    this->buffer=buffer;
    this->ptBufferSorted=ptBufferSorted;
    this->size=size;
    this->index=0;
    this->initialGap=1;

    MedianBufferClear(this);
    MedianBufferInit(this);
    MedianSortingGapInit(this);

}

static void MedianSortingGapInit(median* this)
{
    /* calculate initial gap using Knuth sequence for Shell-Sort */
    while (this->initialGap < this->size / 3)
    {
        this->initialGap = this->initialGap * 3 + 1;
    }
}

extern float MedianFilter(median* this,float input)
{
    if (this == NULL)
        return 0;

    this->buffer[this->index] = input;

    /*increment index*/
    this->index = (this->index + 1) % this->size;

    MedianBufferShellSort(this);

    return MedianValueGet(this);
}

static float MedianValueGet(median* this)
{
    float middleValue;

    if (this->size % 2) 
    {
        middleValue = *this->ptBufferSorted[(this->size / 2)];
    } 
    else
    {
        middleValue = (*this->ptBufferSorted[(this->size / 2)] + *this->ptBufferSorted[(this->size / 2) - 1]) / 2;
    }

    return middleValue;
}

extern unsigned int MedianIterationGet(median* this)
{
    if (this == NULL)
        return 0;

    return this->iterationCount;
}

static void MedianBufferClear(median* this)
{
    if (this == NULL)
        return;

    for (unsigned int i = 0; i < this->size; i++) 
        this->buffer[i] = 0;
}

static void MedianBufferInit(median* this)
{
    for (unsigned int i = 0; i < this->size; i++) 
        this->ptBufferSorted[i] = &this->buffer[i];
}

static void MedianBufferShellSort(median* this)
{
    /* 
    When  type == SHELL

    Knuth sequence:  gap(0..i)=[1, 4, 13, 40,...]
    wc iteration count for inner loop:
    O(n)= (n-gap(i=1))+(n-gap(i=2))     e.g.: n=9 -> WC=13;

    bc iteration count for inner loop:
    O(n)= (n-gap(i=1))+(n-gap(i=2))     e.g.: n=9 -> WC=13;

    wc swap count:
    O(n)= ((n-gap(i=1))+(n-gap(i=2)))-1 e.g.: n=9 -> WC=12;

    bc swap count: 
    O(n)=0                              e.g.: n=9 -> WC=0;        

    wc swap count with *one* changed value: 
    O(n)= (n-1)                         e.g.: n=9 -> WC=8;
    */

    if (this == NULL)
        return;

    this->iterationCount = 0; 
    unsigned int gap=this->initialGap;

    while (gap > 0)
    {
        for (unsigned int  index = gap; index < this->size; index++)
        {   
            float* currentElement = this->ptBufferSorted[index];

            /* compare current element with element 'gap' positions left. 
            If left element is larger, swap them until correct position is found. */

            // Shift elements to the right until the value to the left is 
            while (index >=gap && *this->ptBufferSorted[index - gap] > *currentElement) 
            {   // Shift elements to the right to make space for the current element

                SwapPtPt(&this->ptBufferSorted[index - gap],&this->ptBufferSorted[index]);
                index-= gap;
                this->iterationCount++;
            }
            /* Insert the current element into the correct position */
            this->ptBufferSorted[index] = currentElement;
        }

        /* calculate next gap, using Knuth sequence: */
        if (gap!=1)
        {
            gap = (gap - 1) / 3;
        }else
        { 
            gap=0;
        }
    }
}

static void SwapPtPt(float **a, float **b)
{ 
    float *temp = *a;
    *a = *b;
    *b = temp;
}