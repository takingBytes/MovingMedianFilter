# Moving Median Filter

This project implements a moving median filter in C. The median filter takes in a stream of inputvalues and returns the median value over the buffer size. It does this by sorting the data points with the Shell sort alogorithm and selecting the middle value as the filtered output.

## Benefits of Using a Median Filter

-  Median filters are particularly effective at reducing the impact of isolated outliers or "peaks" in the data.
- They can be more robust to noise than other types of filters, such as moving average filters.

## Getting Started

To use the median filter in your own project, include the `median.h` header file and call the `MedianInit()` function to initialize the filter. Then, call the `MedianFilter()` function with each new value to get the filtered output.

### Using the Median Filter

Here is an example of how to use the median filter in your own C code:

```
#include "median.h"
#include <unistd.h>

#define SIZE 9
float buffer[SIZE];
float* ptBufferSorted[SIZE];
float filteredValue;

median filter;

float getRawValue(void);

int main() 
{
    /* initialize the filter */
    MedianInit(&filter, buffer, ptBufferSorted, SIZE);

    while(true)
    {
        /* apply the filter */
        float filteredValue = MedianFilter(&filter, getRawValue());

        /* do something with the filtered value */
        printf("Filtered value: %f\n", filteredValue);

        sleep(1);
    }
    return 0;
}
```

## Functions

- `MedianInit()`: Initializes the median filter with a given buffer and size.
- `MedianFilter()`: Adds a new value to the filter and returns the filtered output (the median value of the last `size` values).
- `MedianIterationGet()`: Returns the number of iterations of the inner loop in the Shell sort algorithm.

## Sorting Algorithm: Shell Sort

The median filter uses the Shell sort algorithm to sort the data points in the buffer. Shell sort is a sorting algorithm that works by comparing elements that are a certain distance apart (called the gap) and swapping them if they are in the wrong order. The gap size is gradually reduced until the list is fully sorted. The gap size can be calculated using the Knuth sequence to improve the performance of the algorithm. Shell sort is usally faster than some other simple sorting algorithms, such as insertion sort, because it takes advantage of the partially sorted nature of the list and performs fewer swaps and comparisons overall. 

| Knuth sequence | gap(0..i)=[1, 4, 13, 40,...] |
| --- | --- |
| Worstcase iterationcount | O(n)= ((n-gap(i=1))+(n-gap(i=2)...))-1<br>with: n=9 -> WC=12 |
| Bestcase iterationcount | O(n)=0<br>with: n=9 -> WC=0 |
| Worstcase iterationcount<br>with *one* changed value | O(n)= (n-1)<br>with: n=9 -> WC=8 |