// CEEDLING NOTICE: This generated file only to be consumed for test runner creation

#include "utExecutionAndResults/utUnderTest/src/InternalHelper_u32.h"
#include "utExecutionAndResults/utUnderTest/build/vendor/unity/src/unity.h"

void setUp(void)
{
  g_counter_u32 = 0U;
  g_record.id_u16 = 0U;
  g_record.value_u32 = 0U;
  g_systemReady_b =
                   0
}

void tearDown(void)
{
}

void test_y_max_with_x_zero_wraparound(void)
{
  uint32_t result;
  uint32_t seed = 0U;
  uint16_t iterations = 60535U;
  uint32_t accumulator = seed;

  for(uint16_t i = 0U; i < iterations; i++)
{
    accumulator += (uint32_t)(i * 2U);
  }
  uint32_t expected = accumulator;

  result = InternalHelper_u32(seed, iterations);

  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((expected)), (UNITY_INT)(UNITY_UINT32)((result)), (
 ((void *)0)
 ), (UNITY_UINT)(29), UNITY_DISPLAY_STYLE_UINT32);
}