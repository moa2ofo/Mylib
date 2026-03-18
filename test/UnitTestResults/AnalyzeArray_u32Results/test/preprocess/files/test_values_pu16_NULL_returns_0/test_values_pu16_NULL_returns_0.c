// CEEDLING NOTICE: This generated file only to be consumed for test runner creation

#include "mock_MyLib.h"
#include "utExecutionAndResults/utUnderTest/build/vendor/unity/src/unity.h"

void setUp(void) {
}

void tearDown(void) {
}

void test_values_pu16_NULL_returns_0(void) {
  uint32_t result_u32;

  result_u32 = AnalyzeArray_u32(((void *)0), 10U, 5U);

  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((0U)), (UNITY_INT)(UNITY_UINT32)((result_u32)), (((void *)0)), (UNITY_UINT)(16), UNITY_DISPLAY_STYLE_UINT32);
}