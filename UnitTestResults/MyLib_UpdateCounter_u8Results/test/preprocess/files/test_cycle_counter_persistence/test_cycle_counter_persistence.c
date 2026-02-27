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

void test_cycle_counter_persistence(void)
{
  uint8_t i;

  g_systemReady_b =
                   1

  g_counter_u32 = 0U;
  SetSaturationEn_b(
                   0
                        );
  SetCounterLimit_u32(1000U);

  for(i = 0U; i < 16U; i++)
{
    MyLib_UpdateCounter_u8(1U);
  }

 _Bool
      sat_after_16 = GetSaturationEn_b();

  for(i = 0U; i < 16U; i++)
{
    MyLib_UpdateCounter_u8(1U);
  }

 _Bool
      sat_after_32 = GetSaturationEn_b();

  do { if (((sat_after_16) != (sat_after_32)))
{ } else { UnityFail( ((" Expected Not-Equal")), (UNITY_UINT)((47))); } } while (0);
}