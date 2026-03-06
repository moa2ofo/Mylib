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

void test_x_near_max_uint32_with_y_two_wraparound(void)
{
  uint32_t result;
  uint32_t seed = 0xFFFFFFFEU;
  uint16_t iterations = 2U;
  uint32_t accumulator = seed;
  accumulator += 0U;
  accumulator += 2U;
  uint32_t expected = accumulator;

  result = InternalHelper_u32(seed, iterations);

  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((expected)), (UNITY_INT)(UNITY_UINT32)((result)), (
 ((void *)0)
 ), (UNITY_UINT)(27), UNITY_DISPLAY_STYLE_UINT32);
}