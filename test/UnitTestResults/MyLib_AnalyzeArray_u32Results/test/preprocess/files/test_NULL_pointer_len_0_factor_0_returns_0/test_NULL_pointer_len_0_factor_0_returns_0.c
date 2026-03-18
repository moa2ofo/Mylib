// CEEDLING NOTICE: This generated file only to be consumed for test runner creation

#include "mock_MyLib.h"
#include "utExecutionAndResults/utUnderTest/build/vendor/unity/src/unity.h"
#include "utExecutionAndResults/utUnderTest/src/MyLib_AnalyzeArray_u32.h"

void setUp(void) {
}

void tearDown(void) {
}

void test_NULL_pointer_len_0_factor_0_returns_0(void) {
  uint32_t result;

  result = MyLib_AnalyzeArray_u32(((void *)0), 0U, 0U);

  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((0U)), (UNITY_INT)(UNITY_UINT32)((result)), (((void *)0)), (UNITY_UINT)(20), UNITY_DISPLAY_STYLE_UINT32);
}