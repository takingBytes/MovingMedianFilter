# Median Filter

The median filter is a simple yet effective algorithm for removing noise from an input signal. It works by computing the median of a set of values, which is defined as the value that is greater than or equal to half the values in the set.

## Initialization

Before the median filter can be used, it must be initialized using the `MedianInit` function. This function takes the following arguments:

- `this`: A pointer to the `median` struct that stores the internal state of the median filter.
- `buffer`: A pointer to the circular buffer that will store the input values. The buffer must be of size `size`.
- `ptBufferSorted`: A pointer to an array of pointers to the values in the circular buffer, sorted in ascending order. The array must be of size `size`.
- `size`: The size of the circular buffer and sorted array.

The `MedianInit` function sets up the circular buffer and sorted array, and initializes the `index` variable to zero. It also checks that the input pointers are not `NULL` and that the buffer size is not zero.