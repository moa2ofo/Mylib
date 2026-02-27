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

void test_two_elem_factor_one(void)
{
  test_array[0] = 10;
  test_array[1] = 20;
  uint32_t result = MyLib_AnalyzeArray_u32(test_array, 2, 1);
  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((30)), (UNITY_INT)(UNITY_UINT32)((result)), (
 ((void *)0)
 ), (UNITY_UINT)(24), UNITY_DISPLAY_STYLE_UINT32);
}