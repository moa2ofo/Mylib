// CEEDLING NOTICE: This generated file only to be consumed for test runner creation

#include "mock_MyLib.h"
#include "utExecutionAndResults/utUnderTest/build/vendor/unity/src/unity.h"
#include "utExecutionAndResults/utUnderTest/src/MyLib_ProcessRecord.h"

void setUp(void) {
}

void tearDown(void) {
}

void test_value_max_multiplier_two_wraparound(void) {
  MyLib_record_t rec = {.id_u16 = 8U, .value_u32 = (4294967295U)};
  uint32_t initial_counter = g_counter_u32;
  uint32_t expected_acc = (4294967295U) + (4294967295U)

                                              MyLib_ComputeAdjustedValue_u32_CMockExpectAndReturn(16, expected_acc, (const uint16_t *)&(uint8_t){2U}, 0U);
  MyLib_ComputeAdjustedValue_u32_CMockIgnoreArg_delta_pc_u16(17);

  MyLib_ProcessRecord(&rec, 2U);

  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((initial_counter + expected_acc)), (UNITY_INT)(UNITY_UINT32)((g_counter_u32)), (((void *)0)), (UNITY_UINT)(21), UNITY_DISPLAY_STYLE_UINT32);
}