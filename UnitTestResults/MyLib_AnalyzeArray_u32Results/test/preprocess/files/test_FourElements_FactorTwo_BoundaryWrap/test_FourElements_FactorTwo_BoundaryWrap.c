// CEEDLING NOTICE: This generated file only to be consumed for test runner creation

#include "mock_MyLib.h"
#include "utExecutionAndResults/utUnderTest/build/vendor/unity/src/unity.h"
#include "utExecutionAndResults/utUnderTest/src/MyLib_AnalyzeArray_u32.h"

void setUp(void) {
  g_counter_u32 = 0U;
  g_record.id_u16 = 0U;
  g_record.value_u32 = 0U;
  g_systemReady_b = 0
}

void tearDown(void) {
}

void test_FourElements_FactorTwo_BoundaryWrap(void) {
  uint16_t array[4] = {0U, 1U, 32767U, 32768U};
  uint32_t result;
  uint16_t expected_0 = (uint16_t)(0U * 2U);
  uint16_t expected_1 = (uint16_t)(1U * 2U);
  uint16_t expected_2 = (uint16_t)(32767U * 2U);
  uint16_t expected_3 = (uint16_t)(32768U * 2U);
  uint32_t expected_sum = (uint32_t)expected_0 + (uint32_t)expected_1 + (uint32_t)expected_2 + (uint32_t)expected_3;

  MyLib_ComputeAdjustedValue_u32_CMockExpectAndReturn(30, expected_sum, ((void *)0), 0U);

  result = MyLib_AnalyzeArray_u32(array, 4U, 2U);

  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((expected_sum)), (UNITY_INT)(UNITY_UINT32)((result)), (((void *)0)), (UNITY_UINT)(34), UNITY_DISPLAY_STYLE_UINT32);
  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT16)((expected_0)), (UNITY_INT)(UNITY_UINT16)((array[0])), (((void *)0)), (UNITY_UINT)(35), UNITY_DISPLAY_STYLE_UINT16);
  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT16)((expected_1)), (UNITY_INT)(UNITY_UINT16)((array[1])), (((void *)0)), (UNITY_UINT)(36), UNITY_DISPLAY_STYLE_UINT16);
  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT16)((expected_2)), (UNITY_INT)(UNITY_UINT16)((array[2])), (((void *)0)), (UNITY_UINT)(37), UNITY_DISPLAY_STYLE_UINT16);
  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT16)((expected_3)), (UNITY_INT)(UNITY_UINT16)((array[3])), (((void *)0)), (UNITY_UINT)(38), UNITY_DISPLAY_STYLE_UINT16);
}