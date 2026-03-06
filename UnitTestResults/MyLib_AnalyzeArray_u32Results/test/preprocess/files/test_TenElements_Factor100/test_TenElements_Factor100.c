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

void test_TenElements_Factor100(void) {
  uint16_t array[10] = {100U, 200U, 300U, 400U, 500U, 600U, 700U, 800U, 900U, 1000U};
  uint32_t result;
  uint16_t expected[10];
  uint32_t expected_sum = 0U;
  size_t i;

  for(i = 0U; i < 10U; i++) {
    expected[i] = (uint16_t)(array[i] * 100U);
    expected_sum += (uint32_t)expected[i];
  }

  MyLib_ComputeAdjustedValue_u32_CMockExpectAndReturn(33, expected_sum, ((void *)0), 0U);

  result = MyLib_AnalyzeArray_u32(array, 10U, 100U);

  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((expected_sum)), (UNITY_INT)(UNITY_UINT32)((result)), (((void *)0)), (UNITY_UINT)(37), UNITY_DISPLAY_STYLE_UINT32);
  for(i = 0U; i < 10U; i++) {
    UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT16)((expected[i])), (UNITY_INT)(UNITY_UINT16)((array[i])), (((void *)0)), (UNITY_UINT)(39), UNITY_DISPLAY_STYLE_UINT16);
  }
}