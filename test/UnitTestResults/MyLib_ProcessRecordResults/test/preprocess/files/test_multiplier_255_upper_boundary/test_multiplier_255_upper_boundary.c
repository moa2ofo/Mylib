// CEEDLING NOTICE: This generated file only to be consumed for test runner creation

#include "mock_MyLib.h"
#include "utExecutionAndResults/utUnderTest/build/vendor/unity/src/unity.h"
#include "utExecutionAndResults/utUnderTest/src/MyLib_ProcessRecord.h"

void setUp(void) {
}

void tearDown(void) {
}

void test_multiplier_255_upper_boundary(void) {
  MyLib_record_t rec = {.id_u16 = 5U, .value_u32 = 8U};
  uint32_t initial_counter = g_counter_u32;
  uint32_t expected_acc = 255U * 8U;

  MyLib_ComputeAdjustedValue_u32_CMockExpectAndReturn(16, expected_acc, (const uint16_t *)&(uint8_t){255U}, 0U);
  MyLib_ComputeAdjustedValue_u32_CMockIgnoreArg_delta_pc_u16(17);

  MyLib_ProcessRecord(&rec, 255U);

  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((initial_counter + expected_acc)), (UNITY_INT)(UNITY_UINT32)((g_counter_u32)), (((void *)0)), (UNITY_UINT)(21), UNITY_DISPLAY_STYLE_UINT32);
}