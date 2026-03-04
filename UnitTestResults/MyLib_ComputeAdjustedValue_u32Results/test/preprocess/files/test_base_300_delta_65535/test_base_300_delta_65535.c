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

void test_MyLib_ComputeAdjustedValue_u32_base_300_delta_65535(void)
{
  uint32_t base_u32 = 300U;
  uint16_t delta_u16 = 65535U;
  const uint16_t *delta_pc_u16 = &delta_u16;
  uint32_t expected_intermediate = 300U * 65535U;
  uint32_t expected_result = 19660500U;

  InternalHelper_u32_CMockExpectAndReturn(34, expected_intermediate, (uint16_t)(5U), expected_result);

  uint32_t result = MyLib_ComputeAdjustedValue_u32(base_u32, delta_pc_u16);

  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((expected_result)), (UNITY_INT)(UNITY_UINT32)((result)), (
 ((void *)0)
 ), (UNITY_UINT)(38), UNITY_DISPLAY_STYLE_UINT32);
}