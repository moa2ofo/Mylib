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

void test_NullPointer_NonZeroLen_NonZeroFactor(void) {
  uint32_t result;

  result = MyLib_AnalyzeArray_u32(((void *)0), 1U, 1U);

  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((0U)), (UNITY_INT)(UNITY_UINT32)((result)), (((void *)0)), (UNITY_UINT)(26), UNITY_DISPLAY_STYLE_UINT32);
}