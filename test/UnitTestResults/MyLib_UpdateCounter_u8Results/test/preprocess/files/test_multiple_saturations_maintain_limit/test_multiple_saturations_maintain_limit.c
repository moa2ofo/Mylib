// CEEDLING NOTICE: This generated file only to be consumed for test runner creation

#include "mock_MyLib.h"
#include "utExecutionAndResults/utUnderTest/build/vendor/unity/src/unity.h"
#include "utExecutionAndResults/utUnderTest/src/MyLib.h"
#include "utExecutionAndResults/utUnderTest/src/MyLib_UpdateCounter_u8.h"

void setUp(void) {
}

void tearDown(void) {
}

void test_multiple_saturations_maintain_limit(void) {
  uint8_t result1;
  uint8_t result2;
  uint8_t result3;

  g_systemReady_b = 1

      g_counter_u32 = 90U;
  set_SaturationEn_b(1);
  set_CounterLimit_u32(100U);

  result1 = MyLib_UpdateCounter_u8(20U);
  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8)((2U)), (UNITY_INT)(UNITY_UINT8)((result1)), (((void *)0)), (UNITY_UINT)(24), UNITY_DISPLAY_STYLE_UINT8);
  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((100U)), (UNITY_INT)(UNITY_UINT32)((g_counter_u32)), (((void *)0)), (UNITY_UINT)(25), UNITY_DISPLAY_STYLE_UINT32);

  result2 = MyLib_UpdateCounter_u8(50U);
  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8)((2U)), (UNITY_INT)(UNITY_UINT8)((result2)), (((void *)0)), (UNITY_UINT)(28), UNITY_DISPLAY_STYLE_UINT8);
  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((100U)), (UNITY_INT)(UNITY_UINT32)((g_counter_u32)), (((void *)0)), (UNITY_UINT)(29), UNITY_DISPLAY_STYLE_UINT32);

  result3 = MyLib_UpdateCounter_u8(100U);
  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8)((2U)), (UNITY_INT)(UNITY_UINT8)((result3)), (((void *)0)), (UNITY_UINT)(32), UNITY_DISPLAY_STYLE_UINT8);
  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((100U)), (UNITY_INT)(UNITY_UINT32)((g_counter_u32)), (((void *)0)), (UNITY_UINT)(33), UNITY_DISPLAY_STYLE_UINT32);
}