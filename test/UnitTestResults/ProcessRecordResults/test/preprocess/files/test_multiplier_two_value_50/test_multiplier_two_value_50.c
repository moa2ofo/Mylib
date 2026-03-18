// CEEDLING NOTICE: This generated file only to be consumed for test runner creation

#include "mock_MyLib.h"
#include "utExecutionAndResults/utUnderTest/build/vendor/unity/src/unity.h"

void setUp(void) {
}

void tearDown(void) {
}

void test_multiplier_two_value_50(void) {
  MyLib_record_t rec = {.id_u16 = 5U, .value_u32 = 50U};
  uint32_t initial_counter = g_counter_u32;

  MyLib_ComputeAdjustedValue_u32_CMockExpectAndReturn(15, 100U, (const uint16_t *)&(uint8_t){2U}, 0U);
  MyLib_ComputeAdjustedValue_u32_CMockIgnoreArg_delta_pc_u16(16);

  ProcessRecord(&rec, 2U);

  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((initial_counter + 100U)), (UNITY_INT)(UNITY_UINT32)((g_counter_u32)), (((void *)0)), (UNITY_UINT)(20), UNITY_DISPLAY_STYLE_UINT32);
}