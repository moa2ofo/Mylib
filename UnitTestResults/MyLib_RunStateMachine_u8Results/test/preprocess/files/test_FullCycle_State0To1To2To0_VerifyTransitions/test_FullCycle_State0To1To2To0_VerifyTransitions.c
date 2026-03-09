// CEEDLING NOTICE: This generated file only to be consumed for test runner creation

#include "utExecutionAndResults/utUnderTest/src/MyLib_RunStateMachine_u8.h"
#include "utExecutionAndResults/utUnderTest/build/vendor/unity/src/unity.h"
#include "mock_MyLib.h"

void setUp(void)
{
  g_counter_u32 = 0U;
}

void tearDown(void)
{
}

void test_FullCycle_State0To1To2To0_VerifyTransitions(void)
{
  MyLib_record_t input_rec = {.id_u16 = 15U, .value_u32 = 600U};
  uint16_t delta = 50U;
  uint8_t result;

  MyLib_UpdateGlobalRecord_CMockExpect(19,
 ((void *)0)
 , &input_rec);
  MyLib_UpdateGlobalRecord_CMockIgnoreArg_dest_p(20);
  result = MyLib_RunStateMachine_u8(&input_rec, 0U, &delta);
  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((0U)), (UNITY_INT)(UNITY_UINT8 )((result)), (
 ((void *)0)
 ), (UNITY_UINT)(22), UNITY_DISPLAY_STYLE_UINT8);

  MyLib_ProcessRecord_CMockExpect(24,
 ((void *)0)
 , (5U));
  MyLib_ProcessRecord_CMockIgnoreArg_rec_pc(25);
  MyLib_ComputeAdjustedValue_u32_CMockExpectAndReturn(26, 0U, &delta, 200U);
  MyLib_ComputeAdjustedValue_u32_CMockIgnoreArg_base_u32(27);
  result = MyLib_RunStateMachine_u8(
                                   ((void *)0)
                                       , 0U, &delta);
  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((0U)), (UNITY_INT)(UNITY_UINT8 )((result)), (
 ((void *)0)
 ), (UNITY_UINT)(29), UNITY_DISPLAY_STYLE_UINT8);

  MyLib_UpdateCounter_u8_CMockExpectAndReturn(31, 250U, 0U);
  result = MyLib_RunStateMachine_u8(
                                   ((void *)0)
                                       , 50U, &delta);
  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((0U)), (UNITY_INT)(UNITY_UINT8 )((result)), (
 ((void *)0)
 ), (UNITY_UINT)(33), UNITY_DISPLAY_STYLE_UINT8);

  MyLib_UpdateGlobalRecord_CMockExpect(35,
 ((void *)0)
 , &input_rec);
  MyLib_UpdateGlobalRecord_CMockIgnoreArg_dest_p(36);
  result = MyLib_RunStateMachine_u8(&input_rec, 0U,
                                                   ((void *)0)
                                                       );
  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((0U)), (UNITY_INT)(UNITY_UINT8 )((result)), (
 ((void *)0)
 ), (UNITY_UINT)(38), UNITY_DISPLAY_STYLE_UINT8);
}