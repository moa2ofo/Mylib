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

void test_State1_RecordValueMaxDeltaMax_VerifyAdjustedComputed(void)
{
  MyLib_record_t last_rec = {
                            (65535)
                                      ,
                                        (4294967295U)
                                                  };
  uint16_t delta =
                  (65535)

  uint32_t computed = 12345U;
  uint8_t result;

  MyLib_RunStateMachine_u8_SetState_u8(1U);
  MyLib_RunStateMachine_u8_SetLastRecord(&last_rec);

  MyLib_ProcessRecord_CMockExpect(31,
 ((void *)0)
 , (5U));
  MyLib_ProcessRecord_CMockIgnoreArg_rec_pc(32);

  MyLib_ComputeAdjustedValue_u32_CMockExpectAndReturn(34,
 (4294967295U)
 , &delta, computed);

  result = MyLib_RunStateMachine_u8(
                                   ((void *)0)
                                       , 0U, &delta);

  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((0U)), (UNITY_INT)(UNITY_UINT8 )((result)), (
 ((void *)0)
 ), (UNITY_UINT)(38), UNITY_DISPLAY_STYLE_UINT8);
  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((computed)), (UNITY_INT)(UNITY_UINT32)((MyLib_RunStateMachine_u8_GetLastAdjusted_u32())), (
 ((void *)0)
 ), (UNITY_UINT)(39), UNITY_DISPLAY_STYLE_UINT32);
}