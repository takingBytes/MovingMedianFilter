#include <stdbool.h>
#include <stdio.h>
#include "sorting.h"
#include "median.h"

// Function to find the median of an array of values
float median(float* arr, int n)
{
    shell_sort(arr, n);
    return arr[n / 2];
}

