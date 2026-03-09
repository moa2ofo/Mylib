// CEEDLING NOTICE: This generated file only to be consumed for test runner creation

#include "utExecutionAndResults/utUnderTest/src/MyLib_RunStateMachine_u8.h"
#include "utExecutionAndResults/utUnderTest/build/vendor/unity/src/unity.h"
#include "mock_MyLib.h"

void setUp(void)
{
  g_counter_u32 = 0U;
}

void tearDown(void)
{
}

void test_State0_Init_ValidRecPtr_Return0_StateTransitionsTo1(void)
{
  MyLib_record_t rec = {.id_u16 = 10U, .value_u32 = 100U};
  MyLib_record_t expected_last_record = {.id_u16 = 10U, .value_u32 = 100U};
  uint8_t result;

  MyLib_UpdateGlobalRecord_CMockExpect(19,
 ((void *)0)
 , &rec);
  MyLib_UpdateGlobalRecord_CMockIgnoreArg_dest_p(20);

  result = MyLib_RunStateMachine_u8(&rec, 0U,
                                             ((void *)0)
                                                 );

  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((0U)), (UNITY_INT)(UNITY_UINT8 )((result)), (
 ((void *)0)
 ), (UNITY_UINT)(24), UNITY_DISPLAY_STYLE_UINT8);
}