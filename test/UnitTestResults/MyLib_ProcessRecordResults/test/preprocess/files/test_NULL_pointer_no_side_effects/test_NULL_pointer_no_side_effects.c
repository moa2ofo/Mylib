// CEEDLING NOTICE: This generated file only to be consumed for test runner creation

#include "mock_MyLib.h"
#include "utExecutionAndResults/utUnderTest/build/vendor/unity/src/unity.h"
#include "utExecutionAndResults/utUnderTest/src/MyLib_ProcessRecord.h"

void setUp(void) {
}

void tearDown(void) {
}

void test_NULL_pointer_no_side_effects(void) {
  uint32_t initial_counter = g_counter_u32;

  MyLib_ProcessRecord(((void *)0), 5U);

  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((initial_counter)), (UNITY_INT)(UNITY_UINT32)((g_counter_u32)), (((void *)0)), (UNITY_UINT)(16), UNITY_DISPLAY_STYLE_UINT32);
}