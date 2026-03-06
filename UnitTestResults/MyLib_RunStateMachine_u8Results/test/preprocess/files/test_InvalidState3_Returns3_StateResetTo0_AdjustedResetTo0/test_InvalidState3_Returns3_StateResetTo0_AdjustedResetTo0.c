// CEEDLING NOTICE: This generated file only to be consumed for test runner creation

#include "utExecutionAndResults/utUnderTest/build/vendor/unity/src/unity.h"
#include "mock_MyLib.h"

void setUp(void)
{
  g_counter_u32 = 0U;
  g_record.id_u16 = 0U;
  g_record.value_u32 = 0U;
  g_systemReady_b =
                   

  MyLib_RunStateMachine_u8_SetState(0U);
  MyLib_RunStateMachine_u8_SetLastAdjusted(0U);
}

void tearDown(void)
{
}

void test_InvalidState3_Returns3_StateResetTo0_AdjustedResetTo0(void)
{
  uint8_t result;

  MyLib_RunStateMachine_u8_SetState(3U);
  MyLib_RunStateMachine_u8_SetLastAdjusted(999U);

  result = MyLib_RunStateMachine_u8(
                                   ((void *)0)
                                       , 0U,
                                             ((void *)0)
                                                 );

  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((3U)), (UNITY_INT)(UNITY_UINT8 )((result)), (
 ((void *)0)
 ), (UNITY_UINT)(28), UNITY_DISPLAY_STYLE_UINT8);
  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((0U)), (UNITY_INT)(UNITY_UINT8 )((MyLib_RunStateMachine_u8_GetState())), (
 ((void *)0)
 ), (UNITY_UINT)(29), UNITY_DISPLAY_STYLE_UINT8);
  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((0U)), (UNITY_INT)(UNITY_UINT32)((MyLib_RunStateMachine_u8_GetLastAdjusted())), (
 ((void *)0)
 ), (UNITY_UINT)(30), UNITY_DISPLAY_STYLE_UINT32);
}