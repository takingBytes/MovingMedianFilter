#include <stdbool.h>
#include <stdio.h>
#include "sorting.h"
#include "median.h"

float median(float* arr, int n)
{
    shell_sort(arr, n);
    return arr[n / 2];
}

float medianPt(float** ptArr, int n)
{
    printf("%i;",shell_sort_pt(ptArr, n));
    return *ptArr[n / 2];
}


