#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include "median.h"
#include "sorting.h"


#define MAX_SIZE 9
int main(void)
{
    float arr[MAX_SIZE] = {10.5, 8.2, 9.7, 7.1, 11.9, 6.4, 12.8, 5.6, 3.2};

    float med = median(arr, MAX_SIZE);
    printf("The median of the array is: %f\n", med);

    return 0;
}