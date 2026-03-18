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

void test_len_300_factor_1_all_1_unchanged_returns_300(void)
{
  uint16_t array[300];
  uint32_t result;
  size_t i;

  for(i = 0U; i < 300U; i++)
{
    array[i] = 1U;
  }

  MyLib_ComputeAdjustedValue_u32_CMockExpectAndReturn(24, 300U,
 ((void *)0)
 , 0U);
  MyLib_ComputeAdjustedValue_u32_CMockIgnoreArg_delta_pc_u16(25);

  result = MyLib_AnalyzeArray_u32(array, 300U, 1U);

  for(i = 0U; i < 300U; i++)
{
    UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT16)((1U)), (UNITY_INT)(UNITY_UINT16)((array[i])), (
   ((void *)0)
   ), (UNITY_UINT)(30), UNITY_DISPLAY_STYLE_UINT16);
  }
  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((300U)), (UNITY_INT)(UNITY_UINT32)((result)), (
 ((void *)0)
 ), (UNITY_UINT)(32), UNITY_DISPLAY_STYLE_UINT32);
}