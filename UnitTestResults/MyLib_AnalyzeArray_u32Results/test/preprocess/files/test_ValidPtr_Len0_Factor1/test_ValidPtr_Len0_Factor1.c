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

void test_ValidPtr_Len0_Factor1(void)
{
  uint16_t array[1] = {42};
  uint32_t result;

  result = MyLib_AnalyzeArray_u32(array, 0, 1);

  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((0)), (UNITY_INT)(UNITY_UINT32)((result)), (
 ((void *)0)
 ), (UNITY_UINT)(33), UNITY_DISPLAY_STYLE_UINT32);
  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT16)((42)), (UNITY_INT)(UNITY_UINT16)((array[0])), (
 ((void *)0)
 ), (UNITY_UINT)(34), UNITY_DISPLAY_STYLE_UINT16);
}