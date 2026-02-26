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

void test_AnalyzeArray_u32_mock_function_called_correct_params(void)
{
  uint16_t array[3] = {5U, 5U, 5U};
  uint32_t result;
  uint32_t expected_sum = 30U;

  MyLib_ComputeAdjustedValue_u32_CMockExpectAndReturn(56, expected_sum,
 ((void *)0)
 , 100U);

  result = MyLib_AnalyzeArray_u32(array, 3U, 2U);

  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((expected_sum)), (UNITY_INT)(UNITY_UINT32)((result)), (
 ((void *)0)
 ), (UNITY_UINT)(60), UNITY_DISPLAY_STYLE_UINT32);
}