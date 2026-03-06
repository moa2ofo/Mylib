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

void test_State0_RejectionThenValid_FirstReturns1_SecondReturns0_TransitionsTo1(void)
{
  MyLib_record_t input_rec = {.id_u16 = 50U, .value_u32 = 750U};
  uint8_t result1, result2;

  result1 = MyLib_RunStateMachine_u8(
                                    ((void *)0)
                                        , 0U,
                                              ((void *)0)
                                                  );

  MyLib_UpdateGlobalRecord_CMockExpect(26,
 ((void *)0)
 , &input_rec);
  MyLib_UpdateGlobalRecord_CMockIgnoreArg_dest_p(27);
  result2 = MyLib_RunStateMachine_u8(&input_rec, 0U,
                                                    ((void *)0)
                                                        );

  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((1U)), (UNITY_INT)(UNITY_UINT8 )((result1)), (
 ((void *)0)
 ), (UNITY_UINT)(30), UNITY_DISPLAY_STYLE_UINT8);
  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((0U)), (UNITY_INT)(UNITY_UINT8 )((MyLib_RunStateMachine_u8_GetState())), (
 ((void *)0)
 ), (UNITY_UINT)(31), UNITY_DISPLAY_STYLE_UINT8);
  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((0U)), (UNITY_INT)(UNITY_UINT8 )((result2)), (
 ((void *)0)
 ), (UNITY_UINT)(32), UNITY_DISPLAY_STYLE_UINT8);
  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((1U)), (UNITY_INT)(UNITY_UINT8 )((MyLib_RunStateMachine_u8_GetState())), (
 ((void *)0)
 ), (UNITY_UINT)(33), UNITY_DISPLAY_STYLE_UINT8);
}