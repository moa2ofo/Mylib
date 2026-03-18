// CEEDLING NOTICE: This generated file only to be consumed for test runner creation

#include "utExecutionAndResults/utUnderTest/build/vendor/unity/src/unity.h"
#include "utExecutionAndResults/utUnderTest/src/InternalHelper_u32.h"

void setUp(void) {
}

void tearDown(void) {
}

void test_y_ten_accumulates_ninety(void) {
  uint32_t result;
  uint32_t seed = 50U;
  uint32_t expected = 50U + 90U;

  result = InternalHelper_u32(seed, 10U);

  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((expected)), (UNITY_INT)(UNITY_UINT32)((result)), (((void *)0)), (UNITY_UINT)(17), UNITY_DISPLAY_STYLE_UINT32);
}