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

void test_MyLib_Orchestrate_u32_WithIgnoredArguments_FunctionStillExecutes(void)
{
  InternalHelper_u32_CMockExpectAnyArgsAndReturn(34, 175U);

  MyLib_ProcessRecord_CMockExpectAnyArgs(36);

  g_counter_u32 = 25U;

  uint32_t result = MyLib_Orchestrate_u32(100U,
                                               ((void *)0)
                                                   );

  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((200U)), (UNITY_INT)(UNITY_UINT32)((result)), (
 ((void *)0)
 ), (UNITY_UINT)(44), UNITY_DISPLAY_STYLE_UINT32);
}