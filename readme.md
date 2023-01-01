# Moving Median Filter

This project implements a moving median filter in C. The median filter takes in a stream of input values and returns the median value over the buffer size. It does this by sorting the data points with the Shellsort alogorithm and selecting the middle value as the filtered output.

## Benefits of Using a Median Filter

- Median filters are particularly effective at reducing the impact of isolated outliers or "peaks" in the data.
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
- `MedianIterationGet()`: Returns the number of iterations of the inner loop in the Shellsort algorithm.

## Shellsort Algorithm

The median filter uses the Shellsort algorithm to sort the data points in the buffer. Shellsort is a sorting algorithm that works by comparing elements that are a certain distance apart (called the gap) and swapping them if they are in the wrong order. The gap size is gradually reduced until the list is fully sorted. When the gap size is down to 1, it behaves like a standard Insertionsort. The gap size is calculated by using the Knuth sequence to improve the performance of the algorithm. Shellsort is usally faster than some other simple sorting algorithms, because it takes advantage of the partially sorted nature of the buffer and performs fewer swaps and comparisons overall.

This Shellsort implementation leverages the fact that sorting algorithms tend to be faster on partially sorted lists by using two buffers. A ring buffer that stores the raw input values, and a sorted buffer that holds a list of pointers to the raw data. This allows the median filter to quickly find the median value without having to sort the entire list of values each time, improving the performance of the filter. Using the Knuth sequence, the worst and best case iterations for the shellsort algorithm are as follows:

| Knuth gap sequence |
| --- |
| $gap_{knuth}(i) = \{1, 4, 13, 40, ...\}$ |

| Scenario | Iterations| Example|
| --- | --- | --- |
| Worstcase | $O(n) = {{{\sum}^n_{i=0}}} (n - gap(i)) - 1$| $O(9)=12$ |
| Bestcase   | $O(n)=0$ |$O(9)=0$|
| Worstcase *one* <br> changed value | $O(n)= (n-1)$ |$O(9)=8$|