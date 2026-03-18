// CEEDLING NOTICE: This generated file only to be consumed for test runner creation

#include "mock_MyLib.h"
#include "utExecutionAndResults/utUnderTest/build/vendor/unity/src/unity.h"

void setUp(void) {
}

void tearDown(void) {
}

void test_counter_at_max_wraps_to_zero(void) {
  MyLib_record_t rec = {.id_u16 = 12U, .value_u32 = 1U};
  g_counter_u32 = (4294967295U)

      MyLib_ComputeAdjustedValue_u32_CMockExpectAndReturn(15, 1U, (const uint16_t *)&(uint8_t){1U}, 0U);
  MyLib_ComputeAdjustedValue_u32_CMockIgnoreArg_delta_pc_u16(16);

  ProcessRecord(&rec, 1U);

  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((0U)), (UNITY_INT)(UNITY_UINT32)((g_counter_u32)), (((void *)0)), (UNITY_UINT)(20), UNITY_DISPLAY_STYLE_UINT32);
}