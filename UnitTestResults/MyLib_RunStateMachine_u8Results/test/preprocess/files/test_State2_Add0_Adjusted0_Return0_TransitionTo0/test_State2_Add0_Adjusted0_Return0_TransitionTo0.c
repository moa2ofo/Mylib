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

void test_State2_Add0_Adjusted0_Return0_TransitionTo0(void)
{
  MyLib_record_t input_rec = {.id_u16 = 1U, .value_u32 = 0U};
  uint8_t result;

  MyLib_UpdateGlobalRecord_CMockExpect(18,
 ((void *)0)
 , &input_rec);
  MyLib_UpdateGlobalRecord_CMockIgnoreArg_dest_p(19);
  result = MyLib_RunStateMachine_u8(&input_rec, 0U,
                                                   ((void *)0)
                                                       );

  MyLib_ProcessRecord_CMockExpect(22,
 ((void *)0)
 , (5U));
  MyLib_ProcessRecord_CMockIgnoreArg_rec_pc(23);
  MyLib_ComputeAdjustedValue_u32_CMockExpectAndReturn(24, 0U,
 ((void *)0)
 , 0U);
  MyLib_ComputeAdjustedValue_u32_CMockIgnoreArg_base_u32(25);
  result = MyLib_RunStateMachine_u8(
                                   ((void *)0)
                                       , 0U,
                                             ((void *)0)
                                                 );

  MyLib_UpdateCounter_u8_CMockExpectAndReturn(28, 0U, 0U);
  result = MyLib_RunStateMachine_u8(
                                   ((void *)0)
                                       , 0U,
                                             ((void *)0)
                                                 );
  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((0U)), (UNITY_INT)(UNITY_UINT8 )((result)), (
 ((void *)0)
 ), (UNITY_UINT)(30), UNITY_DISPLAY_STYLE_UINT8);
}