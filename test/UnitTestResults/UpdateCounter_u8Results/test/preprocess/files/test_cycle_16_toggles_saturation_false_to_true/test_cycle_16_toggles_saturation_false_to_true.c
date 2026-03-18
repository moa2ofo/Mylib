// CEEDLING NOTICE: This generated file only to be consumed for test runner creation

#include "mock_MyLib.h"
#include "utExecutionAndResults/utUnderTest/build/vendor/unity/src/unity.h"

void setUp(void) {
}

void tearDown(void) {
}

void test_cycle_16_toggles_saturation_false_to_true(void) {
  uint8_t result;
  int i;

  g_systemReady_b = 1

      g_counter_u32 = 0U;
  set_SaturationEn_b(0);
  set_CounterLimit_u32(1000U);

  for(i = 0; i < 15; i++) {
    result = UpdateCounter_u8(1U);
  }

  UnityAssertEqualNumber((UNITY_INT)((0)), (UNITY_INT)((get_SaturationEn_b())), (((void *)0)), (UNITY_UINT)(24), UNITY_DISPLAY_STYLE_INT);

  result = UpdateCounter_u8(1U);

  UnityAssertEqualNumber((UNITY_INT)((1)), (UNITY_INT)((get_SaturationEn_b())), (((void *)0)), (UNITY_UINT)(28), UNITY_DISPLAY_STYLE_INT);
}