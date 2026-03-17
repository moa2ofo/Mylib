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

void test_record_id_lower_16_bits_all_zero(void)
{
  uint32_t l_base_u32 = 0x00010000U;
  MyLib_record_t expected_rec;
  uint32_t result;

  g_counter_u32 = 10U;

  InternalHelper_u32_CMockExpectAndReturn(20, 50U, 0U, l_base_u32);

  expected_rec.id_u16 = 0x0000U;
  expected_rec.value_u32 = l_base_u32 / 2U;

  MyLib_ProcessRecord_CMockExpect(25, &expected_rec, (5U));
  MyLib_ProcessRecord_CMockIgnoreArg_rec_pc(26);

  result = MyLib_Orchestrate_u32(50U,
                                     ((void *)0)
                                         );

  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((l_base_u32 + g_counter_u32)), (UNITY_INT)(UNITY_UINT32)((result)), (
 ((void *)0)
 ), (UNITY_UINT)(30), UNITY_DISPLAY_STYLE_UINT32);
}