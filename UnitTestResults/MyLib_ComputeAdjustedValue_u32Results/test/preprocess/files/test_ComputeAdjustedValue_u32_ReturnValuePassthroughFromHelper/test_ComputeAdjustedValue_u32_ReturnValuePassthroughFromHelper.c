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

void test_ComputeAdjustedValue_u32_ReturnValuePassthroughFromHelper(void)
{
  uint32_t base_u32 = 50U;
  uint16_t delta = 2U;
  uint32_t expected_helper_input = 100U;
  uint16_t expected_helper_multiplier = 5U;
  uint32_t expected_return_value = 12345U;

  InternalHelper_u32_CMockExpectAndReturn(23, expected_helper_input, expected_helper_multiplier, expected_return_value);

  uint32_t result = MyLib_ComputeAdjustedValue_u32(base_u32, &delta);

  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((expected_return_value)), (UNITY_INT)(UNITY_UINT32)((result)), (
 ((void *)0)
 ), (UNITY_UINT)(27), UNITY_DISPLAY_STYLE_UINT32);
}