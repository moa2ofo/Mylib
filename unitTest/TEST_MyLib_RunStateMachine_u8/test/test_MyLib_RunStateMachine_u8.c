#include "MyLib_RunStateMachine_u8.h"
#include "mock_MyLib.h"
#include "unity.h"

void setUp(void) {
}
void tearDown(void) {
}
void test_State0_NullRecPtr_RejectInit_Return1(void) {
  uint8_t result;

  result = MyLib_RunStateMachine_u8(NULL, 0U, NULL);

  TEST_ASSERT_EQUAL_UINT8(1U, result);

  result = MyLib_RunStateMachine_u8(NULL, 0U, NULL);
  TEST_ASSERT_EQUAL_UINT8(1U, result);
}
void test_State0_ValidRecPtr_InitSuccess_Return0(void) {
  MyLib_record_t input_rec = {10U, 200U};
  MyLib_record_t expected_rec = {10U, 200U};
  uint8_t result;

  MyLib_UpdateGlobalRecord_Expect(NULL, &input_rec);
  MyLib_UpdateGlobalRecord_IgnoreArg_dest_p();

  result = MyLib_RunStateMachine_u8(&input_rec, 0U, NULL);

  TEST_ASSERT_EQUAL_UINT8(0U, result);
}
void test_State1_ProcessWithNullDelta_Return0(void) {
  MyLib_record_t input_rec = {5U, 100U};
  uint8_t result;

  MyLib_UpdateGlobalRecord_Expect(NULL, &input_rec);
  MyLib_UpdateGlobalRecord_IgnoreArg_dest_p();

  result = MyLib_RunStateMachine_u8(&input_rec, 0U, NULL);
  TEST_ASSERT_EQUAL_UINT8(0U, result);

  MyLib_ProcessRecord_Expect(NULL, MYLIB_MULT_VALUE_U8);
  MyLib_ProcessRecord_IgnoreArg_rec_pc();
  MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(0U, NULL, 50U);
  MyLib_ComputeAdjustedValue_u32_IgnoreArg_base_u32();

  result = MyLib_RunStateMachine_u8(&input_rec, 0U, NULL);

  TEST_ASSERT_EQUAL_UINT8(0U, result);
}
void test_State1_ProcessWithValidDelta_Return0(void) {
  MyLib_record_t input_rec = {7U, 150U};
  uint16_t delta = 25U;
  uint8_t result;

  MyLib_UpdateGlobalRecord_Expect(NULL, &input_rec);
  MyLib_UpdateGlobalRecord_IgnoreArg_dest_p();

  result = MyLib_RunStateMachine_u8(&input_rec, 0U, &delta);
  TEST_ASSERT_EQUAL_UINT8(0U, result);

  MyLib_ProcessRecord_Expect(NULL, MYLIB_MULT_VALUE_U8);
  MyLib_ProcessRecord_IgnoreArg_rec_pc();
  MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(0U, &delta, 75U);
  MyLib_ComputeAdjustedValue_u32_IgnoreArg_base_u32();

  result = MyLib_RunStateMachine_u8(&input_rec, 0U, &delta);

  TEST_ASSERT_EQUAL_UINT8(0U, result);
}
void test_State2_AddZero_AdjustedZero_Return0(void) {
  MyLib_record_t input_rec = {1U, 0U};
  uint8_t result;

  MyLib_UpdateGlobalRecord_Expect(NULL, &input_rec);
  MyLib_UpdateGlobalRecord_IgnoreArg_dest_p();
  result = MyLib_RunStateMachine_u8(&input_rec, 0U, NULL);
  TEST_ASSERT_EQUAL_UINT8(0U, result);

  MyLib_ProcessRecord_Expect(NULL, MYLIB_MULT_VALUE_U8);
  MyLib_ProcessRecord_IgnoreArg_rec_pc();
  MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(0U, NULL, 0U);
  MyLib_ComputeAdjustedValue_u32_IgnoreArg_base_u32();
  result = MyLib_RunStateMachine_u8(&input_rec, 0U, NULL);
  TEST_ASSERT_EQUAL_UINT8(0U, result);

  MyLib_UpdateCounter_u8_ExpectAndReturn(0U, 0U);
  result = MyLib_RunStateMachine_u8(&input_rec, 0U, NULL);

  TEST_ASSERT_EQUAL_UINT8(0U, result);
}
void test_State2_MidRange_Return0(void) {
  MyLib_record_t input_rec = {2U, 500U};
  uint32_t add_val = 1000U;
  uint8_t result;

  MyLib_UpdateGlobalRecord_Expect(NULL, &input_rec);
  MyLib_UpdateGlobalRecord_IgnoreArg_dest_p();
  result = MyLib_RunStateMachine_u8(&input_rec, add_val, NULL);
  TEST_ASSERT_EQUAL_UINT8(0U, result);

  MyLib_ProcessRecord_Expect(NULL, MYLIB_MULT_VALUE_U8);
  MyLib_ProcessRecord_IgnoreArg_rec_pc();
  MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(0U, NULL, 2000U);
  MyLib_ComputeAdjustedValue_u32_IgnoreArg_base_u32();
  result = MyLib_RunStateMachine_u8(&input_rec, add_val, NULL);
  TEST_ASSERT_EQUAL_UINT8(0U, result);

  MyLib_UpdateCounter_u8_ExpectAndReturn(3000U, 0U);
  result = MyLib_RunStateMachine_u8(&input_rec, add_val, NULL);

  TEST_ASSERT_EQUAL_UINT8(0U, result);
}
void test_State2_AddMax_AdjustedZero_Return0(void) {
  MyLib_record_t input_rec = {3U, 0U};
  uint32_t add_val = UINT32_MAX;
  uint8_t result;

  MyLib_UpdateGlobalRecord_Expect(NULL, &input_rec);
  MyLib_UpdateGlobalRecord_IgnoreArg_dest_p();
  result = MyLib_RunStateMachine_u8(&input_rec, add_val, NULL);
  TEST_ASSERT_EQUAL_UINT8(0U, result);

  MyLib_ProcessRecord_Expect(NULL, MYLIB_MULT_VALUE_U8);
  MyLib_ProcessRecord_IgnoreArg_rec_pc();
  MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(0U, NULL, 0U);
  MyLib_ComputeAdjustedValue_u32_IgnoreArg_base_u32();
  result = MyLib_RunStateMachine_u8(&input_rec, add_val, NULL);
  TEST_ASSERT_EQUAL_UINT8(0U, result);

  MyLib_UpdateCounter_u8_ExpectAndReturn(UINT32_MAX, 0U);
  result = MyLib_RunStateMachine_u8(&input_rec, add_val, NULL);

  TEST_ASSERT_EQUAL_UINT8(0U, result);
}
void test_State2_AddZero_AdjustedMax_Return0(void) {
  MyLib_record_t input_rec = {4U, 1000U};
  uint32_t add_val = 0U;
  uint8_t result;

  MyLib_UpdateGlobalRecord_Expect(NULL, &input_rec);
  MyLib_UpdateGlobalRecord_IgnoreArg_dest_p();
  result = MyLib_RunStateMachine_u8(&input_rec, add_val, NULL);
  TEST_ASSERT_EQUAL_UINT8(0U, result);

  MyLib_ProcessRecord_Expect(NULL, MYLIB_MULT_VALUE_U8);
  MyLib_ProcessRecord_IgnoreArg_rec_pc();
  MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(0U, NULL, UINT32_MAX);
  MyLib_ComputeAdjustedValue_u32_IgnoreArg_base_u32();
  result = MyLib_RunStateMachine_u8(&input_rec, add_val, NULL);
  TEST_ASSERT_EQUAL_UINT8(0U, result);

  MyLib_UpdateCounter_u8_ExpectAndReturn(UINT32_MAX, 0U);
  result = MyLib_RunStateMachine_u8(&input_rec, add_val, NULL);

  TEST_ASSERT_EQUAL_UINT8(0U, result);
}
void test_State2_Saturation_Return2(void) {
  MyLib_record_t input_rec = {5U, 300U};
  uint32_t add_val = 500U;
  uint8_t result;

  MyLib_UpdateGlobalRecord_Expect(NULL, &input_rec);
  MyLib_UpdateGlobalRecord_IgnoreArg_dest_p();
  result = MyLib_RunStateMachine_u8(&input_rec, add_val, NULL);
  TEST_ASSERT_EQUAL_UINT8(0U, result);

  MyLib_ProcessRecord_Expect(NULL, MYLIB_MULT_VALUE_U8);
  MyLib_ProcessRecord_IgnoreArg_rec_pc();
  MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(0U, NULL, 600U);
  MyLib_ComputeAdjustedValue_u32_IgnoreArg_base_u32();
  result = MyLib_RunStateMachine_u8(&input_rec, add_val, NULL);
  TEST_ASSERT_EQUAL_UINT8(0U, result);

  MyLib_UpdateCounter_u8_ExpectAndReturn(1100U, 2U);
  result = MyLib_RunStateMachine_u8(&input_rec, add_val, NULL);

  TEST_ASSERT_EQUAL_UINT8(2U, result);
}
void test_FullCycle_InitProcessUpdateSuccess_ReturnToState0(void) {
  MyLib_record_t input_rec1 = {10U, 100U};
  MyLib_record_t input_rec2 = {20U, 200U};
  uint32_t add_val = 50U;
  uint8_t result;

  MyLib_UpdateGlobalRecord_Expect(NULL, &input_rec1);
  MyLib_UpdateGlobalRecord_IgnoreArg_dest_p();
  result = MyLib_RunStateMachine_u8(&input_rec1, add_val, NULL);
  TEST_ASSERT_EQUAL_UINT8(0U, result);

  MyLib_ProcessRecord_Expect(NULL, MYLIB_MULT_VALUE_U8);
  MyLib_ProcessRecord_IgnoreArg_rec_pc();
  MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(0U, NULL, 150U);
  MyLib_ComputeAdjustedValue_u32_IgnoreArg_base_u32();
  result = MyLib_RunStateMachine_u8(&input_rec1, add_val, NULL);
  TEST_ASSERT_EQUAL_UINT8(0U, reult);

  MyLib_UpdateCounter_u8_ExpectAndReturn(200U, 0U);
  result = MyLib_RunStateMachine_u8(&input_rec1, add_val, NULL);
  TEST_ASSERT_EQUAL_UINT8(0U, result);

  MyLib_UpdateGlobalRecord_Expect(NULL, &input_rec2);
  MyLib_UpdateGlobalRecord_IgnoreArg_dest_p();
  result = MyLib_RunStateMachine_u8(&input_rec2, add_val, NULL);
  TEST_ASSERT_EQUAL_UINT8(0U, result);
}
void test_FullCycle_InitProcessUpdateSaturation_ReturnToState0(void) {
  MyLib_record_t input_rec1 = {11U, 110U};
  MyLib_record_t input_rec2 = {21U, 210U};
  uint32_t add_val = 60U;
  uint8_t result;

  MyLib_UpdateGlobalRecord_Expect(NULL, &input_rec1);
  MyLib_UpdateGlobalRecord_IgnoreArg_dest_p();
  result = MyLib_RunStateMachine_u8(&input_rec1, add_val, NULL);
  TEST_ASSERT_EQUAL_UINT8(0U, result);

  MyLib_ProcessRecord_Expect(NULL, MYLIB_MULT_VALUE_U8);
  MyLib_ProcessRecord_IgnoreArg_rec_pc();
  MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(0U, NULL, 160U);
  MyLib_ComputeAdjustedValue_u32_IgnoreArg_base_u32();
  result = MyLib_RunStateMachine_u8(&input_rec1, add_val, NULL);
  TEST_ASSERT_EQUAL_UINT8(0U, result);

  MyLib_UpdateCounter_u8_ExpectAndReturn(220U, 2U);
  result = MyLib_RunStateMachine_u8(&input_rec1, add_val, NULL);
  TEST_ASSERT_EQUAL_UINT8(2U, result);

  MyLib_UpdateGlobalRecord_Expect(NULL, &input_rec2);
  MyLib_UpdateGlobalRecord_IgnoreArg_dest_p();
  result = MyLib_RunStateMachine_u8(&input_rec2, add_val, NULL);
  TEST_ASSERT_EQUAL_UINT8(0U, result);
}
void test_State0_ValidRecPtr_ValueZero_InitSuccess(void) {
  MyLib_record_t input_rec = {15U, 0U};
  uint8_t result;

  MyLib_UpdateGlobalRecord_Expect(NULL, &input_rec);
  MyLib_UpdateGlobalRecord_IgnoreArg_dest_p();

  result = MyLib_RunStateMachine_u8(&input_rec, 0U, NULL);

  TEST_ASSERT_EQUAL_UINT8(0U, result);
}
void test_State0_ValidRecPtr_ValueMax_InitSuccess(void) {
  MyLib_record_t input_rec = {16U, UINT32_MAX};
  uint8_t result;

  MyLib_UpdateGlobalRecord_Expect(NULL, &input_rec);
  MyLib_UpdateGlobalRecord_IgnoreArg_dest_p();

  result = MyLib_RunStateMachine_u8(&input_rec, 0U, NULL);

  TEST_ASSERT_EQUAL_UINT8(0U, result);
}
void test_State2_WrapAround_VerifyBehavior(void) {
  MyLib_record_t input_rec = {17U, 500U};
  uint32_t add_val = UINT32_MAX;
  uint8_t result;

  MyLib_UpdateGlobalRecord_Expect(NULL, &input_rec);
  MyLib_UpdateGlobalRecord_IgnoreArg_dest_p();
  result = MyLib_RunStateMachine_u8(&input_rec, add_val, NULL);
  TEST_ASSERT_EQUAL_UINT8(0U, result);

  MyLib_ProcessRecord_Expect(NULL, MYLIB_MULT_VALUE_U8);
  MyLib_ProcessRecord_IgnoreArg_rec_pc();
  MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(0U, NULL, 100U);
  MyLib_ComputeAdjustedValue_u32_IgnoreArg_base_u32();
  result = MyLib_RunStateMachine_u8(&input_rec, add_val, NULL);
  TEST_ASSERT_EQUAL_UINT8(0U, result);

  uint32_t expected_wrap = add_val + 100U;
  MyLib_UpdateCounter_u8_ExpectAndReturn(expected_wrap, 0U);
  result = MyLib_RunStateMachine_u8(&input_rec, add_val, NULL);

  TEST_ASSERT_EQUAL_UINT8(0U, result);
}
void test_State0_MultipleNullCalls_EachReturns1(void) {
  uint8_t result;

  result = MyLib_RunStateMachine_u8(NULL, 0U, NULL);
  TEST_ASSERT_EQUAL_UINT8(1U, result);

  result = MyLib_RunStateMachine_u8(NULL, 0U, NULL);
  TEST_ASSERT_EQUAL_UINT8(1U, result);

  result = MyLib_RunStateMachine_u8(NULL, 0U, NULL);
  TEST_ASSERT_EQUAL_UINT8(1U, result);

  result = MyLib_RunStateMachine_u8(NULL, 0U, NULL);
  TEST_ASSERT_EQUAL_UINT8(1U, result);
}
void test_State1_DeltaPointingToZero_Return0(void) {
  MyLib_record_t input_rec = {18U, 250U};
  uint16_t delta = 0U;
  uint8_t result;

  MyLib_UpdateGlobalRecord_Expect(NULL, &input_rec);
  MyLib_UpdateGlobalRecord_IgnoreArg_dest_p();
  result = MyLib_RunStateMachine_u8(&input_rec, 0U, &delta);
  TEST_ASSERT_EQUAL_UINT8(0U, result);

  MyLib_ProcessRecord_Expect(NULL, MYLIB_MULT_VALUE_U8);
  MyLib_ProcessRecord_IgnoreArg_rec_pc();
  MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(0U, &delta, 125U);
  MyLib_ComputeAdjustedValue_u32_IgnoreArg_base_u32();

  result = MyLib_RunStateMachine_u8(&input_rec, 0U, &delta);

  TEST_ASSERT_EQUAL_UINT8(0U, result);
}
void test_State1_DeltaPointingToMax_Return0(void) {
  MyLib_record_t input_rec = {19U, 350U};
  uint16_t delta = UINT16_MAX;
  uint8_t result;

  MyLib_UpdateGlobalRecord_Expect(NULL, &input_rec);
  MyLib_UpdateGlobalRecord_IgnoreArg_dest_p();
  result = MyLib_RunStateMachine_u8(&input_rec, 0U, &delta);
  TEST_ASSERT_EQUAL_UINT8(0U, result);

  MyLib_ProcessRecord_Expect(NULL, MYLIB_MULT_VALUE_U8);
  MyLib_ProcessRecord_IgnoreArg_rec_pc();
  MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(0U, &delta, 175U);
  MyLib_ComputeAdjustedValue_u32_IgnoreArg_base_u32();

  result = MyLib_RunStateMachine_u8(&input_rec, 0U, &delta);

  TEST_ASSERT_EQUAL_UINT8(0U, result);
}
