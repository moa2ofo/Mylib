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

void test_MyLib_Orchestrate_u32_SequentialCalls_CounterAccumulatesAsExpected(void)
{
  InternalHelper_u32_CMockExpectAndReturn(34, 10U, 0U, 50U);
  MyLib_ProcessRecord_CMockExpect(35,
 ((void *)0)
 , (5U));
  MyLib_ProcessRecord_CMockIgnoreArg_rec_pc(36);
  g_counter_u32 = 10U;

  uint32_t result1 = MyLib_Orchestrate_u32(10U,
                                               ((void *)0)
                                                   );
  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((60U)), (UNITY_INT)(UNITY_UINT32)((result1)), (
 ((void *)0)
 ), (UNITY_UINT)(40), UNITY_DISPLAY_STYLE_UINT32);

  InternalHelper_u32_CMockExpectAndReturn(43, 20U, 0U, 100U);
  MyLib_ProcessRecord_CMockExpect(44,
 ((void *)0)
 , (5U));
  MyLib_ProcessRecord_CMockIgnoreArg_rec_pc(45);
  g_counter_u32 = 30U;

  uint32_t result2 = MyLib_Orchestrate_u32(20U,
                                               ((void *)0)
                                                   );
  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((130U)), (UNITY_INT)(UNITY_UINT32)((result2)), (
 ((void *)0)
 ), (UNITY_UINT)(49), UNITY_DISPLAY_STYLE_UINT32);
}