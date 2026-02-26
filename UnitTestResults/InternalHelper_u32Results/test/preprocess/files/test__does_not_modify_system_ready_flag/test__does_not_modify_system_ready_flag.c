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

void test_InternalHelper_u32__does_not_modify_system_ready_flag(void)
{
  g_systemReady_b =
                   

 _Bool
      ready_before = g_systemReady_b;
  uint32_t x_u32 = 100U;
  uint16_t y_u16 = 5U;

  InternalHelper_u32(x_u32, y_u16);

  UnityAssertEqualNumber((UNITY_INT)((ready_before)), (UNITY_INT)((g_systemReady_b)), (
 ((void *)0)
 ), (UNITY_UINT)(28), UNITY_DISPLAY_STYLE_INT);
  do { if (!(g_systemReady_b))
{ } else { UnityFail( ((" Expected FALSE Was TRUE")), (UNITY_UINT)((29))); } } while (0);
}