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

void test_MyLib_ComputeAdjustedValue_u32_base_0_delta_NULL(void)
{
  uint32_t base_u32 = 0U;
  const uint16_t *delta_pc_u16 =
                                ((void *)0)

  uint32_t expected_intermediate = 0U * 1U;
  uint32_t expected_result = 42U;

  InternalHelper_u32_CMockExpectAndReturn(33, expected_intermediate, (uint16_t)(5U), expected_result);

  uint32_t result = MyLib_ComputeAdjustedValue_u32(base_u32, delta_pc_u16);

  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((expected_result)), (UNITY_INT)(UNITY_UINT32)((result)), (
 ((void *)0)
 ), (UNITY_UINT)(37), UNITY_DISPLAY_STYLE_UINT32);
}