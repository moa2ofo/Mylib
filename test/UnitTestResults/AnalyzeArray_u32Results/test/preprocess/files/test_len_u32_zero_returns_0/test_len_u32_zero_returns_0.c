// CEEDLING NOTICE: This generated file only to be consumed for test runner creation

#include "utExecutionAndResults/utUnderTest/build/vendor/unity/src/unity.h"
#include "mock_MyLib.h"

void setUp(void)
{
}

void tearDown(void)
{
}

void test_len_u32_zero_returns_0(void)
{
  uint16_t values_au16[5] = {1U, 2U, 3U, 4U, 5U};
  uint32_t result_u32;

  result_u32 = AnalyzeArray_u32(values_au16, 0U, 5U);

  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((0U)), (UNITY_INT)(UNITY_UINT32)((result_u32)), (
 ((void *)0)
 ), (UNITY_UINT)(17), UNITY_DISPLAY_STYLE_UINT32);
}