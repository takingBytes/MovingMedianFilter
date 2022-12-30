#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include "median.h"

#define MAX_SIZE 9
#define MAX_RUN 100

float buffArr[MAX_SIZE];
float* ptArr[MAX_SIZE];
float raw=0;
float med;
median filter;

void main(void)
{
    srand(time(NULL));

    MedianInit(&filter,buffArr,ptArr,MAX_SIZE);
    for (unsigned int i = 0; i < MAX_RUN; i++) 
    {
        raw =(float) (10* (float)rand() / (float)(RAND_MAX));

        med = MedianFilter(&filter,raw);
        printf("iter->%i;",MedianIterationGet(&filter));

        printf(" Pt ");  
        for (unsigned int i = 0; i < MAX_SIZE; i++) 
        {

            printf(";%0.f", *ptArr[i]);
        }

        
        printf("dt");  
        for (unsigned int i = 0; i < MAX_SIZE; i++) 
        {
            printf(";%.f", buffArr[i]);
        }
        
        printf("  %0.1f\n", med);
    }
}