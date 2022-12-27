#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include "median.h"
#include "sorting.h"

#define MAX_SIZE 10
#define MAX_RUN 100

float arr[MAX_SIZE];
float* ptArr[MAX_SIZE];
float raw=0;
float med;

median filter;

void main(void)
{
    srand(time(NULL));
    MedianInit(&filter,arr,ptArr,MAX_SIZE);
    for (unsigned int i = 0; i < MAX_RUN; i++) 
    {
        raw =(float) (10* (unsigned int)rand() / (unsigned int)(RAND_MAX))+1;

        med = MedianFilter(&filter,raw);

        printf("pt");  
        for (unsigned int i = 0; i < MAX_SIZE; i++) 
        {
            printf(";%.f", *ptArr[i]);
        }

       /*
        printf("dt");  
        for (unsigned int i = 0; i < MAX_SIZE; i++) 
        {
            printf(";%.f", arr[i]);
        }
        */
        printf(";->%.1f\n", med);

    }
}