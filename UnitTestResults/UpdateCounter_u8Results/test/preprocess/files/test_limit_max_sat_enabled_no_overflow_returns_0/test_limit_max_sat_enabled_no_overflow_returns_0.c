// CEEDLING NOTICE: This generated file only to be consumed for test runner creation

#include "utExecutionAndResults/utUnderTest/build/vendor/unity/src/unity.h"
#include "mock_MyLib.h"

void setUp(void)
{
}

void tearDown(void)
{
}

void test_limit_max_sat_enabled_no_overflow_returns_0(void)
{
  uint8_t result;
  uint32_t initial_counter = 100U;
  uint32_t add_value = 50U;

  g_systemReady_b =
                   1

  g_counter_u32 = initial_counter;
  set_SaturationEn_b(
                    1
                        );
  set_CounterLimit_u32(0xFFFFFFFFU);

  result = UpdateCounter_u8(add_value);

  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((0U)), (UNITY_INT)(UNITY_UINT8 )((result)), (
 ((void *)0)
 ), (UNITY_UINT)(23), UNITY_DISPLAY_STYLE_UINT8);
  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((initial_counter + add_value)), (UNITY_INT)(UNITY_UINT32)((g_counter_u32)), (
 ((void *)0)
 ), (UNITY_UINT)(24), UNITY_DISPLAY_STYLE_UINT32);
}