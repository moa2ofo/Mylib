// CEEDLING NOTICE: This generated file only to be consumed for test runner creation

#include "utExecutionAndResults/utUnderTest/src/MyLib_ProcessRecord.h"
#include "utExecutionAndResults/utUnderTest/build/vendor/unity/src/unity.h"
#include "mock_MyLib.h"

static MyLib_record_t test_record;
static uint32_t initial_counter;

void setUp(void)
{
  test_record.id_u16 = 0U;
  test_record.value_u32 = 0U;

  initial_counter = g_counter_u32;
}

void tearDown(void)
{
}

void test_MyLib_ProcessRecord_SequentialCalls_StateConsistency(void)
{
  test_record.id_u16 = 1U;
  test_record.value_u32 = 100U;

  uint32_t first_accumulation = 100U * 2U;
  MyLib_ComputeAdjustedValue_u32_CMockExpectAndReturn(31, first_accumulation,
 ((void *)0)
 , 0U);
  MyLib_ComputeAdjustedValue_u32_CMockIgnoreArg_delta_pc_u16(32);

  MyLib_ProcessRecord(&test_record, 2U);
  uint32_t counter_after_first = g_counter_u32;

  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((initial_counter + 200U)), (UNITY_INT)(UNITY_UINT32)((counter_after_first)), (
 ((void *)0)
 ), (UNITY_UINT)(38), UNITY_DISPLAY_STYLE_UINT32);

  test_record.value_u32 = 50U;
  uint32_t second_accumulation = 50U * 3U;
  MyLib_ComputeAdjustedValue_u32_CMockExpectAndReturn(43, second_accumulation,
 ((void *)0)
 , 0U);
  MyLib_ComputeAdjustedValue_u32_CMockIgnoreArg_delta_pc_u16(44);

  MyLib_ProcessRecord(&test_record, 3U);

  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((counter_after_first + 150U)), (UNITY_INT)(UNITY_UINT32)((g_counter_u32)), (
 ((void *)0)
 ), (UNITY_UINT)(49), UNITY_DISPLAY_STYLE_UINT32);
}