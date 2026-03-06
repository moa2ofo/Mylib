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

void test_SingleElement_MaxFactor_MaxValue_Overflow(void) {
  uint16_t array[1] = {65535U};
  uint32_t result;
  uint16_t expected = (uint16_t)(65535U * 65535U);

  MyLib_ComputeAdjustedValue_u32_CMockExpectAndReturn(26, (uint32_t)expected, ((void *)0), 0U);

  result = MyLib_AnalyzeArray_u32(array, 1U, 65535U);

  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)(((uint32_t)expected)), (UNITY_INT)(UNITY_UINT32)((result)), (((void *)0)), (UNITY_UINT)(30), UNITY_DISPLAY_STYLE_UINT32);
  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT16)((expected)), (UNITY_INT)(UNITY_UINT16)((array[0])), (((void *)0)), (UNITY_UINT)(31), UNITY_DISPLAY_STYLE_UINT16);
}