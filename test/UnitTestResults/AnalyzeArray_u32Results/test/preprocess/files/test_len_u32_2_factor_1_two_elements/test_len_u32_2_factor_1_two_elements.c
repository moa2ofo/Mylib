// CEEDLING NOTICE: This generated file only to be consumed for test runner creation

#include "utExecutionAndResults/utUnderTest/build/vendor/unity/src/unity.h"
#include "mock_MyLib.h"

void setUp(void)
{
}

void tearDown(void)
{
}

void test_len_u32_2_factor_1_two_elements(void)
{
  uint16_t values_au16[2] = {10U, 20U};
  uint32_t result_u32;
  uint32_t expected_sum_u32 = 30U;

  MyLib_ComputeAdjustedValue_u32_CMockExpectAndReturn(16, expected_sum_u32,
 ((void *)0)
 , expected_sum_u32);

  result_u32 = AnalyzeArray_u32(values_au16, 2U, 1U);

  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT16)((10U)), (UNITY_INT)(UNITY_UINT16)((values_au16[0])), (
 ((void *)0)
 ), (UNITY_UINT)(20), UNITY_DISPLAY_STYLE_UINT16);
  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT16)((20U)), (UNITY_INT)(UNITY_UINT16)((values_au16[1])), (
 ((void *)0)
 ), (UNITY_UINT)(21), UNITY_DISPLAY_STYLE_UINT16);
  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((expected_sum_u32)), (UNITY_INT)(UNITY_UINT32)((result_u32)), (
 ((void *)0)
 ), (UNITY_UINT)(22), UNITY_DISPLAY_STYLE_UINT32);
}