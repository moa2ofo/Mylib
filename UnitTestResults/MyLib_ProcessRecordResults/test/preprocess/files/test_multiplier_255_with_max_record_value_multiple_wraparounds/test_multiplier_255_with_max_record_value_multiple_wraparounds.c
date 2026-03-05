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

void test_MyLib_ProcessRecord_multiplier_255_with_max_record_value_multiple_wraparounds(void)
{
  MyLib_record_t record;
  record.id_u16 = 13U;
  record.value_u32 = 0xFFFFFFFFU;

  uint32_t initial_counter = 1000U;
  g_counter_u32 = initial_counter;

  uint32_t expected_acc = 0xFFFFFF01U;

  MyLib_ComputeAdjustedValue_u32_CMockExpectAndReturn(31, expected_acc, (const uint16_t *)&(uint8_t){255U}, 0U);
  MyLib_ComputeAdjustedValue_u32_CMockIgnoreArg_delta_pc_u16(32);

  MyLib_ProcessRecord(&record, 255U);

  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((initial_counter + expected_acc)), (UNITY_INT)(UNITY_UINT32)((g_counter_u32)), (
 ((void *)0)
 ), (UNITY_UINT)(36), UNITY_DISPLAY_STYLE_UINT32);
}