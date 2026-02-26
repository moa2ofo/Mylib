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

void test_ComputeAdjustedValue_u32_WithMaxDelta_HandlesLargeMultiplication(void)
{
  uint32_t base_u32 = 100U;
  uint16_t delta = 65535U;
  uint32_t expected_helper_input = (uint32_t)100U * 65535U;
  uint16_t expected_helper_multiplier = 5U;
  uint32_t mocked_helper_result = 500U;

  InternalHelper_u32_CMockExpectAndReturn(23, expected_helper_input, expected_helper_multiplier, mocked_helper_result);

  uint32_t result = MyLib_ComputeAdjustedValue_u32(base_u32, &delta);

  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((mocked_helper_result)), (UNITY_INT)(UNITY_UINT32)((result)), (
 ((void *)0)
 ), (UNITY_UINT)(27), UNITY_DISPLAY_STYLE_UINT32);
}