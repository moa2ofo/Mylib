// CEEDLING NOTICE: This generated file only to be consumed for test runner creation

#include "utExecutionAndResults/utUnderTest/src/MyLib.h"
#include "utExecutionAndResults/utUnderTest/src/MyLib_UpdateCounter_u8.h"
#include "utExecutionAndResults/utUnderTest/build/vendor/unity/src/unity.h"
#include "mock_MyLib.h"

void setUp(void)
{
  g_counter_u32 = 0U;
  g_systemReady_b =
                   

  set_CounterLimit_u32(0U);
  set_SaturationEn_b(
                    0
                         );
}

void tearDown(void)
{
}

void test_MyLib_UpdateCounter_u8_ready_saturation_enabled_new_far_above_limit_returns_2_clamped(void)
{
  uint8_t result_u8;

  g_systemReady_b =
                   1

  g_counter_u32 = 50U;
  set_SaturationEn_b(
                    1
                        );
  set_CounterLimit_u32(100U);

  result_u8 = MyLib_UpdateCounter_u8(1000U);

  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((2U)), (UNITY_INT)(UNITY_UINT8 )((result_u8)), (
 ((void *)0)
 ), (UNITY_UINT)(41), UNITY_DISPLAY_STYLE_UINT8);
  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((100U)), (UNITY_INT)(UNITY_UINT32)((g_counter_u32)), (
 ((void *)0)
 ), (UNITY_UINT)(42), UNITY_DISPLAY_STYLE_UINT32);
}