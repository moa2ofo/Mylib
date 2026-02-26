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

void test_AnalyzeArray_u32_mock_return_value_unused(void)
{
  uint16_t array[2] = {10U, 20U};
  uint32_t result;

  MyLib_ComputeAdjustedValue_u32_CMockExpectAndReturn(54, 60U,
 ((void *)0)
 , 999U);

  result = MyLib_AnalyzeArray_u32(array, 2U, 2U);

  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((60U)), (UNITY_INT)(UNITY_UINT32)((result)), (
 ((void *)0)
 ), (UNITY_UINT)(58), UNITY_DISPLAY_STYLE_UINT32);
}