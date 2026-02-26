// CEEDLING NOTICE: This generated file only to be consumed for test runner creation

#include "utExecutionAndResults/utUnderTest/src/MyLib_Orchestrate_u32.h"
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

void test_MyLib_Orchestrate_u32_CallsInternalHelperWithCorrectArguments_Verified(void)
{
  uint32_t start_u32 = 150U;
  uint16_t delta_value = 25U;

  InternalHelper_u32_CMockExpectAndReturn(38, start_u32, delta_value, 300U);

  MyLib_ProcessRecord_CMockExpect(40,
 ((void *)0)
 , (5U));
  MyLib_ProcessRecord_CMockIgnoreArg_rec_pc(41);

  g_counter_u32 = 0U;

  MyLib_Orchestrate_u32(start_u32, &delta_value);

  do { UnityMessage(("InternalHelper_u32 called with correct arguments"), 49); longjmp(Unity.AbortFrame, 1); } while (0);
}