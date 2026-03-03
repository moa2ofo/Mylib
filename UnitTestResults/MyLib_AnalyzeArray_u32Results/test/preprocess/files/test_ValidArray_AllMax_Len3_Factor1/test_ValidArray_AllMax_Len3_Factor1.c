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

void test_ValidArray_AllMax_Len3_Factor1(void)
{
  uint16_t array[3] = {65535, 65535, 65535};
  uint32_t result;
  uint32_t expected_sum = 3 * 65535;

  MyLib_ComputeAdjustedValue_u32_CMockExpectAndReturn(32, expected_sum,
 ((void *)0)
 , 0);

  result = MyLib_AnalyzeArray_u32(array, 3, 1);

  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((expected_sum)), (UNITY_INT)(UNITY_UINT32)((result)), (
 ((void *)0)
 ), (UNITY_UINT)(36), UNITY_DISPLAY_STYLE_UINT32);
  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT16)((65535)), (UNITY_INT)(UNITY_UINT16)((array[0])), (
 ((void *)0)
 ), (UNITY_UINT)(37), UNITY_DISPLAY_STYLE_UINT16);
  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT16)((65535)), (UNITY_INT)(UNITY_UINT16)((array[1])), (
 ((void *)0)
 ), (UNITY_UINT)(38), UNITY_DISPLAY_STYLE_UINT16);
  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT16)((65535)), (UNITY_INT)(UNITY_UINT16)((array[2])), (
 ((void *)0)
 ), (UNITY_UINT)(39), UNITY_DISPLAY_STYLE_UINT16);
}