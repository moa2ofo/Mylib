// CEEDLING NOTICE: This generated file only to be consumed for test runner creation

#include "mock_MyLib.h"
#include "utExecutionAndResults/utUnderTest/build/vendor/unity/src/unity.h"
#include "utExecutionAndResults/utUnderTest/src/MyLib.h"
#include "utExecutionAndResults/utUnderTest/src/MyLib_UpdateCounter_u8.h"

void setUp(void) {
}

void tearDown(void) {
}

void test_sat_limit_max_no_wrap_returns_0(void) {
  uint8_t result;

  g_systemReady_b = 1

      g_counter_u32 = (4294967295U) - 10U;
  set_SaturationEn_b(1);
  set_CounterLimit_u32((4294967295U));

  result = MyLib_UpdateCounter_u8(5U);

  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8)((0U)), (UNITY_INT)(UNITY_UINT8)((result)), (((void *)0)), (UNITY_UINT)(23), UNITY_DISPLAY_STYLE_UINT8);
  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)(((4294967295U) - 5U)), (UNITY_INT)(UNITY_UINT32)((g_counter_u32)), (((void *)0)), (UNITY_UINT)(24), UNITY_DISPLAY_STYLE_UINT32);
}