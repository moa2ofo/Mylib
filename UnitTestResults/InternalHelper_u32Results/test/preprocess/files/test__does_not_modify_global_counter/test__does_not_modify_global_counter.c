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

void test_InternalHelper_u32__does_not_modify_global_counter(void)
{
  g_counter_u32 = 0U;
  uint32_t x_u32 = 100U;
  uint16_t y_u16 = 5U;
  uint32_t counter_before = g_counter_u32;

  InternalHelper_u32(x_u32, y_u16);

  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((counter_before)), (UNITY_INT)(UNITY_UINT32)((g_counter_u32)), (
 ((void *)0)
 ), (UNITY_UINT)(28), UNITY_DISPLAY_STYLE_UINT32);
  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((0U)), (UNITY_INT)(UNITY_UINT32)((g_counter_u32)), (
 ((void *)0)
 ), (UNITY_UINT)(29), UNITY_DISPLAY_STYLE_UINT32);
}