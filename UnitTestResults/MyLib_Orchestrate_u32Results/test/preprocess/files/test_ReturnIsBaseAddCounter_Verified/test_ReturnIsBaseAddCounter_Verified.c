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

void test_MyLib_Orchestrate_u32_ReturnIsBaseAddCounter_Verified(void)
{
  uint32_t start_u32 = 0U;
  uint32_t l_base_u32 = 123U;
  uint32_t counter_value = 456U;
  uint32_t expected_return = 123U + 456U;

  InternalHelper_u32_CMockExpectAndReturn(39, start_u32, 0U, l_base_u32);

  MyLib_ProcessRecord_CMockExpect(41,
 ((void *)0)
 , (5U));
  MyLib_ProcessRecord_CMockIgnoreArg_rec_pc(42);

  g_counter_u32 = counter_value;

  uint32_t result = MyLib_Orchestrate_u32(start_u32,
                                                    ((void *)0)
                                                        );

  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((expected_return)), (UNITY_INT)(UNITY_UINT32)((result)), (
 ((void *)0)
 ), (UNITY_UINT)(50), UNITY_DISPLAY_STYLE_UINT32);
  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((579U)), (UNITY_INT)(UNITY_UINT32)((result)), (
 ((void *)0)
 ), (UNITY_UINT)(51), UNITY_DISPLAY_STYLE_UINT32);
}