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

void test_MyLib_UpdateCounter_u8_cycle_counter_no_toggle_on_non_16th_call(void)
{
  uint8_t result_u8;
  _Bool initial_saturation_b;

  g_systemReady_b =
                   1

  g_counter_u32 = 0U;
  set_SaturationEn_b(
                    1
                        );
  set_CounterLimit_u32(1000U);
  initial_saturation_b = get_SaturationEn_b();

  result_u8 = MyLib_UpdateCounter_u8(1U);

  UnityAssertEqualNumber((UNITY_INT)((initial_saturation_b)), (UNITY_INT)((get_SaturationEn_b())), (
 ((void *)0)
 ), (UNITY_UINT)(46), UNITY_DISPLAY_STYLE_INT);
}