// CEEDLING NOTICE: This generated file only to be consumed for test runner creation

#include "utExecutionAndResults/utUnderTest/src/MyLib_RunStateMachine_u8.h"
#include "utExecutionAndResults/utUnderTest/build/vendor/unity/src/unity.h"
#include "mock_MyLib.h"

void setUp(void)
{
  g_counter_u32 = 0U;
  g_record.id_u16 = 0U;
  g_record.value_u32 = 0U;
  g_systemReady_b =
                   

  MyLib_RunStateMachine_u8_SetState_u8(0U);
  MyLib_RunStateMachine_u8_SetLastAdjusted_u32(0U);
}

void tearDown(void)
{
}

void test_State2_MidRangeValue_Returns0_StateTransitionsTo0(void)
{
  uint8_t result;

  MyLib_RunStateMachine_u8_SetState_u8(2U);
  MyLib_RunStateMachine_u8_SetLastAdjusted_u32(1000U);

  MyLib_UpdateCounter_u8_CMockExpectAndReturn(26, 2000U, 0U);

  result = MyLib_RunStateMachine_u8(
                                   ((void *)0)
                                       , 1000U,
                                                ((void *)0)
                                                    );

  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((0U)), (UNITY_INT)(UNITY_UINT8 )((result)), (
 ((void *)0)
 ), (UNITY_UINT)(30), UNITY_DISPLAY_STYLE_UINT8);
  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((0U)), (UNITY_INT)(UNITY_UINT8 )((MyLib_RunStateMachine_u8_GetState_u8())), (
 ((void *)0)
 ), (UNITY_UINT)(31), UNITY_DISPLAY_STYLE_UINT8);
}