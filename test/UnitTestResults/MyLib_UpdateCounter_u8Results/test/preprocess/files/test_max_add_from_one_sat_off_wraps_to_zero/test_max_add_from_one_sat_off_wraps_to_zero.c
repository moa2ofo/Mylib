// CEEDLING NOTICE: This generated file only to be consumed for test runner creation

#include "mock_MyLib.h"
#include "utExecutionAndResults/utUnderTest/build/vendor/unity/src/unity.h"
#include "utExecutionAndResults/utUnderTest/src/MyLib.h"
#include "utExecutionAndResults/utUnderTest/src/MyLib_UpdateCounter_u8.h"

void setUp(void) {
}

void tearDown(void) {
}

void test_max_add_from_one_sat_off_wraps_to_zero(void) {
  uint8_t result;

  g_systemReady_b = 1

      g_counter_u32 = 1U;
  set_SaturationEn_b(0);

  result = MyLib_UpdateCounter_u8((4294967295U));

  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8)((0U)), (UNITY_INT)(UNITY_UINT8)((result)), (((void *)0)), (UNITY_UINT)(22), UNITY_DISPLAY_STYLE_UINT8);
  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((0U)), (UNITY_INT)(UNITY_UINT32)((g_counter_u32)), (((void *)0)), (UNITY_UINT)(23), UNITY_DISPLAY_STYLE_UINT32);
}