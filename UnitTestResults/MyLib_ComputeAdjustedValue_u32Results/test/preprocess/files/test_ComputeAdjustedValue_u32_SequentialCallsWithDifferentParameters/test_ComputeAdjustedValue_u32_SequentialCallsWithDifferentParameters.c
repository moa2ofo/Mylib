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

void test_ComputeAdjustedValue_u32_SequentialCallsWithDifferentParameters(void)
{
  uint32_t result1 = 0U;
  InternalHelper_u32_CMockExpectAndReturn(19, 10U, 5U, 100U);
  result1 = MyLib_ComputeAdjustedValue_u32(10U,
                                               ((void *)0)
                                                   );
  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((100U)), (UNITY_INT)(UNITY_UINT32)((result1)), (
 ((void *)0)
 ), (UNITY_UINT)(21), UNITY_DISPLAY_STYLE_UINT32);

  uint32_t delta2 = 3U;
  InternalHelper_u32_CMockExpectAndReturn(25, 60U, 5U, 150U);
  uint32_t result2 = MyLib_ComputeAdjustedValue_u32(20U, &delta2);
  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((150U)), (UNITY_INT)(UNITY_UINT32)((result2)), (
 ((void *)0)
 ), (UNITY_UINT)(27), UNITY_DISPLAY_STYLE_UINT32);
}