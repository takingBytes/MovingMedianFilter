#include <stdbool.h>
#include <stdio.h>
#define MAX_SIZE 9





/*direct sorting*/
// Function to swap the values of two variables
void swap(float *a, float *b)
{
    float temp = *a;
    *a = *b;
    *b = temp;
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
            {
                break;
            }
        }
    }
}

void shell_sort(float *arr, int size)
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


/*pointer based sorting*/
void swap_pt(float **a, float **b)
{ 
    float *temp = *a;
    *a = *b;
    *b = temp;
}

int bubble_sort_pt(float** pointers, int n) 
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
    bool swapped=false;
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (*pointers[j] > *pointers[j + 1])
            {   
                iteration_count++;
                swap_pt(&pointers[j], &pointers[j + 1]);
                swapped=true;
            }
        }

        if (!swapped)  /* If flag is still false, array is sorted */
        {
            break;
        }
    }
    return iteration_count;
}

int shell_sort_pt(float** pointers, int n)
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
            float *temp = pointers[i];
            int j;
            for (j = i; j >= gap && *pointers[j - gap] > *temp; j -= gap)
            {
                swap_pt(&pointers[j], &pointers[j - gap]);
                iteration_count++;
            }
            pointers[j] = temp;
        }

        /* calculate next gap using Knuth sequence */
        gap = (gap - 1) / 3;
    }
    return iteration_count;
}


float  data_bc[MAX_SIZE] = {10,2,3,4,5,6,7,8,9};
float  data_wc[MAX_SIZE] = {9,8,7,6,5,4,3,2,1};
float* pointers[MAX_SIZE];
int iterations=0;

int main() {

  for (int i = 0; i < MAX_SIZE; i++) 
  {
    pointers[i] = &data_bc[i];
  }

  iterations=shell_sort_pt(pointers, MAX_SIZE);
  for (int i = 0; i < MAX_SIZE; i++) 
  {
    printf("pt:%.1f ", *pointers[i]);
  }
  printf("iterations_bc:%i\n",iterations);


    for (int i = 0; i < MAX_SIZE; i++) 
  {
    pointers[i] = &data_wc[i];
  }

  iterations=shell_sort_pt(pointers, MAX_SIZE);
  for (int i = 0; i < MAX_SIZE; i++) 
  {
    printf("pt:%.1f ", *pointers[i]);
  }
  printf("iterations_wc:%i\n",iterations);

  for (int i = 0; i < MAX_SIZE; i++) 
  {
    printf("dt:%.1f ", data_wc[i]);
  }
  printf("\n");
  return 0;
}
