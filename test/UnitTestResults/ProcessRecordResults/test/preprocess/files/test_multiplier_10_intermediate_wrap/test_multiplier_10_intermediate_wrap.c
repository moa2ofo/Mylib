// CEEDLING NOTICE: This generated file only to be consumed for test runner creation

#include "utExecutionAndResults/utUnderTest/build/vendor/unity/src/unity.h"
#include "mock_MyLib.h"

void setUp(void)
{
}

void tearDown(void)
{
}

void test_multiplier_10_intermediate_wrap(void)
{
  MyLib_record_t rec = {.id_u16 = 11U, .value_u32 = 0xFFFFFFFFU / 5U + 1U};
  g_counter_u32 = 0U;
  uint32_t expected_acc = (uint32_t)((uint64_t)rec.value_u32 * 10ULL);

  MyLib_ComputeAdjustedValue_u32_CMockExpectAndReturn(16, expected_acc, (const uint16_t *)&(uint8_t){10U}, 0U);
  MyLib_ComputeAdjustedValue_u32_CMockIgnoreArg_delta_pc_u16(17);

  ProcessRecord(&rec, 10U);

  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((expected_acc)), (UNITY_INT)(UNITY_UINT32)((g_counter_u32)), (
 ((void *)0)
 ), (UNITY_UINT)(21), UNITY_DISPLAY_STYLE_UINT32);
}