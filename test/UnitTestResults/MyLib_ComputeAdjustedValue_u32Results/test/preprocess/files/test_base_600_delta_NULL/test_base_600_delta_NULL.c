// CEEDLING NOTICE: This generated file only to be consumed for test runner creation

#include "mock_MyLib.h"
#include "utExecutionAndResults/utUnderTest/build/vendor/unity/src/unity.h"
#include "utExecutionAndResults/utUnderTest/src/MyLib_ComputeAdjustedValue_u32.h"

void setUp(void) {
}

void tearDown(void) {
}

void test_base_600_delta_NULL(void) {
  uint32_t l_result_u32;
  uint32_t l_expected_u32 = 500U;

  InternalHelper_u32_CMockExpectAndReturn(15, 600U, (uint16_t)(5U), l_expected_u32);

  l_result_u32 = MyLib_ComputeAdjustedValue_u32(600U, ((void *)0));

  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((l_expected_u32)), (UNITY_INT)(UNITY_UINT32)((l_result_u32)), (((void *)0)), (UNITY_UINT)(19), UNITY_DISPLAY_STYLE_UINT32);
}