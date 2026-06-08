// CEEDLING NOTICE: This generated file only to be consumed for test runner creation

#include "utExecutionAndResults/utUnderTest/build/vendor/unity/src/unity.h"
#include "mock_MyLib.h"

void setUp(void)
{
}

void tearDown(void)
{
}

void test_factor_u16_1_elements_unchanged(void)
{
  uint16_t values_au16[5] = {10U, 20U, 30U, 40U, 50U};
  uint32_t result_u32;
  uint32_t expected_sum_u32 = 150U;

  MyLib_ComputeAdjustedValue_u32_CMockExpectAndReturn(16, expected_sum_u32,
 ((void *)0)
 , expected_sum_u32);

  result_u32 = AnalyzeArray_u32(values_au16, 5U, 1U);

  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT16)((10U)), (UNITY_INT)(UNITY_UINT16)((values_au16[0])), (
 ((void *)0)
 ), (UNITY_UINT)(20), UNITY_DISPLAY_STYLE_UINT16);
  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT16)((20U)), (UNITY_INT)(UNITY_UINT16)((values_au16[1])), (
 ((void *)0)
 ), (UNITY_UINT)(21), UNITY_DISPLAY_STYLE_UINT16);
  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT16)((30U)), (UNITY_INT)(UNITY_UINT16)((values_au16[2])), (
 ((void *)0)
 ), (UNITY_UINT)(22), UNITY_DISPLAY_STYLE_UINT16);
  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT16)((40U)), (UNITY_INT)(UNITY_UINT16)((values_au16[3])), (
 ((void *)0)
 ), (UNITY_UINT)(23), UNITY_DISPLAY_STYLE_UINT16);
  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT16)((50U)), (UNITY_INT)(UNITY_UINT16)((values_au16[4])), (
 ((void *)0)
 ), (UNITY_UINT)(24), UNITY_DISPLAY_STYLE_UINT16);
  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((expected_sum_u32)), (UNITY_INT)(UNITY_UINT32)((result_u32)), (
 ((void *)0)
 ), (UNITY_UINT)(25), UNITY_DISPLAY_STYLE_UINT32);
}