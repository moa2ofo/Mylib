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

void test_MyLib_ProcessRecord_MockFunctionCalledWithCorrectParams(void)
{
  test_record.id_u16 = 100U;
  test_record.value_u32 = 300U;

  uint32_t expected_accumulation = 300U * 3U;

  MyLib_ComputeAdjustedValue_u32_CMockExpectAndReturn(33, expected_accumulation,
 ((void *)0)
 , 55U);
  MyLib_ComputeAdjustedValue_u32_CMockIgnoreArg_delta_pc_u16(34);

  MyLib_ProcessRecord(&test_record, 3U);

  do { if ((
 1
 ))
{ } else { UnityFail( ((" Expected TRUE Was FALSE")), (UNITY_UINT)((40))); } } while (0);
}