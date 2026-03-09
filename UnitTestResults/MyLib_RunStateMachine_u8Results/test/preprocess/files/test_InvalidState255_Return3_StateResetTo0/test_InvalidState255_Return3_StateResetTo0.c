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

void test_InvalidState255_Return3_StateResetTo0(void)
{
  MyLib_record_t rec = {.id_u16 = 6U, .value_u32 = 60U};
  uint8_t result;
  uint8_t i;

  MyLib_UpdateGlobalRecord_CMockExpect(19,
 ((void *)0)
 , &rec);
  MyLib_UpdateGlobalRecord_CMockIgnoreArg_dest_p(20);
  result = MyLib_RunStateMachine_u8(&rec, 0U,
                                             ((void *)0)
                                                 );
  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((0U)), (UNITY_INT)(UNITY_UINT8 )((result)), (
 ((void *)0)
 ), (UNITY_UINT)(22), UNITY_DISPLAY_STYLE_UINT8);

  for(i = 0U; i < 254U; i++)
{
    if(i == 0U)
{
      MyLib_ProcessRecord_CMockExpect(26,
     ((void *)0)
     , (5U));
      MyLib_ProcessRecord_CMockIgnoreArg_rec_pc(27);
      MyLib_ComputeAdjustedValue_u32_CMockExpectAndReturn(28, 60U,
     ((void *)0)
     , 70U);
      result = MyLib_RunStateMachine_u8(
                                       ((void *)0)
                                           , 0U,
                                                 ((void *)0)
                                                     );
      UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((0U)), (UNITY_INT)(UNITY_UINT8 )((result)), (
     ((void *)0)
     ), (UNITY_UINT)(30), UNITY_DISPLAY_STYLE_UINT8);
    } else if(i == 1U)
{
      MyLib_UpdateCounter_u8_CMockExpectAndReturn(32, 70U, 0U);
      result = MyLib_RunStateMachine_u8(
                                       ((void *)0)
                                           , 0U,
                                                 ((void *)0)
                                                     );
      UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((0U)), (UNITY_INT)(UNITY_UINT8 )((result)), (
     ((void *)0)
     ), (UNITY_UINT)(34), UNITY_DISPLAY_STYLE_UINT8);
    } else {
      result = MyLib_RunStateMachine_u8(
                                       ((void *)0)
                                           , 0U,
                                                 ((void *)0)
                                                     );
      UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((3U)), (UNITY_INT)(UNITY_UINT8 )((result)), (
     ((void *)0)
     ), (UNITY_UINT)(37), UNITY_DISPLAY_STYLE_UINT8);
    }
  }

  result = MyLib_RunStateMachine_u8(
                                   ((void *)0)
                                       , 0U,
                                             ((void *)0)
                                                 );
  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((1U)), (UNITY_INT)(UNITY_UINT8 )((result)), (
 ((void *)0)
 ), (UNITY_UINT)(42), UNITY_DISPLAY_STYLE_UINT8);
}