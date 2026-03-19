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

void test_FullCycle_ValidInit_NullDelta_NoSaturation(void)
{
  MyLib_record_t input_rec = {10, 100};
  uint8_t result;

  MyLib_UpdateGlobalRecord_CMockExpect(19,
 ((void *)0)
 , &input_rec);
  MyLib_UpdateGlobalRecord_CMockIgnoreArg_dest_p(20);
  result = MyLib_RunStateMachine_u8(&input_rec, 5,
                                                  ((void *)0)
                                                      );
  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((0)), (UNITY_INT)(UNITY_UINT8 )((result)), (
 ((void *)0)
 ), (UNITY_UINT)(22), UNITY_DISPLAY_STYLE_UINT8);

  MyLib_ProcessRecord_CMockExpect(24,
 ((void *)0)
 , (5U));
  MyLib_ProcessRecord_CMockIgnoreArg_rec_pc(25);
  MyLib_ComputeAdjustedValue_u32_CMockExpectAndReturn(26, 0,
 ((void *)0)
 , 50);
  MyLib_ComputeAdjustedValue_u32_CMockIgnoreArg_base_u32(27);
  result = MyLib_RunStateMachine_u8(
                                   ((void *)0)
                                       , 5,
                                            ((void *)0)
                                                );
  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((0)), (UNITY_INT)(UNITY_UINT8 )((result)), (
 ((void *)0)
 ), (UNITY_UINT)(29), UNITY_DISPLAY_STYLE_UINT8);

  MyLib_UpdateCounter_u8_CMockExpectAndReturn(31, 55, 0);
  result = MyLib_RunStateMachine_u8(
                                   ((void *)0)
                                       , 5,
                                            ((void *)0)
                                                );
  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((0)), (UNITY_INT)(UNITY_UINT8 )((result)), (
 ((void *)0)
 ), (UNITY_UINT)(33), UNITY_DISPLAY_STYLE_UINT8);

  MyLib_UpdateGlobalRecord_CMockExpect(35,
 ((void *)0)
 , &input_rec);
  MyLib_UpdateGlobalRecord_CMockIgnoreArg_dest_p(36);
  result = MyLib_RunStateMachine_u8(&input_rec, 0,
                                                  ((void *)0)
                                                      );
  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((0)), (UNITY_INT)(UNITY_UINT8 )((result)), (
 ((void *)0)
 ), (UNITY_UINT)(38), UNITY_DISPLAY_STYLE_UINT8);
}