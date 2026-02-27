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

void test_combo_sat_toggled_via_cycle_count(void)
{
  uint8_t i;
  uint8_t result;

  g_systemReady_b =
                   1

  g_counter_u32 = 0U;
  SetSaturationEn_b(
                   1
                       );
  SetCounterLimit_u32(50U);

  for(i = 0U; i < 15U; i++)
{
    MyLib_UpdateCounter_u8(1U);
  }

  UnityAssertEqualNumber((UNITY_INT)((
 1
 )), (UNITY_INT)((GetSaturationEn_b())), (
 ((void *)0)
 ), (UNITY_UINT)(40), UNITY_DISPLAY_STYLE_INT);

  result = MyLib_UpdateCounter_u8(100U);
  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((2U)), (UNITY_INT)(UNITY_UINT8 )((result)), (
 ((void *)0)
 ), (UNITY_UINT)(43), UNITY_DISPLAY_STYLE_UINT8);
  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((50U)), (UNITY_INT)(UNITY_UINT32)((g_counter_u32)), (
 ((void *)0)
 ), (UNITY_UINT)(44), UNITY_DISPLAY_STYLE_UINT32);

  UnityAssertEqualNumber((UNITY_INT)((
 0
 )), (UNITY_INT)((GetSaturationEn_b())), (
 ((void *)0)
 ), (UNITY_UINT)(46), UNITY_DISPLAY_STYLE_INT);

  result = MyLib_UpdateCounter_u8(100U);
  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((0U)), (UNITY_INT)(UNITY_UINT8 )((result)), (
 ((void *)0)
 ), (UNITY_UINT)(49), UNITY_DISPLAY_STYLE_UINT8);
  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((150U)), (UNITY_INT)(UNITY_UINT32)((g_counter_u32)), (
 ((void *)0)
 ), (UNITY_UINT)(50), UNITY_DISPLAY_STYLE_UINT32);
}