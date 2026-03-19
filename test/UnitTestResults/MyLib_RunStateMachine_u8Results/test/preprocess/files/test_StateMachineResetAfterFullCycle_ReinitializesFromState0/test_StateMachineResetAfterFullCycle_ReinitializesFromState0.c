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

void test_StateMachineResetAfterFullCycle_ReinitializesFromState0(void)
{
  MyLib_record_t input_rec1 = {10U, 100U};
  MyLib_record_t input_rec2 = {20U, 200U};
  uint8_t result;

  MyLib_UpdateGlobalRecord_CMockExpect(16,
 ((void *)0)
 , &input_rec1);
  MyLib_UpdateGlobalRecord_CMockIgnoreArg_dest_p(17);
  result = MyLib_RunStateMachine_u8(&input_rec1, 10U,
                                                     ((void *)0)
                                                         );
  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((0U)), (UNITY_INT)(UNITY_UINT8 )((result)), (
 ((void *)0)
 ), (UNITY_UINT)(19), UNITY_DISPLAY_STYLE_UINT8);

  MyLib_ProcessRecord_CMockExpect(21,
 ((void *)0)
 , (5U));
  MyLib_ProcessRecord_CMockIgnoreArg_rec_pc(22);
  MyLib_ComputeAdjustedValue_u32_CMockExpectAndReturn(23, 0U,
 ((void *)0)
 , 150U);
  MyLib_ComputeAdjustedValue_u32_CMockIgnoreArg_base_u32(24);
  result = MyLib_RunStateMachine_u8(
                                   ((void *)0)
                                       , 10U,
                                              ((void *)0)
                                                  );
  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((0U)), (UNITY_INT)(UNITY_UINT8 )((result)), (
 ((void *)0)
 ), (UNITY_UINT)(26), UNITY_DISPLAY_STYLE_UINT8);

  MyLib_UpdateCounter_u8_CMockExpectAndReturn(28, 160U, 0U);
  result = MyLib_RunStateMachine_u8(
                                   ((void *)0)
                                       , 10U,
                                              ((void *)0)
                                                  );
  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((0U)), (UNITY_INT)(UNITY_UINT8 )((result)), (
 ((void *)0)
 ), (UNITY_UINT)(30), UNITY_DISPLAY_STYLE_UINT8);

  MyLib_UpdateGlobalRecord_CMockExpect(32,
 ((void *)0)
 , &input_rec2);
  MyLib_UpdateGlobalRecord_CMockIgnoreArg_dest_p(33);
  result = MyLib_RunStateMachine_u8(&input_rec2, 20U,
                                                     ((void *)0)
                                                         );
  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((0U)), (UNITY_INT)(UNITY_UINT8 )((result)), (
 ((void *)0)
 ), (UNITY_UINT)(35), UNITY_DISPLAY_STYLE_UINT8);
}