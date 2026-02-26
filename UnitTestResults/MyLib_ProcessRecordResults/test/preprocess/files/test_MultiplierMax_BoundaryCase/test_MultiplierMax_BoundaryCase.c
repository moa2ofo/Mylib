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

void test_MyLib_ProcessRecord_MultiplierMax_BoundaryCase(void)
{
  test_record.id_u16 = 1U;
  test_record.value_u32 = 10U;

  uint32_t expected_accumulation = 10U * 255U;
  uint32_t expected_counter = initial_counter + expected_accumulation;

  MyLib_ComputeAdjustedValue_u32_CMockExpectAndReturn(34, expected_accumulation,
 ((void *)0)
 , 0U);
  MyLib_ComputeAdjustedValue_u32_CMockIgnoreArg_delta_pc_u16(35);

  MyLib_ProcessRecord(&test_record, 255U);

  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((expected_counter)), (UNITY_INT)(UNITY_UINT32)((g_counter_u32)), (
 ((void *)0)
 ), (UNITY_UINT)(41), UNITY_DISPLAY_STYLE_UINT32);
}