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

void test_MyLib_UpdateCounter_u8_limit_max_saturation_enabled_increment_causing_wrap_correct_comparison(void)
{
  uint8_t result_u8;

  g_systemReady_b =
                   1

  g_counter_u32 = 0xFFFFFFF0U;
  set_SaturationEn_b(
                    1
                        );
  set_CounterLimit_u32(0xFFFFFFFFU);

  result_u8 = MyLib_UpdateCounter_u8(0x20U);

  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((0U)), (UNITY_INT)(UNITY_UINT8 )((result_u8)), (
 ((void *)0)
 ), (UNITY_UINT)(41), UNITY_DISPLAY_STYLE_UINT8);
  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((0x10U)), (UNITY_INT)(UNITY_UINT32)((g_counter_u32)), (
 ((void *)0)
 ), (UNITY_UINT)(42), UNITY_DISPLAY_STYLE_UINT32);
}