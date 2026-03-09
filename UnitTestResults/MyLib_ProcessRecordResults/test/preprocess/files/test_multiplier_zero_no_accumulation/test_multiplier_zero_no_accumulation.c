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

void test_MyLib_ProcessRecord_multiplier_zero_no_accumulation(void)
{
  MyLib_record_t record;
  record.id_u16 = 1U;
  record.value_u32 = 100U;

  uint32_t initial_counter = 50U;
  g_counter_u32 = initial_counter;

  MyLib_ComputeAdjustedValue_u32_CMockExpectAndReturn(29, 0U, (const uint16_t *)&(uint8_t){0U}, 0U);
  MyLib_ComputeAdjustedValue_u32_CMockIgnoreArg_delta_pc_u16(30);

  MyLib_ProcessRecord(&record, 0U);

  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((initial_counter)), (UNITY_INT)(UNITY_UINT32)((g_counter_u32)), (
 ((void *)0)
 ), (UNITY_UINT)(34), UNITY_DISPLAY_STYLE_UINT32);
}