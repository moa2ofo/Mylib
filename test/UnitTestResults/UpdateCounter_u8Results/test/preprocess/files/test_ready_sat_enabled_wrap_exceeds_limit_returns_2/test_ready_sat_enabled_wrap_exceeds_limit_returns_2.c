// CEEDLING NOTICE: This generated file only to be consumed for test runner creation

#include "utExecutionAndResults/utUnderTest/build/vendor/unity/src/unity.h"
#include "mock_MyLib.h"

void setUp(void)
{
}

void tearDown(void)
{
}

void test_ready_sat_enabled_wrap_exceeds_limit_returns_2(void)
{
  uint8_t result;
  uint32_t initial_counter = 0xFFFFFFFFU;
  uint32_t add_value = 100U;
  uint32_t limit = 50U;

  g_systemReady_b =
                   1

  g_counter_u32 = initial_counter;
  set_SaturationEn_b(
                    1
                        );
  set_CounterLimit_u32(limit);

  result = UpdateCounter_u8(add_value);

  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((2U)), (UNITY_INT)(UNITY_UINT8 )((result)), (
 ((void *)0)
 ), (UNITY_UINT)(24), UNITY_DISPLAY_STYLE_UINT8);
  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((limit)), (UNITY_INT)(UNITY_UINT32)((g_counter_u32)), (
 ((void *)0)
 ), (UNITY_UINT)(25), UNITY_DISPLAY_STYLE_UINT32);
}