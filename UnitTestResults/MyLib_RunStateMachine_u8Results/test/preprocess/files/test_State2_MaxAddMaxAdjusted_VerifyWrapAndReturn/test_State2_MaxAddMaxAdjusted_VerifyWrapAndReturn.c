// CEEDLING NOTICE: This generated file only to be consumed for test runner creation

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
  MyLib_record_t zero_record = {0U, 0U};
  MyLib_RunStateMachine_u8_SetLastRecord(&zero_record);
}

void tearDown(void)
{
}

void test_State2_MaxAddMaxAdjusted_VerifyWrapAndReturn(void)
{
  uint8_t result;
  uint32_t expected_wrapped =
                             (4294967295U)
                                        - 1U;

  MyLib_RunStateMachine_u8_SetState_u8(2U);
  MyLib_RunStateMachine_u8_SetLastAdjusted_u32(
                                              (4294967295U)
                                                        );

  MyLib_UpdateCounter_u8_CMockExpectAndReturn(29, expected_wrapped, 1U);

  result = MyLib_RunStateMachine_u8(
                                   ((void *)0)
                                       ,
                                         (4294967295U)
                                                   ,
                                                     ((void *)0)
                                                         );

  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((1U)), (UNITY_INT)(UNITY_UINT8 )((result)), (
 ((void *)0)
 ), (UNITY_UINT)(33), UNITY_DISPLAY_STYLE_UINT8);
  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((0U)), (UNITY_INT)(UNITY_UINT8 )((MyLib_RunStateMachine_u8_GetState_u8())), (
 ((void *)0)
 ), (UNITY_UINT)(34), UNITY_DISPLAY_STYLE_UINT8);
}