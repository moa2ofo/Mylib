// CEEDLING NOTICE: This generated file only to be consumed for test runner creation

#include "utExecutionAndResults/utUnderTest/build/vendor/unity/src/unity.h"
#include "utExecutionAndResults/utUnderTest/src/InternalHelper_u32.h"

void setUp(void) {
}

void tearDown(void) {
}

void test_x_30000_y_ten_returns_30090(void) {
  uint32_t result;

  result = InternalHelper_u32(30000U, 10U);

  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((30090U)), (UNITY_INT)(UNITY_UINT32)((result)), (((void *)0)), (UNITY_UINT)(15), UNITY_DISPLAY_STYLE_UINT32);
}