// CEEDLING NOTICE: This generated file only to be consumed for test runner creation

#include "mock_MyLib.h"
#include "utExecutionAndResults/utUnderTest/build/vendor/unity/src/unity.h"
#include "utExecutionAndResults/utUnderTest/src/MyLib_RunStateMachine_u8.h"

void setUp(void) {
}

void tearDown(void) {
}

void test_State1_ProcessWithValidDelta_Return0(void) {
  MyLib_record_t input_rec = {7U, 150U};
  uint16_t delta = 25U;
  uint8_t result;

  MyLib_UpdateGlobalRecord_CMockExpect(16, ((void *)0), &input_rec);
  MyLib_UpdateGlobalRecord_CMockIgnoreArg_dest_p(17);

  result = MyLib_RunStateMachine_u8(&input_rec, 0U, &delta);
  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8)((0U)), (UNITY_INT)(UNITY_UINT8)((result)), (((void *)0)), (UNITY_UINT)(20), UNITY_DISPLAY_STYLE_UINT8);

  MyLib_ProcessRecord_CMockExpect(22, ((void *)0), (5U));
  MyLib_ProcessRecord_CMockIgnoreArg_rec_pc(23);
  MyLib_ComputeAdjustedValue_u32_CMockExpectAndReturn(24, 0U, &delta, 75U);
  MyLib_ComputeAdjustedValue_u32_CMockIgnoreArg_base_u32(25);

  result = MyLib_RunStateMachine_u8(&input_rec, 0U, &delta);

  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8)((0U)), (UNITY_INT)(UNITY_UINT8)((result)), (((void *)0)), (UNITY_UINT)(29), UNITY_DISPLAY_STYLE_UINT8);
}