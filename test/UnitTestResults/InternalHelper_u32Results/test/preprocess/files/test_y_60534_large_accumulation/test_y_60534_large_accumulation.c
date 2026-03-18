// CEEDLING NOTICE: This generated file only to be consumed for test runner creation

#include "utExecutionAndResults/utUnderTest/build/vendor/unity/src/unity.h"
#include "utExecutionAndResults/utUnderTest/src/InternalHelper_u32.h"

void setUp(void) {
}

void tearDown(void) {
}

void test_y_60534_large_accumulation(void) {
  uint32_t result;
  uint32_t seed = 0U;
  uint32_t expected_sum = 0U;
  uint32_t i;

  for(i = 0U; i < 60534U; i++) {
    expected_sum += (i * 2U);
  }

  result = InternalHelper_u32(seed, 60534U);

  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((expected_sum)), (UNITY_INT)(UNITY_UINT32)((result)), (((void *)0)), (UNITY_UINT)(22), UNITY_DISPLAY_STYLE_UINT32);
}