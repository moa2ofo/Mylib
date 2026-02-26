// CEEDLING NOTICE: This generated file only to be consumed for test runner creation

#include "utExecutionAndResults/utUnderTest/src/MyLib_UpdateCounter_u8.h"
#include "utExecutionAndResults/utUnderTest/build/vendor/unity/src/unity.h"
#include "mock_MyLib.h"

void setUp(void)
{
  g_counter_u32 = 0U;
  g_systemReady_b =
                   0

  g_record.id_u16 = 0U;
  g_record.value_u32 = 0U;

  SetCounterLimit_u32((100U));
  SetSaturationEn_b(
                   1
                       );
}

void tearDown(void)
{
}

void test_MyLib_UpdateCounter_u8_CycleToggle_FromDisabledToEnabled(void)
{
  uint8_t result;

  g_systemReady_b =
                   1

  SetSaturationEn_b(
                   0
                        );
  SetCounterLimit_u32(100U);
  g_counter_u32 = 0U;

  for(int i = 0; i < 15; i++)
{
    result = MyLib_UpdateCounter_u8(1U);
    UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((0U)), (UNITY_INT)(UNITY_UINT8 )((result)), (
   ((void *)0)
   ), (UNITY_UINT)(37), UNITY_DISPLAY_STYLE_UINT8);
    UnityAssertEqualNumber((UNITY_INT)((
   0
   )), (UNITY_INT)((GetSaturationEn_b())), (
   ((void *)0)
   ), (UNITY_UINT)(38), UNITY_DISPLAY_STYLE_INT);
  }

  result = MyLib_UpdateCounter_u8(1U);
  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((0U)), (UNITY_INT)(UNITY_UINT8 )((result)), (
 ((void *)0)
 ), (UNITY_UINT)(43), UNITY_DISPLAY_STYLE_UINT8);

  UnityAssertEqualNumber((UNITY_INT)((
 1
 )), (UNITY_INT)((GetSaturationEn_b())), (
 ((void *)0)
 ), (UNITY_UINT)(46), UNITY_DISPLAY_STYLE_INT);
}