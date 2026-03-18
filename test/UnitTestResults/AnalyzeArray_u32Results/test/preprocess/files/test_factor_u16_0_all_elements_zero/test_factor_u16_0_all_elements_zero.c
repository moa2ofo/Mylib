// CEEDLING NOTICE: This generated file only to be consumed for test runner creation

#include "mock_MyLib.h"
#include "utExecutionAndResults/utUnderTest/build/vendor/unity/src/unity.h"

void setUp(void) {
}

void tearDown(void) {
}

void test_factor_u16_0_all_elements_zero(void) {
  uint16_t values_au16[5] = {10U, 20U, 30U, 40U, 50U};
  uint32_t result_u32;
  size_t i_u32;

  MyLib_ComputeAdjustedValue_u32_CMockExpectAndReturn(16, 0U, ((void *)0), 0U);

  result_u32 = AnalyzeArray_u32(values_au16, 5U, 0U);

  for(i_u32 = 0U; i_u32 < 5U; i_u32++) {
    UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT16)((0U)), (UNITY_INT)(UNITY_UINT16)((values_au16[i_u32])), (((void *)0)), (UNITY_UINT)(21), UNITY_DISPLAY_STYLE_UINT16);
  }
  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((0U)), (UNITY_INT)(UNITY_UINT32)((result_u32)), (((void *)0)), (UNITY_UINT)(23), UNITY_DISPLAY_STYLE_UINT32);
}