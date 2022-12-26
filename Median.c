#include <stdbool.h>
#include <stdio.h>
#include "sorting.h"

// Function to find the median of an array of values
float median(float* arr, int n)
{
    shell_sort(arr, n);
    return arr[n / 2];
}

int main(void)
{
    float arr[9] = {10.5, 8.2, 9.7, 7.1, 11.9, 6.4, 12.8, 5.6, 3.2};
    int n = sizeof(arr) / sizeof(arr[0]);

    float med = median((float*)&arr, n);
    printf("The median of the array is: %f\n", med);

    return 0;
}