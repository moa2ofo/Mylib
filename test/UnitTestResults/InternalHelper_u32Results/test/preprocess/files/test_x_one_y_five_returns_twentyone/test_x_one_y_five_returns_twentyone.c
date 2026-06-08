// CEEDLING NOTICE: This generated file only to be consumed for test runner creation

#include "utExecutionAndResults/utUnderTest/src/InternalHelper_u32.h"
#include "utExecutionAndResults/utUnderTest/build/vendor/unity/src/unity.h"

void setUp(void)
{
}

void tearDown(void)
{
}

void test_x_one_y_five_returns_twentyone(void)
{
  uint32_t result;

  result = InternalHelper_u32(1U, 5U);

  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((21U)), (UNITY_INT)(UNITY_UINT32)((result)), (
 ((void *)0)
 ), (UNITY_UINT)(15), UNITY_DISPLAY_STYLE_UINT32);
}