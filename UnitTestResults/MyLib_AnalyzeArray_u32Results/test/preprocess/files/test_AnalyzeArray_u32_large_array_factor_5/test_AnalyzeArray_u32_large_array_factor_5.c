// CEEDLING NOTICE: This generated file only to be consumed for test runner creation

#include "utExecutionAndResults/utUnderTest/src/MyLib_AnalyzeArray_u32.h"
#include "utExecutionAndResults/utUnderTest/build/vendor/unity/src/unity.h"
#include "mock_MyLib.h"

void setUp(void)
{
  g_counter_u32 = 0U;
  g_record.id_u16 = 0U;
  g_record.value_u32 = 0U;
  g_systemReady_b =
                   

  mock_MyLib_Init();
}

void tearDown(void)
{
  mock_MyLib_Verify();
}

void test_AnalyzeArray_u32_large_array_factor_5(void)
{
  uint16_t array[5] = {1U, 2U, 3U, 4U, 5U};
  uint16_t expected[5] = {5U, 10U, 15U, 20U, 25U};
  uint32_t expected_sum = 75U;
  uint32_t result;

  MyLib_ComputeAdjustedValue_u32_CMockExpectAndReturn(56, expected_sum,
 ((void *)0)
 , 0U);

  result = MyLib_AnalyzeArray_u32(array, 5U, 5U);

  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((expected_sum)), (UNITY_INT)(UNITY_UINT32)((result)), (
 ((void *)0)
 ), (UNITY_UINT)(60), UNITY_DISPLAY_STYLE_UINT32);
  UnityAssertEqualIntArray(( const void*)((expected)), ( const void*)((array)), (UNITY_UINT32)((5U)), (
 ((void *)0)
 ), (UNITY_UINT)(61), UNITY_DISPLAY_STYLE_UINT16, UNITY_ARRAY_TO_ARRAY);
}