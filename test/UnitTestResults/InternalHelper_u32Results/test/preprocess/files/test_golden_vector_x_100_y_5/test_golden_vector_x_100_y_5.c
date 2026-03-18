// CEEDLING NOTICE: This generated file only to be consumed for test runner creation

#include "utExecutionAndResults/utUnderTest/build/vendor/unity/src/unity.h"
#include "utExecutionAndResults/utUnderTest/src/InternalHelper_u32.h"

void setUp(void) {
}

void tearDown(void) {
}

void test_golden_vector_x_100_y_5(void) {
  uint32_t result;

  result = InternalHelper_u32(100U, 5U);

  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((120U)), (UNITY_INT)(UNITY_UINT32)((result)), (((void *)0)), (UNITY_UINT)(15), UNITY_DISPLAY_STYLE_UINT32);
}