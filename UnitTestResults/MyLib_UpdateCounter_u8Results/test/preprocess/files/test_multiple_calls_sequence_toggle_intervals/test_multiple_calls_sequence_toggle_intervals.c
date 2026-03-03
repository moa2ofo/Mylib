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

void test_MyLib_UpdateCounter_u8_multiple_calls_sequence_toggle_intervals(void)
{
  uint8_t result_u8;
  uint8_t i;
  _Bool saturation_state_b;

  g_systemReady_b =
                   1

  g_counter_u32 = 0U;
  set_SaturationEn_b(
                    0
                         );
  set_CounterLimit_u32(10000U);

  for(i = 1U; i <= 48U; i++)
{
    saturation_state_b = get_SaturationEn_b();
    result_u8 = MyLib_UpdateCounter_u8(1U);

    if((i % 16U) == 0U)
{
      do { if (((saturation_state_b) != (get_SaturationEn_b())))
{ } else { UnityFail( ((" Expected Not-Equal")), (UNITY_UINT)((49))); } } while (0);
    }
  }

  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((48U)), (UNITY_INT)(UNITY_UINT32)((g_counter_u32)), (
 ((void *)0)
 ), (UNITY_UINT)(54), UNITY_DISPLAY_STYLE_UINT32);

  UnityAssertEqualNumber((UNITY_INT)((
 0
 )), (UNITY_INT)((get_SaturationEn_b())), (
 ((void *)0)
 ), (UNITY_UINT)(57), UNITY_DISPLAY_STYLE_INT);
}