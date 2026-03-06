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

void test_599Elements_FactorOne_AllOnes(void) {
  uint16_t array[599];
  uint32_t result;
  size_t i;

  for(i = 0U; i < 599U; i++) {
    array[i] = 1U;
  }

  MyLib_ComputeAdjustedValue_u32_CMockExpectAndReturn(30, 599U, ((void *)0), 0U);

  result = MyLib_AnalyzeArray_u32(array, 599U, 1U);

  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((599U)), (UNITY_INT)(UNITY_UINT32)((result)), (((void *)0)), (UNITY_UINT)(34), UNITY_DISPLAY_STYLE_UINT32);
  for(i = 0U; i < 599U; i++) {
    UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT16)((1U)), (UNITY_INT)(UNITY_UINT16)((array[i])), (((void *)0)), (UNITY_UINT)(36), UNITY_DISPLAY_STYLE_UINT16);
  }
}