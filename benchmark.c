#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#define N 9  // size of the array to sort
void swap(float **a, float **b)
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
    int iteration_count = 0; 
    bool swapped=false;
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (*pointers[j] > *pointers[j + 1])
            {   
                iteration_count++;
                swap(&pointers[j], &pointers[j + 1]);
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

int shell_sort_pt(float** pointers, int size)
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

    /* calculate initial gap using Knuth sequence */
    int gap = 1;
    while (gap < size / 3)
    {
        gap = gap * 3 + 1;
    }

    while (gap > 0)
    {
        /* Perform gap-insertion sort */
        for (int i = gap; i < size; i++)
        {   
            float *temp = pointers[i];
            int j;
            for (j = i; j >= gap && *pointers[j - gap] > *temp; j -= gap)
            {
                swap(&pointers[j], &pointers[j - gap]);
                iteration_count++;
            }
            pointers[j] = temp;
        }

        /* calculate next gap using Knuth sequence */
        gap = (gap - 1) / 3;
    }
    return iteration_count;
}
int main() {
  float **pointers = malloc(N * sizeof(float*));
  for (int i = 0; i < N; i++) {
    pointers[i] = malloc(sizeof(float));
    *pointers[i] = (float)i;
  }

  // shuffle the array
  srand(time(NULL));  // seed the random number generator
  for (int i = 0; i < N; i++) {
    int j = rand() % N;
    swap(&pointers[i], &pointers[j]);
  }

  // measure the time taken by bubble sort
  clock_t start = clock();
  int bubble_iterations = bubble_sort_pt(pointers, N);
  clock_t stop = clock();
  double duration = (double)(stop - start) / CLOCKS_PER_SEC;
  printf("Bubble sort: %d iterations, %.6f seconds\n", bubble_iterations, duration);

  // shuffle the array again
  srand(time(NULL));  // seed the random number generator
  for (int i = 0; i < N; i++) {
    int j = rand() % N;
    swap(&pointers[i], &pointers[j]);
  }

  // measure the time taken by shell sort
  start = clock();
  int shell_iterations = shell_sort_pt(pointers, N);
  stop = clock();
  duration = (double)(stop - start) / CLOCKS_PER_SEC;
  printf("Shell sort: %d iterations, %.6f seconds\n", shell_iterations, duration);

  // clean up
  for (int i = 0; i < N; i++) {
    free(pointers[i]);
  }
  free(pointers);

  return 0;
}
