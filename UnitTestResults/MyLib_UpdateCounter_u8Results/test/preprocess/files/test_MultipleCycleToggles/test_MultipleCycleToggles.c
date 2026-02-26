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

void test_MyLib_UpdateCounter_u8_MultipleCycleToggles(void)
{
  uint8_t result;

 _Bool
      saturation_state;
  int toggle_count = 0;

  g_systemReady_b =
                   1

  SetSaturationEn_b(
                   1
                       );
  SetCounterLimit_u32(100U);
  g_counter_u32 = 0U;

  saturation_state = GetSaturationEn_b();

  for(int i = 0; i < 48; i++)
{
    result = MyLib_UpdateCounter_u8(1U);
    UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((0U)), (UNITY_INT)(UNITY_UINT8 )((result)), (
   ((void *)0)
   ), (UNITY_UINT)(41), UNITY_DISPLAY_STYLE_UINT8);

   _Bool
        current_state = GetSaturationEn_b();
    if(current_state != saturation_state)
{
      toggle_count++;
      saturation_state = current_state;
    }
  }

  UnityAssertGreaterOrLessOrEqualNumber((UNITY_INT) ((2)), (UNITY_INT) ((toggle_count)), UNITY_GREATER_OR_EQUAL, (
 ((void *)0)
 ), (UNITY_UINT)(51), UNITY_DISPLAY_STYLE_INT);
  UnityAssertGreaterOrLessOrEqualNumber((UNITY_INT) ((3)), (UNITY_INT) ((toggle_count)), UNITY_SMALLER_OR_EQUAL, (
 ((void *)0)
 ), (UNITY_UINT)(52), UNITY_DISPLAY_STYLE_INT);

  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((48U)), (UNITY_INT)(UNITY_UINT32)((g_counter_u32)), (
 ((void *)0)
 ), (UNITY_UINT)(55), UNITY_DISPLAY_STYLE_UINT32);
}