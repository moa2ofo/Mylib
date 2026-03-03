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

void test_ValidArray_Len10_Factor0_AllZero(void)
{
  uint16_t array[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  uint32_t result;
  size_t i;

  MyLib_ComputeAdjustedValue_u32_CMockExpectAndReturn(32, 0,
 ((void *)0)
 , 0);

  result = MyLib_AnalyzeArray_u32(array, 10, 0);

  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((0)), (UNITY_INT)(UNITY_UINT32)((result)), (
 ((void *)0)
 ), (UNITY_UINT)(36), UNITY_DISPLAY_STYLE_UINT32);
  for(i = 0; i < 10; i++)
{
    UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT16)((0)), (UNITY_INT)(UNITY_UINT16)((array[i])), (
   ((void *)0)
   ), (UNITY_UINT)(38), UNITY_DISPLAY_STYLE_UINT16);
  }
}