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

void test_AnalyzeArray_u32_sum_accumulation_10_elements(void)
{
  uint16_t array[10] = {1U, 2U, 3U, 4U, 5U, 6U, 7U, 8U, 9U, 10U};
  uint16_t expected[10] = {1U, 2U, 3U, 4U, 5U, 6U, 7U, 8U, 9U, 10U};
  uint32_t expected_sum = 55U;
  uint32_t result;

  MyLib_ComputeAdjustedValue_u32_CMockExpectAndReturn(55, expected_sum,
 ((void *)0)
 , 0U);

  result = MyLib_AnalyzeArray_u32(array, 10U, 1U);

  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((expected_sum)), (UNITY_INT)(UNITY_UINT32)((result)), (
 ((void *)0)
 ), (UNITY_UINT)(59), UNITY_DISPLAY_STYLE_UINT32);
  UnityAssertEqualIntArray(( const void*)((expected)), ( const void*)((array)), (UNITY_UINT32)((10U)), (
 ((void *)0)
 ), (UNITY_UINT)(60), UNITY_DISPLAY_STYLE_UINT16, UNITY_ARRAY_TO_ARRAY);
}