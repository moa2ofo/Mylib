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

void test_RecoveryFromInvalidState_ThenValidInit_VerifySequence(void)
{
  MyLib_record_t input_rec = {.id_u16 = 77U, .value_u32 = 888U};
  uint8_t result1, result2;

  MyLib_RunStateMachine_u8_SetState(10U);
  MyLib_RunStateMachine_u8_SetLastAdjusted(5555U);

  result1 = MyLib_RunStateMachine_u8(
                                    ((void *)0)
                                        , 0U,
                                              ((void *)0)
                                                  );

  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((3U)), (UNITY_INT)(UNITY_UINT8 )((result1)), (
 ((void *)0)
 ), (UNITY_UINT)(29), UNITY_DISPLAY_STYLE_UINT8);
  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((0U)), (UNITY_INT)(UNITY_UINT8 )((MyLib_RunStateMachine_u8_GetState())), (
 ((void *)0)
 ), (UNITY_UINT)(30), UNITY_DISPLAY_STYLE_UINT8);
  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((0U)), (UNITY_INT)(UNITY_UINT32)((MyLib_RunStateMachine_u8_GetLastAdjusted())), (
 ((void *)0)
 ), (UNITY_UINT)(31), UNITY_DISPLAY_STYLE_UINT32);

  MyLib_UpdateGlobalRecord_CMockExpect(33,
 ((void *)0)
 , &input_rec);
  MyLib_UpdateGlobalRecord_CMockIgnoreArg_dest_p(34);
  result2 = MyLib_RunStateMachine_u8(&input_rec, 0U,
                                                    ((void *)0)
                                                        );

  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((0U)), (UNITY_INT)(UNITY_UINT8 )((result2)), (
 ((void *)0)
 ), (UNITY_UINT)(37), UNITY_DISPLAY_STYLE_UINT8);
  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((1U)), (UNITY_INT)(UNITY_UINT8 )((MyLib_RunStateMachine_u8_GetState())), (
 ((void *)0)
 ), (UNITY_UINT)(38), UNITY_DISPLAY_STYLE_UINT8);
}