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

void test_State2_WrapBoundary_ReturnFromUpdateCounter_StateTransitionsTo0(void)
{
  uint8_t result;
  uint32_t add_value =
                      (4294967295U)

  uint32_t adjusted_value = 1U;
  uint32_t expected_wrapped = 0U;

  MyLib_RunStateMachine_u8_SetState_u8(2U);
  MyLib_RunStateMachine_u8_SetLastAdjusted_u32(adjusted_value);

  MyLib_UpdateCounter_u8_CMockExpectAndReturn(31, expected_wrapped, 0U);

  result = MyLib_RunStateMachine_u8(
                                   ((void *)0)
                                       , add_value,
                                                    ((void *)0)
                                                        );

  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((0U)), (UNITY_INT)(UNITY_UINT8 )((result)), (
 ((void *)0)
 ), (UNITY_UINT)(35), UNITY_DISPLAY_STYLE_UINT8);
  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((0U)), (UNITY_INT)(UNITY_UINT8 )((MyLib_RunStateMachine_u8_GetState_u8())), (
 ((void *)0)
 ), (UNITY_UINT)(36), UNITY_DISPLAY_STYLE_UINT8);
}