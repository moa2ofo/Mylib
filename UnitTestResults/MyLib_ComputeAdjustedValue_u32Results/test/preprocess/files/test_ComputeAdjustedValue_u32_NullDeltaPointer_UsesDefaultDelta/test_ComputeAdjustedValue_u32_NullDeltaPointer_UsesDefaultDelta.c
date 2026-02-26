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

void test_ComputeAdjustedValue_u32_NullDeltaPointer_UsesDefaultDelta(void)
{
  uint32_t base_u32 = 100U;
  uint32_t expected_helper_input = 100U;
  uint16_t expected_helper_multiplier = 5U;
  uint32_t mocked_helper_result = 200U;

  InternalHelper_u32_CMockExpectAndReturn(23, expected_helper_input, expected_helper_multiplier, mocked_helper_result);

  uint32_t result = MyLib_ComputeAdjustedValue_u32(base_u32,
                                                            ((void *)0)
                                                                );

  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((mocked_helper_result)), (UNITY_INT)(UNITY_UINT32)((result)), (
 ((void *)0)
 ), (UNITY_UINT)(29), UNITY_DISPLAY_STYLE_UINT32);
}