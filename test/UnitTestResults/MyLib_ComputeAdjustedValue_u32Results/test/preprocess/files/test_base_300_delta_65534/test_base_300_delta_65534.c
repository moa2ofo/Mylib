// CEEDLING NOTICE: This generated file only to be consumed for test runner creation

#include "mock_MyLib.h"
#include "utExecutionAndResults/utUnderTest/build/vendor/unity/src/unity.h"
#include "utExecutionAndResults/utUnderTest/src/MyLib_ComputeAdjustedValue_u32.h"

void setUp(void) {
}

void tearDown(void) {
}

void test_base_300_delta_65534(void) {
  uint32_t l_result_u32;
  uint32_t l_expected_u32 = 400U;
  uint16_t l_delta_u16 = 65534U;
  uint32_t l_intermediate_u32 = 300U * 65534U;

  InternalHelper_u32_CMockExpectAndReturn(17, l_intermediate_u32, (uint16_t)(5U), l_expected_u32);

  l_result_u32 = MyLib_ComputeAdjustedValue_u32(300U, &l_delta_u16);

  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((l_expected_u32)), (UNITY_INT)(UNITY_UINT32)((l_result_u32)), (((void *)0)), (UNITY_UINT)(21), UNITY_DISPLAY_STYLE_UINT32);
}