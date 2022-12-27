#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include "median.h"
#include "sorting.h"

#define MAX_SIZE 13
#define MAX_RUN 10000

//float arr[MAX_SIZE] = {1,2,3,4,5,6,7,8,9};
float arr[MAX_SIZE] = {9,8,7,6,5,4,3,2,1};
float* ptArr[MAX_SIZE];
float raw=0;
float med;
void main(void)
{
   srand(time(NULL));
    int index = 0;
 /*
  for (int i = 0; i < MAX_RUN; i++) 
  {
    float raw =(float) (5* (int)rand() / (int)(RAND_MAX));
    arr[index] = raw;
    float med = median(arr, MAX_SIZE);
    printf("raw;%.0f med;%.0f\n", raw,med);
    index = (index + 1) % MAX_SIZE;
  }
*/

    pointerArrayInit(arr,ptArr,MAX_SIZE);
  for (int i = 0; i < MAX_RUN; i++) 
  {
    //pointerArrayInit(arr,ptArr,MAX_SIZE);
    med = medianPt(ptArr, MAX_SIZE);
    //printf("\n");

    
  /*  for (int i = 0; i < MAX_SIZE; i++) 
    {
        printf("pt:%.1f ", *ptArr[i]);
    }
    printf("\n");
    
*/
   /* for (int i = 0; i < MAX_SIZE; i++) 
    {
        printf("dt:%.1f ", arr[i]);
    }
    printf("\n");
    */

   
   //printf("raw;%.0f med;%.0f\n", raw,med);
   

    raw =(float) (10* (int)rand() / (int)(RAND_MAX));
    arr[index] = raw;
    index = (index + 1) % MAX_SIZE;
  }
  

  //TestSort();

}