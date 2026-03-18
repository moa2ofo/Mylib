// CEEDLING NOTICE: This generated file only to be consumed for test runner creation

#include "mock_MyLib.h"
#include "utExecutionAndResults/utUnderTest/build/vendor/unity/src/unity.h"

void setUp(void) {
}

void tearDown(void) {
}

void test_uint32_overflow_in_sum(void) {
  uint16_t values_au16[10];
  uint32_t result_u32;
  uint32_t expected_sum_u32 = 0U;
  size_t i_u32;

  for(i_u32 = 0U; i_u32 < 10U; i_u32++) {
    values_au16[i_u32] = 60000U;
  }

  for(i_u32 = 0U; i_u32 < 10U; i_u32++) {
    expected_sum_u32 += (uint32_t)((uint16_t)(60000U * 1000U));
  }

  MyLib_ComputeAdjustedValue_u32_CMockExpectAndReturn(25, expected_sum_u32, ((void *)0), expected_sum_u32);

  result_u32 = AnalyzeArray_u32(values_au16, 10U, 1000U);

  for(i_u32 = 0U; i_u32 < 10U; i_u32++) {
    UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT16)(((uint16_t)(60000U * 1000U))), (UNITY_INT)(UNITY_UINT16)((values_au16[i_u32])), (((void *)0)), (UNITY_UINT)(30), UNITY_DISPLAY_STYLE_UINT16);
  }
  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((expected_sum_u32)), (UNITY_INT)(UNITY_UINT32)((result_u32)), (((void *)0)), (UNITY_UINT)(32), UNITY_DISPLAY_STYLE_UINT32);
}