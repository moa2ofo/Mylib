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

void test_AnalyzeArray_u32_in_place_modification(void)
{
  uint16_t original_array[5] = {1U, 2U, 3U, 4U, 5U};
  uint16_t *array_ptr = original_array;
  uint32_t result;

  MyLib_ComputeAdjustedValue_u32_CMockExpectAndReturn(54, 45U,
 ((void *)0)
 , 0U);

  result = MyLib_AnalyzeArray_u32(array_ptr, 5U, 3U);

  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT16)((3U)), (UNITY_INT)(UNITY_UINT16)((original_array[0])), (
 ((void *)0)
 ), (UNITY_UINT)(59), UNITY_DISPLAY_STYLE_UINT16);
  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT16)((6U)), (UNITY_INT)(UNITY_UINT16)((original_array[1])), (
 ((void *)0)
 ), (UNITY_UINT)(60), UNITY_DISPLAY_STYLE_UINT16);
  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT16)((9U)), (UNITY_INT)(UNITY_UINT16)((original_array[2])), (
 ((void *)0)
 ), (UNITY_UINT)(61), UNITY_DISPLAY_STYLE_UINT16);
  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT16)((12U)), (UNITY_INT)(UNITY_UINT16)((original_array[3])), (
 ((void *)0)
 ), (UNITY_UINT)(62), UNITY_DISPLAY_STYLE_UINT16);
  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT16)((15U)), (UNITY_INT)(UNITY_UINT16)((original_array[4])), (
 ((void *)0)
 ), (UNITY_UINT)(63), UNITY_DISPLAY_STYLE_UINT16);
  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((45U)), (UNITY_INT)(UNITY_UINT32)((result)), (
 ((void *)0)
 ), (UNITY_UINT)(64), UNITY_DISPLAY_STYLE_UINT32);
}