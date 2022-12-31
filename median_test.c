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

/*test function declarations*/
static void TestMedianFilterConstantInputEven(void);
static void TestMedianFilterConstantInputOdd(void);
static void TestMedianFilterMixedInputOdd(void);
static void TestMedianFilterTheoreticalMaxIterations(void);

/*helper function declarations*/
static uint8_t calcShellSortMaxIterations(uint8_t size);
static void initBufferWithWorstCase(float* drain, float* source);

void setUp(void)
{  
    MedianInit(&medianFilterOdd, bufferOdd, ptBufferSortedOdd, MEDIAN_SIZE_ODD);
    MedianInit(&medianFilterEven, bufferEven, ptBufferSortedEven, MEDIAN_SIZE_EVEN);
}

void tearDown(void)
{
}

static void TestMedianFilterConstantInputEven(void)
{
    float input[MEDIAN_SIZE_EVEN] = {9,8,7,6,5,4,3,2,1,0};
    float expectedMedian[MEDIAN_SIZE_EVEN] = {0,0,0,0,2.5,4.5,4.5,4.5,4.5,4.5};

    for (uint8_t i = 0; i < MEDIAN_SIZE_EVEN; i++)
    {
        float result = MedianFilter(&medianFilterEven, input[i]);
        TEST_ASSERT_EQUAL_FLOAT(expectedMedian[i], result); 

        for (uint8_t j = 0; j < MEDIAN_SIZE_EVEN; j++) 
        {
            printf("%.f;", *ptBufferSortedEven[j]);
        }
            printf("->  %0.1f\n", result);
    }
}

static void TestMedianFilterConstantInputOdd(void)
{
    float input[MEDIAN_SIZE_ODD] = {9,8,7,6,5,4,3,2,1};
    float expectedMedian[MEDIAN_SIZE_ODD] = {0,0,0,0,5,5,5,5,5};

    for (uint8_t i = 0; i < MEDIAN_SIZE_ODD; i++)
    {
        float result = MedianFilter(&medianFilterOdd, input[i]);
        TEST_ASSERT_EQUAL_FLOAT(expectedMedian[i], result); 

        for (uint8_t j = 0; j < MEDIAN_SIZE_ODD; j++) 
        {
            printf("%.f;", *ptBufferSortedOdd[j]);
        }
            printf("->  %0.1f\n", result);
    }
}

static void TestMedianFilterMixedInputOdd(void)
{
    // Test with odd-sized buffer
    float input[MEDIAN_SIZE_ODD] = {-9, 8, -7, 6, -5, 4, -3, 2, -1};
    float expectedMedian[MEDIAN_SIZE_ODD] = {0, 0, 0, 0, 0, 0, 0, 0, -1};

    for (uint8_t i = 0; i < MEDIAN_SIZE_ODD; i++)
    {
        float result = MedianFilter(&medianFilterOdd, input[i]);
        TEST_ASSERT_EQUAL_FLOAT(expectedMedian[i], result); 

         for (uint8_t j = 0; j < MEDIAN_SIZE_ODD; j++) 
        {
            printf("%.f;", *ptBufferSortedOdd[j]);
        }
            printf("->  %0.1f\n", result);
    }
}

static void TestMedianFilterTheoreticalMaxIterations(void)
{
    float input[MEDIAN_SIZE_ODD] = {9,8,7,6,5,4,3,2,1};
    float expectedMedian[MEDIAN_SIZE_ODD] = {0,0,0,0,5,5,5,5,5};

    initBufferWithWorstCase(bufferOdd,input);
    
    uint8_t maxIteration =calcShellSortMaxIterations(MEDIAN_SIZE_ODD);

    float result = MedianFilter(&medianFilterOdd, input[0]);
    uint8_t iterations = MedianIterationGet(&medianFilterOdd);
    TEST_ASSERT_EQUAL_UINT8(maxIteration, iterations); 
    printf("Iterationcount->  %i\n", iterations);
}

static void initBufferWithWorstCase(float* drain, float* source)
{
    for (uint8_t i = 0; i < MEDIAN_SIZE_ODD; i++) 
    {
        drain[i]=source[i];
    }
}

static uint8_t calcShellSortMaxIterations(uint8_t size)
{
    uint8_t gap = 1;
    uint8_t maxIteration =MEDIAN_SIZE_ODD - gap;

    while (gap < MEDIAN_SIZE_ODD / 3)
    {
        gap = gap * 3 + 1;
        maxIteration += MEDIAN_SIZE_ODD - gap;
    }
    return maxIteration - 1; 
}

int main(void)
{
    UNITY_BEGIN();
    RUN_TEST(TestMedianFilterConstantInputEven);
    RUN_TEST(TestMedianFilterConstantInputOdd);
    RUN_TEST(TestMedianFilterMixedInputOdd);
    RUN_TEST(TestMedianFilterTheoreticalMaxIterations);
    return UNITY_END();
}