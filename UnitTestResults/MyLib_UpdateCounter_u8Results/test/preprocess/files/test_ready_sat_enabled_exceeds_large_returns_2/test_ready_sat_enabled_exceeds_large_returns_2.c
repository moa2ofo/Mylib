// CEEDLING NOTICE: This generated file only to be consumed for test runner creation

#include "utExecutionAndResults/utUnderTest/src/MyLib.h"
#include "utExecutionAndResults/utUnderTest/src/MyLib_UpdateCounter_u8.h"
#include "utExecutionAndResults/utUnderTest/build/vendor/unity/src/unity.h"
#include "mock_MyLib.h"

void setUp(void)
{
  g_counter_u32 = 0U;
  g_systemReady_b =
                   0

  SetCounterLimit_u32(0U);
  SetSaturationEn_b(
                   0
                        );
}

void tearDown(void)
{
}

void test_ready_sat_enabled_exceeds_large_returns_2(void)
{
  uint8_t result;

  g_systemReady_b =
                   1

  g_counter_u32 = 50U;
  SetSaturationEn_b(
                   1
                       );
  SetCounterLimit_u32(100U);

  result = MyLib_UpdateCounter_u8(1000U);

  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((2U)), (UNITY_INT)(UNITY_UINT8 )((result)), (
 ((void *)0)
 ), (UNITY_UINT)(37), UNITY_DISPLAY_STYLE_UINT8);
  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((100U)), (UNITY_INT)(UNITY_UINT32)((g_counter_u32)), (
 ((void *)0)
 ), (UNITY_UINT)(38), UNITY_DISPLAY_STYLE_UINT32);
}