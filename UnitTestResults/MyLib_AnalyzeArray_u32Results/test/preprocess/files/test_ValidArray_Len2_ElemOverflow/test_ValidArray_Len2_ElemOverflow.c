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

void test_ValidArray_Len2_ElemOverflow(void)
{
  uint16_t array[2] = {40000, 50000};
  uint32_t result;
  uint16_t expected_elem0 = (uint16_t)(40000 * 2);
  uint16_t expected_elem1 = (uint16_t)(50000 * 2);
  uint32_t expected_sum = (uint32_t)expected_elem0 + (uint32_t)expected_elem1;

  MyLib_ComputeAdjustedValue_u32_CMockExpectAndReturn(34, expected_sum,
 ((void *)0)
 , 0);

  result = MyLib_AnalyzeArray_u32(array, 2, 2);

  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((expected_sum)), (UNITY_INT)(UNITY_UINT32)((result)), (
 ((void *)0)
 ), (UNITY_UINT)(38), UNITY_DISPLAY_STYLE_UINT32);
  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT16)((expected_elem0)), (UNITY_INT)(UNITY_UINT16)((array[0])), (
 ((void *)0)
 ), (UNITY_UINT)(39), UNITY_DISPLAY_STYLE_UINT16);
  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT16)((expected_elem1)), (UNITY_INT)(UNITY_UINT16)((array[1])), (
 ((void *)0)
 ), (UNITY_UINT)(40), UNITY_DISPLAY_STYLE_UINT16);
}