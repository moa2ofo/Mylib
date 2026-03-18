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

void test_len_3_factor_10_values_100_200_300_becomes_1000_2000_3000_returns_6000(void)
{
  uint16_t array[3] = {100U, 200U, 300U};
  uint32_t result;

  MyLib_ComputeAdjustedValue_u32_CMockExpectAndReturn(19, 6000U,
 ((void *)0)
 , 0U);
  MyLib_ComputeAdjustedValue_u32_CMockIgnoreArg_delta_pc_u16(20);

  result = MyLib_AnalyzeArray_u32(array, 3U, 10U);

  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT16)((1000U)), (UNITY_INT)(UNITY_UINT16)((array[0])), (
 ((void *)0)
 ), (UNITY_UINT)(24), UNITY_DISPLAY_STYLE_UINT16);
  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT16)((2000U)), (UNITY_INT)(UNITY_UINT16)((array[1])), (
 ((void *)0)
 ), (UNITY_UINT)(25), UNITY_DISPLAY_STYLE_UINT16);
  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT16)((3000U)), (UNITY_INT)(UNITY_UINT16)((array[2])), (
 ((void *)0)
 ), (UNITY_UINT)(26), UNITY_DISPLAY_STYLE_UINT16);
  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((6000U)), (UNITY_INT)(UNITY_UINT32)((result)), (
 ((void *)0)
 ), (UNITY_UINT)(27), UNITY_DISPLAY_STYLE_UINT32);
}