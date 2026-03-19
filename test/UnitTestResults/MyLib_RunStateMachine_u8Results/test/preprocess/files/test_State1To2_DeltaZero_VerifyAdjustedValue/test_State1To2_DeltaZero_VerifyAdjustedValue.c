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

void test_State1To2_DeltaZero_VerifyAdjustedValue(void)
{
  MyLib_record_t input_rec = {10, 100};
  uint16_t delta = 0;
  uint8_t result;

  MyLib_UpdateGlobalRecord_CMockExpect(20,
 ((void *)0)
 , &input_rec);
  MyLib_UpdateGlobalRecord_CMockIgnoreArg_dest_p(21);
  result = MyLib_RunStateMachine_u8(&input_rec, 0,
                                                  ((void *)0)
                                                      );

  MyLib_ProcessRecord_CMockExpect(24,
 ((void *)0)
 , (5U));
  MyLib_ProcessRecord_CMockIgnoreArg_rec_pc(25);
  MyLib_ComputeAdjustedValue_u32_CMockExpectAndReturn(26, 0, &delta, 100);
  MyLib_ComputeAdjustedValue_u32_CMockIgnoreArg_base_u32(27);

  result = MyLib_RunStateMachine_u8(
                                   ((void *)0)
                                       , 0, &delta);

  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((0)), (UNITY_INT)(UNITY_UINT8 )((result)), (
 ((void *)0)
 ), (UNITY_UINT)(31), UNITY_DISPLAY_STYLE_UINT8);
}