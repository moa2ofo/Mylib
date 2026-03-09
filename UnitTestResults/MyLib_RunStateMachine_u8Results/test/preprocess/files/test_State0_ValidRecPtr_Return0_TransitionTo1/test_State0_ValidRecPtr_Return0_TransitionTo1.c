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

void test_State0_ValidRecPtr_Return0_TransitionTo1(void)
{
  MyLib_record_t input_rec = {.id_u16 = 42U, .value_u32 = 1000U};
  uint8_t result;

  MyLib_UpdateGlobalRecord_CMockExpect(18,
 ((void *)0)
 , &input_rec);
  MyLib_UpdateGlobalRecord_CMockIgnoreArg_dest_p(19);

  result = MyLib_RunStateMachine_u8(&input_rec, 0U,
                                                   ((void *)0)
                                                       );
  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((0U)), (UNITY_INT)(UNITY_UINT8 )((result)), (
 ((void *)0)
 ), (UNITY_UINT)(22), UNITY_DISPLAY_STYLE_UINT8);
}