// CEEDLING NOTICE: This generated file only to be consumed for test runner creation

#include "utExecutionAndResults/utUnderTest/src/MyLib_ComputeAdjustedValue_u32.h"
#include "utExecutionAndResults/utUnderTest/build/vendor/unity/src/unity.h"
#include "mock_MyLib.h"

void setUp(void)
{ }

void tearDown(void)
{ }
void test_ComputeAdjustedValue_u32_NullDeltaPointer_UsesDefaultDelta(void)
{
  uint32_t base_u32 = 100U;
  uint32_t expected_helper_input = 100U;
  uint16_t expected_helper_multiplier = 5U;
  uint32_t mocked_helper_result = 200U;

  InternalHelper_u32_CMockExpectAndReturn(41, expected_helper_input, expected_helper_multiplier, mocked_helper_result);

  uint32_t result = MyLib_ComputeAdjustedValue_u32(base_u32,
                                                            ((void *)0)
                                                                );

  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((mocked_helper_result)), (UNITY_INT)(UNITY_UINT32)((result)), (
 ((void *)0)
 ), (UNITY_UINT)(47), UNITY_DISPLAY_STYLE_UINT32);
}
void test_ComputeAdjustedValue_u32_WithValidDelta_ComputesCorrectly(void)
{
  uint32_t base_u32 = 50U;
  uint16_t delta = 3U;
  uint32_t expected_helper_input = 150U;
  uint16_t expected_helper_multiplier = 5U;
  uint32_t mocked_helper_result = 180U;

  InternalHelper_u32_CMockExpectAndReturn(72, expected_helper_input, expected_helper_multiplier, mocked_helper_result);

  uint32_t result = MyLib_ComputeAdjustedValue_u32(base_u32, &delta);

  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((mocked_helper_result)), (UNITY_INT)(UNITY_UINT32)((result)), (
 ((void *)0)
 ), (UNITY_UINT)(76), UNITY_DISPLAY_STYLE_UINT32);
}
void test_ComputeAdjustedValue_u32_WithDeltaOne_PassesThroughBase(void)
{
  uint32_t base_u32 = 200U;
  uint16_t delta = 1U;
  uint32_t expected_helper_input = 200U;
  uint16_t expected_helper_multiplier = 5U;
  uint32_t mocked_helper_result = 250U;

  InternalHelper_u32_CMockExpectAndReturn(100, expected_helper_input, expected_helper_multiplier, mocked_helper_result);

  uint32_t result = MyLib_ComputeAdjustedValue_u32(base_u32, &delta);

  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((mocked_helper_result)), (UNITY_INT)(UNITY_UINT32)((result)), (
 ((void *)0)
 ), (UNITY_UINT)(104), UNITY_DISPLAY_STYLE_UINT32);
}
void test_ComputeAdjustedValue_u32_WithZeroBase_ReturnsHelperResult(void)
{
  uint32_t base_u32 = 0U;
  uint16_t delta = 10U;
  uint32_t expected_helper_input = 0U;
  uint16_t expected_helper_multiplier = 5U;
  uint32_t mocked_helper_result = 0U;

  InternalHelper_u32_CMockExpectAndReturn(129, expected_helper_input, expected_helper_multiplier, mocked_helper_result);

  uint32_t result = MyLib_ComputeAdjustedValue_u32(base_u32, &delta);

  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((mocked_helper_result)), (UNITY_INT)(UNITY_UINT32)((result)), (
 ((void *)0)
 ), (UNITY_UINT)(133), UNITY_DISPLAY_STYLE_UINT32);
}
void test_ComputeAdjustedValue_u32_WithLargeValues_HandlesMultiplication(void)
{
  uint32_t base_u32 = 600U;
  uint16_t delta = 100U;
  uint32_t expected_helper_input = 60000U;
  uint16_t expected_helper_multiplier = 5U;
  uint32_t mocked_helper_result = 60050U;

  InternalHelper_u32_CMockExpectAndReturn(158, expected_helper_input, expected_helper_multiplier, mocked_helper_result);

  uint32_t result = MyLib_ComputeAdjustedValue_u32(base_u32, &delta);

  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((mocked_helper_result)), (UNITY_INT)(UNITY_UINT32)((result)), (
 ((void *)0)
 ), (UNITY_UINT)(162), UNITY_DISPLAY_STYLE_UINT32);
}
void test_ComputeAdjustedValue_u32_WithMaxDelta_HandlesLargeMultiplication(void)
{
  uint32_t base_u32 = 100U;
  uint16_t delta = 65535U;
  uint32_t expected_helper_input = (uint32_t)100U * 65535U;
  uint16_t expected_helper_multiplier = 5U;
  uint32_t mocked_helper_result = 500U;

  InternalHelper_u32_CMockExpectAndReturn(187, expected_helper_input, expected_helper_multiplier, mocked_helper_result);

  uint32_t result = MyLib_ComputeAdjustedValue_u32(base_u32, &delta);

  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((mocked_helper_result)), (UNITY_INT)(UNITY_UINT32)((result)), (
 ((void *)0)
 ), (UNITY_UINT)(191), UNITY_DISPLAY_STYLE_UINT32);
}
void test_ComputeAdjustedValue_u32_HelperMultiplierAlwaysFive(void)
{
  uint32_t base_u32 = 75U;
  uint16_t delta = 8U;
  uint32_t expected_helper_input = 600U;
  uint16_t expected_helper_multiplier = 5U;
  uint32_t mocked_helper_result = 320U;

  InternalHelper_u32_CMockExpectAndReturn(214, expected_helper_input, expected_helper_multiplier, mocked_helper_result);

  uint32_t result = MyLib_ComputeAdjustedValue_u32(base_u32, &delta);

  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((mocked_helper_result)), (UNITY_INT)(UNITY_UINT32)((result)), (
 ((void *)0)
 ), (UNITY_UINT)(218), UNITY_DISPLAY_STYLE_UINT32);
}
void test_ComputeAdjustedValue_u32_ReturnValuePassthroughFromHelper(void)
{
  uint32_t base_u32 = 50U;
  uint16_t delta = 2U;
  uint32_t expected_helper_input = 100U;
  uint16_t expected_helper_multiplier = 5U;
  uint32_t expected_return_value = 12345U;

  InternalHelper_u32_CMockExpectAndReturn(242, expected_helper_input, expected_helper_multiplier, expected_return_value);

  uint32_t result = MyLib_ComputeAdjustedValue_u32(base_u32, &delta);

  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((expected_return_value)), (UNITY_INT)(UNITY_UINT32)((result)), (
 ((void *)0)
 ), (UNITY_UINT)(246), UNITY_DISPLAY_STYLE_UINT32);
}
void test_ComputeAdjustedValue_u32_SequentialCallsWithDifferentParameters(void)
{
  uint32_t result1 = 0U;
  InternalHelper_u32_CMockExpectAndReturn(267, 10U, 5U, 100U);
  result1 = MyLib_ComputeAdjustedValue_u32(10U,
                                               ((void *)0)
                                                   );
  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((100U)), (UNITY_INT)(UNITY_UINT32)((result1)), (
 ((void *)0)
 ), (UNITY_UINT)(269), UNITY_DISPLAY_STYLE_UINT32);

  uint32_t delta2 = 3U;
  InternalHelper_u32_CMockExpectAndReturn(273, 60U, 5U, 150U);
  uint32_t result2 = MyLib_ComputeAdjustedValue_u32(20U, &delta2);
  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((150U)), (UNITY_INT)(UNITY_UINT32)((result2)), (
 ((void *)0)
 ), (UNITY_UINT)(275), UNITY_DISPLAY_STYLE_UINT32);
}
void test_ComputeAdjustedValue_u32_WithZeroDelta_ResultsInZeroProduct(void)
{
  uint32_t base_u32 = 100U;
  uint16_t delta = 0U;
  uint32_t expected_helper_input = 0U;
  uint16_t expected_helper_multiplier = 5U;
  uint32_t mocked_helper_result = 5U;

  InternalHelper_u32_CMockExpectAndReturn(299, expected_helper_input, expected_helper_multiplier, mocked_helper_result);

  uint32_t result = MyLib_ComputeAdjustedValue_u32(base_u32, &delta);

  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((mocked_helper_result)), (UNITY_INT)(UNITY_UINT32)((result)), (
 ((void *)0)
 ), (UNITY_UINT)(303), UNITY_DISPLAY_STYLE_UINT32);
}