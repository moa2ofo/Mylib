// CEEDLING NOTICE: This generated file only to be consumed for test runner creation

#include "utExecutionAndResults/utUnderTest/build/vendor/unity/src/unity.h"
#include "mock_MyLib.h"

void setUp(void)
{
}

void tearDown(void)
{
}

void test_multiplier_255_value_max_wraps(void)
{
  MyLib_record_t rec = {.id_u16 = 10U, .value_u32 =
                                                   (4294967295U)
                                                             };
  g_counter_u32 = 0U;
  uint32_t expected_acc = (uint32_t)(255ULL *
                                             (4294967295U)
                                                       );

  MyLib_ComputeAdjustedValue_u32_CMockExpectAndReturn(16, expected_acc, (const uint16_t *)&(uint8_t){255U}, 0U);
  MyLib_ComputeAdjustedValue_u32_CMockIgnoreArg_delta_pc_u16(17);

  ProcessRecord(&rec, 255U);

  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((expected_acc)), (UNITY_INT)(UNITY_UINT32)((g_counter_u32)), (
 ((void *)0)
 ), (UNITY_UINT)(21), UNITY_DISPLAY_STYLE_UINT32);
}