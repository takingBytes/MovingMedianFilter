#include <stdbool.h>
#include <stdio.h>
#include "sorting.h"
#include "median.h"

float medianPt(float** ptArr, int n)
{
    float median= 0;
    int sortingIterations = 0;
    int middle = 0;

    if ((ptArr == NULL)||(n == 0))
    {
        return 0;
    }

    middle = n / 2;
    sortingIterations = shell_sort_pt(ptArr, n);

    if (n % 2) 
    {
        median = *ptArr[middle];
    } else 
    {
        median= (*ptArr[middle] + *ptArr[middle - 1]) / 2;
    }

    printf("%i;",sortingIterations);
    return median;
}


