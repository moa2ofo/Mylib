// CEEDLING NOTICE: This generated file only to be consumed for test runner creation

#include "utExecutionAndResults/utUnderTest/src/MyLib_RunStateMachine_u8.h"
#include "utExecutionAndResults/utUnderTest/build/vendor/unity/src/unity.h"
#include "mock_MyLib.h"

void setUp(void)
{
}

void tearDown(void)
{
}

void test_State2_AddZero_AdjustedNonZero_CallsUpdateWithSum(void)
{
  MyLib_record_t input_rec = {10U, 100U};
  uint8_t result;

  MyLib_UpdateGlobalRecord_CMockExpect(15,
 ((void *)0)
 , &input_rec);
  MyLib_UpdateGlobalRecord_CMockIgnoreArg_dest_p(16);
  result = MyLib_RunStateMachine_u8(&input_rec, 0U,
                                                   ((void *)0)
                                                       );

  MyLib_ProcessRecord_CMockExpect(19,
 ((void *)0)
 , (5U));
  MyLib_ProcessRecord_CMockIgnoreArg_rec_pc(20);
  MyLib_ComputeAdjustedValue_u32_CMockExpectAndReturn(21, 0U,
 ((void *)0)
 , 75U);
  MyLib_ComputeAdjustedValue_u32_CMockIgnoreArg_base_u32(22);
  result = MyLib_RunStateMachine_u8(
                                   ((void *)0)
                                       , 0U,
                                             ((void *)0)
                                                 );

  MyLib_UpdateCounter_u8_CMockExpectAndReturn(25, 75U, 0U);

  result = MyLib_RunStateMachine_u8(
                                   ((void *)0)
                                       , 0U,
                                             ((void *)0)
                                                 );

  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((0U)), (UNITY_INT)(UNITY_UINT8 )((result)), (
 ((void *)0)
 ), (UNITY_UINT)(29), UNITY_DISPLAY_STYLE_UINT8);
}