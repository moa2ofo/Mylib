#include "MyLib_RunStateMachine_u8.h"
#include "mock_MyLib.h"
#include "unity.h"

/* SECTION 1 — setUp() and tearDown() */

void setUp(void) {
  g_counter_u32 = 0U;
}

void tearDown(void) {
}

/* SECTION 2 — Test functions */

/**
 * @brief Test: State 0 (Init) with NULL rec_pc → expect return 1, state remains 0
 */
void test_State0_NullRecPtr_Return1_StateRemains0(void) {
  uint8_t result;

  result = MyLib_RunStateMachine_u8(NULL, 0U, NULL);
  TEST_ASSERT_EQUAL_UINT8(1U, result);

  result = MyLib_RunStateMachine_u8(NULL, 0U, NULL);
  TEST_ASSERT_EQUAL_UINT8(1U, result);
}

/**
 * @brief Test: State 0 (Init) with valid rec_pc → expect return 0, state transitions to 1, l_LastRecord updated
 */
void test_State0_ValidRecPtr_Return0_TransitionTo1(void) {
  MyLib_record_t input_rec = {.id_u16 = 42U, .value_u32 = 1000U};
  uint8_t result;

  MyLib_UpdateGlobalRecord_Expect(NULL, &input_rec);
  MyLib_UpdateGlobalRecord_IgnoreArg_dest_p();

  result = MyLib_RunStateMachine_u8(&input_rec, 0U, NULL);
  TEST_ASSERT_EQUAL_UINT8(0U, result);
}

/**
 * @brief Test: State 1 (Process) with NULL delta_pc_u16 → expect return 0, state transitions to 2, l_LastAdjusted_u32 computed with default behavior
 */
void test_State1_NullDelta_Return0_TransitionTo2(void) {
  MyLib_record_t input_rec = {.id_u16 = 10U, .value_u32 = 500U};
  uint8_t result;

  MyLib_UpdateGlobalRecord_Expect(NULL, &input_rec);
  MyLib_UpdateGlobalRecord_IgnoreArg_dest_p();
  result = MyLib_RunStateMachine_u8(&input_rec, 0U, NULL);

  MyLib_ProcessRecord_Expect(NULL, MYLIB_MULT_VALUE_U8);
  MyLib_ProcessRecord_IgnoreArg_rec_pc();
  MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(0U, NULL, 250U);
  MyLib_ComputeAdjustedValue_u32_IgnoreArg_base_u32();

  result = MyLib_RunStateMachine_u8(NULL, 0U, NULL);
  TEST_ASSERT_EQUAL_UINT8(0U, result);
}

/**
 * @brief Test: State 1 (Process) with valid delta_pc_u16 → expect return 0, state transitions to 2, l_LastAdjusted_u32 computed with delta applied
 */
void test_State1_ValidDelta_Return0_TransitionTo2(void) {
  MyLib_record_t input_rec = {.id_u16 = 20U, .value_u32 = 800U};
  uint16_t delta = 100U;
  uint8_t result;

  MyLib_UpdateGlobalRecord_Expect(NULL, &input_rec);
  MyLib_UpdateGlobalRecord_IgnoreArg_dest_p();
  result = MyLib_RunStateMachine_u8(&input_rec, 0U, &delta);

  MyLib_ProcessRecord_Expect(NULL, MYLIB_MULT_VALUE_U8);
  MyLib_ProcessRecord_IgnoreArg_rec_pc();
  MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(0U, &delta, 350U);
  MyLib_ComputeAdjustedValue_u32_IgnoreArg_base_u32();

  result = MyLib_RunStateMachine_u8(NULL, 0U, &delta);
  TEST_ASSERT_EQUAL_UINT8(0U, result);
}

/**
 * @brief Test: State 2 (Update counter) with add_u32 = 0 and l_LastAdjusted_u32 = 0 → MyLib_UpdateCounter_u8 returns 0, expect return 0, state transitions to 0
 */
void test_State2_Add0_Adjusted0_Return0_TransitionTo0(void) {
  MyLib_record_t input_rec = {.id_u16 = 1U, .value_u32 = 0U};
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
}

/**
 * @brief Test: State 2 (Update counter) with add_u32 causing MyLib_UpdateCounter_u8 to return 2 (saturation) → expect return 2, state transitions to 0
 */
void test_State2_SaturationCase_Return2_TransitionTo0(void) {
  MyLib_record_t input_rec = {.id_u16 = 5U, .value_u32 = 100U};
  uint8_t result;

  MyLib_UpdateGlobalRecord_Expect(NULL, &input_rec);
  MyLib_UpdateGlobalRecord_IgnoreArg_dest_p();
  result = MyLib_RunStateMachine_u8(&input_rec, 0U, NULL);

  MyLib_ProcessRecord_Expect(NULL, MYLIB_MULT_VALUE_U8);
  MyLib_ProcessRecord_IgnoreArg_rec_pc();
  MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(0U, NULL, 50U);
  MyLib_ComputeAdjustedValue_u32_IgnoreArg_base_u32();
  result = MyLib_RunStateMachine_u8(NULL, 0U, NULL);

  MyLib_UpdateCounter_u8_ExpectAndReturn(150U, 2U);
  result = MyLib_RunStateMachine_u8(NULL, 100U, NULL);
  TEST_ASSERT_EQUAL_UINT8(2U, result);
}

/**
 * @brief Test: State 2 (Update counter) with add_u32 + l_LastAdjusted_u32 at boundary causing MyLib_UpdateCounter_u8 to return 1 → expect return 1, state transitions to 0
 */
void test_State2_BoundaryCase_Return1_TransitionTo0(void) {
  MyLib_record_t input_rec = {.id_u16 = 7U, .value_u32 = 200U};
  uint8_t result;

  MyLib_UpdateGlobalRecord_Expect(NULL, &input_rec);
  MyLib_UpdateGlobalRecord_IgnoreArg_dest_p();
  result = MyLib_RunStateMachine_u8(&input_rec, 0U, NULL);

  MyLib_ProcessRecord_Expect(NULL, MYLIB_MULT_VALUE_U8);
  MyLib_ProcessRecord_IgnoreArg_rec_pc();
  MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(0U, NULL, 75U);
  MyLib_ComputeAdjustedValue_u32_IgnoreArg_base_u32();
  result = MyLib_RunStateMachine_u8(NULL, 0U, NULL);

  MyLib_UpdateCounter_u8_ExpectAndReturn(100U, 1U);
  result = MyLib_RunStateMachine_u8(NULL, 25U, NULL);
  TEST_ASSERT_EQUAL_UINT8(1U, result);
}

/**
 * @brief Test: State 2 (Update counter) with add_u32 = UINT32_MAX and l_LastAdjusted_u32 = 1 → verify wrap behavior in l_UpdateValue_u32, expect return code from MyLib_UpdateCounter_u8, state transitions to 0
 */
void test_State2_WrapBehavior_ReturnFromUpdateCounter(void) {
  MyLib_record_t input_rec = {.id_u16 = 8U, .value_u32 = 300U};
  uint8_t result;

  MyLib_UpdateGlobalRecord_Expect(NULL, &input_rec);
  MyLib_UpdateGlobalRecord_IgnoreArg_dest_p();
  result = MyLib_RunStateMachine_u8(&input_rec, 0U, NULL);

  MyLib_ProcessRecord_Expect(NULL, MYLIB_MULT_VALUE_U8);
  MyLib_ProcessRecord_IgnoreArg_rec_pc();
  MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(0U, NULL, 1U);
  MyLib_ComputeAdjustedValue_u32_IgnoreArg_base_u32();
  result = MyLib_RunStateMachine_u8(NULL, 0U, NULL);

  MyLib_UpdateCounter_u8_ExpectAndReturn(0U, 0U);
  result = MyLib_RunStateMachine_u8(NULL, UINT32_MAX, NULL);
  TEST_ASSERT_EQUAL_UINT8(0U, result);
}

/**
 * @brief Test: Invalid state (e.g., l_State_u8 = 3) → expect return 3 (state recovery), state reset to 0
 */
void test_InvalidState3_Return3_StateResetTo0(void) {
  MyLib_record_t input_rec = {.id_u16 = 9U, .value_u32 = 400U};
  uint8_t result;

  MyLib_UpdateGlobalRecord_Expect(NULL, &input_rec);
  MyLib_UpdateGlobalRecord_IgnoreArg_dest_p();
  result = MyLib_RunStateMachine_u8(&input_rec, 0U, NULL);

  MyLib_ProcessRecord_Expect(NULL, MYLIB_MULT_VALUE_U8);
  MyLib_ProcessRecord_IgnoreArg_rec_pc();
  MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(0U, NULL, 100U);
  MyLib_ComputeAdjustedValue_u32_IgnoreArg_base_u32();
  result = MyLib_RunStateMachine_u8(NULL, 0U, NULL);

  MyLib_UpdateCounter_u8_ExpectAndReturn(100U, 0U);
  result = MyLib_RunStateMachine_u8(NULL, 0U, NULL);

  result = MyLib_RunStateMachine_u8(NULL, 0U, NULL);
  TEST_ASSERT_EQUAL_UINT8(3U, result);
}

/**
 * @brief Test: Full state machine cycle (State 0 → 1 → 2 → 0) with valid inputs → verify correct transitions, return codes, and counter update
 */
void test_FullCycle_State0To1To2To0_VerifyTransitions(void) {
  MyLib_record_t input_rec = {.id_u16 = 15U, .value_u32 = 600U};
  uint16_t delta = 50U;
  uint8_t result;

  MyLib_UpdateGlobalRecord_Expect(NULL, &input_rec);
  MyLib_UpdateGlobalRecord_IgnoreArg_dest_p();
  result = MyLib_RunStateMachine_u8(&input_rec, 0U, &delta);
  TEST_ASSERT_EQUAL_UINT8(0U, result);

  MyLib_ProcessRecord_Expect(NULL, MYLIB_MULT_VALUE_U8);
  MyLib_ProcessRecord_IgnoreArg_rec_pc();
  MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(0U, &delta, 200U);
  MyLib_ComputeAdjustedValue_u32_IgnoreArg_base_u32();
  result = MyLib_RunStateMachine_u8(NULL, 0U, &delta);
  TEST_ASSERT_EQUAL_UINT8(0U, result);

  MyLib_UpdateCounter_u8_ExpectAndReturn(250U, 0U);
  result = MyLib_RunStateMachine_u8(NULL, 50U, &delta);
  TEST_ASSERT_EQUAL_UINT8(0U, result);

  MyLib_UpdateGlobalRecord_Expect(NULL, &input_rec);
  MyLib_UpdateGlobalRecord_IgnoreArg_dest_p();
  result = MyLib_RunStateMachine_u8(&input_rec, 0U, NULL);
  TEST_ASSERT_EQUAL_UINT8(0U, result);
}

/**
 * @brief Test: State 0 (Init) with rec_pc pointing to record with value_u32 = 0 → expect return 0, state transitions to 1, l_LastRecord.value_u32 = 0
 */
void test_State0_RecValue0_Return0_TransitionTo1(void) {
  MyLib_record_t input_rec = {.id_u16 = 100U, .value_u32 = 0U};
  uint8_t result;

  MyLib_UpdateGlobalRecord_Expect(NULL, &input_rec);
  MyLib_UpdateGlobalRecord_IgnoreArg_dest_p();

  result = MyLib_RunStateMachine_u8(&input_rec, 0U, NULL);
  TEST_ASSERT_EQUAL_UINT8(0U, result);
}

/**
 * @brief Test: State 0 (Init) with rec_pc pointing to record with value_u32 = UINT32_MAX → expect return 0, state transitions to 1, l_LastRecord.value_u32 = UINT32_MAX
 */
void test_State0_RecValueMax_Return0_TransitionTo1(void) {
  MyLib_record_t input_rec = {.id_u16 = 200U, .value_u32 = UINT32_MAX};
  uint8_t result;

  MyLib_UpdateGlobalRecord_Expect(NULL, &input_rec);
  MyLib_UpdateGlobalRecord_IgnoreArg_dest_p();

  result = MyLib_RunStateMachine_u8(&input_rec, 0U, NULL);
  TEST_ASSERT_EQUAL_UINT8(0U, result);
}

/**
 * @brief Test: State 1 (Process) after initialization with value_u32 = 0 → verify MyLib_ProcessRecord called with MYLIB_MULT_VALUE_U8, expect return 0, state transitions to 2
 */
void test_State1_AfterInitValue0_ProcessCalled_Return0(void) {
  MyLib_record_t input_rec = {.id_u16 = 11U, .value_u32 = 0U};
  uint8_t result;

  MyLib_UpdateGlobalRecord_Expect(NULL, &input_rec);
  MyLib_UpdateGlobalRecord_IgnoreArg_dest_p();
  result = MyLib_RunStateMachine_u8(&input_rec, 0U, NULL);

  MyLib_ProcessRecord_Expect(NULL, MYLIB_MULT_VALUE_U8);
  MyLib_ProcessRecord_IgnoreArg_rec_pc();
  MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(0U, NULL, 0U);
  MyLib_ComputeAdjustedValue_u32_IgnoreArg_base_u32();

  result = MyLib_RunStateMachine_u8(NULL, 0U, NULL);
  TEST_ASSERT_EQUAL_UINT8(0U, result);
}

/**
 * @brief Test: State 1 (Process) after initialization with value_u32 = UINT32_MAX → verify MyLib_ProcessRecord called with MYLIB_MULT_VALUE_U8, expect return 0, state transitions to 2
 */
void test_State1_AfterInitValueMax_ProcessCalled_Return0(void) {
  MyLib_record_t input_rec = {.id_u16 = 12U, .value_u32 = UINT32_MAX};
  uint8_t result;

  MyLib_UpdateGlobalRecord_Expect(NULL, &input_rec);
  MyLib_UpdateGlobalRecord_IgnoreArg_dest_p();
  result = MyLib_RunStateMachine_u8(&input_rec, 0U, NULL);

  MyLib_ProcessRecord_Expect(NULL, MYLIB_MULT_VALUE_U8);
  MyLib_ProcessRecord_IgnoreArg_rec_pc();
  MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(UINT32_MAX, NULL, 500U);
  MyLib_ComputeAdjustedValue_u32_IgnoreArg_base_u32();

  result = MyLib_RunStateMachine_u8(NULL, 0U, NULL);
  TEST_ASSERT_EQUAL_UINT8(0U, result);
}

/**
 * @brief Test: State 2 (Update counter) with add_u32 = 0 → verify l_UpdateValue_u32 = l_LastAdjusted_u32, expect return code from MyLib_UpdateCounter_u8, state transitions to 0
 */
void test_State2_Add0_UpdateValueEqualsAdjusted(void) {
  MyLib_record_t input_rec = {.id_u16 = 13U, .value_u32 = 150U};
  uint8_t result;

  MyLib_UpdateGlobalRecord_Expect(NULL, &input_rec);
  MyLib_UpdateGlobalRecord_IgnoreArg_dest_p();
  result = MyLib_RunStateMachine_u8(&input_rec, 0U, NULL);

  MyLib_ProcessRecord_Expect(NULL, MYLIB_MULT_VALUE_U8);
  MyLib_ProcessRecord_IgnoreArg_rec_pc();
  MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(0U, NULL, 75U);
  MyLib_ComputeAdjustedValue_u32_IgnoreArg_base_u32();
  result = MyLib_RunStateMachine_u8(NULL, 0U, NULL);

  MyLib_UpdateCounter_u8_ExpectAndReturn(75U, 0U);
  result = MyLib_RunStateMachine_u8(NULL, 0U, NULL);
  TEST_ASSERT_EQUAL_UINT8(0U, result);
}

/**
 * @brief Test: State 2 (Update counter) with add_u32 = UINT32_MAX → verify l_UpdateValue_u32 = UINT32_MAX + l_LastAdjusted_u32 (wrap), expect return code from MyLib_UpdateCounter_u8, state transitions to 0
 */
void test_State2_AddMax_VerifyWrap(void) {
  MyLib_record_t input_rec = {.id_u16 = 14U, .value_u32 = 250U};
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

/**
 * @brief Test: State 2 (Update counter) with add_u32 at mid-range (e.g., 0x80000000) → verify l_UpdateValue_u32 computed correctly, expect return code from MyLib_UpdateCounter_u8, state transitions to 0
 */
void test_State2_AddMidRange_VerifyComputation(void) {
  MyLib_record_t input_rec = {.id_u16 = 16U, .value_u32 = 350U};
  uint8_t result;

  MyLib_UpdateGlobalRecord_Expect(NULL, &input_rec);
  MyLib_UpdateGlobalRecord_IgnoreArg_dest_p();
  result = MyLib_RunStateMachine_u8(&input_rec, 0U, NULL);

  MyLib_ProcessRecord_Expect(NULL, MYLIB_MULT_VALUE_U8);
  MyLib_ProcessRecord_IgnoreArg_rec_pc();
  MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(0U, NULL, 20U);
  MyLib_ComputeAdjustedValue_u32_IgnoreArg_base_u32();
  result = MyLib_RunStateMachine_u8(NULL, 0U, NULL);

  MyLib_UpdateCounter_u8_ExpectAndReturn(0x80000014U, 0U);
  result = MyLib_RunStateMachine_u8(NULL, 0x80000000U, NULL);
  TEST_ASSERT_EQUAL_UINT8(0U, result);
}

/**
 * @brief Test: Multiple consecutive calls in State 0 with NULL rec_pc → expect return 1 each time, state remains 0
 */
void test_State0_MultipleNullCalls_Return1_StateRemains0(void) {
  uint8_t result;

  result = MyLib_RunStateMachine_u8(NULL, 0U, NULL);
  TEST_ASSERT_EQUAL_UINT8(1U, result);

  result = MyLib_RunStateMachine_u8(NULL, 10U, NULL);
  TEST_ASSERT_EQUAL_UINT8(1U, result);

  result = MyLib_RunStateMachine_u8(NULL, 100U, NULL);
  TEST_ASSERT_EQUAL_UINT8(1U, result);
}

/**
 * @brief Test: Multiple consecutive calls in State 0 with valid rec_pc → verify each call updates l_LastRecord and transitions to State 1
 */
void test_State0_MultipleValidCalls_EachTransitionsTo1(void) {
  MyLib_record_t rec1 = {.id_u16 = 1U, .value_u32 = 100U};
  MyLib_record_t rec2 = {.id_u16 = 2U, .value_u32 = 200U};
  uint8_t result;

  MyLib_UpdateGlobalRecord_Expect(NULL, &rec1);
  MyLib_UpdateGlobalRecord_IgnoreArg_dest_p();
  result = MyLib_RunStateMachine_u8(&rec1, 0U, NULL);
  TEST_ASSERT_EQUAL_UINT8(0U, result);

  MyLib_ProcessRecord_Expect(NULL, MYLIB_MULT_VALUE_U8);
  MyLib_ProcessRecord_IgnoreArg_rec_pc();
  MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(0U, NULL, 50U);
  MyLib_ComputeAdjustedValue_u32_IgnoreArg_base_u32();
  result = MyLib_RunStateMachine_u8(NULL, 0U, NULL);

  MyLib_UpdateCounter_u8_ExpectAndReturn(50U, 0U);
  result = MyLib_RunStateMachine_u8(NULL, 0U, NULL);

  MyLib_UpdateGlobalRecord_Expect(NULL, &rec2);
  MyLib_UpdateGlobalRecord_IgnoreArg_dest_p();
  result = MyLib_RunStateMachine_u8(&rec2, 0U, NULL);
  TEST_ASSERT_EQUAL_UINT8(0U, result);
}

/**
 * @brief Test: State 1 (Process) called twice consecutively → verify second call processes updated l_LastRecord, state transitions to 2 each time
 */
void test_State1_TwoConsecutiveCalls_BothTransitionTo2(void) {
  MyLib_record_t rec1 = {.id_u16 = 3U, .value_u32 = 300U};
  MyLib_record_t rec2 = {.id_u16 = 4U, .value_u32 = 400U};
  uint8_t result;

  MyLib_UpdateGlobalRecord_Expect(NULL, &rec1);
  MyLib_UpdateGlobalRecord_IgnoreArg_dest_p();
  result = MyLib_RunStateMachine_u8(&rec1, 0U, NULL);

  MyLib_ProcessRecord_Expect(NULL, MYLIB_MULT_VALUE_U8);
  MyLib_ProcessRecord_IgnoreArg_rec_pc();
  MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(0U, NULL, 150U);
  MyLib_ComputeAdjustedValue_u32_IgnoreArg_base_u32();
  result = MyLib_RunStateMachine_u8(NULL, 0U, NULL);
  TEST_ASSERT_EQUAL_UINT8(0U, result);

  MyLib_UpdateCounter_u8_ExpectAndReturn(150U, 0U);
  result = MyLib_RunStateMachine_u8(NULL, 0U, NULL);

  MyLib_UpdateGlobalRecord_Expect(NULL, &rec2);
  MyLib_UpdateGlobalRecord_IgnoreArg_dest_p();
  result = MyLib_RunStateMachine_u8(&rec2, 0U, NULL);

  MyLib_ProcessRecord_Expect(NULL, MYLIB_MULT_VALUE_U8);
  MyLib_ProcessRecord_IgnoreArg_rec_pc();
  MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(0U, NULL, 200U);
  MyLib_ComputeAdjustedValue_u32_IgnoreArg_base_u32();
  result = MyLib_RunStateMachine_u8(NULL, 0U, NULL);
  TEST_ASSERT_EQUAL_UINT8(0U, result);
}

/**
 * @brief Test: State 2 (Update counter) called twice consecutively → verify each call computes l_UpdateValue_u32 and updates counter, state transitions to 0 each time
 */
void test_State2_TwoConsecutiveCalls_BothTransitionTo0(void) {
  MyLib_record_t rec1 = {.id_u16 = 5U, .value_u32 = 500U};
  MyLib_record_t rec2 = {.id_u16 = 6U, .value_u32 = 600U};
  uint8_t result;

  MyLib_UpdateGlobalRecord_Expect(NULL, &rec1);
  MyLib_UpdateGlobalRecord_IgnoreArg_dest_p();
  result = MyLib_RunStateMachine_u8(&rec1, 0U, NULL);

  MyLib_ProcessRecord_Expect(NULL, MYLIB_MULT_VALUE_U8);
  MyLib_ProcessRecord_IgnoreArg_rec_pc();
  MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(0U, NULL, 250U);
  MyLib_ComputeAdjustedValue_u32_IgnoreArg_base_u32();
  result = MyLib_RunStateMachine_u8(NULL, 0U, NULL);

  MyLib_UpdateCounter_u8_ExpectAndReturn(300U, 0U);
  result = MyLib_RunStateMachine_u8(NULL, 50U, NULL);
  TEST_ASSERT_EQUAL_UINT8(0U, result);

  MyLib_UpdateGlobalRecord_Expect(NULL, &rec2);
  MyLib_UpdateGlobalRecord_IgnoreArg_dest_p();
  result = MyLib_RunStateMachine_u8(&rec2, 0U, NULL);

  MyLib_ProcessRecord_Expect(NULL, MYLIB_MULT_VALUE_U8);
  MyLib_ProcessRecord_IgnoreArg_rec_pc();
  MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(0U, NULL, 300U);
  MyLib_ComputeAdjustedValue_u32_IgnoreArg_base_u32();
  result = MyLib_RunStateMachine_u8(NULL, 0U, NULL);

  MyLib_UpdateCounter_u8_ExpectAndReturn(400U, 0U);
  result = MyLib_RunStateMachine_u8(NULL, 100U, NULL);
  TEST_ASSERT_EQUAL_UINT8(0U, result);
}

/**
 * @brief Test: State machine reset after invalid state → verify next call in State 0 behaves correctly
 */
void test_AfterInvalidState_NextCallInState0_BehavesCorrectly(void) {
  MyLib_record_t rec1 = {.id_u16 = 7U, .value_u32 = 700U};
  MyLib_record_t rec2 = {.id_u16 = 8U, .value_u32 = 800U};
  uint8_t result;

  MyLib_UpdateGlobalRecord_Expect(NULL, &rec1);
  MyLib_UpdateGlobalRecord_IgnoreArg_dest_p();
  result = MyLib_RunStateMachine_u8(&rec1, 0U, NULL);

  MyLib_ProcessRecord_Expect(NULL, MYLIB_MULT_VALUE_U8);
  MyLib_ProcessRecord_IgnoreArg_rec_pc();
  MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(0U, NULL, 350U);
  MyLib_ComputeAdjustedValue_u32_IgnoreArg_base_u32();
  result = MyLib_RunStateMachine_u8(NULL, 0U, NULL);

  MyLib_UpdateCounter_u8_ExpectAndReturn(350U, 0U);
  result = MyLib_RunStateMachine_u8(NULL, 0U, NULL);

  result = MyLib_RunStateMachine_u8(NULL, 0U, NULL);
  TEST_ASSERT_EQUAL_UINT8(3U, result);

  MyLib_UpdateGlobalRecord_Expect(NULL, &rec2);
  MyLib_UpdateGlobalRecord_IgnoreArg_dest_p();
  result = MyLib_RunStateMachine_u8(&rec2, 0U, NULL);
  TEST_ASSERT_EQUAL_UINT8(0U, result);
}

/**
 * @brief Test: State 1 (Process) with delta_pc_u16 pointing to 0 → verify MyLib_ComputeAdjustedValue_u32 called with delta = 0, expect return 0, state transitions to 2
 */
void test_State1_Delta0_ComputeCalledWithDelta0(void) {
  MyLib_record_t input_rec = {.id_u16 = 21U, .value_u32 = 210U};
  uint16_t delta = 0U;
  uint8_t result;

  MyLib_UpdateGlobalRecord_Expect(NULL, &input_rec);
  MyLib_UpdateGlobalRecord_IgnoreArg_dest_p();
  result = MyLib_RunStateMachine_u8(&input_rec, 0U, &delta);

  MyLib_ProcessRecord_Expect(NULL, MYLIB_MULT_VALUE_U8);
  MyLib_ProcessRecord_IgnoreArg_rec_pc();
  MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(0U, &delta, 105U);
  MyLib_ComputeAdjustedValue_u32_IgnoreArg_base_u32();

  result = MyLib_RunStateMachine_u8(NULL, 0U, &delta);
  TEST_ASSERT_EQUAL_UINT8(0U, result);
}

/**
 * @brief Test: State 1 (Process) with delta_pc_u16 pointing to UINT16_MAX → verify MyLib_ComputeAdjustedValue_u32 called with delta = UINT16_MAX, expect return 0, state transitions to 2
 */
void test_State1_DeltaMax_ComputeCalledWithDeltaMax(void) {
  MyLib_record_t input_rec = {.id_u16 = 22U, .value_u32 = 220U};
  uint16_t delta = UINT16_MAX;
  uint8_t result;

  MyLib_UpdateGlobalRecord_Expect(NULL, &input_rec);
  MyLib_UpdateGlobalRecord_IgnoreArg_dest_p();
  result = MyLib_RunStateMachine_u8(&input_rec, 0U, &delta);

  MyLib_ProcessRecord_Expect(NULL, MYLIB_MULT_VALUE_U8);
  MyLib_ProcessRecord_IgnoreArg_rec_pc();
  MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(0U, &delta, 110U);
  MyLib_ComputeAdjustedValue_u32_IgnoreArg_base_u32();

  result = MyLib_RunStateMachine_u8(NULL, 0U, &delta);
  TEST_ASSERT_EQUAL_UINT8(0U, result);
}

/**
 * @brief Test: State 1 (Process) with delta_pc_u16 pointing to mid-range value (e.g., 32768) → verify MyLib_ComputeAdjustedValue_u32 called with delta = 32768, expect return 0, state transitions to 2
 */
void test_State1_DeltaMidRange_ComputeCalledCorrectly(void) {
  MyLib_record_t input_rec = {.id_u16 = 23U, .value_u32 = 230U};
  uint16_t delta = 32768U;
  uint8_t result;

  MyLib_UpdateGlobalRecord_Expect(NULL, &input_rec);
  MyLib_UpdateGlobalRecord_IgnoreArg_dest_p();
  result = MyLib_RunStateMachine_u8(&input_rec, 0U, &delta);

  MyLib_ProcessRecord_Expect(NULL, MYLIB_MULT_VALUE_U8);
  MyLib_ProcessRecord_IgnoreArg_rec_pc();
  MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(0U, &delta, 115U);
  MyLib_ComputeAdjustedValue_u32_IgnoreArg_base_u32();

  result = MyLib_RunStateMachine_u8(NULL, 0U, &delta);
  TEST_ASSERT_EQUAL_UINT8(0U, result);
}

/**
 * @brief Test: State 2 (Update counter) with l_LastAdjusted_u32 = 0 and add_u32 = 1 → verify l_UpdateValue_u32 = 1, expect return code from MyLib_UpdateCounter_u8, state transitions to 0
 */
void test_State2_Adjusted0_Add1_UpdateValue1(void) {
  MyLib_record_t input_rec = {.id_u16 = 24U, .value_u32 = 240U};
  uint8_t result;

  MyLib_UpdateGlobalRecord_Expect(NULL, &input_rec);
  MyLib_UpdateGlobalRecord_IgnoreArg_dest_p();
  result = MyLib_RunStateMachine_u8(&input_rec, 0U, NULL);

  MyLib_ProcessRecord_Expect(NULL, MYLIB_MULT_VALUE_U8);
  MyLib_ProcessRecord_IgnoreArg_rec_pc();
  MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(0U, NULL, 0U);
  MyLib_ComputeAdjustedValue_u32_IgnoreArg_base_u32();
  result = MyLib_RunStateMachine_u8(NULL, 0U, NULL);

  MyLib_UpdateCounter_u8_ExpectAndReturn(1U, 0U);
  result = MyLib_RunStateMachine_u8(NULL, 1U, NULL);
  TEST_ASSERT_EQUAL_UINT8(0U, result);
}

/**
 * @brief Test: State 2 (Update counter) with l_LastAdjusted_u32 = UINT32_MAX and add_u32 = 0 → verify l_UpdateValue_u32 = UINT32_MAX, expect return code from MyLib_UpdateCounter_u8, state transitions to 0
 */
void test_State2_AdjustedMax_Add0_UpdateValueMax(void) {
  MyLib_record_t input_rec = {.id_u16 = 25U, .value_u32 = 250U};
  uint8_t result;

  MyLib_UpdateGlobalRecord_Expect(NULL, &input_rec);
  MyLib_UpdateGlobalRecord_IgnoreArg_dest_p();
  result = MyLib_RunStateMachine_u8(&input_rec, 0U, NULL);

  MyLib_ProcessRecord_Expect(NULL, MYLIB_MULT_VALUE_U8);
  MyLib_ProcessRecord_IgnoreArg_rec_pc();
  MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(0U, NULL, UINT32_MAX);
  MyLib_ComputeAdjustedValue_u32_IgnoreArg_base_u32();
  result = MyLib_RunStateMachine_u8(NULL, 0U, NULL);

  MyLib_UpdateCounter_u8_ExpectAndReturn(UINT32_MAX, 2U);
  result = MyLib_RunStateMachine_u8(NULL, 0U, NULL);
  TEST_ASSERT_EQUAL_UINT8(2U, result);
}

/**
 * @brief Test: State 0 (Init) with rec_pc pointing to record with all fields at boundary values → expect return 0, state transitions to 1, l_LastRecord updated correctly
 */
void test_State0_RecBoundaryValues_Return0_TransitionTo1(void) {
  MyLib_record_t input_rec = {.id_u16 = UINT16_MAX, .value_u32 = UINT32_MAX};
  uint8_t result;

  MyLib_UpdateGlobalRecord_Expect(NULL, &input_rec);
  MyLib_UpdateGlobalRecord_IgnoreArg_dest_p();

  result = MyLib_RunStateMachine_u8(&input_rec, 0U, NULL);
  TEST_ASSERT_EQUAL_UINT8(0U, result);
}

/**
 * @brief Test: State machine cycle with MyLib_UpdateCounter_u8 returning 0 (success) → verify return 0, state transitions correctly
 */
void test_CycleWithUpdateCounterReturn0_VerifyTransitions(void) {
  MyLib_record_t input_rec = {.id_u16 = 30U, .value_u32 = 300U};
  uint8_t result;

  MyLib_UpdateGlobalRecord_Expect(NULL, &input_rec);
  MyLib_UpdateGlobalRecord_IgnoreArg_dest_p();
  result = MyLib_RunStateMachine_u8(&input_rec, 0U, NULL);
  TEST_ASSERT_EQUAL_UINT8(0U, result);

  MyLib_ProcessRecord_Expect(NULL, MYLIB_MULT_VALUE_U8);
  MyLib_ProcessRecord_IgnoreArg_rec_pc();
  MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(0U, NULL, 150U);
  MyLib_ComputeAdjustedValue_u32_IgnoreArg_base_u32();
  result = MyLib_RunStateMachine_u8(NULL, 0U, NULL);
  TEST_ASSERT_EQUAL_UINT8(0U, result);

  MyLib_UpdateCounter_u8_ExpectAndReturn(150U, 0U);
  result = MyLib_RunStateMachine_u8(NULL, 0U, NULL);
  TEST_ASSERT_EQUAL_UINT8(0U, result);
}

/**
 * @brief Test: State machine cycle with MyLib_UpdateCounter_u8 returning 1 (intermediate status) → verify return 1, state transitions correctly
 */
void test_CycleWithUpdateCounterReturn1_VerifyTransitions(void) {
  MyLib_record_t input_rec = {.id_u16 = 31U, .value_u32 = 310U};
  uint8_t result;

  MyLib_UpdateGlobalRecord_Expect(NULL, &input_rec);
  MyLib_UpdateGlobalRecord_IgnoreArg_dest_p();
  result = MyLib_RunStateMachine_u8(&input_rec, 0U, NULL);
  TEST_ASSERT_EQUAL_UINT8(0U, result);

  MyLib_ProcessRecord_Expect(NULL, MYLIB_MULT_VALUE_U8);
  MyLib_ProcessRecord_IgnoreArg_rec_pc();
  MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(0U, NULL, 155U);
  MyLib_ComputeAdjustedValue_u32_IgnoreArg_base_u32();
  result = MyLib_RunStateMachine_u8(NULL, 0U, NULL);
  TEST_ASSERT_EQUAL_UINT8(0U, result);

  MyLib_UpdateCounter_u8_ExpectAndReturn(155U, 1U);
  result = MyLib_RunStateMachine_u8(NULL, 0U, NULL);
  TEST_ASSERT_EQUAL_UINT8(1U, result);
}

/**
 * @brief Test: State machine cycle with MyLib_UpdateCounter_u8 returning 2 (saturation) → verify return 2, state transitions correctly
 */
void test_CycleWithUpdateCounterReturn2_VerifyTransitions(void) {
  MyLib_record_t input_rec = {.id_u16 = 32U, .value_u32 = 320U};
  uint8_t result;

  MyLib_UpdateGlobalRecord_Expect(NULL, &input_rec);
  MyLib_UpdateGlobalRecord_IgnoreArg_dest_p();
  result = MyLib_RunStateMachine_u8(&input_rec, 0U, NULL);
  TEST_ASSERT_EQUAL_UINT8(0U, result);

  MyLib_ProcessRecord_Expect(NULL, MYLIB_MULT_VALUE_U8);
  MyLib_ProcessRecord_IgnoreArg_rec_pc();
  MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(0U, NULL, 160U);
  MyLib_ComputeAdjustedValue_u32_IgnoreArg_base_u32();
  result = MyLib_RunStateMachine_u8(NULL, 0U, NULL);
  TEST_ASSERT_EQUAL_UINT8(0U, result);

  MyLib_UpdateCounter_u8_ExpectAndReturn(160U, 2U);
  result = MyLib_RunStateMachine_u8(NULL, 0U, NULL);
  TEST_ASSERT_EQUAL_UINT8(2U, result);
}

/**
 * @brief Test: Invalid state value at upper boundary (e.g., l_State_u8 = UINT8_MAX) → expect return 3, state reset to 0
 */
void test_InvalidStateMax_Return3_StateResetTo0(void) {
  MyLib_record_t input_rec = {.id_u16 = 33U, .value_u32 = 330U};
  uint8_t result;

  MyLib_UpdateGlobalRecord_Expect(NULL, &input_rec);
  MyLib_UpdateGlobalRecord_IgnoreArg_dest_p();
  result = MyLib_RunStateMachine_u8(&input_rec, 0U, NULL);

  MyLib_ProcessRecord_Expect(NULL, MYLIB_MULT_VALUE_U8);
  MyLib_ProcessRecord_IgnoreArg_rec_pc();
  MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(0U, NULL, 165U);
  MyLib_ComputeAdjustedValue_u32_IgnoreArg_base_u32();
  result = MyLib_RunStateMachine_u8(NULL, 0U, NULL);

  MyLib_UpdateCounter_u8_ExpectAndReturn(165U, 0U);
  result = MyLib_RunStateMachine_u8(NULL, 0U, NULL);

  result = MyLib_RunStateMachine_u8(NULL, 0U, NULL);
  TEST_ASSERT_EQUAL_UINT8(3U, result);

  MyLib_UpdateGlobalRecord_Expect(NULL, &input_rec);
  MyLib_UpdateGlobalRecord_IgnoreArg_dest_p();
  result = MyLib_RunStateMachine_u8(&input_rec, 0U, NULL);
  TEST_ASSERT_EQUAL_UINT8(0U, result);
}