// CEEDLING NOTICE: This generated file only to be consumed for test runner creation

#include "utExecutionAndResults/utUnderTest/src/MyLib_RunStateMachine_u8.h"
#include "utExecutionAndResults/utUnderTest/build/vendor/unity/src/unity.h"
#include "mock_MyLib.h"

void setUp(void)
{
}

void tearDown(void)
{
}

void test_State1_ValidDelta_Return0_TransitionTo2(void)
{
  MyLib_record_t input_rec = {10, 100};
  uint16_t delta = 20;
  uint8_t result;

  MyLib_UpdateGlobalRecord_CMockExpect(20,
 ((void *)0)
 , &input_rec);
  MyLib_UpdateGlobalRecord_CMockIgnoreArg_dest_p(21);
  result = MyLib_RunStateMachine_u8(&input_rec, 0,
                                                  ((void *)0)
                                                      );
  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((0)), (UNITY_INT)(UNITY_UINT8 )((result)), (
 ((void *)0)
 ), (UNITY_UINT)(23), UNITY_DISPLAY_STYLE_UINT8);

  MyLib_ProcessRecord_CMockExpect(25,
 ((void *)0)
 , (5U));
  MyLib_ProcessRecord_CMockIgnoreArg_rec_pc(26);
  MyLib_ComputeAdjustedValue_u32_CMockExpectAndReturn(27, 0, &delta, 120);
  MyLib_ComputeAdjustedValue_u32_CMockIgnoreArg_base_u32(28);

  result = MyLib_RunStateMachine_u8(
                                   ((void *)0)
                                       , 0, &delta);

  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((0)), (UNITY_INT)(UNITY_UINT8 )((result)), (
 ((void *)0)
 ), (UNITY_UINT)(32), UNITY_DISPLAY_STYLE_UINT8);
}