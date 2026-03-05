// CEEDLING NOTICE: This generated file only to be consumed for test runner creation

#include "utExecutionAndResults/utUnderTest/src/MyLib_Orchestrate_u32.h"
#include "utExecutionAndResults/utUnderTest/build/vendor/unity/src/unity.h"
#include "mock_MyLib.h"

static uint32_t stub_base_value;
static uint16_t stub_delta_value;
static int InternalHelper_call_count;

static uint32_t InternalHelper_u32_Callback(uint32_t x_u32, uint16_t y_u16, int call_count)
{
  InternalHelper_call_count = call_count;
  stub_delta_value = y_u16;
  return stub_base_value;
}

void setUp(void)
{
  stub_base_value = 0;
  stub_delta_value = 0;
  InternalHelper_call_count = 0;
  g_counter_u32 = 0;
}

void tearDown(void)
{
}

void test_start_100_delta_NULL_verify_return_and_ProcessRecord(void)
{
  uint32_t result;
  MyLib_record_t expected_rec;

  stub_base_value = 150;
  g_counter_u32 = 50;

  InternalHelper_u32_Stub(InternalHelper_u32_Callback);

  expected_rec.id_u16 = (uint16_t)(stub_base_value & 0xFFFF);
  expected_rec.value_u32 = stub_base_value / 2;

  MyLib_ProcessRecord_CMockExpect(39, &expected_rec, (5U));
  MyLib_ProcessRecord_CMockIgnoreArg_rec_pc(40);

  result = MyLib_Orchestrate_u32(100,
                                     ((void *)0)
                                         );

  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((stub_base_value + g_counter_u32)), (UNITY_INT)(UNITY_UINT32)((result)), (
 ((void *)0)
 ), (UNITY_UINT)(44), UNITY_DISPLAY_STYLE_UINT32);
  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT16)((0)), (UNITY_INT)(UNITY_UINT16)((stub_delta_value)), (
 ((void *)0)
 ), (UNITY_UINT)(45), UNITY_DISPLAY_STYLE_UINT16);
}