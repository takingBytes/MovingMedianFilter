#include <stdint.h>
#include "median.h"
#include "unity.h"


#define MEDIAN_SIZE_ODD 9
#define MEDIAN_SIZE_EVEN MEDIAN_SIZE_ODD+1

static float bufferOdd[MEDIAN_SIZE_ODD];
static float* ptBufferSortedOdd[MEDIAN_SIZE_ODD];

static float bufferEven[MEDIAN_SIZE_EVEN];
static float* ptBufferSortedEven[MEDIAN_SIZE_EVEN];


static median medianFilterOdd,medianFilterEven;

void setUp(void)
{
    MedianInit(&medianFilterOdd, bufferOdd, ptBufferSortedOdd, MEDIAN_SIZE_ODD);
    MedianInit(&medianFilterEven, bufferEven, ptBufferSortedEven, MEDIAN_SIZE_EVEN);
}

void tearDown(void)
{
}

void test_MedianFilter_constantInputStream_ODD(void)
{
    float input[MEDIAN_SIZE_ODD] = {9,8,7,6,5,4,3,2,1};
    float expectedMedian[MEDIAN_SIZE_ODD] = {0,0,0,0,5,5,5,5,5};

    for (uint8_t i = 0; i < MEDIAN_SIZE_ODD; i++)
    {
        float result = MedianFilter(&medianFilterOdd, input[i]);
        TEST_ASSERT_EQUAL_FLOAT(expectedMedian[i], result); 

        for (uint8_t j = 0; j < MEDIAN_SIZE_ODD; j++) 
        {
            printf("%.f;", bufferOdd[j]);
        }
            printf("->  %0.1f\n", result);
    }
}

void test_MedianFilter_constantInputStream_EVEN(void)
{
    float input[MEDIAN_SIZE_EVEN] = {9,8,7,6,5,4,3,2,1,0};
    float expectedMedian[MEDIAN_SIZE_EVEN] = {0,0,0,0,2.5,4.5,4.5,4.5,4.5,4.5};

    for (uint8_t i = 0; i < MEDIAN_SIZE_EVEN; i++)
    {
        float result = MedianFilter(&medianFilterEven, input[i]);
        TEST_ASSERT_EQUAL_FLOAT(expectedMedian[i], result); 

        for (uint8_t j = 0; j < MEDIAN_SIZE_EVEN; j++) 
        {
            printf("%.f;", bufferEven[j]);
        }
            printf("->  %0.1f\n", result);
    }
}

int main(void)
{
    UNITY_BEGIN();
    RUN_TEST(test_MedianFilter_constantInputStream_EVEN);
    RUN_TEST(test_MedianFilter_constantInputStream_ODD);
    return UNITY_END();
}