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

void test_InternalHelper_u32__x_is_zero_y_max_u16(void)
{
  uint32_t x_u32 = 0U;
  uint16_t y_u16 =
                  (65535)

  uint32_t expected_u32;

  expected_u32 = (uint32_t)
                          (65535)
                                     * (uint32_t)(
                                                  (65535)
                                                             - 1U);

  uint32_t result_u32 = InternalHelper_u32(x_u32, y_u16);

  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((expected_u32)), (UNITY_INT)(UNITY_UINT32)((result_u32)), (
 ((void *)0)
 ), (UNITY_UINT)(31), UNITY_DISPLAY_STYLE_UINT32);
}