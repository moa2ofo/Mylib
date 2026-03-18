// CEEDLING NOTICE: This generated file only to be consumed for test runner creation

#include "mock_MyLib.h"
#include "utExecutionAndResults/utUnderTest/build/vendor/unity/src/unity.h"

void setUp(void) {
}

void tearDown(void) {
}

void test_len_u32_300_factor_1_mid_range(void) {
  uint16_t values_au16[300];
  uint32_t result_u32;
  uint32_t expected_sum_u32 = 0U;
  size_t i_u32;

  for(i_u32 = 0U; i_u32 < 300U; i_u32++) {
    values_au16[i_u32] = 2U;
    expected_sum_u32 += 2U;
  }

  MyLib_ComputeAdjustedValue_u32_CMockExpectAndReturn(22, expected_sum_u32, ((void *)0), expected_sum_u32);

  result_u32 = AnalyzeArray_u32(values_au16, 300U, 1U);

  for(i_u32 = 0U; i_u32 < 300U; i_u32++) {
    UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT16)((2U)), (UNITY_INT)(UNITY_UINT16)((values_au16[i_u32])), (((void *)0)), (UNITY_UINT)(27), UNITY_DISPLAY_STYLE_UINT16);
  }
  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((expected_sum_u32)), (UNITY_INT)(UNITY_UINT32)((result_u32)), (((void *)0)), (UNITY_UINT)(29), UNITY_DISPLAY_STYLE_UINT32);
}