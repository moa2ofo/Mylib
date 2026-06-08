// CEEDLING NOTICE: This generated file only to be consumed for test runner creation

#include "utExecutionAndResults/utUnderTest/src/InternalHelper_u32.h"
#include "utExecutionAndResults/utUnderTest/build/vendor/unity/src/unity.h"

void setUp(void)
{
}

void tearDown(void)
{
}

void test_x_near_max_y_ten_wraparound(void)
{
  uint32_t result;
  uint32_t seed = 0xFFFFFFF0U;
  uint32_t expected = seed;
  uint16_t i;

  for(i = 0U; i < 10U; i++)
{
    expected += (i * 2U);
  }

  result = InternalHelper_u32(seed, 10U);

  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((expected)), (UNITY_INT)(UNITY_UINT32)((result)), (
 ((void *)0)
 ), (UNITY_UINT)(22), UNITY_DISPLAY_STYLE_UINT32);
}