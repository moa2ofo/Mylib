// CEEDLING NOTICE: This generated file only to be consumed for test runner creation

#include "utExecutionAndResults/utUnderTest/src/MyLib_ProcessRecord.h"
#include "utExecutionAndResults/utUnderTest/build/vendor/unity/src/unity.h"
#include "mock_MyLib.h"

void setUp(void)
{
  g_counter_u32 = 0U;
  g_record.id_u16 = 0U;
  g_record.value_u32 = 0U;
  g_systemReady_b =
                   0
}

void tearDown(void)
{
}

void test_MyLib_ProcessRecord_value_u32_max_multiplier_1(void)
{
  MyLib_record_t rec;
  rec.id_u16 = 7U;
  rec.value_u32 =
                 (4294967295U)

  uint32_t initial_counter = g_counter_u32;
  uint32_t expected_acc =
                         (4294967295U)

  MyLib_ComputeAdjustedValue_u32_CMockExpectAndReturn(33, expected_acc, (const uint16_t *)&(uint8_t){1U}, 0U);
  MyLib_ComputeAdjustedValue_u32_CMockIgnoreArg_delta_pc_u16(34);

  MyLib_ProcessRecord(&rec, 1U);

  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((initial_counter + expected_acc)), (UNITY_INT)(UNITY_UINT32)((g_counter_u32)), (
 ((void *)0)
 ), (UNITY_UINT)(38), UNITY_DISPLAY_STYLE_UINT32);
}