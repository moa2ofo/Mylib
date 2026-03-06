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

void test_State1_ValidDelta_Returns0_StateTransitionsTo2(void)
{
  MyLib_record_t input_rec = {.id_u16 = 20U, .value_u32 = 800U};
  uint16_t delta = 50U;
  uint8_t result;

  MyLib_RunStateMachine_u8_SetState(1U);

  MyLib_ProcessRecord_CMockExpect(27,
 ((void *)0)
 , (5U));
  MyLib_ProcessRecord_CMockIgnoreArg_rec_pc(28);

  MyLib_ComputeAdjustedValue_u32_CMockExpectAndReturn(30, 0U, &delta, 350U);
  MyLib_ComputeAdjustedValue_u32_CMockIgnoreArg_base_u32(31);

  result = MyLib_RunStateMachine_u8(&input_rec, 0U, &delta);

  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((0U)), (UNITY_INT)(UNITY_UINT8 )((result)), (
 ((void *)0)
 ), (UNITY_UINT)(35), UNITY_DISPLAY_STYLE_UINT8);
  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((2U)), (UNITY_INT)(UNITY_UINT8 )((MyLib_RunStateMachine_u8_GetState())), (
 ((void *)0)
 ), (UNITY_UINT)(36), UNITY_DISPLAY_STYLE_UINT8);
  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((350U)), (UNITY_INT)(UNITY_UINT32)((MyLib_RunStateMachine_u8_GetLastAdjusted())), (
 ((void *)0)
 ), (UNITY_UINT)(37), UNITY_DISPLAY_STYLE_UINT32);
}