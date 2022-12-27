#include <stdbool.h>
#include <stdio.h>
#include "sorting.h"

//#define MAX_SIZE 9

/*direct sorting*/
// Function to swap the values of two variables
static void swap(float *a, float *b)
{
    float temp = *a;
    *a = *b;
    *b = temp;
}

extern void shell_sort(float *arr, int size)
{
    /*
    WC Time: O(n^2)
    BC Time: O(n*log(n))

    WC Space: O(1)
    no additional memory needed, with higher sizes
    */

    // Calculate initial gap
    int gap = size / 2;

    while (gap > 0)
    {
        // Perform gap-insertion sort
        for (int i = gap; i < size; i++)
        {
            float temp = arr[i];
            int j;
            for (j = i; j >= gap && arr[j - gap] > temp; j -= gap)
            {
                arr[j] = arr[j - gap];
            }
            arr[j] = temp;
        }

        // Calculate next gap
        gap /= 2;
    }
}


// Function to sort the values in the array using bubble sort
void bubble_sort(float *arr, int n)
{
    /*
    WC Time: O(n^2)
    BC Time: O(n)

    WC Space: O(1)
    no additional memory needed, with higher sizes
    */

    bool swapped=false;
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (*(arr + j) > *(arr + j + 1))
            {
                swap(arr + j, arr + j + 1);
                swapped=true;
            }

            if (!swapped)  // If the flag is still 0 after the inner loop, the array is sorted
              break;
        }
    }
}

/*pointer based sorting*/
static void swap_pt(float **a, float **b)
{ 
    float *temp = *a;
    *a = *b;
    *b = temp;
}

extern int bubble_sort_pt(float** pointers, int n) 
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
if ((pointers == NULL)||(n == 0))
{
  return 0;
}
    int iteration_count = 0; 
    // Perform bubble sort
    for (int i = 0; i < n - 1; i++)
    {
        bool swapped = false;
        for (int j = 0; j < n - i - 1; j++)
        {
            if (*pointers[j] > *pointers[j + 1])
            {   
                iteration_count++;
                swap_pt(&pointers[j], &pointers[j + 1]);
                swapped = true;
            }
        }
        if (!swapped)
        {
           break;
        }
    }
    return iteration_count;
}

extern int insertion_sort_pt(float** pointers, int n) 
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

   int iteration_count = 0; 

  if ((pointers == NULL)||(n == 0)) 
  {
    return 0;
  }

  for (int i = 1; i < n; i++) 
  {
    float* current_value = pointers[i];
    int current_index = i;
    /*
        Shift all elements to the right of the current element
        until we find the correct position for the current element
    */
    while (current_index > 0 && *pointers[current_index - 1] > *current_value) 
    {
      swap_pt(&pointers[current_index], &pointers[current_index - 1]);
      current_index--;
      iteration_count++;
    }
    /* Insert the current element into its correct position*/
    pointers[current_index] = current_value;
  }
  /* Return the number of iterations required to sort the array*/
  return iteration_count;
}

extern int shell_sort_pt(float** pointers, int n)
{
  /* Knuth sequence:  gap(0..i)=[1, 4, 13, 40,...]
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

  int iteration_count = 0; 
  int gap = 1;

  if ((pointers == NULL)||(n == 0))
  {
    return 0;
  }

    /* calculate initial gap using Knuth sequence */
    while (gap < n / 3)
    {
        gap = gap * 3 + 1;
    }

    while (gap > 0)
    {
        /* Perform gap-insertion sort */
        for (int i = gap; i < n; i++)
        {   
            float* current_value = pointers[i];
            int current_index = i;
            while (current_index >=gap && *pointers[current_index - gap] > *current_value) 
            {
                swap_pt(&pointers[current_index], &pointers[current_index - gap]);
                current_index-= gap;
                iteration_count++;
            }
            pointers[current_index] = current_value;
        }

        /* calculate next gap using Knuth sequence */
        gap = (gap - 1) / 3;
    }
    return iteration_count;
}
extern void pointerArrayInit(float *array,float **ptArray,int size)
{
  for (int i = 0; i < size; i++) 
    ptArray[i] = &array[i];
}

#define TEST_SIZE 9

float  data_bc[TEST_SIZE] = {1,2,3,4,5,6,7,8,9};
float  data_wc[TEST_SIZE] = {9,8,7,6,5,4,3,2,1};
float* pointers[TEST_SIZE];
int iterations=0;

extern void TestSort(void) 
{
  pointerArrayInit(data_bc,pointers,TEST_SIZE);
  iterations=shell_sort_pt(pointers, TEST_SIZE);

  for (int i = 0; i < TEST_SIZE; i++) 
    printf("pt:%.1f ", *pointers[i]);

  printf("iterations_bc:%i\n",iterations);

  pointerArrayInit(data_wc,pointers,TEST_SIZE);
  iterations=shell_sort_pt(pointers, TEST_SIZE);

  for (int i = 0; i < TEST_SIZE; i++) 
    printf("pt:%.1f ", *pointers[i]);

  printf("iterations_wc:%i\n",iterations);

  for (int i = 0; i < TEST_SIZE; i++) 
    printf("dt:%.1f ", data_wc[i]);

  printf("\n");
}
