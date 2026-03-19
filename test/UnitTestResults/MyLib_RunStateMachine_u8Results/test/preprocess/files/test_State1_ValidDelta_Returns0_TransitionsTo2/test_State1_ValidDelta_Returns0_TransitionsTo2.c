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

void test_State1_ValidDelta_Returns0_TransitionsTo2(void)
{
  MyLib_record_t input_rec = {10U, 200U};
  uint16_t delta = 50U;
  uint8_t result;

  MyLib_UpdateGlobalRecord_CMockExpect(16,
 ((void *)0)
 , &input_rec);
  MyLib_UpdateGlobalRecord_CMockIgnoreArg_dest_p(17);
  result = MyLib_RunStateMachine_u8(&input_rec, 0U, &delta);
  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((0U)), (UNITY_INT)(UNITY_UINT8 )((result)), (
 ((void *)0)
 ), (UNITY_UINT)(19), UNITY_DISPLAY_STYLE_UINT8);

  MyLib_ProcessRecord_CMockExpect(21,
 ((void *)0)
 , (5U));
  MyLib_ProcessRecord_CMockIgnoreArg_rec_pc(22);
  MyLib_ComputeAdjustedValue_u32_CMockExpectAndReturn(23, 0U, &delta, 250U);
  MyLib_ComputeAdjustedValue_u32_CMockIgnoreArg_base_u32(24);

  result = MyLib_RunStateMachine_u8(
                                   ((void *)0)
                                       , 0U, &delta);

  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((0U)), (UNITY_INT)(UNITY_UINT8 )((result)), (
 ((void *)0)
 ), (UNITY_UINT)(28), UNITY_DISPLAY_STYLE_UINT8);
}