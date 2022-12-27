#include <stdbool.h>
#include <stdio.h>
#include "sorting.h"

static unsigned int SortInsertionPt(float** ptBufferSorted,Sorter type, unsigned int n);
static unsigned int SortBubblePt(float** ptBufferSorted, unsigned int n) ;

extern void SortPtBufferInit(float *bufferUnsorted,float **ptBufferSorted,unsigned int size)
{
  for (unsigned int i = 0; i < size; i++) 
    ptBufferSorted[i] = &bufferUnsorted[i];
}

extern unsigned int SortPt(float** ptBufferSorted,Sorter type, unsigned int n)
{
    if ((ptBufferSorted == NULL)||(n == 0))
    {
        return 0;
    }

    if (type==BUBBLE)
    {
        return SortBubblePt(ptBufferSorted,n);
    }else
    {
        return SortInsertionPt(ptBufferSorted,type,n);
    }
}

static void SwapPtPt(float **a, float **b)
{ 
    float *temp = *a;
    *a = *b;
    *b = temp;
}
static unsigned int SortBubblePt(float** ptBufferSorted, unsigned int n) 
{
/*
wc iteration count for inner loop:
O(n)= n(n-1)/2      e.g.: n=9 -> WC=36;

bc iteration count for inner loop:
O(n)= n-1           e.g.: n=9 -> WC=8;

wc swap count:
O(n)= n(n-1)/2      e.g.: n=9 -> WC=36;

bc swap count: 
O(n)=0              e.g.: n=9 -> WC=0;

wc swap count with *one* changed value: 
O(n)=(n-1)          e.g.: n=9 -> WC=8;
*/
if ((ptBufferSorted == NULL)||(n == 0))
{
  return 0;
}
    unsigned int iterationCount = 0; 
    // Perform bubble sort
    for (unsigned int i = 0; i < n - 1; i++)
    {
        bool swapped = false;
        for (unsigned int j = 0; j < n - i - 1; j++)
        {
            if (*ptBufferSorted[j] > *ptBufferSorted[j + 1])
            {   
                iterationCount++;
                SwapPtPt(&ptBufferSorted[j], &ptBufferSorted[j + 1]);
                swapped = true;
            }
        }
        if (!swapped)
        {
           break;
        }
    }
    return iterationCount;
}

static unsigned int SortInsertionPt(float** ptBufferSorted,Sorter type, unsigned int n)
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

    /*
    When  type == INSERTION

    wc iteration count for inner loop:
    O(n)= n(n-1)/2      e.g.: n=9 -> WC=36;

    bc iteration count for inner loop:
    O(n)= n-1           e.g.: n=9 -> WC=8;

    wc swap count:
    O(n)= n(n-1)/2      e.g.: n=9 -> WC=36;

    bc swap count: 
    O(n)=0              e.g.: n=9 -> WC=0;

    wc swap count with *one* changed value: 
    O(n)=(n-1)          e.g.: n=9 -> WC=8;
    */

    unsigned int iterationCount = 0; 
    unsigned int gap=1;

    if ((ptBufferSorted == NULL)||(n == 0))
    {
    return 0;
    }

    if (type==SHELL)
    {
        /* calculate initial gap using Knuth sequence for Shell-Sort */
        while (gap < n / 3)
        {
            gap = gap * 3 + 1;
        }
    }else
    {   /* use initial gap standard gap=1 for Insertion-Sort */
        gap = 1;
    }

    while (gap > 0)
    {
        for (unsigned int  index = gap; index < n; index++)
        {   
            float* currentElement = ptBufferSorted[index];

            /* compare current element with element 'gap' positions left. 
            If left element is larger, swap them until correct position is found. */

            while (index >=gap && *ptBufferSorted[index - gap] > *currentElement) 
            {
                SwapPtPt(&ptBufferSorted[index], &ptBufferSorted[index - gap]);
                index-= gap;
                iterationCount++;
            }
            ptBufferSorted[index] = currentElement;
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
    return iterationCount;
}