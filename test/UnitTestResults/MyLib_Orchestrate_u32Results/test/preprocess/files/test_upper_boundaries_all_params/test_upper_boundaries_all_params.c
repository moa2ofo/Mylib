// CEEDLING NOTICE: This generated file only to be consumed for test runner creation

#include "mock_MyLib.h"
#include "utExecutionAndResults/utUnderTest/build/vendor/unity/src/unity.h"
#include "utExecutionAndResults/utUnderTest/src/MyLib_Orchestrate_u32.h"

void setUp(void) {
}

void tearDown(void) {
}

void test_upper_boundaries_all_params(void) {
  uint16_t delta = 65535U;
  uint32_t l_base_u32 = 300U;
  MyLib_record_t expected_rec;
  uint32_t result;

  g_counter_u32 = 500U;

  InternalHelper_u32_CMockExpectAndReturn(21, 200U, 65535U, l_base_u32);

  expected_rec.id_u16 = (uint16_t)(l_base_u32 & 0xFFFFU);
  expected_rec.value_u32 = l_base_u32 / 2U;

  MyLib_ProcessRecord_CMockExpect(26, &expected_rec, (5U));
  MyLib_ProcessRecord_CMockIgnoreArg_rec_pc(27);

  result = MyLib_Orchestrate_u32(200U, &delta);

  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((l_base_u32 + g_counter_u32)), (UNITY_INT)(UNITY_UINT32)((result)), (((void *)0)), (UNITY_UINT)(31), UNITY_DISPLAY_STYLE_UINT32);
}