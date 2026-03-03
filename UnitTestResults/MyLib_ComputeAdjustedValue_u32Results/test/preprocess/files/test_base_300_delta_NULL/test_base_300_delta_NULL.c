// CEEDLING NOTICE: This generated file only to be consumed for test runner creation

#include "utExecutionAndResults/utUnderTest/src/MyLib_ComputeAdjustedValue_u32.h"
#include "utExecutionAndResults/utUnderTest/build/vendor/unity/src/unity.h"
#include "mock_MyLib.h"

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

void test_MyLib_ComputeAdjustedValue_u32_base_300_delta_NULL(void)
{
  uint32_t l_val_u32;
  uint32_t l_expected_u32;

  l_val_u32 = 300U * 1U;
  l_expected_u32 = 1500U;

  InternalHelper_u32_CMockExpectAndReturn(26, l_val_u32, (uint16_t)(5U), l_expected_u32);

  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((l_expected_u32)), (UNITY_INT)(UNITY_UINT32)((MyLib_ComputeAdjustedValue_u32(300U,
 ((void *)0)
 ))), (
 ((void *)0)
 ), (UNITY_UINT)(28), UNITY_DISPLAY_STYLE_UINT32);
}