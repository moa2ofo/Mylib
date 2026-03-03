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

void test_MyLib_ComputeAdjustedValue_u32_base_600_delta_1_duplicate(void)
{
  uint32_t l_val_u32;
  uint32_t l_expected_u32;
  uint16_t l_delta_u16 = 1U;

  l_val_u32 = 600U * 1U;
  l_expected_u32 = 3000U;

  InternalHelper_u32_CMockExpectAndReturn(27, l_val_u32, (uint16_t)(5U), l_expected_u32);

  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((l_expected_u32)), (UNITY_INT)(UNITY_UINT32)((MyLib_ComputeAdjustedValue_u32(600U, &l_delta_u16))), (
 ((void *)0)
 ), (UNITY_UINT)(29), UNITY_DISPLAY_STYLE_UINT32);
}