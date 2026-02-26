// CEEDLING NOTICE: This generated file only to be consumed for test runner creation

#include "utExecutionAndResults/utUnderTest/src/MyLib_UpdateCounter_u8.h"
#include "utExecutionAndResults/utUnderTest/build/vendor/unity/src/unity.h"
#include "utExecutionAndResults/utUnderTest/src/MyLib.h"
#include "mock_MyLib.h"

```

    static uint32_t s_counterLimit_u32;
static
      _Bool
           s_saturationEn_b;

uint32_t GetCounterLimit_u32(void)
{
  return s_counterLimit_u32;
}

void SetCounterLimit_u32(uint32_t value)
{
  s_counterLimit_u32 = value;
}

_Bool
    GetSaturationEn_b(void)
{
  return s_saturationEn_b;
}

void SetSaturationEn_b(
                      _Bool
                           enable)
{
  s_saturationEn_b = enable;
}

void setUp(void)
{
  g_counter_u32 = 0U;
  s_counterLimit_u32 = 255U;
  s_saturationEn_b =
                    0
}

void tearDown(void)
{
}

void test_change_limit_255_to_100_counter_150_add_ten_saturation_enabled(void)
{
  uint8_t result;

  g_counter_u32 = 150U;
  SetCounterLimit_u32(255U);
  SetSaturationEn_b(
                   1
                       );

  SetCounterLimit_u32(100U);

  result = MyLib_UpdateCounter_u8(10U);

  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((100U)), (UNITY_INT)(UNITY_UINT32)((g_counter_u32)), (
 ((void *)0)
 ), (UNITY_UINT)(49), UNITY_DISPLAY_STYLE_UINT32);
  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((100U)), (UNITY_INT)(UNITY_UINT8 )((result)), (
 ((void *)0)
 ), (UNITY_UINT)(50), UNITY_DISPLAY_STYLE_UINT8);
}