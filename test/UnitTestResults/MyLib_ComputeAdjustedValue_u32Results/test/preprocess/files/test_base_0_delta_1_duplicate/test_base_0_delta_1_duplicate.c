// CEEDLING NOTICE: This generated file only to be consumed for test runner creation

#include "utExecutionAndResults/utUnderTest/src/MyLib_ComputeAdjustedValue_u32.h"
#include "utExecutionAndResults/utUnderTest/build/vendor/unity/src/unity.h"
#include "mock_MyLib.h"

void setUp(void)
{
}

void tearDown(void)
{
}

void test_base_0_delta_1_duplicate(void)
{
  uint32_t l_result_u32;
  uint32_t l_expected_u32 = 42U;
  uint16_t l_delta_u16 = 1U;

  InternalHelper_u32_CMockExpectAndReturn(16, 0U, (uint16_t)(5U), l_expected_u32);

  l_result_u32 = MyLib_ComputeAdjustedValue_u32(0U, &l_delta_u16);

  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((l_expected_u32)), (UNITY_INT)(UNITY_UINT32)((l_result_u32)), (
 ((void *)0)
 ), (UNITY_UINT)(20), UNITY_DISPLAY_STYLE_UINT32);
}