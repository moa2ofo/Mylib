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

void test_State2_TwoConsecutiveCalls_BothTransitionTo0(void)
{
  MyLib_record_t rec1 = {.id_u16 = 5U, .value_u32 = 500U};
  MyLib_record_t rec2 = {.id_u16 = 6U, .value_u32 = 600U};
  uint8_t result;

  MyLib_UpdateGlobalRecord_CMockExpect(19,
 ((void *)0)
 , &rec1);
  MyLib_UpdateGlobalRecord_CMockIgnoreArg_dest_p(20);
  result = MyLib_RunStateMachine_u8(&rec1, 0U,
                                              ((void *)0)
                                                  );

  MyLib_ProcessRecord_CMockExpect(23,
 ((void *)0)
 , (5U));
  MyLib_ProcessRecord_CMockIgnoreArg_rec_pc(24);
  MyLib_ComputeAdjustedValue_u32_CMockExpectAndReturn(25, 0U,
 ((void *)0)
 , 250U);
  MyLib_ComputeAdjustedValue_u32_CMockIgnoreArg_base_u32(26);
  result = MyLib_RunStateMachine_u8(
                                   ((void *)0)
                                       , 0U,
                                             ((void *)0)
                                                 );

  MyLib_UpdateCounter_u8_CMockExpectAndReturn(29, 300U, 0U);
  result = MyLib_RunStateMachine_u8(
                                   ((void *)0)
                                       , 50U,
                                              ((void *)0)
                                                  );
  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((0U)), (UNITY_INT)(UNITY_UINT8 )((result)), (
 ((void *)0)
 ), (UNITY_UINT)(31), UNITY_DISPLAY_STYLE_UINT8);

  MyLib_UpdateGlobalRecord_CMockExpect(33,
 ((void *)0)
 , &rec2);
  MyLib_UpdateGlobalRecord_CMockIgnoreArg_dest_p(34);
  result = MyLib_RunStateMachine_u8(&rec2, 0U,
                                              ((void *)0)
                                                  );

  MyLib_ProcessRecord_CMockExpect(37,
 ((void *)0)
 , (5U));
  MyLib_ProcessRecord_CMockIgnoreArg_rec_pc(38);
  MyLib_ComputeAdjustedValue_u32_CMockExpectAndReturn(39, 0U,
 ((void *)0)
 , 300U);
  MyLib_ComputeAdjustedValue_u32_CMockIgnoreArg_base_u32(40);
  result = MyLib_RunStateMachine_u8(
                                   ((void *)0)
                                       , 0U,
                                             ((void *)0)
                                                 );

  MyLib_UpdateCounter_u8_CMockExpectAndReturn(43, 400U, 0U);
  result = MyLib_RunStateMachine_u8(
                                   ((void *)0)
                                       , 100U,
                                               ((void *)0)
                                                   );
  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((0U)), (UNITY_INT)(UNITY_UINT8 )((result)), (
 ((void *)0)
 ), (UNITY_UINT)(45), UNITY_DISPLAY_STYLE_UINT8);
}