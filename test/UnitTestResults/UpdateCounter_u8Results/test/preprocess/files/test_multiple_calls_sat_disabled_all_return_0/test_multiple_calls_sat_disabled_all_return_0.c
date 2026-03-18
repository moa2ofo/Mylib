// CEEDLING NOTICE: This generated file only to be consumed for test runner creation

#include "mock_MyLib.h"
#include "utExecutionAndResults/utUnderTest/build/vendor/unity/src/unity.h"

void setUp(void) {
}

void tearDown(void) {
}

void test_multiple_calls_sat_disabled_all_return_0(void) {
  uint8_t result;
  int i;

  g_systemReady_b = 1

      g_counter_u32 = 0U;
  set_SaturationEn_b(0);

  for(i = 0; i < 10; i++) {
    result = UpdateCounter_u8(1U);
    UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8)((0U)), (UNITY_INT)(UNITY_UINT8)((result)), (((void *)0)), (UNITY_UINT)(21), UNITY_DISPLAY_STYLE_UINT8);
    UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((i + 1)), (UNITY_INT)(UNITY_UINT32)((g_counter_u32)), (((void *)0)), (UNITY_UINT)(22), UNITY_DISPLAY_STYLE_UINT32);
  }
}