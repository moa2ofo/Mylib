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

void test_MyLib_Orchestrate_u32_WhenCounterIsZero_ReturnsBaseValue(void)
{
  uint32_t start_u32 = 42U;
  uint32_t l_base_u32 = 555U;

  InternalHelper_u32_CMockExpectAndReturn(37, start_u32, 0U, l_base_u32);

  MyLib_ProcessRecord_CMockExpect(39,
 ((void *)0)
 , (5U));
  MyLib_ProcessRecord_CMockIgnoreArg_rec_pc(40);

  g_counter_u32 = 0U;

  uint32_t result = MyLib_Orchestrate_u32(start_u32,
                                                    ((void *)0)
                                                        );

  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((l_base_u32)), (UNITY_INT)(UNITY_UINT32)((result)), (
 ((void *)0)
 ), (UNITY_UINT)(48), UNITY_DISPLAY_STYLE_UINT32);
}