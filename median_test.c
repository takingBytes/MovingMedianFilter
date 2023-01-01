#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>

#include "median.h"
#include "unity.h"

#define MEDIAN_SIZE_EVEN 10
#define MEDIAN_SIZE_ODD MEDIAN_SIZE_EVEN-1


static float buffer[MEDIAN_SIZE_EVEN];
static float* ptBufferSorted[MEDIAN_SIZE_EVEN];

static median medianFilterOdd,medianFilterEven;

/*test function declarations*/
static void Test_ConstantInput_Even(void);
static void Test_ConstantInput_Odd(void);
static void Test_MixedInput_Odd(void);
static void Test_TheoreticalMaxIterations(void);
static void Test_PracticalMaxIterations(void);
static void Test_InvalidSize(void);


/*helper function declarations*/
static uint8_t ShellSortIterations_Calc(uint8_t size);
static void Buffer_Init(float* drain, float* source);

void setUp(void)
{  
    MedianInit(&medianFilterOdd, buffer, ptBufferSorted, MEDIAN_SIZE_ODD);
    MedianInit(&medianFilterEven, buffer, ptBufferSorted, MEDIAN_SIZE_EVEN);
}

void tearDown(void)
{
}

static void Test_ConstantInput_Even(void)
{
    float input[MEDIAN_SIZE_EVEN] = {9,8,7,6,5,4,3,2,1,0};
    float expectedMedian[MEDIAN_SIZE_EVEN] = {0,0,0,0,2.5,4.5,4.5,4.5,4.5,4.5};

    for (uint8_t i = 0; i < MEDIAN_SIZE_EVEN; i++)
    {
        float median = MedianFilter(&medianFilterEven, input[i]);
        TEST_ASSERT_EQUAL_FLOAT(expectedMedian[i], median); 

        for (uint8_t j = 0; j < MEDIAN_SIZE_EVEN; j++) 
        {
            printf("%.f;", *ptBufferSorted[j]);
        }
            printf(" med->  %0.1f\n", median);
    }
}

static void Test_ConstantInput_Odd(void)
{
    float input[MEDIAN_SIZE_ODD] = {9,8,7,6,5,4,3,2,1};
    float expectedMedian[MEDIAN_SIZE_ODD] = {0,0,0,0,5,5,5,5,5};

    for (uint8_t i = 0; i < MEDIAN_SIZE_ODD; i++)
    {
        float median = MedianFilter(&medianFilterOdd, input[i]);
        TEST_ASSERT_EQUAL_FLOAT(expectedMedian[i], median); 

        for (uint8_t j = 0; j < MEDIAN_SIZE_ODD; j++) 
        {
            printf("%.f;", *ptBufferSorted[j]);
        }
            printf(" med->  %0.1f\n", median);
    }
}

static void Test_MixedInput_Odd(void)
{
    float input[MEDIAN_SIZE_ODD] = {-9,8,-7,6,-5,4,-3,2,-1};
    float expectedMedian[MEDIAN_SIZE_ODD] = {0,0,0,0,0,0,0,0,-1};

    for (uint8_t i = 0; i < MEDIAN_SIZE_ODD; i++)
    {
        float median = MedianFilter(&medianFilterOdd, input[i]);
        TEST_ASSERT_EQUAL_FLOAT(expectedMedian[i], median); 

         for (uint8_t j = 0; j < MEDIAN_SIZE_ODD; j++) 
        {
            printf("%.f;", *ptBufferSorted[j]);
        }
            printf(" med->  %0.1f\n", median);
    }
}

static void Test_TheoreticalMaxIterations(void)
{
    float input[MEDIAN_SIZE_ODD] = {9,8,7,6,5,4,3,2,1};

    Buffer_Init(buffer,input);
    
    uint8_t maxIteration =ShellSortIterations_Calc(MEDIAN_SIZE_ODD);

    float result = MedianFilter(&medianFilterOdd, input[0]);
    uint8_t iterations = MedianIterationGet(&medianFilterOdd);
    TEST_ASSERT_EQUAL_UINT8(maxIteration, iterations); 
    printf("Theoretical-Max-Iterations->  %i\n", iterations);
}

static void Test_PracticalMaxIterations(void)
{
    float input[MEDIAN_SIZE_ODD] = {1,2,3,4,5,6,7,8,9};

    Buffer_Init(buffer,input);
    uint8_t maxIteration =MEDIAN_SIZE_ODD-1;

    float result = MedianFilter(&medianFilterOdd, input[maxIteration]+1);
    uint8_t iterations = MedianIterationGet(&medianFilterOdd);
    TEST_ASSERT_EQUAL_UINT8(maxIteration, iterations); 

    printf("Practical-Max-Iterations->  %i\n", iterations);
}

static void Test_InvalidSize(void)
{
    MedianInit(&medianFilterOdd, buffer, ptBufferSorted, 0);
    TEST_ASSERT_FALSE(medianFilterOdd.init);

    MedianInit(&medianFilterOdd, buffer, ptBufferSorted, 1);
    TEST_ASSERT_FALSE(medianFilterOdd.init);

    MedianInit(&medianFilterOdd, buffer, ptBufferSorted, 2);
    TEST_ASSERT_FALSE(medianFilterOdd.init);

    MedianInit(&medianFilterOdd, buffer, ptBufferSorted, 3);
    TEST_ASSERT_TRUE(medianFilterOdd.init);    
}

static void Test_MinSize(void)
{
    MedianInit(&medianFilterOdd, buffer, ptBufferSorted, 3);
    const uint8_t minSize=3;

    float input[] = {3,2,1,3,2,1};
    float expectedMedian[] = {0,2,2,2,2,2};

    for (uint8_t i = 0; i < minSize*2; i++)
    {
        float result = MedianFilter(&medianFilterOdd, input[i]);
        TEST_ASSERT_EQUAL_FLOAT(expectedMedian[i], result); 

        for (uint8_t j = 0; j < minSize; j++) 
        {
            printf("%.f;", *ptBufferSorted[j]);
        }
            printf(" med->  %0.1f\n", result);
    }
}


/*helper functions*/
static void Buffer_Init(float* drain, float* source)
{
    for (uint8_t i = 0; i < MEDIAN_SIZE_ODD; i++) 
    {
        drain[i]=source[i];
    }
}

/* Calculates maximum number of iterations needed for shell sort using the Knuth sequence.*/
static uint8_t ShellSortIterations_Calc(uint8_t size)
{
    uint8_t gap = 1;
    uint8_t maxIteration = size - gap;

    while (gap < size / 3)
    {
        gap = gap * 3 + 1;
        maxIteration += size - gap;
    }
    maxIteration=maxIteration-1;

    return maxIteration; 
}

int main(void)
{
    UNITY_BEGIN();
    RUN_TEST(Test_ConstantInput_Even);
    RUN_TEST(Test_ConstantInput_Odd);
    RUN_TEST(Test_MixedInput_Odd);
    RUN_TEST(Test_TheoreticalMaxIterations);
    RUN_TEST(Test_PracticalMaxIterations);
    RUN_TEST(Test_InvalidSize);
    RUN_TEST(Test_MinSize);
    return UNITY_END();
}