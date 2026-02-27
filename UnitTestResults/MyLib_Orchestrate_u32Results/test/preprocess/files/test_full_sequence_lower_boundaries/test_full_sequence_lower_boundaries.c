// CEEDLING NOTICE: This generated file only to be consumed for test runner creation

#include "utExecutionAndResults/utUnderTest/src/MyLib_Orchestrate_u32.h"
#include "utExecutionAndResults/utUnderTest/build/vendor/unity/src/unity.h"
#include "mock_MyLib.h"

static uint32_t mock_InternalHelper_result;
static uint32_t mock_InternalHelper_call_count;
static uint32_t mock_InternalHelper_last_x;
static uint16_t mock_InternalHelper_last_y;

static uint32_t InternalHelper_u32_MockCallback(uint32_t x_u32, uint16_t y_u16, int call_count)
{
  mock_InternalHelper_call_count++;
  mock_InternalHelper_last_x = x_u32;
  mock_InternalHelper_last_y = y_u16;
  return mock_InternalHelper_result;
}

static const MyLib_record_t *captured_record_ptr;
static uint8_t captured_multiplier;
static uint32_t MyLib_ProcessRecord_call_count;

static void MyLib_ProcessRecord_MockCallback(const MyLib_record_t *rec_pc, uint8_t multiplier_u8, int call_count)
{
  MyLib_ProcessRecord_call_count++;
  captured_record_ptr = rec_pc;
  captured_multiplier = multiplier_u8;
}

void setUp(void)
{
  mock_InternalHelper_result = 0;
  mock_InternalHelper_call_count = 0;
  mock_InternalHelper_last_x = 0;
  mock_InternalHelper_last_y = 0;
  captured_record_ptr =
                       ((void *)0)

  captured_multiplier = 0;
  MyLib_ProcessRecord_call_count = 0;
  g_counter_u32 = 0;
}

void tearDown(void)
{
}

void test_full_sequence_lower_boundaries(void)
{
  g_counter_u32 = 0;
  mock_InternalHelper_result = 100;

  InternalHelper_u32_CMockStubWithCallback(InternalHelper_u32_MockCallback);
  MyLib_ProcessRecord_CMockStubWithCallback(MyLib_ProcessRecord_MockCallback);

  uint32_t result = MyLib_Orchestrate_u32(0,
                                            ((void *)0)
                                                );

  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((1)), (UNITY_INT)(UNITY_UINT32)((mock_InternalHelper_call_count)), (
 ((void *)0)
 ), (UNITY_UINT)(52), UNITY_DISPLAY_STYLE_UINT32);
  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((0)), (UNITY_INT)(UNITY_UINT32)((mock_InternalHelper_last_x)), (
 ((void *)0)
 ), (UNITY_UINT)(53), UNITY_DISPLAY_STYLE_UINT32);
  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT16)((0)), (UNITY_INT)(UNITY_UINT16)((mock_InternalHelper_last_y)), (
 ((void *)0)
 ), (UNITY_UINT)(54), UNITY_DISPLAY_STYLE_UINT16);
  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((1)), (UNITY_INT)(UNITY_UINT32)((MyLib_ProcessRecord_call_count)), (
 ((void *)0)
 ), (UNITY_UINT)(55), UNITY_DISPLAY_STYLE_UINT32);
  do { if ((((captured_record_ptr)) !=
 ((void *)0)
 ))
{ } else { UnityFail( (((" Expected Non-NULL"))), (UNITY_UINT)(((56)))); } } while (0);
  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT16)((100)), (UNITY_INT)(UNITY_UINT16)((captured_record_ptr->id_u16)), (
 ((void *)0)
 ), (UNITY_UINT)(57), UNITY_DISPLAY_STYLE_UINT16);
  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((50)), (UNITY_INT)(UNITY_UINT32)((captured_record_ptr->value_u32)), (
 ((void *)0)
 ), (UNITY_UINT)(58), UNITY_DISPLAY_STYLE_UINT32);
  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )(((5U))), (UNITY_INT)(UNITY_UINT8 )((captured_multiplier)), (
 ((void *)0)
 ), (UNITY_UINT)(59), UNITY_DISPLAY_STYLE_UINT8);
  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((100)), (UNITY_INT)(UNITY_UINT32)((result)), (
 ((void *)0)
 ), (UNITY_UINT)(60), UNITY_DISPLAY_STYLE_UINT32);
}