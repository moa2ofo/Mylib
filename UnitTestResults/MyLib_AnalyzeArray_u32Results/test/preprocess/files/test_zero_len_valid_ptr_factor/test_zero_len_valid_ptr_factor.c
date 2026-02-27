// CEEDLING NOTICE: This generated file only to be consumed for test runner creation

#include "utExecutionAndResults/utUnderTest/src/MyLib_AnalyzeArray_u32.h"
#include "utExecutionAndResults/utUnderTest/build/vendor/unity/src/unity.h"
#include "mock_MyLib.h"

static uint16_t test_array[100];

void setUp(void)
{
  for(size_t i = 0; i < 100; i++)
{
    test_array[i] = 0;
  }
}

void tearDown(void)
{
}

void test_zero_len_valid_ptr_factor(void)
{
  test_array[0] = 100;
  uint32_t result = MyLib_AnalyzeArray_u32(test_array, 0, 5);
  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((0)), (UNITY_INT)(UNITY_UINT32)((result)), (
 ((void *)0)
 ), (UNITY_UINT)(23), UNITY_DISPLAY_STYLE_UINT32);
}