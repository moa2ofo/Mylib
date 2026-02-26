// CEEDLING NOTICE: This generated file only to be consumed for test runner creation

#include "utExecutionAndResults/utUnderTest/src/InternalHelper_u32.h"
#include "utExecutionAndResults/utUnderTest/build/vendor/unity/src/unity.h"

void setUp(void)
{
  g_counter_u32 = 0U;
  g_record.id_u16 = 0U;
  g_record.value_u32 = 0U;
  g_systemReady_b =
                   0
}

void tearDown(void)
{
}

void test_InternalHelper_u32__alternating_values_consistency(void)
{
  uint32_t result1 = InternalHelper_u32(10U, 2U);
  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((12U)), (UNITY_INT)(UNITY_UINT32)((result1)), (
 ((void *)0)
 ), (UNITY_UINT)(20), UNITY_DISPLAY_STYLE_UINT32);

  uint32_t result2 = InternalHelper_u32(20U, 3U);
  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((26U)), (UNITY_INT)(UNITY_UINT32)((result2)), (
 ((void *)0)
 ), (UNITY_UINT)(24), UNITY_DISPLAY_STYLE_UINT32);

  uint32_t result3 = InternalHelper_u32(30U, 1U);
  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((30U)), (UNITY_INT)(UNITY_UINT32)((result3)), (
 ((void *)0)
 ), (UNITY_UINT)(28), UNITY_DISPLAY_STYLE_UINT32);
}