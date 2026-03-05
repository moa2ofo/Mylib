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

void test_MyLib_UpdateCounter_u8_cycle_counter_toggle_after_16_calls(void)
{
  uint8_t i;

 _Bool
      initial_saturation_b;

 _Bool
      final_saturation_b;

  g_systemReady_b =
                   1

  g_counter_u32 = 0U;
  set_SaturationEn_b(
                    0
                         );
  set_CounterLimit_u32(1000U);

  initial_saturation_b = get_SaturationEn_b();

  for(i = 0U; i < 16U; i++)
{
    MyLib_UpdateCounter_u8(1U);
  }

  final_saturation_b = get_SaturationEn_b();

  do { if (((initial_saturation_b) != (final_saturation_b)))
{ } else { UnityFail( ((" Expected Not-Equal")), (UNITY_UINT)((49))); } } while (0);
}