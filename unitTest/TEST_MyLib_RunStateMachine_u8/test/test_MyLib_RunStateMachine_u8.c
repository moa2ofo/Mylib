#include "MyLib_RunStateMachine_u8.h"
#include "mock_MyLib.h"
#include "unity.h"

void setUp(void) {
}
void tearDown(void) {
}
void test_State0_Init_NullRecPtr_Returns1_StateRemains0(void) {
  uint8_t result;

  result = MyLib_RunStateMachine_u8(NULL, 0U, NULL);

  TEST_ASSERT_EQUAL_UINT8(1U, result);

  result = MyLib_RunStateMachine_u8(NULL, 0U, NULL);
  TEST_ASSERT_EQUAL_UINT8(1U, result);
}
void test_State0_Init_ValidRecPtr_Returns0_StateTransitionsTo1(void) {
  MyLib_record_t input_rec = {10U, 100U};
  MyLib_record_t expected_rec = {10U, 100U};
  uint8_t result;

  MyLib_UpdateGlobalRecord_Expect(NULL, &input_rec);
  MyLib_UpdateGlobalRecord_IgnoreArg_dest_p();

  result = MyLib_RunStateMachine_u8(&input_rec, 0U, NULL);

  TEST_ASSERT_EQUAL_UINT8(0U, result);
}
void test_State1_Process_NullDelta_Returns0_StateTransitionsTo2(void) {
  MyLib_record_t input_rec = {10U, 100U};
  uint8_t result;

  MyLib_UpdateGlobalRecord_Expect(NULL, &input_rec);
  MyLib_UpdateGlobalRecord_IgnoreArg_dest_p();
  result = MyLib_RunStateMachine_u8(&input_rec, 0U, NULL);
  TEST_ASSERT_EQUAL_UINT8(0U, result);

  MyLib_ProcessRecord_Expect(NULL, MYLIB_MULT_VALUE_U8);
  MyLib_ProcessRecord_IgnoreArg_rec_pc();
  MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(0U, NULL, 50U);
  MyLib_ComputeAdjustedValue_u32_IgnoreArg_base_u32();

  result = MyLib_RunStateMachine_u8(NULL, 0U, NULL);

  TEST_ASSERT_EQUAL_UINT8(0U, result);
}
void test_State1_Process_ValidDelta_Returns0_StateTransitionsTo2(void) {
  MyLib_record_t input_rec = {10U, 100U};
  uint16_t delta = 25U;
  uint8_t result;

  MyLib_UpdateGlobalRecord_Expect(NULL, &input_rec);
  MyLib_UpdateGlobalRecord_IgnoreArg_dest_p();
  result = MyLib_RunStateMachine_u8(&input_rec, 0U, NULL);
  TEST_ASSERT_EQUAL_UINT8(0U, result);

  MyLib_ProcessRecord_Expect(NULL, MYLIB_MULT_VALUE_U8);
  MyLib_ProcessRecord_IgnoreArg_rec_pc();
  MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(0U, &delta, 75U);
  MyLib_ComputeAdjustedValue_u32_IgnoreArg_base_u32();

  result = MyLib_RunStateMachine_u8(NULL, 0U, &delta);

  TEST_ASSERT_EQUAL_UINT8(0U, result);
}
void test_State2_UpdateCounter_Add0_Adjusted0_PropagatesReturn_StateTransitionsTo0(void) {
  MyLib_record_t input_rec = {10U, 100U};
  uint8_t result;

  MyLib_UpdateGlobalRecord_Expect(NULL, &input_rec);
  MyLib_UpdateGlobalRecord_IgnoreArg_dest_p();
  result = MyLib_RunStateMachine_u8(&input_rec, 0U, NULL);

  MyLib_ProcessRecord_Expect(NULL, MYLIB_MULT_VALUE_U8);
  MyLib_ProcessRecord_IgnoreArg_rec_pc();
  MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(0U, NULL, 0U);
  MyLib_ComputeAdjustedValue_u32_IgnoreArg_base_u32();
  result = MyLib_RunStateMachine_u8(NULL, 0U, NULL);

  MyLib_UpdateCounter_u8_ExpectAndReturn(0U, 0U);

  result = MyLib_RunStateMachine_u8(NULL, 0U, NULL);

  TEST_ASSERT_EQUAL_UINT8(0U, result);

  MyLib_UpdateGlobalRecord_Expect(NULL, &input_rec);
  MyLib_UpdateGlobalRecord_IgnoreArg_dest_p();
  result = MyLib_RunStateMachine_u8(&input_rec, 0U, NULL);
  TEST_ASSERT_EQUAL_UINT8(0U, result);
}
void test_State2_UpdateCounter_NoSaturation_Returns0_StateTransitionsTo0(void) {
  MyLib_record_t input_rec = {10U, 100U};
  uint8_t result;

  MyLib_UpdateGlobalRecord_Expect(NULL, &input_rec);
  MyLib_UpdateGlobalRecord_IgnoreArg_dest_p();
  result = MyLib_RunStateMachine_u8(&input_rec, 0U, NULL);

  MyLib_ProcessRecord_Expect(NULL, MYLIB_MULT_VALUE_U8);
  MyLib_ProcessRecord_IgnoreArg_rec_pc();
  MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(0U, NULL, 30U);
  MyLib_ComputeAdjustedValue_u32_IgnoreArg_base_u32();
  result = MyLib_RunStateMachine_u8(NULL, 0U, NULL);

  MyLib_UpdateCounter_u8_ExpectAndReturn(50U, 0U);

  result = MyLib_RunStateMachine_u8(NULL, 20U, NULL);

  TEST_ASSERT_EQUAL_UINT8(0U, result);
}
void test_State2_UpdateCounter_Saturation_Returns2_StateTransitionsTo0(void) {
  MyLib_record_t input_rec = {10U, 100U};
  uint8_t result;

  MyLib_UpdateGlobalRecord_Expect(NULL, &input_rec);
  MyLib_UpdateGlobalRecord_IgnoreArg_dest_p();
  result = MyLib_RunStateMachine_u8(&input_rec, 0U, NULL);

  MyLib_ProcessRecord_Expect(NULL, MYLIB_MULT_VALUE_U8);
  MyLib_ProcessRecord_IgnoreArg_rec_pc();
  MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(0U, NULL, 60U);
  MyLib_ComputeAdjustedValue_u32_IgnoreArg_base_u32();
  result = MyLib_RunStateMachine_u8(NULL, 0U, NULL);

  MyLib_UpdateCounter_u8_ExpectAndReturn(110U, 2U);

  result = MyLib_RunStateMachine_u8(NULL, 50U, NULL);

  TEST_ASSERT_EQUAL_UINT8(2U, result);
}
void test_State2_UpdateCounter_AddUINT32MAX_PropagatesReturn_StateTransitionsTo0(void) {
  MyLib_record_t input_rec = {10U, 100U};
  uint8_t result;

  MyLib_UpdateGlobalRecord_Expect(NULL, &input_rec);
  MyLib_UpdateGlobalRecord_IgnoreArg_dest_p();
  result = MyLib_RunStateMachine_u8(&input_rec, 0U, NULL);

  MyLib_ProcessRecord_Expect(NULL, MYLIB_MULT_VALUE_U8);
  MyLib_ProcessRecord_IgnoreArg_rec_pc();
  MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(0U, NULL, 10U);
  MyLib_ComputeAdjustedValue_u32_IgnoreArg_base_u32();
  result = MyLib_RunStateMachine_u8(NULL, 0U, NULL);

  MyLib_UpdateCounter_u8_ExpectAndReturn(9U, 1U);

  result = MyLib_RunStateMachine_u8(NULL, UINT32_MAX, NULL);

  TEST_ASSERT_EQUAL_UINT8(1U, result);
}
void test_FullCycle_ValidInputs_NoSaturation_Returns000_StateCyclesTo0(void) {
  MyLib_record_t input_rec = {15U, 200U};
  uint16_t delta = 10U;
  uint8_t result;

  MyLib_UpdateGlobalRecord_Expect(NULL, &input_rec);
  MyLib_UpdateGlobalRecord_IgnoreArg_dest_p();
  result = MyLib_RunStateMachine_u8(&input_rec, 0U, NULL);
  TEST_ASSERT_EQUAL_UINT8(0U, result);

  MyLib_ProcessRecord_Expect(NULL, MYLIB_MULT_VALUE_U8);
  MyLib_ProcessRecord_IgnoreArg_rec_pc();
  MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(0U, &delta, 40U);
  MyLib_ComputeAdjustedValue_u32_IgnoreArg_base_u32();
  result = MyLib_RunStateMachine_u8(NULL, 0U, &delta);
  TEST_ASSERT_EQUAL_UINT8(0U, result);

  MyLib_UpdateCounter_u8_ExpectAndReturn(60U, 0U);
  result = MyLib_RunStateMachine_u8(NULL, 20U, NULL);
  TEST_ASSERT_EQUAL_UINT8(0U, result);

  MyLib_UpdateGlobalRecord_Expect(NULL, &input_rec);
  MyLib_UpdateGlobalRecord_IgnoreArg_dest_p();
  result = MyLib_RunStateMachine_u8(&input_rec, 0U, NULL);
  TEST_ASSERT_EQUAL_UINT8(0U, result);
}
void test_FullCycle_NullRecPcFirstCall_Returns1_StateRemains0_UntilValidRecPc(void) {
  MyLib_record_t input_rec = {15U, 200U};
  uint8_t result;

  result = MyLib_RunStateMachine_u8(NULL, 0U, NULL);
  TEST_ASSERT_EQUAL_UINT8(1U, result);

  result = MyLib_RunStateMachine_u8(NULL, 0U, NULL);
  TEST_ASSERT_EQUAL_UINT8(1U, result);

  MyLib_UpdateGlobalRecord_Expect(NULL, &input_rec);
  MyLib_UpdateGlobalRecord_IgnoreArg_dest_p();
  result = MyLib_RunStateMachine_u8(&input_rec, 0U, NULL);
  TEST_ASSERT_EQUAL_UINT8(0U, result);

  MyLib_ProcessRecord_Expect(NULL, MYLIB_MULT_VALUE_U8);
  MyLib_ProcessRecord_IgnoreArg_rec_pc();
  MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(0U, NULL, 50U);
  MyLib_ComputeAdjustedValue_u32_IgnoreArg_base_u32();
  result = MyLib_RunStateMachine_u8(NULL, 0U, NULL);
  TEST_ASSERT_EQUAL_UINT8(0U, result);
}
void test_FullCycle_SaturationInUpdate_Returns002_StateCyclesTo0(void) {
  MyLib_record_t input_rec = {20U, 300U};
  uint16_t delta = 15U;
  uint8_t result;

  MyLib_UpdateGlobalRecord_Expect(NULL, &input_rec);
  MyLib_UpdateGlobalRecord_IgnoreArg_dest_p();
  result = MyLib_RunStateMachine_u8(&input_rec, 0U, NULL);
  TEST_ASSERT_EQUAL_UINT8(0U, result);

  MyLib_ProcessRecord_Expect(NULL, MYLIB_MULT_VALUE_U8);
  MyLib_ProcessRecord_IgnoreArg_rec_pc();
  MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(0U, &delta, 80U);
  MyLib_ComputeAdjustedValue_u32_IgnoreArg_base_u32();
  result = MyLib_RunStateMachine_u8(NULL, 0U, &delta);
  TEST_ASSERT_EQUAL_UINT8(0U, result);

  MyLib_UpdateCounter_u8_ExpectAndReturn(180U, 2U);
  result = MyLib_RunStateMachine_u8(NULL, 100U, NULL);
  TEST_ASSERT_EQUAL_UINT8(2U, result);

  MyLib_UpdateGlobalRecord_Expect(NULL, &input_rec);
  MyLib_UpdateGlobalRecord_IgnoreArg_dest_p();
  result = MyLib_RunStateMachine_u8(&input_rec, 0U, NULL);
  TEST_ASSERT_EQUAL_UINT8(0U, result);
}
void test_State0_Init_CalledTwice_BothReturn0_RecordUpdatedEachCall(void) {
  MyLib_record_t input_rec1 = {10U, 100U};
  MyLib_record_t input_rec2 = {20U, 200U};
  uint8_t result;

  MyLib_UpdateGlobalRecord_Expect(NULL, &input_rec1);
  MyLib_UpdateGlobalRecord_IgnoreArg_dest_p();
  result = MyLib_RunStateMachine_u8(&input_rec1, 0U, NULL);
  TEST_ASSERT_EQUAL_UINT8(0U, result);

  MyLib_ProcessRecord_Expect(NULL, MYLIB_MULT_VALUE_U8);
  MyLib_ProcessRecord_IgnoreArg_rec_pc();
  MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(0U, NULL, 50U);
  MyLib_ComputeAdjustedValue_u32_IgnoreArg_base_u32();
  result = MyLib_RunStateMachine_u8(&input_rec2, 0U, NULL);
  TEST_ASSERT_EQUAL_UINT8(0U, result);
}
void test_State1_Process_ReEntry_Returns0_StateTransitionsTo2(void) {
  MyLib_record_t input_rec = {10U, 100U};
  uint8_t result;

  MyLib_UpdateGlobalRecord_Expect(NULL, &input_rec);
  MyLib_UpdateGlobalRecord_IgnoreArg_dest_p();
  result = MyLib_RunStateMachine_u8(&input_rec, 0U, NULL);
  TEST_ASSERT_EQUAL_UINT8(0U, result);

  MyLib_ProcessRecord_Expect(NULL, MYLIB_MULT_VALUE_U8);
  MyLib_ProcessRecord_IgnoreArg_rec_pc();
  MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(0U, NULL, 50U);
  MyLib_ComputeAdjustedValue_u32_IgnoreArg_base_u32();
  result = MyLib_RunStateMachine_u8(NULL, 0U, NULL);
  TEST_ASSERT_EQUAL_UINT8(0U, result);
}
void test_State2_UpdateCounter_ReEntry_PropagatesReturn_StateTransitionsTo0(void) {
  MyLib_record_t input_rec = {10U, 100U};
  uint8_t result;

  MyLib_UpdateGlobalRecord_Expect(NULL, &input_rec);
  MyLib_UpdateGlobalRecord_IgnoreArg_dest_p();
  result = MyLib_RunStateMachine_u8(&input_rec, 0U, NULL);

  MyLib_ProcessRecord_Expect(NULL, MYLIB_MULT_VALUE_U8);
  MyLib_ProcessRecord_IgnoreArg_rec_pc();
  MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(0U, NULL, 40U);
  MyLib_ComputeAdjustedValue_u32_IgnoreArg_base_u32();
  result = MyLib_RunStateMachine_u8(NULL, 0U, NULL);

  MyLib_UpdateCounter_u8_ExpectAndReturn(50U, 0U);
  result = MyLib_RunStateMachine_u8(NULL, 10U, NULL);
  TEST_ASSERT_EQUAL_UINT8(0U, result);
}
void test_StateMachine_ResetAfterFullCycle_AcceptsNewRecPc_Returns0_TransitionsTo1(void) {
  MyLib_record_t input_rec1 = {10U, 100U};
  MyLib_record_t input_rec2 = {30U, 300U};
  uint8_t result;

  MyLib_UpdateGlobalRecord_Expect(NULL, &input_rec1);
  MyLib_UpdateGlobalRecord_IgnoreArg_dest_p();
  result = MyLib_RunStateMachine_u8(&input_rec1, 0U, NULL);
  TEST_ASSERT_EQUAL_UINT8(0U, result);

  MyLib_ProcessRecord_Expect(NULL, MYLIB_MULT_VALUE_U8);
  MyLib_ProcessRecord_IgnoreArg_rec_pc();
  MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(0U, NULL, 50U);
  MyLib_ComputeAdjustedValue_u32_IgnoreArg_base_u32();
  result = MyLib_RunStateMachine_u8(NULL, 0U, NULL);
  TEST_ASSERT_EQUAL_UINT8(0U, result);

  MyLib_UpdateCounter_u8_ExpectAndReturn(60U, 0U);
  result = MyLib_RunStateMachine_u8(NULL, 10U, NULL);
  TEST_ASSERT_EQUAL_UINT8(0U, result);

  MyLib_UpdateGlobalRecord_Expect(NULL, &input_rec2);
  MyLib_UpdateGlobalRecord_IgnoreArg_dest_p();
  result = MyLib_RunStateMachine_u8(&input_rec2, 0U, NULL);
  TEST_ASSERT_EQUAL_UINT8(0U, result);
}
void test_State1_Process_DeltaBoundary0_Returns0_StateTransitionsTo2(void) {
  MyLib_record_t input_rec = {10U, 100U};
  uint16_t delta = 0U;
  uint8_t result;

  MyLib_UpdateGlobalRecord_Expect(NULL, &input_rec);
  MyLib_UpdateGlobalRecord_IgnoreArg_dest_p();
  result = MyLib_RunStateMachine_u8(&input_rec, 0U, NULL);
  TEST_ASSERT_EQUAL_UINT8(0U, result);

  MyLib_ProcessRecord_Expect(NULL, MYLIB_MULT_VALUE_U8);
  MyLib_ProcessRecord_IgnoreArg_rec_pc();
  MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(0U, &delta, 25U);
  MyLib_ComputeAdjustedValue_u32_IgnoreArg_base_u32();

  result = MyLib_RunStateMachine_u8(NULL, 0U, &delta);

  TEST_ASSERT_EQUAL_UINT8(0U, result);
}
void test_State1_Process_DeltaBoundaryUINT16MAX_Returns0_StateTransitionsTo2(void) {
  MyLib_record_t input_rec = {10U, 100U};
  uint16_t delta = UINT16_MAX;
  uint8_t result;

  MyLib_UpdateGlobalRecord_Expect(NULL, &input_rec);
  MyLib_UpdateGlobalRecord_IgnoreArg_dest_p();
  result = MyLib_RunStateMachine_u8(&input_rec, 0U, NULL);
  TEST_ASSERT_EQUAL_UINT8(0U, result);

  MyLib_ProcessRecord_Expect(NULL, MYLIB_MULT_VALUE_U8);
  MyLib_ProcessRecord_IgnoreArg_rec_pc();
  MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(0U, &delta, 70000U);
  MyLib_ComputeAdjustedValue_u32_IgnoreArg_base_u32();

  result = MyLib_RunStateMachine_u8(NULL, 0U, &delta);

  TEST_ASSERT_EQUAL_UINT8(0U, result);
}
void test_State2_UpdateCounter_Add1_AdjustedMidRange_PropagatesReturn_StateTransitionsTo0(void) {
  MyLib_record_t input_rec = {10U, 100U};
  uint8_t result;

  MyLib_UpdateGlobalRecord_Expect(NULL, &input_rec);
  MyLib_UpdateGlobalRecord_IgnoreArg_dest_p();
  result = MyLib_RunStateMachine_u8(&input_rec, 0U, NULL);

  MyLib_ProcessRecord_Expect(NULL, MYLIB_MULT_VALUE_U8);
  MyLib_ProcessRecord_IgnoreArg_rec_pc();
  MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(0U, NULL, 0x80000000U);
  MyLib_ComputeAdjustedValue_u32_IgnoreArg_base_u32();
  result = MyLib_RunStateMachine_u8(NULL, 0U, NULL);

  MyLib_UpdateCounter_u8_ExpectAndReturn(0x80000001U, 1U);

  result = MyLib_RunStateMachine_u8(NULL, 1U, NULL);

  TEST_ASSERT_EQUAL_UINT8(1U, result);
}
void test_State2_UpdateCounter_AddMidRange_PropagatesReturn_StateTransitionsTo0(void) {
  MyLib_record_t input_rec = {10U, 100U};
  uint8_t result;

  MyLib_UpdateGlobalRecord_Expect(NULL, &input_rec);
  MyLib_UpdateGlobalRecord_IgnoreArg_dest_p();
  result = MyLib_RunStateMachine_u8(&input_rec, 0U, NULL);

  MyLib_ProcessRecord_Expect(NULL, MYLIB_MULT_VALUE_U8);
  MyLib_ProcessRecord_IgnoreArg_rec_pc();
  MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(0U, NULL, 100U);
  MyLib_ComputeAdjustedValue_u32_IgnoreArg_base_u32();
  result = MyLib_RunStateMachine_u8(NULL, 0U, NULL);

  MyLib_UpdateCounter_u8_ExpectAndReturn(0x80000064U, 0U);

  result = MyLib_RunStateMachine_u8(NULL, 0x80000000U, NULL);

  TEST_ASSERT_EQUAL_UINT8(0U, result);
}
