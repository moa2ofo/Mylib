// CEEDLING NOTICE: This generated file only to be consumed for test runner creation

#include "utExecutionAndResults/utUnderTest/build/vendor/unity/src/unity.h"
#include "utExecutionAndResults/utUnderTest/src/InternalHelper_u32.h"

void setUp(void) {
}

void tearDown(void) {
}

void test_x_max_y_one_no_overflow(void) {
  uint32_t result;

  result = InternalHelper_u32(0xFFFFFFFFU, 1U);

  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((0xFFFFFFFFU)), (UNITY_INT)(UNITY_UINT32)((result)), (((void *)0)), (UNITY_UINT)(15), UNITY_DISPLAY_STYLE_UINT32);
}