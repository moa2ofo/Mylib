// CEEDLING NOTICE: This generated file only to be consumed for test runner creation

#include "utExecutionAndResults/utUnderTest/build/vendor/unity/src/unity.h"
#include "mock_MyLib.h"

void setUp(void)
{
}

void tearDown(void)
{
}

void test_system_not_ready_returns_1_no_counter_change(void)
{
  uint8_t result;
  uint32_t initial_counter = 42U;

  g_systemReady_b =
                   0

  g_counter_u32 = initial_counter;

  result = UpdateCounter_u8(10U);

  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((1U)), (UNITY_INT)(UNITY_UINT8 )((result)), (
 ((void *)0)
 ), (UNITY_UINT)(20), UNITY_DISPLAY_STYLE_UINT8);
  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((initial_counter)), (UNITY_INT)(UNITY_UINT32)((g_counter_u32)), (
 ((void *)0)
 ), (UNITY_UINT)(21), UNITY_DISPLAY_STYLE_UINT32);
}