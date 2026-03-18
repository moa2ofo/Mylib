// CEEDLING NOTICE: This generated file only to be consumed for test runner creation

#include "utExecutionAndResults/utUnderTest/build/vendor/unity/src/unity.h"
#include "utExecutionAndResults/utUnderTest/src/InternalHelper_u32.h"

void setUp(void) {
}

void tearDown(void) {
}

void test_x_60534_y_one_returns_60534(void) {
  uint32_t result;

  result = InternalHelper_u32(60534U, 1U);

  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((60534U)), (UNITY_INT)(UNITY_UINT32)((result)), (((void *)0)), (UNITY_UINT)(15), UNITY_DISPLAY_STYLE_UINT32);
}