// CEEDLING NOTICE: This generated file only to be consumed for test runner creation

#include "utExecutionAndResults/utUnderTest/src/MyLib_AnalyzeArray_u32.h"
#include "utExecutionAndResults/utUnderTest/build/vendor/unity/src/unity.h"
#include "mock_MyLib.h"

void setUp(void)
{
}

void tearDown(void)
{
}

void test_ValidArray_Len1_Factor65535(void)
{
  uint16_t array[1] = {2};
  uint32_t result;
  uint32_t expected_scaled = (uint16_t)(2 * 65535);

  MyLib_ComputeAdjustedValue_u32_CMockExpectAndReturn(32, expected_scaled,
 ((void *)0)
 , 0);

  result = MyLib_AnalyzeArray_u32(array, 1, 65535);

  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((expected_scaled)), (UNITY_INT)(UNITY_UINT32)((result)), (
 ((void *)0)
 ), (UNITY_UINT)(36), UNITY_DISPLAY_STYLE_UINT32);
  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT16)((expected_scaled)), (UNITY_INT)(UNITY_UINT16)((array[0])), (
 ((void *)0)
 ), (UNITY_UINT)(37), UNITY_DISPLAY_STYLE_UINT16);
}