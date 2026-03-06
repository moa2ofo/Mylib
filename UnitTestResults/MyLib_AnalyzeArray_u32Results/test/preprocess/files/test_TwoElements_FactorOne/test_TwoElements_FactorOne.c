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

void test_TwoElements_FactorOne(void) {
  uint16_t array[2] = {10U, 20U};
  uint32_t result;

  MyLib_ComputeAdjustedValue_u32_CMockExpectAndReturn(25, 30U, ((void *)0), 0U);

  result = MyLib_AnalyzeArray_u32(array, 2U, 1U);

  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((30U)), (UNITY_INT)(UNITY_UINT32)((result)), (((void *)0)), (UNITY_UINT)(29), UNITY_DISPLAY_STYLE_UINT32);
  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT16)((10U)), (UNITY_INT)(UNITY_UINT16)((array[0])), (((void *)0)), (UNITY_UINT)(30), UNITY_DISPLAY_STYLE_UINT16);
  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT16)((20U)), (UNITY_INT)(UNITY_UINT16)((array[1])), (((void *)0)), (UNITY_UINT)(31), UNITY_DISPLAY_STYLE_UINT16);
}