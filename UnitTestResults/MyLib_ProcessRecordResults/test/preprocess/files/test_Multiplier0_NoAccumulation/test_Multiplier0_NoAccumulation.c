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

void test_MyLib_ProcessRecord_Multiplier0_NoAccumulation(void)
{
  test_record.id_u16 = 100U;
  test_record.value_u32 = 1000U;

  MyLib_ComputeAdjustedValue_u32_CMockExpectAndReturn(31, 0U,
 ((void *)0)
 , 0U);
  MyLib_ComputeAdjustedValue_u32_CMockIgnoreArg_delta_pc_u16(32);

  MyLib_ProcessRecord(&test_record, 0U);

  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((initial_counter)), (UNITY_INT)(UNITY_UINT32)((g_counter_u32)), (
 ((void *)0)
 ), (UNITY_UINT)(38), UNITY_DISPLAY_STYLE_UINT32);
}