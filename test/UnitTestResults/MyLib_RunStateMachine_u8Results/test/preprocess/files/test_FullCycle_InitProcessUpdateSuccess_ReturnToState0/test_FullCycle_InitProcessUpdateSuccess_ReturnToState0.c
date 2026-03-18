// CEEDLING NOTICE: This generated file only to be consumed for test runner creation

#include "mock_MyLib.h"
#include "utExecutionAndResults/utUnderTest/build/vendor/unity/src/unity.h"
#include "utExecutionAndResults/utUnderTest/src/MyLib_RunStateMachine_u8.h"

void setUp(void) {
}

void tearDown(void) {
}

void test_FullCycle_InitProcessUpdateSuccess_ReturnToState0(void) {
  MyLib_record_t input_rec1 = {10U, 100U};
  MyLib_record_t input_rec2 = {20U, 200U};
  uint32_t add_val = 50U;
  uint8_t result;

  MyLib_UpdateGlobalRecord_CMockExpect(17, ((void *)0), &input_rec1);
  MyLib_UpdateGlobalRecord_CMockIgnoreArg_dest_p(18);
  result = MyLib_RunStateMachine_u8(&input_rec1, add_val, ((void *)0));
  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8)((0U)), (UNITY_INT)(UNITY_UINT8)((result)), (((void *)0)), (UNITY_UINT)(20), UNITY_DISPLAY_STYLE_UINT8);

  MyLib_ProcessRecord_CMockExpect(22, ((void *)0), (5U));
  MyLib_ProcessRecord_CMockIgnoreArg_rec_pc(23);
  MyLib_ComputeAdjustedValue_u32_CMockExpectAndReturn(24, 0U, ((void *)0), 150U);
  MyLib_ComputeAdjustedValue_u32_CMockIgnoreArg_base_u32(25);
  result = MyLib_RunStateMachine_u8(&input_rec1, add_val, ((void *)0));
  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8)((0U)), (UNITY_INT)(UNITY_UINT8)((reult)), (((void *)0)), (UNITY_UINT)(27), UNITY_DISPLAY_STYLE_UINT8);

  MyLib_UpdateCounter_u8_CMockExpectAndReturn(29, 200U, 0U);
  result = MyLib_RunStateMachine_u8(&input_rec1, add_val, ((void *)0));
  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8)((0U)), (UNITY_INT)(UNITY_UINT8)((result)), (((void *)0)), (UNITY_UINT)(31), UNITY_DISPLAY_STYLE_UINT8);

  MyLib_UpdateGlobalRecord_CMockExpect(33, ((void *)0), &input_rec2);
  MyLib_UpdateGlobalRecord_CMockIgnoreArg_dest_p(34);
  result = MyLib_RunStateMachine_u8(&input_rec2, add_val, ((void *)0));
  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8)((0U)), (UNITY_INT)(UNITY_UINT8)((result)), (((void *)0)), (UNITY_UINT)(36), UNITY_DISPLAY_STYLE_UINT8);
}