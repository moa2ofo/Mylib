// CEEDLING NOTICE: This generated file only to be consumed for test runner creation

#include "mock_MyLib.h"
#include "utExecutionAndResults/utUnderTest/build/vendor/unity/src/unity.h"

void setUp(void) {
}

void tearDown(void) {
}

void test_ready_add_one_sat_disabled_returns_0(void) {
  uint8_t result;
  uint32_t initial_counter = 50U;

  g_systemReady_b = 1

      g_counter_u32 = initial_counter;
  set_SaturationEn_b(0);

  result = UpdateCounter_u8(1U);

  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8)((0U)), (UNITY_INT)(UNITY_UINT8)((result)), (((void *)0)), (UNITY_UINT)(21), UNITY_DISPLAY_STYLE_UINT8);
  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((initial_counter + 1U)), (UNITY_INT)(UNITY_UINT32)((g_counter_u32)), (((void *)0)), (UNITY_UINT)(22), UNITY_DISPLAY_STYLE_UINT32);
}