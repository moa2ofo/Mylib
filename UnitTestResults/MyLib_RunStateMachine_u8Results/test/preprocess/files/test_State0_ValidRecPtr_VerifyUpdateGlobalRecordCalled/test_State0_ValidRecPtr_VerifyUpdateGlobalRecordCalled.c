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

void test_State0_ValidRecPtr_VerifyUpdateGlobalRecordCalled(void)
{
  MyLib_record_t input_rec = {99U, 88U};
  uint8_t result;

  MyLib_RunStateMachine_u8_SetState_u8(0U);

  MyLib_UpdateGlobalRecord_CMockExpect(28,
 ((void *)0)
 , &input_rec);
  MyLib_UpdateGlobalRecord_CMockIgnoreArg_dest_p(29);

  result = MyLib_RunStateMachine_u8(&input_rec, 0U,
                                                   ((void *)0)
                                                       );

  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((0U)), (UNITY_INT)(UNITY_UINT8 )((result)), (
 ((void *)0)
 ), (UNITY_UINT)(33), UNITY_DISPLAY_STYLE_UINT8);
}