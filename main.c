#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include "median.h"
#include "sorting.h"

#define MAX_SIZE 10
#define MAX_RUN 100

float arr[MAX_SIZE] = {10,9,8,7,6,5,4,3,2,1};
float* ptArr[MAX_SIZE];
float raw=0;
float med;

void main(void)
{
    srand(time(NULL));
    int index = 0;

    pointerArrayInit(arr,ptArr,MAX_SIZE);
    for (int i = 0; i < MAX_RUN; i++) 
    {
        med = medianPt(ptArr, MAX_SIZE);

        printf("pt");  
        for (int i = 0; i < MAX_SIZE; i++) 
        {
            printf(";%.f", *ptArr[i]);
        }
        printf(";->%.1f\n", med);
            
        raw =(float) (10* (int)rand() / (int)(RAND_MAX));
        arr[index] = raw;
        index = (index + 1) % MAX_SIZE;
    }
}