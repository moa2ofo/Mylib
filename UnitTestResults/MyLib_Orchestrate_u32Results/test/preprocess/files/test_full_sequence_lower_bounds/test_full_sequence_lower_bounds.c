// CEEDLING NOTICE: This generated file only to be consumed for test runner creation

#include "utExecutionAndResults/utUnderTest/src/MyLib_Orchestrate_u32.h"
#include "utExecutionAndResults/utUnderTest/build/vendor/unity/src/unity.h"
#include "mock_MyLib.h"

static uint32_t InternalHelper_u32_fake_retval;

static uint32_t InternalHelper_u32_Callback(uint32_t x_u32, uint16_t y_u16, int call_count)
{
  (void)call_count;
  (void)x_u32;
  (void)y_u16;
  return InternalHelper_u32_fake_retval;
}

static MyLib_record_t captured_record;
static uint8_t captured_multiplier;
static int MyLib_ProcessRecord_call_count;

static void MyLib_ProcessRecord_Callback(const MyLib_record_t *rec_pc, uint8_t multiplier_u8, int call_count)
{
  (void)call_count;
  MyLib_ProcessRecord_call_count++;
  captured_record.id_u16 = rec_pc->id_u16;
  captured_record.value_u32 = rec_pc->value_u32;
  captured_multiplier = multiplier_u8;
}

void setUp(void)
{
  g_counter_u32 = 0;
  InternalHelper_u32_fake_retval = 0;
  captured_record.id_u16 = 0;
  captured_record.value_u32 = 0;
  captured_multiplier = 0;
  MyLib_ProcessRecord_call_count = 0;
}

void tearDown(void)
{
}

void test_full_sequence_lower_bounds(void)
{
  g_counter_u32 = 0;
  InternalHelper_u32_fake_retval = 0;

  InternalHelper_u32_CMockExpectAndReturn(44, 0, 0, 0);
  MyLib_ProcessRecord_Stub(MyLib_ProcessRecord_Callback);

  uint32_t result = MyLib_Orchestrate_u32(0,
                                            ((void *)0)
                                                );

  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((0)), (UNITY_INT)(UNITY_UINT32)((result)), (
 ((void *)0)
 ), (UNITY_UINT)(49), UNITY_DISPLAY_STYLE_UINT32);
  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT16)((0)), (UNITY_INT)(UNITY_UINT16)((captured_record.id_u16)), (
 ((void *)0)
 ), (UNITY_UINT)(50), UNITY_DISPLAY_STYLE_UINT16);
  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((0)), (UNITY_INT)(UNITY_UINT32)((captured_record.value_u32)), (
 ((void *)0)
 ), (UNITY_UINT)(51), UNITY_DISPLAY_STYLE_UINT32);
  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )(((5U))), (UNITY_INT)(UNITY_UINT8 )((captured_multiplier)), (
 ((void *)0)
 ), (UNITY_UINT)(52), UNITY_DISPLAY_STYLE_UINT8);
}