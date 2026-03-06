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

void test_MultipleCycles_VerifyStaticVariablesPersist(void)
{
  MyLib_record_t rec1 = {1U, 10U};
  MyLib_record_t rec2 = {2U, 20U};
  uint16_t delta1 = 5U;
  uint16_t delta2 = 10U;
  uint32_t adjusted1 = 15U;
  uint32_t adjusted2 = 30U;
  uint8_t result;

  MyLib_RunStateMachine_u8_SetState_u8(0U);

  MyLib_UpdateGlobalRecord_CMockExpect(33,
 ((void *)0)
 , &rec1);
  MyLib_UpdateGlobalRecord_CMockIgnoreArg_dest_p(34);
  result = MyLib_RunStateMachine_u8(&rec1, 0U,
                                              ((void *)0)
                                                  );
  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((0U)), (UNITY_INT)(UNITY_UINT8 )((result)), (
 ((void *)0)
 ), (UNITY_UINT)(36), UNITY_DISPLAY_STYLE_UINT8);

  MyLib_ProcessRecord_CMockExpect(38,
 ((void *)0)
 , (5U));
  MyLib_ProcessRecord_CMockIgnoreArg_rec_pc(39);
  MyLib_ComputeAdjustedValue_u32_CMockExpectAndReturn(40, 10U, &delta1, adjusted1);
  result = MyLib_RunStateMachine_u8(
                                   ((void *)0)
                                       , 0U, &delta1);
  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((0U)), (UNITY_INT)(UNITY_UINT8 )((result)), (
 ((void *)0)
 ), (UNITY_UINT)(42), UNITY_DISPLAY_STYLE_UINT8);

  MyLib_UpdateCounter_u8_CMockExpectAndReturn(44, 15U, 0U);
  result = MyLib_RunStateMachine_u8(
                                   ((void *)0)
                                       , 0U,
                                             ((void *)0)
                                                 );
  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((0U)), (UNITY_INT)(UNITY_UINT8 )((result)), (
 ((void *)0)
 ), (UNITY_UINT)(46), UNITY_DISPLAY_STYLE_UINT8);

  MyLib_UpdateGlobalRecord_CMockExpect(48,
 ((void *)0)
 , &rec2);
  MyLib_UpdateGlobalRecord_CMockIgnoreArg_dest_p(49);
  result = MyLib_RunStateMachine_u8(&rec2, 0U,
                                              ((void *)0)
                                                  );
  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((0U)), (UNITY_INT)(UNITY_UINT8 )((result)), (
 ((void *)0)
 ), (UNITY_UINT)(51), UNITY_DISPLAY_STYLE_UINT8);

  MyLib_ProcessRecord_CMockExpect(53,
 ((void *)0)
 , (5U));
  MyLib_ProcessRecord_CMockIgnoreArg_rec_pc(54);
  MyLib_ComputeAdjustedValue_u32_CMockExpectAndReturn(55, 20U, &delta2, adjusted2);
  result = MyLib_RunStateMachine_u8(
                                   ((void *)0)
                                       , 0U, &delta2);
  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((0U)), (UNITY_INT)(UNITY_UINT8 )((result)), (
 ((void *)0)
 ), (UNITY_UINT)(57), UNITY_DISPLAY_STYLE_UINT8);

  MyLib_UpdateCounter_u8_CMockExpectAndReturn(59, 30U, 0U);
  result = MyLib_RunStateMachine_u8(
                                   ((void *)0)
                                       , 0U,
                                             ((void *)0)
                                                 );
  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((0U)), (UNITY_INT)(UNITY_UINT8 )((result)), (
 ((void *)0)
 ), (UNITY_UINT)(61), UNITY_DISPLAY_STYLE_UINT8);
}