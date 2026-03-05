// CEEDLING NOTICE: This generated file only to be consumed for test runner creation

#include "utExecutionAndResults/utUnderTest/src/MyLib_Orchestrate_u32.h"
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

void test_start_just_outside_upper_boundary_201_with_delta_pointing_to_100(void)
{
  uint32_t start_u32 = 201U;
  uint16_t delta_value = 100U;
  const uint16_t *delta_pc_u16 = &delta_value;
  uint32_t l_base_u32 = 510U;
  uint32_t expected_return;
  uint32_t actual_return;
  MyLib_record_t expected_record;

  g_counter_u32 = 95U;

  InternalHelper_u32_CMockExpectAndReturn(30, start_u32, delta_value, l_base_u32);

  expected_record.id_u16 = (uint16_t)(l_base_u32 & 0xFFFFU);
  expected_record.value_u32 = l_base_u32 / 2U;

  MyLib_ProcessRecord_CMockExpect(35, &expected_record, (5U));
  MyLib_ProcessRecord_CMockIgnoreArg_rec_pc(36);

  expected_return = l_base_u32 + g_counter_u32;

  actual_return = MyLib_Orchestrate_u32(start_u32, delta_pc_u16);

  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((expected_return)), (UNITY_INT)(UNITY_UINT32)((actual_return)), (
 ((void *)0)
 ), (UNITY_UINT)(42), UNITY_DISPLAY_STYLE_UINT32);
}