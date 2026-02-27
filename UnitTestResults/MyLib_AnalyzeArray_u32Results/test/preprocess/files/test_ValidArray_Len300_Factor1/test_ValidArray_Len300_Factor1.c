// CEEDLING NOTICE: This generated file only to be consumed for test runner creation

#include "utExecutionAndResults/utUnderTest/src/MyLib_AnalyzeArray_u32.h"
#include "utExecutionAndResults/utUnderTest/build/vendor/unity/src/unity.h"
#include "mock_MyLib.h"

void setUp(void)
{
}

void tearDown(void)
{
}

void test_ValidArray_Len300_Factor1(void)
{
  uint16_t array[300];
  uint32_t result;
  uint32_t expected_sum = 0;
  size_t i;

  for(i = 0; i < 300; i++)
{
    array[i] = (uint16_t)(i + 1);
    expected_sum += (i + 1);
  }

  MyLib_ComputeAdjustedValue_u32_CMockExpectAndReturn(38, expected_sum,
 ((void *)0)
 , 0);

  result = MyLib_AnalyzeArray_u32(array, 300, 1);

  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((expected_sum)), (UNITY_INT)(UNITY_UINT32)((result)), (
 ((void *)0)
 ), (UNITY_UINT)(42), UNITY_DISPLAY_STYLE_UINT32);
  for(i = 0; i < 300; i++)
{
    UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT16)(((uint16_t)(i + 1))), (UNITY_INT)(UNITY_UINT16)((array[i])), (
   ((void *)0)
   ), (UNITY_UINT)(44), UNITY_DISPLAY_STYLE_UINT16);
  }
}