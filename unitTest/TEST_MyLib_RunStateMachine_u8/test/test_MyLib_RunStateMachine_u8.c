#include "mock_MyLib.h"
#include "unity.h"
#include <MyLib_RunStateMachine_u8.h>

/* SECTION 1 — setUp() and tearDown() */

void setUp(void) {
  g_counter_u32 = 0U;
  g_record.id_u16 = 0U;
  g_record.value_u32 = 0U;
  g_systemReady_b = false;

  MyLib_RunStateMachine_u8_SetState_u8(0U);
  MyLib_RunStateMachine_u8_SetLastAdjusted_u32(0U);
  MyLib_record_t zero_record = {0U, 0U};
  MyLib_RunStateMachine_u8_SetLastRecord(&zero_record);
}

void tearDown(void) {
}

/* SECTION 2 — Test functions */

/**
 * @brief Test: State 0 (Init) with NULL rec_pc → expect return 1, state remains 0
 */
void test_State0_NullRecPtr_Return1_StateRemains0(void) {
  uint8_t result;

  MyLib_RunStateMachine_u8_SetState_u8(0U);

  result = MyLib_RunStateMachine_u8(NULL, 0U, NULL);

  TEST_ASSERT_EQUAL_UINT8(1U, result);
  TEST_ASSERT_EQUAL_UINT8(0U, MyLib_RunStateMachine_u8_GetState_u8());
}

/**
 * @brief Test: State 0 (Init) with valid rec_pc → expect return 0, state transitions to 1, l_LastRecord updated
 */
void test_State0_ValidRecPtr_Return0_StateTransitionsTo1(void) {
  MyLib_record_t input_rec = {123U, 456U};
  MyLib_record_t expected_rec = {123U, 456U};
  uint8_t result;
  MyLib_record_t actual_rec;

  MyLib_RunStateMachine_u8_SetState_u8(0U);

  MyLib_UpdateGlobalRecord_Expect(NULL, &input_rec);
  MyLib_UpdateGlobalRecord_IgnoreArg_dest_p();

  result = MyLib_RunStateMachine_u8(&input_rec, 0U, NULL);

  TEST_ASSERT_EQUAL_UINT8(0U, result);
  TEST_ASSERT_EQUAL_UINT8(1U, MyLib_RunStateMachine_u8_GetState_u8());
}

/**
 * @brief Test: State 1 (Process) with delta_pc_u16 = NULL → expect return 0, state transitions to 2, l_LastAdjusted_u32 computed with default behavior
 */
void test_State1_NullDelta_Return0_StateTransitionsTo2(void) {
  MyLib_record_t last_rec = {10U, 100U};
  uint8_t result;
  uint32_t computed_value = 200U;

  MyLib_RunStateMachine_u8_SetState_u8(1U);
  MyLib_RunStateMachine_u8_SetLastRecord(&last_rec);

  MyLib_ProcessRecord_Expect(NULL, MYLIB_MULT_VALUE_U8);
  MyLib_ProcessRecord_IgnoreArg_rec_pc();

  MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(100U, NULL, computed_value);

  result = MyLib_RunStateMachine_u8(NULL, 0U, NULL);

  TEST_ASSERT_EQUAL_UINT8(0U, result);
  TEST_ASSERT_EQUAL_UINT8(2U, MyLib_RunStateMachine_u8_GetState_u8());
  TEST_ASSERT_EQUAL_UINT32(computed_value, MyLib_RunStateMachine_u8_GetLastAdjusted_u32());
}

/**
 * @brief Test: State 1 (Process) with valid delta_pc_u16 → expect return 0, state transitions to 2, l_LastAdjusted_u32 computed with delta applied
 */
void test_State1_ValidDelta_Return0_StateTransitionsTo2(void) {
  MyLib_record_t last_rec = {20U, 300U};
  uint16_t delta = 50U;
  uint8_t result;
  uint32_t computed_value = 350U;

  MyLib_RunStateMachine_u8_SetState_u8(1U);
  MyLib_RunStateMachine_u8_SetLastRecord(&last_rec);

  MyLib_ProcessRecord_Expect(NULL, MYLIB_MULT_VALUE_U8);
  MyLib_ProcessRecord_IgnoreArg_rec_pc();

  MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(300U, &delta, computed_value);

  result = MyLib_RunStateMachine_u8(NULL, 0U, &delta);

  TEST_ASSERT_EQUAL_UINT8(0U, result);
  TEST_ASSERT_EQUAL_UINT8(2U, MyLib_RunStateMachine_u8_GetState_u8());
  TEST_ASSERT_EQUAL_UINT32(computed_value, MyLib_RunStateMachine_u8_GetLastAdjusted_u32());
}

/**
 * @brief Test: State 2 (Update counter) with add_u32 = 0 and l_LastAdjusted_u32 = 0 → MyLib_UpdateCounter_u8 returns 0 → expect return 0, state transitions to 0
 */
void test_State2_AddZero_AdjustedZero_Return0_StateTransitionsTo0(void) {
  uint8_t result;

  MyLib_RunStateMachine_u8_SetState_u8(2U);
  MyLib_RunStateMachine_u8_SetLastAdjusted_u32(0U);

  MyLib_UpdateCounter_u8_ExpectAndReturn(0U, 0U);

  result = MyLib_RunStateMachine_u8(NULL, 0U, NULL);

  TEST_ASSERT_EQUAL_UINT8(0U, result);
  TEST_ASSERT_EQUAL_UINT8(0U, MyLib_RunStateMachine_u8_GetState_u8());
}

/**
 * @brief Test: State 2 (Update counter) with add_u32 causing MyLib_UpdateCounter_u8 to return 2 (saturation) → expect return 2, state transitions to 0
 */
void test_State2_Saturation_Return2_StateTransitionsTo0(void) {
  uint8_t result;
  uint32_t add_value = 1000U;
  uint32_t adjusted_value = 500U;

  MyLib_RunStateMachine_u8_SetState_u8(2U);
  MyLib_RunStateMachine_u8_SetLastAdjusted_u32(adjusted_value);

  MyLib_UpdateCounter_u8_ExpectAndReturn(1500U, 2U);

  result = MyLib_RunStateMachine_u8(NULL, add_value, NULL);

  TEST_ASSERT_EQUAL_UINT8(2U, result);
  TEST_ASSERT_EQUAL_UINT8(0U, MyLib_RunStateMachine_u8_GetState_u8());
}

/**
 * @brief Test: State 2 (Update counter) with add_u32 at boundary causing wrap in l_UpdateValue_u32 (UINT32_MAX + 1) → expect return code from MyLib_UpdateCounter_u8, state transitions to 0
 */
void test_State2_WrapBoundary_ReturnFromUpdateCounter_StateTransitionsTo0(void) {
  uint8_t result;
  uint32_t add_value = UINT32_MAX;
  uint32_t adjusted_value = 1U;
  uint32_t expected_wrapped = 0U;

  MyLib_RunStateMachine_u8_SetState_u8(2U);
  MyLib_RunStateMachine_u8_SetLastAdjusted_u32(adjusted_value);

  MyLib_UpdateCounter_u8_ExpectAndReturn(expected_wrapped, 0U);

  result = MyLib_RunStateMachine_u8(NULL, add_value, NULL);

  TEST_ASSERT_EQUAL_UINT8(0U, result);
  TEST_ASSERT_EQUAL_UINT8(0U, MyLib_RunStateMachine_u8_GetState_u8());
}

/**
 * @brief Test: Invalid state (e.g., l_State_u8 = 3) → expect return 3, state reset to 0, l_LastAdjusted_u32 reset to 0
 */
void test_InvalidState3_Return3_StateResetTo0_AdjustedResetTo0(void) {
  uint8_t result;

  MyLib_RunStateMachine_u8_SetState_u8(3U);
  MyLib_RunStateMachine_u8_SetLastAdjusted_u32(999U);

  result = MyLib_RunStateMachine_u8(NULL, 0U, NULL);

  TEST_ASSERT_EQUAL_UINT8(3U, result);
  TEST_ASSERT_EQUAL_UINT8(0U, MyLib_RunStateMachine_u8_GetState_u8());
  TEST_ASSERT_EQUAL_UINT32(0U, MyLib_RunStateMachine_u8_GetLastAdjusted_u32());
}

/**
 * @brief Test: Invalid state (e.g., l_State_u8 = 255) → expect return 3, state reset to 0, l_LastAdjusted_u32 reset to 0
 */
void test_InvalidState255_Return3_StateResetTo0_AdjustedResetTo0(void) {
  uint8_t result;

  MyLib_RunStateMachine_u8_SetState_u8(255U);
  MyLib_RunStateMachine_u8_SetLastAdjusted_u32(12345U);

  result = MyLib_RunStateMachine_u8(NULL, 0U, NULL);

  TEST_ASSERT_EQUAL_UINT8(3U, result);
  TEST_ASSERT_EQUAL_UINT8(0U, MyLib_RunStateMachine_u8_GetState_u8());
  TEST_ASSERT_EQUAL_UINT32(0U, MyLib_RunStateMachine_u8_GetLastAdjusted_u32());
}

/**
 * @brief Test: Full state machine cycle (0→1→2→0) with valid inputs → verify correct state transitions and return codes at each step
 */
void test_FullCycle_State0To1To2To0_VerifyTransitionsAndReturns(void) {
  MyLib_record_t input_rec = {111U, 222U};
  uint16_t delta = 10U;
  uint32_t add_value = 5U;
  uint32_t computed_adjusted = 232U;
  uint8_t result;

  MyLib_RunStateMachine_u8_SetState_u8(0U);

  MyLib_UpdateGlobalRecord_Expect(NULL, &input_rec);
  MyLib_UpdateGlobalRecord_IgnoreArg_dest_p();
  result = MyLib_RunStateMachine_u8(&input_rec, 0U, NULL);
  TEST_ASSERT_EQUAL_UINT8(0U, result);
  TEST_ASSERT_EQUAL_UINT8(1U, MyLib_RunStateMachine_u8_GetState_u8());

  MyLib_ProcessRecord_Expect(NULL, MYLIB_MULT_VALUE_U8);
  MyLib_ProcessRecord_IgnoreArg_rec_pc();
  MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(222U, &delta, computed_adjusted);
  result = MyLib_RunStateMachine_u8(NULL, 0U, &delta);
  TEST_ASSERT_EQUAL_UINT8(0U, result);
  TEST_ASSERT_EQUAL_UINT8(2U, MyLib_RunStateMachine_u8_GetState_u8());

  MyLib_UpdateCounter_u8_ExpectAndReturn(237U, 0U);
  result = MyLib_RunStateMachine_u8(NULL, add_value, NULL);
  TEST_ASSERT_EQUAL_UINT8(0U, result);
  TEST_ASSERT_EQUAL_UINT8(0U, MyLib_RunStateMachine_u8_GetState_u8());
}

/**
 * @brief Test: State 0 (Init) rejection followed by valid initialization → verify state remains 0 after rejection, then transitions to 1 on valid call
 */
void test_State0_RejectionThenValid_StateRemains0ThenTransitionsTo1(void) {
  MyLib_record_t input_rec = {50U, 75U};
  uint8_t result;

  MyLib_RunStateMachine_u8_SetState_u8(0U);

  result = MyLib_RunStateMachine_u8(NULL, 0U, NULL);
  TEST_ASSERT_EQUAL_UINT8(1U, result);
  TEST_ASSERT_EQUAL_UINT8(0U, MyLib_RunStateMachine_u8_GetState_u8());

  MyLib_UpdateGlobalRecord_Expect(NULL, &input_rec);
  MyLib_UpdateGlobalRecord_IgnoreArg_dest_p();
  result = MyLib_RunStateMachine_u8(&input_rec, 0U, NULL);
  TEST_ASSERT_EQUAL_UINT8(0U, result);
  TEST_ASSERT_EQUAL_UINT8(1U, MyLib_RunStateMachine_u8_GetState_u8());
}

/**
 * @brief Test: State 2 (Update counter) with add_u32 = UINT32_MAX and l_LastAdjusted_u32 = UINT32_MAX → verify wrap behavior in l_UpdateValue_u32 and return code from MyLib_UpdateCounter_u8
 */
void test_State2_MaxAddMaxAdjusted_VerifyWrapAndReturn(void) {
  uint8_t result;
  uint32_t expected_wrapped = UINT32_MAX - 1U;

  MyLib_RunStateMachine_u8_SetState_u8(2U);
  MyLib_RunStateMachine_u8_SetLastAdjusted_u32(UINT32_MAX);

  MyLib_UpdateCounter_u8_ExpectAndReturn(expected_wrapped, 1U);

  result = MyLib_RunStateMachine_u8(NULL, UINT32_MAX, NULL);

  TEST_ASSERT_EQUAL_UINT8(1U, result);
  TEST_ASSERT_EQUAL_UINT8(0U, MyLib_RunStateMachine_u8_GetState_u8());
}

/**
 * @brief Test: State 1 (Process) → verify MyLib_ProcessRecord called with l_LastRecord and MYLIB_MULT_VALUE_U8, and MyLib_ComputeAdjustedValue_u32 called with l_LastRecord.value_u32 and delta_pc_u16
 */
void test_State1_VerifyFunctionCallsWithCorrectParams(void) {
  MyLib_record_t last_rec = {33U, 444U};
  uint16_t delta = 20U;
  uint32_t computed = 464U;
  uint8_t result;

  MyLib_RunStateMachine_u8_SetState_u8(1U);
  MyLib_RunStateMachine_u8_SetLastRecord(&last_rec);

  MyLib_ProcessRecord_Expect(NULL, MYLIB_MULT_VALUE_U8);
  MyLib_ProcessRecord_IgnoreArg_rec_pc();

  MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(444U, &delta, computed);

  result = MyLib_RunStateMachine_u8(NULL, 0U, &delta);

  TEST_ASSERT_EQUAL_UINT8(0U, result);
}

/**
 * @brief Test: State 2 (Update counter) → verify MyLib_UpdateCounter_u8 called with (add_u32 + l_LastAdjusted_u32) and g_counter_u32 updated accordingly
 */
void test_State2_VerifyUpdateCounterCalledWithSum(void) {
  uint32_t add_value = 100U;
  uint32_t adjusted_value = 200U;
  uint32_t expected_sum = 300U;
  uint8_t result;

  MyLib_RunStateMachine_u8_SetState_u8(2U);
  MyLib_RunStateMachine_u8_SetLastAdjusted_u32(adjusted_value);

  MyLib_UpdateCounter_u8_ExpectAndReturn(expected_sum, 0U);

  result = MyLib_RunStateMachine_u8(NULL, add_value, NULL);

  TEST_ASSERT_EQUAL_UINT8(0U, result);
}

/**
 * @brief Test: State 0 (Init) with valid rec_pc → verify MyLib_UpdateGlobalRecord called with &l_LastRecord and rec_pc
 */
void test_State0_ValidRecPtr_VerifyUpdateGlobalRecordCalled(void) {
  MyLib_record_t input_rec = {99U, 88U};
  uint8_t result;

  MyLib_RunStateMachine_u8_SetState_u8(0U);

  MyLib_UpdateGlobalRecord_Expect(NULL, &input_rec);
  MyLib_UpdateGlobalRecord_IgnoreArg_dest_p();

  result = MyLib_RunStateMachine_u8(&input_rec, 0U, NULL);

  TEST_ASSERT_EQUAL_UINT8(0U, result);
}

/**
 * @brief Test: Multiple cycles through state machine → verify static variables (l_State_u8, l_LastRecord, l_LastAdjusted_u32) persist correctly across calls
 */
void test_MultipleCycles_VerifyStaticVariablesPersist(void) {
  MyLib_record_t rec1 = {1U, 10U};
  MyLib_record_t rec2 = {2U, 20U};
  uint16_t delta1 = 5U;
  uint16_t delta2 = 10U;
  uint32_t adjusted1 = 15U;
  uint32_t adjusted2 = 30U;
  uint8_t result;

  MyLib_RunStateMachine_u8_SetState_u8(0U);

  MyLib_UpdateGlobalRecord_Expect(NULL, &rec1);
  MyLib_UpdateGlobalRecord_IgnoreArg_dest_p();
  result = MyLib_RunStateMachine_u8(&rec1, 0U, NULL);
  TEST_ASSERT_EQUAL_UINT8(0U, result);

  MyLib_ProcessRecord_Expect(NULL, MYLIB_MULT_VALUE_U8);
  MyLib_ProcessRecord_IgnoreArg_rec_pc();
  MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(10U, &delta1, adjusted1);
  result = MyLib_RunStateMachine_u8(NULL, 0U, &delta1);
  TEST_ASSERT_EQUAL_UINT8(0U, result);

  MyLib_UpdateCounter_u8_ExpectAndReturn(15U, 0U);
  result = MyLib_RunStateMachine_u8(NULL, 0U, NULL);
  TEST_ASSERT_EQUAL_UINT8(0U, result);

  MyLib_UpdateGlobalRecord_Expect(NULL, &rec2);
  MyLib_UpdateGlobalRecord_IgnoreArg_dest_p();
  result = MyLib_RunStateMachine_u8(&rec2, 0U, NULL);
  TEST_ASSERT_EQUAL_UINT8(0U, result);

  MyLib_ProcessRecord_Expect(NULL, MYLIB_MULT_VALUE_U8);
  MyLib_ProcessRecord_IgnoreArg_rec_pc();
  MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(20U, &delta2, adjusted2);
  result = MyLib_RunStateMachine_u8(NULL, 0U, &delta2);
  TEST_ASSERT_EQUAL_UINT8(0U, result);

  MyLib_UpdateCounter_u8_ExpectAndReturn(30U, 0U);
  result = MyLib_RunStateMachine_u8(NULL, 0U, NULL);
  TEST_ASSERT_EQUAL_UINT8(0U, result);
}

/**
 * @brief Test: State 2 (Update counter) with add_u32 = 1 and l_LastAdjusted_u32 = 1 → verify l_UpdateValue_u32 = 2 passed to MyLib_UpdateCounter_u8
 */
void test_State2_Add1Adjusted1_VerifySum2PassedToUpdateCounter(void) {
  uint8_t result;

  MyLib_RunStateMachine_u8_SetState_u8(2U);
  MyLib_RunStateMachine_u8_SetLastAdjusted_u32(1U);

  MyLib_UpdateCounter_u8_ExpectAndReturn(2U, 0U);

  result = MyLib_RunStateMachine_u8(NULL, 1U, NULL);

  TEST_ASSERT_EQUAL_UINT8(0U, result);
}

/**
 * @brief Test: State 1 (Process) with l_LastRecord.value_u32 = 0 and delta_pc_u16 pointing to 0 → verify l_LastAdjusted_u32 computed correctly
 */
void test_State1_RecordValue0Delta0_VerifyAdjustedComputed(void) {
  MyLib_record_t last_rec = {0U, 0U};
  uint16_t delta = 0U;
  uint32_t computed = 0U;
  uint8_t result;

  MyLib_RunStateMachine_u8_SetState_u8(1U);
  MyLib_RunStateMachine_u8_SetLastRecord(&last_rec);

  MyLib_ProcessRecord_Expect(NULL, MYLIB_MULT_VALUE_U8);
  MyLib_ProcessRecord_IgnoreArg_rec_pc();

  MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(0U, &delta, computed);

  result = MyLib_RunStateMachine_u8(NULL, 0U, &delta);

  TEST_ASSERT_EQUAL_UINT8(0U, result);
  TEST_ASSERT_EQUAL_UINT32(computed, MyLib_RunStateMachine_u8_GetLastAdjusted_u32());
}

/**
 * @brief Test: State 1 (Process) with l_LastRecord.value_u32 = UINT32_MAX and delta_pc_u16 pointing to UINT16_MAX → verify l_LastAdjusted_u32 computed correctly
 */
void test_State1_RecordValueMaxDeltaMax_VerifyAdjustedComputed(void) {
  MyLib_record_t last_rec = {UINT16_MAX, UINT32_MAX};
  uint16_t delta = UINT16_MAX;
  uint32_t computed = 12345U;
  uint8_t result;

  MyLib_RunStateMachine_u8_SetState_u8(1U);
  MyLib_RunStateMachine_u8_SetLastRecord(&last_rec);

  MyLib_ProcessRecord_Expect(NULL, MYLIB_MULT_VALUE_U8);
  MyLib_ProcessRecord_IgnoreArg_rec_pc();

  MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(UINT32_MAX, &delta, computed);

  result = MyLib_RunStateMachine_u8(NULL, 0U, &delta);

  TEST_ASSERT_EQUAL_UINT8(0U, result);
  TEST_ASSERT_EQUAL_UINT32(computed, MyLib_RunStateMachine_u8_GetLastAdjusted_u32());
}

/**
 * @brief Test: Invalid state (l_State_u8 = 4) → verify recovery: return 3, l_State_u8 = 0, l_LastAdjusted_u32 = 0
 */
void test_InvalidState4_VerifyRecovery_Return3_State0_Adjusted0(void) {
  uint8_t result;

  MyLib_RunStateMachine_u8_SetState_u8(4U);
  MyLib_RunStateMachine_u8_SetLastAdjusted_u32(7777U);

  result = MyLib_RunStateMachine_u8(NULL, 0U, NULL);

  TEST_ASSERT_EQUAL_UINT8(3U, result);
  TEST_ASSERT_EQUAL_UINT8(0U, MyLib_RunStateMachine_u8_GetState_u8());
  TEST_ASSERT_EQUAL_UINT32(0U, MyLib_RunStateMachine_u8_GetLastAdjusted_u32());
}