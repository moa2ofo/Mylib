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

void test_cycle_toggle_after_32_calls(void)
{
  uint8_t i;

 _Bool
      initial_sat;

 _Bool
      after_16_sat;

 _Bool
      after_32_sat;

  g_systemReady_b =
                   1

  g_counter_u32 = 0U;
  SetSaturationEn_b(
                   0
                        );
  SetCounterLimit_u32(1000U);

  initial_sat = GetSaturationEn_b();

  for(i = 0U; i < 16U; i++)
{
    MyLib_UpdateCounter_u8(1U);
  }

  after_16_sat = GetSaturationEn_b();
  do { if (((initial_sat) != (after_16_sat)))
{ } else { UnityFail( ((" Expected Not-Equal")), (UNITY_UINT)((45))); } } while (0);

  for(i = 0U; i < 15U; i++)
{
    MyLib_UpdateCounter_u8(1U);
  }

  UnityAssertEqualNumber((UNITY_INT)((after_16_sat)), (UNITY_INT)((GetSaturationEn_b())), (
 ((void *)0)
 ), (UNITY_UINT)(51), UNITY_DISPLAY_STYLE_INT);

  MyLib_UpdateCounter_u8(1U);

  after_32_sat = GetSaturationEn_b();
  do { if (((after_16_sat) != (after_32_sat)))
{ } else { UnityFail( ((" Expected Not-Equal")), (UNITY_UINT)((56))); } } while (0);
  UnityAssertEqualNumber((UNITY_INT)((initial_sat)), (UNITY_INT)((after_32_sat)), (
 ((void *)0)
 ), (UNITY_UINT)(57), UNITY_DISPLAY_STYLE_INT);
}