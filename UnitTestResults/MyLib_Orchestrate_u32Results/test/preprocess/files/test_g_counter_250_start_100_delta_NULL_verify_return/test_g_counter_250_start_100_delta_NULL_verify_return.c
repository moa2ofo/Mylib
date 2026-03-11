// CEEDLING NOTICE: This generated file only to be consumed for test runner creation

#include "utExecutionAndResults/utUnderTest/src/MyLib_Orchestrate_u32.h"
#include "utExecutionAndResults/utUnderTest/build/vendor/unity/src/unity.h"
#include "mock_MyLib.h"

void setUp(void)
{
}

void tearDown(void)
{
}

void test_g_counter_250_start_100_delta_NULL_verify_return(void)
{
  uint32_t l_base_u32 = 140U;
  MyLib_record_t expected_rec;
  uint32_t result;

  g_counter_u32 = 250U;

  InternalHelper_u32_CMockExpectAndReturn(20, 100U, 0U, l_base_u32);

  expected_rec.id_u16 = (uint16_t)(l_base_u32 & 0xFFFFU);
  expected_rec.value_u32 = l_base_u32 / 2U;

  MyLib_ProcessRecord_CMockExpect(25, &expected_rec, (5U));
  MyLib_ProcessRecord_CMockIgnoreArg_rec_pc(26);

  result = MyLib_Orchestrate_u32(100U,
                                      ((void *)0)
                                          );

  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((l_base_u32 + 250U)), (UNITY_INT)(UNITY_UINT32)((result)), (
 ((void *)0)
 ), (UNITY_UINT)(30), UNITY_DISPLAY_STYLE_UINT32);
}