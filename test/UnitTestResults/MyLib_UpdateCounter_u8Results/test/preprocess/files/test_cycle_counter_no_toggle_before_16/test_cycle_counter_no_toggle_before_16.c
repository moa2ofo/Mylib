// CEEDLING NOTICE: This generated file only to be consumed for test runner creation

#include "utExecutionAndResults/utUnderTest/src/MyLib.h"
#include "utExecutionAndResults/utUnderTest/src/MyLib_UpdateCounter_u8.h"
#include "utExecutionAndResults/utUnderTest/build/vendor/unity/src/unity.h"
#include "mock_MyLib.h"

void setUp(void)
{
}

void tearDown(void)
{
}

void test_cycle_counter_no_toggle_before_16(void)
{
  uint8_t i;

 _Bool
      initial_sat;

 _Bool
      final_sat;

  g_systemReady_b =
                   1

  g_counter_u32 = 0U;
  set_SaturationEn_b(
                    0
                         );
  set_CounterLimit_u32(1000U);

  initial_sat = get_SaturationEn_b();

  for(i = 0U; i < 15U; i++)
{
    MyLib_UpdateCounter_u8(1U);
  }

  final_sat = get_SaturationEn_b();

  UnityAssertEqualNumber((UNITY_INT)((initial_sat)), (UNITY_INT)((final_sat)), (
 ((void *)0)
 ), (UNITY_UINT)(31), UNITY_DISPLAY_STYLE_INT);
}