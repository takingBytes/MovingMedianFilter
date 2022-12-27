#include <stdbool.h>
#include <stdio.h>
#include "sorting.h"
#include "median.h"

void MedianInit(median* this, float* arr,float** ptArr, unsigned int n)
{
    if ((arr == NULL)||(ptArr == NULL)||(n == 0))
    {
        return;
    }

    pointerArrayInit(arr,ptArr,n);

    this->arr=arr;
    this->ptArr=ptArr;
    this->size=n;
    this->cnt=0;
}


extern float MedianFilter(median* this,float in)
{
    float median= 0;
    unsigned int sortingIterations = 0;
    unsigned int middle = 0;


    this->arr[this->cnt] = in;
    this->cnt = (this->cnt + 1) % this->size;

    middle = this->size / 2;
    sortingIterations = shell_sort_pt(this->ptArr, this->size);

    if (this->size % 2) 
    {
        median = *this->ptArr[middle];
    } else 
    {
        median= (*this->ptArr[middle] + *this->ptArr[middle - 1]) / 2;
    }

    printf("%i;",sortingIterations);
    return median;
}