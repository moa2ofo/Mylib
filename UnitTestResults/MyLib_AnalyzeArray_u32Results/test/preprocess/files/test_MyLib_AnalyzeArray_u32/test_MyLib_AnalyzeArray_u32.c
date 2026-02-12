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

void test_AnalyzeArray_u32_NULL_pointer_returns_zero(void)
{
  uint32_t result;

  result = MyLib_AnalyzeArray_u32(
                                 ((void *)0)
                                     , 10U, 2U);

  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((0U)), (UNITY_INT)(UNITY_UINT32)((result)), (
 ((void *)0)
 ), (UNITY_UINT)(62), UNITY_DISPLAY_STYLE_UINT32);
  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((0U)), (UNITY_INT)(UNITY_UINT32)((g_counter_u32)), (
 ((void *)0)
 ), (UNITY_UINT)(63), UNITY_DISPLAY_STYLE_UINT32);
  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT16)((0U)), (UNITY_INT)(UNITY_UINT16)((g_record.id_u16)), (
 ((void *)0)
 ), (UNITY_UINT)(64), UNITY_DISPLAY_STYLE_UINT16);
  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((0U)), (UNITY_INT)(UNITY_UINT32)((g_record.value_u32)), (
 ((void *)0)
 ), (UNITY_UINT)(65), UNITY_DISPLAY_STYLE_UINT32);
  UnityAssertEqualNumber((UNITY_INT)((
 0
 )), (UNITY_INT)((g_systemReady_b)), (
 ((void *)0)
 ), (UNITY_UINT)(66), UNITY_DISPLAY_STYLE_INT);
}

void test_AnalyzeArray_u32_zero_length_returns_zero(void)
{
  uint16_t array[5] = {1U, 2U, 3U, 4U, 5U};
  uint32_t result;
  uint16_t expected_array[5] = {1U, 2U, 3U, 4U, 5U};

  result = MyLib_AnalyzeArray_u32(array, 0U, 5U);

  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((0U)), (UNITY_INT)(UNITY_UINT32)((result)), (
 ((void *)0)
 ), (UNITY_UINT)(86), UNITY_DISPLAY_STYLE_UINT32);

  UnityAssertEqualIntArray(( const void*)((expected_array)), ( const void*)((array)), (UNITY_UINT32)((5U)), (
 ((void *)0)
 ), (UNITY_UINT)(88), UNITY_DISPLAY_STYLE_UINT16, UNITY_ARRAY_TO_ARRAY);
  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((0U)), (UNITY_INT)(UNITY_UINT32)((g_counter_u32)), (
 ((void *)0)
 ), (UNITY_UINT)(89), UNITY_DISPLAY_STYLE_UINT32);
  UnityAssertEqualNumber((UNITY_INT)((
 0
 )), (UNITY_INT)((g_systemReady_b)), (
 ((void *)0)
 ), (UNITY_UINT)(90), UNITY_DISPLAY_STYLE_INT);
}

void test_AnalyzeArray_u32_single_element_factor_1(void)
{
  uint16_t array[1] = {42U};
  uint32_t result;

  MyLib_ComputeAdjustedValue_u32_CMockExpectAndReturn(106, 42U,
 ((void *)0)
 , 0U);

  result = MyLib_AnalyzeArray_u32(array, 1U, 1U);

  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((42U)), (UNITY_INT)(UNITY_UINT32)((result)), (
 ((void *)0)
 ), (UNITY_UINT)(110), UNITY_DISPLAY_STYLE_UINT32);
  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT16)((42U)), (UNITY_INT)(UNITY_UINT16)((array[0])), (
 ((void *)0)
 ), (UNITY_UINT)(111), UNITY_DISPLAY_STYLE_UINT16);
}

void test_AnalyzeArray_u32_single_element_factor_zero(void)
{
  uint16_t array[1] = {100U};
  uint32_t result;

  MyLib_ComputeAdjustedValue_u32_CMockExpectAndReturn(126, 0U,
 ((void *)0)
 , 0U);

  result = MyLib_AnalyzeArray_u32(array, 1U, 0U);

  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((0U)), (UNITY_INT)(UNITY_UINT32)((result)), (
 ((void *)0)
 ), (UNITY_UINT)(130), UNITY_DISPLAY_STYLE_UINT32);
  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT16)((0U)), (UNITY_INT)(UNITY_UINT16)((array[0])), (
 ((void *)0)
 ), (UNITY_UINT)(131), UNITY_DISPLAY_STYLE_UINT16);
}

void test_AnalyzeArray_u32_single_element_factor_max(void)
{
  uint16_t array[1] = {1U};
  uint32_t result;

  MyLib_ComputeAdjustedValue_u32_CMockExpectAndReturn(146, 65535U,
 ((void *)0)
 , 0U);

  result = MyLib_AnalyzeArray_u32(array, 1U, 65535U);

  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((65535U)), (UNITY_INT)(UNITY_UINT32)((result)), (
 ((void *)0)
 ), (UNITY_UINT)(150), UNITY_DISPLAY_STYLE_UINT32);
  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT16)((65535U)), (UNITY_INT)(UNITY_UINT16)((array[0])), (
 ((void *)0)
 ), (UNITY_UINT)(151), UNITY_DISPLAY_STYLE_UINT16);
}

void test_AnalyzeArray_u32_multiple_elements_factor_2(void)
{
  uint16_t array[3] = {10U, 20U, 30U};
  uint16_t expected_array[3] = {20U, 40U, 60U};
  uint32_t result;

  MyLib_ComputeAdjustedValue_u32_CMockExpectAndReturn(168, 120U,
 ((void *)0)
 , 0U);

  result = MyLib_AnalyzeArray_u32(array, 3U, 2U);

  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((120U)), (UNITY_INT)(UNITY_UINT32)((result)), (
 ((void *)0)
 ), (UNITY_UINT)(172), UNITY_DISPLAY_STYLE_UINT32);
  UnityAssertEqualIntArray(( const void*)((expected_array)), ( const void*)((array)), (UNITY_UINT32)((3U)), (
 ((void *)0)
 ), (UNITY_UINT)(173), UNITY_DISPLAY_STYLE_UINT16, UNITY_ARRAY_TO_ARRAY);
}

void test_AnalyzeArray_u32_multiple_elements_factor_zero(void)
{
  uint16_t array[4] = {5U, 10U, 15U, 20U};
  uint16_t expected_array[4] = {0U, 0U, 0U, 0U};
  uint32_t result;

  MyLib_ComputeAdjustedValue_u32_CMockExpectAndReturn(190, 0U,
 ((void *)0)
 , 0U);

  result = MyLib_AnalyzeArray_u32(array, 4U, 0U);

  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((0U)), (UNITY_INT)(UNITY_UINT32)((result)), (
 ((void *)0)
 ), (UNITY_UINT)(194), UNITY_DISPLAY_STYLE_UINT32);
  UnityAssertEqualIntArray(( const void*)((expected_array)), ( const void*)((array)), (UNITY_UINT32)((4U)), (
 ((void *)0)
 ), (UNITY_UINT)(195), UNITY_DISPLAY_STYLE_UINT16, UNITY_ARRAY_TO_ARRAY);
}

void test_AnalyzeArray_u32_in_place_modification(void)
{
  uint16_t original_array[5] = {1U, 2U, 3U, 4U, 5U};
  uint16_t *array_ptr = original_array;
  uint32_t result;

  MyLib_ComputeAdjustedValue_u32_CMockExpectAndReturn(210, 45U,
 ((void *)0)
 , 0U);

  result = MyLib_AnalyzeArray_u32(array_ptr, 5U, 3U);

  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT16)((3U)), (UNITY_INT)(UNITY_UINT16)((original_array[0])), (
 ((void *)0)
 ), (UNITY_UINT)(215), UNITY_DISPLAY_STYLE_UINT16);
  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT16)((6U)), (UNITY_INT)(UNITY_UINT16)((original_array[1])), (
 ((void *)0)
 ), (UNITY_UINT)(216), UNITY_DISPLAY_STYLE_UINT16);
  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT16)((9U)), (UNITY_INT)(UNITY_UINT16)((original_array[2])), (
 ((void *)0)
 ), (UNITY_UINT)(217), UNITY_DISPLAY_STYLE_UINT16);
  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT16)((12U)), (UNITY_INT)(UNITY_UINT16)((original_array[3])), (
 ((void *)0)
 ), (UNITY_UINT)(218), UNITY_DISPLAY_STYLE_UINT16);
  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT16)((15U)), (UNITY_INT)(UNITY_UINT16)((original_array[4])), (
 ((void *)0)
 ), (UNITY_UINT)(219), UNITY_DISPLAY_STYLE_UINT16);
  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((45U)), (UNITY_INT)(UNITY_UINT32)((result)), (
 ((void *)0)
 ), (UNITY_UINT)(220), UNITY_DISPLAY_STYLE_UINT32);
}

void test_AnalyzeArray_u32_sum_accumulation_10_elements(void)
{
  uint16_t array[10] = {1U, 2U, 3U, 4U, 5U, 6U, 7U, 8U, 9U, 10U};
  uint16_t expected[10] = {1U, 2U, 3U, 4U, 5U, 6U, 7U, 8U, 9U, 10U};
  uint32_t expected_sum = 55U;
  uint32_t result;

  MyLib_ComputeAdjustedValue_u32_CMockExpectAndReturn(236, expected_sum,
 ((void *)0)
 , 0U);

  result = MyLib_AnalyzeArray_u32(array, 10U, 1U);

  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((expected_sum)), (UNITY_INT)(UNITY_UINT32)((result)), (
 ((void *)0)
 ), (UNITY_UINT)(240), UNITY_DISPLAY_STYLE_UINT32);
  UnityAssertEqualIntArray(( const void*)((expected)), ( const void*)((array)), (UNITY_UINT32)((10U)), (
 ((void *)0)
 ), (UNITY_UINT)(241), UNITY_DISPLAY_STYLE_UINT16, UNITY_ARRAY_TO_ARRAY);
}

void test_AnalyzeArray_u32_large_array_factor_5(void)
{
  uint16_t array[5] = {1U, 2U, 3U, 4U, 5U};
  uint16_t expected[5] = {5U, 10U, 15U, 20U, 25U};
  uint32_t expected_sum = 75U;
  uint32_t result;

  MyLib_ComputeAdjustedValue_u32_CMockExpectAndReturn(258, expected_sum,
 ((void *)0)
 , 0U);

  result = MyLib_AnalyzeArray_u32(array, 5U, 5U);

  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((expected_sum)), (UNITY_INT)(UNITY_UINT32)((result)), (
 ((void *)0)
 ), (UNITY_UINT)(262), UNITY_DISPLAY_STYLE_UINT32);
  UnityAssertEqualIntArray(( const void*)((expected)), ( const void*)((array)), (UNITY_UINT32)((5U)), (
 ((void *)0)
 ), (UNITY_UINT)(263), UNITY_DISPLAY_STYLE_UINT16, UNITY_ARRAY_TO_ARRAY);
}

void test_AnalyzeArray_u32_mock_function_called_correct_params(void)
{
  uint16_t array[3] = {5U, 5U, 5U};
  uint32_t result;
  uint32_t expected_sum = 30U;

  MyLib_ComputeAdjustedValue_u32_CMockExpectAndReturn(280, expected_sum,
 ((void *)0)
 , 100U);

  result = MyLib_AnalyzeArray_u32(array, 3U, 2U);

  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((expected_sum)), (UNITY_INT)(UNITY_UINT32)((result)), (
 ((void *)0)
 ), (UNITY_UINT)(284), UNITY_DISPLAY_STYLE_UINT32);
}

void test_AnalyzeArray_u32_mock_return_value_unused(void)
{
  uint16_t array[2] = {10U, 20U};
  uint32_t result;

  MyLib_ComputeAdjustedValue_u32_CMockExpectAndReturn(299, 60U,
 ((void *)0)
 , 999U);

  result = MyLib_AnalyzeArray_u32(array, 2U, 2U);

  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((60U)), (UNITY_INT)(UNITY_UINT32)((result)), (
 ((void *)0)
 ), (UNITY_UINT)(303), UNITY_DISPLAY_STYLE_UINT32);
}

void test_AnalyzeArray_u32_all_zeros_with_factor(void)
{
  uint16_t array[5] = {0U, 0U, 0U, 0U, 0U};
  uint16_t expected[5] = {0U, 0U, 0U, 0U, 0U};
  uint32_t result;

  MyLib_ComputeAdjustedValue_u32_CMockExpectAndReturn(318, 0U,
 ((void *)0)
 , 0U);

  result = MyLib_AnalyzeArray_u32(array, 5U, 100U);

  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((0U)), (UNITY_INT)(UNITY_UINT32)((result)), (
 ((void *)0)
 ), (UNITY_UINT)(322), UNITY_DISPLAY_STYLE_UINT32);
  UnityAssertEqualIntArray(( const void*)((expected)), ( const void*)((array)), (UNITY_UINT32)((5U)), (
 ((void *)0)
 ), (UNITY_UINT)(323), UNITY_DISPLAY_STYLE_UINT16, UNITY_ARRAY_TO_ARRAY);
}