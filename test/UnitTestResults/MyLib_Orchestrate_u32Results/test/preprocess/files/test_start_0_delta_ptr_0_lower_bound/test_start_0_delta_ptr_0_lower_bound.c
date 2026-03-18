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

void test_start_0_delta_ptr_0_lower_bound(void)
{
  uint16_t delta = 0U;
  uint32_t l_base_u32 = 60U;
  MyLib_record_t expected_rec;
  uint32_t result;

  g_counter_u32 = 25U;

  InternalHelper_u32_CMockExpectAndReturn(21, 0U, 0U, l_base_u32);

  expected_rec.id_u16 = (uint16_t)(l_base_u32 & 0xFFFFU);
  expected_rec.value_u32 = l_base_u32 / 2U;

  MyLib_ProcessRecord_CMockExpect(26, &expected_rec, (5U));
  MyLib_ProcessRecord_CMockIgnoreArg_rec_pc(27);

  result = MyLib_Orchestrate_u32(0U, &delta);

  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((l_base_u32 + g_counter_u32)), (UNITY_INT)(UNITY_UINT32)((result)), (
 ((void *)0)
 ), (UNITY_UINT)(31), UNITY_DISPLAY_STYLE_UINT32);
}