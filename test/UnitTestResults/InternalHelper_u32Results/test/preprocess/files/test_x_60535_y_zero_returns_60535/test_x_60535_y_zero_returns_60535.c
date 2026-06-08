// CEEDLING NOTICE: This generated file only to be consumed for test runner creation

#include "utExecutionAndResults/utUnderTest/src/InternalHelper_u32.h"
#include "utExecutionAndResults/utUnderTest/build/vendor/unity/src/unity.h"

void setUp(void)
{
}

void tearDown(void)
{
}

void test_x_60535_y_zero_returns_60535(void)
{
  uint32_t result;

  result = InternalHelper_u32(60535U, 0U);

  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((60535U)), (UNITY_INT)(UNITY_UINT32)((result)), (
 ((void *)0)
 ), (UNITY_UINT)(15), UNITY_DISPLAY_STYLE_UINT32);
}