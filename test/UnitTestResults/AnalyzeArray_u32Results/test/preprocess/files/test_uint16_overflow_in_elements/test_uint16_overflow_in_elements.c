// CEEDLING NOTICE: This generated file only to be consumed for test runner creation

#include "mock_MyLib.h"
#include "utExecutionAndResults/utUnderTest/build/vendor/unity/src/unity.h"

void setUp(void) {
}

void tearDown(void) {
}

void test_uint16_overflow_in_elements(void) {
  uint16_t values_au16[3] = {40000U, 50000U, 60000U};
  uint32_t result_u32;
  uint32_t expected_sum_u32;

  expected_sum_u32 = (uint32_t)((uint16_t)(40000U * 2U)) + (uint32_t)((uint16_t)(50000U * 2U)) + (uint32_t)((uint16_t)(60000U * 2U));

  MyLib_ComputeAdjustedValue_u32_CMockExpectAndReturn(18, expected_sum_u32, ((void *)0), expected_sum_u32);

  result_u32 = AnalyzeArray_u32(values_au16, 3U, 2U);

  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT16)(((uint16_t)(40000U * 2U))), (UNITY_INT)(UNITY_UINT16)((values_au16[0])), (((void *)0)), (UNITY_UINT)(22), UNITY_DISPLAY_STYLE_UINT16);
  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT16)(((uint16_t)(50000U * 2U))), (UNITY_INT)(UNITY_UINT16)((values_au16[1])), (((void *)0)), (UNITY_UINT)(23), UNITY_DISPLAY_STYLE_UINT16);
  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT16)(((uint16_t)(60000U * 2U))), (UNITY_INT)(UNITY_UINT16)((values_au16[2])), (((void *)0)), (UNITY_UINT)(24), UNITY_DISPLAY_STYLE_UINT16);
  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((expected_sum_u32)), (UNITY_INT)(UNITY_UINT32)((result_u32)), (((void *)0)), (UNITY_UINT)(25), UNITY_DISPLAY_STYLE_UINT32);
}