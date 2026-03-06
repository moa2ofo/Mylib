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

void test_FullCycle_UpdateReturns2_VerifySequence002_FinalState0(void)
{
  MyLib_record_t input_rec = {.id_u16 = 200U, .value_u32 = 3000U};
  uint8_t result1, result2, result3;

  MyLib_UpdateGlobalRecord_CMockExpect(24,
 ((void *)0)
 , &input_rec);
  MyLib_UpdateGlobalRecord_CMockIgnoreArg_dest_p(25);
  result1 = MyLib_RunStateMachine_u8(&input_rec, 100U,
                                                      ((void *)0)
                                                          );

  MyLib_ProcessRecord_CMockExpect(28,
 ((void *)0)
 , (5U));
  MyLib_ProcessRecord_CMockIgnoreArg_rec_pc(29);
  MyLib_ComputeAdjustedValue_u32_CMockExpectAndReturn(30, 0U,
 ((void *)0)
 , 2500U);
  MyLib_ComputeAdjustedValue_u32_CMockIgnoreArg_base_u32(31);
  result2 = MyLib_RunStateMachine_u8(&input_rec, 100U,
                                                      ((void *)0)
                                                          );

  MyLib_UpdateCounter_u8_CMockExpectAndReturn(34, 2600U, 2U);
  result3 = MyLib_RunStateMachine_u8(&input_rec, 100U,
                                                      ((void *)0)
                                                          );

  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((0U)), (UNITY_INT)(UNITY_UINT8 )((result1)), (
 ((void *)0)
 ), (UNITY_UINT)(37), UNITY_DISPLAY_STYLE_UINT8);
  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((0U)), (UNITY_INT)(UNITY_UINT8 )((result2)), (
 ((void *)0)
 ), (UNITY_UINT)(38), UNITY_DISPLAY_STYLE_UINT8);
  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((2U)), (UNITY_INT)(UNITY_UINT8 )((result3)), (
 ((void *)0)
 ), (UNITY_UINT)(39), UNITY_DISPLAY_STYLE_UINT8);
  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((0U)), (UNITY_INT)(UNITY_UINT8 )((MyLib_RunStateMachine_u8_GetState())), (
 ((void *)0)
 ), (UNITY_UINT)(40), UNITY_DISPLAY_STYLE_UINT8);
}