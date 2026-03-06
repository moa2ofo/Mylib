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
void test_State0_Init_NullRecPtr_Returns1_StateRemains0(void) {
  uint8_t result;

  result = MyLib_RunStateMachine_u8(NULL, 0U, NULL);

  TEST_ASSERT_EQUAL_UINT8(1U, result);

  result = MyLib_RunStateMachine_u8(NULL, 0U, NULL);
  TEST_ASSERT_EQUAL_UINT8(1U, result);
}

/**
 * @brief Test: State 0 (Init) with valid rec_pc → expect return 0, state transitions to 1, l_LastRecord updated
 */
void test_State0_Init_ValidRecPtr_Returns0_StateTransitionsTo1(void) {
  MyLib_record_t input_rec = {123U, 456U};
  MyLib_record_t expected_rec = {123U, 456U};
  uint8_t result;

  MyLib_UpdateGlobalRecord_Expect(NULL, &input_rec);
  MyLib_UpdateGlobalRecord_IgnoreArg_dest_p();

  result = MyLib_RunStateMachine_u8(&input_rec, 0U, NULL);

  TEST_ASSERT_EQUAL_UINT8(0U, result);
}

/**
 * @brief Test: State 1 (Process) with delta_pc_u16 = NULL → expect return 0, state transitions to 2, l_LastAdjusted_u32 computed with default behavior
 */
void test_State1_Process_NullDelta_Returns0_StateTransitionsTo2(void) {
  MyLib_record_t input_rec = {100U, 200U};
  uint8_t result;

  MyLib_UpdateGlobalRecord_Expect(NULL, &input_rec);
  MyLib_UpdateGlobalRecord_IgnoreArg_dest_p();
  result = MyLib_RunStateMachine_u8(&input_rec, 0U, NULL);
  TEST_ASSERT_EQUAL_UINT8(0U, result);

  MyLib_ProcessRecord_Expect(NULL, MYLIB_MULT_VALUE_U8);
  MyLib_ProcessRecord_IgnoreArg_rec_pc();
  MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(0U, NULL, 500U);
  MyLib_ComputeAdjustedValue_u32_IgnoreArg_base_u32();

  result = MyLib_RunStateMachine_u8(NULL, 0U, NULL);

  TEST_ASSERT_EQUAL_UINT8(0U, result);
}

/**
 * @brief Test: State 1 (Process) with valid delta_pc_u16 → expect return 0, state transitions to 2, l_LastAdjusted_u32 computed with delta applied
 */
void test_State1_Process_ValidDelta_Returns0_StateTransitionsTo2(void) {
  MyLib_record_t input_rec = {100U, 200U};
  uint16_t delta = 50U;
  uint8_t result;

  MyLib_UpdateGlobalRecord_Expect(NULL, &input_rec);
  MyLib_UpdateGlobalRecord_IgnoreArg_dest_p();
  result = MyLib_RunStateMachine_u8(&input_rec, 0U, NULL);
  TEST_ASSERT_EQUAL_UINT8(0U, result);

  MyLib_ProcessRecord_Expect(NULL, MYLIB_MULT_VALUE_U8);
  MyLib_ProcessRecord_IgnoreArg_rec_pc();
  MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(0U, &delta, 750U);
  MyLib_ComputeAdjustedValue_u32_IgnoreArg_base_u32();

  result = MyLib_RunStateMachine_u8(NULL, 0U, &delta);

  TEST_ASSERT_EQUAL_UINT8(0U, result);
}

/**
 * @brief Test: State 2 (Update counter) with add_u32 = 0 and l_LastAdjusted_u32 = 0 → MyLib_UpdateCounter_u8 returns 0, expect return 0, state transitions to 0
 */
void test_State2_UpdateCounter_AddZero_AdjustedZero_Returns0_StateTransitionsTo0(void) {
  MyLib_record_t input_rec = {100U, 200U};
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
 * @brief Test: State 2 (Update counter) with add_u32 at boundary causing no saturation → MyLib_UpdateCounter_u8 returns 0, expect return 0, state transitions to 0
 */
void test_State2_UpdateCounter_BoundaryNoSaturation_Returns0_StateTransitionsTo0(void) {
  MyLib_record_t input_rec = {100U, 200U};
  uint8_t result;

  MyLib_UpdateGlobalRecord_Expect(NULL, &input_rec);
  MyLib_UpdateGlobalRecord_IgnoreArg_dest_p();
  result = MyLib_RunStateMachine_u8(&input_rec, 0U, NULL);

  MyLib_ProcessRecord_Expect(NULL, MYLIB_MULT_VALUE_U8);
  MyLib_ProcessRecord_IgnoreArg_rec_pc();
  MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(0U, NULL, 50U);
  MyLib_ComputeAdjustedValue_u32_IgnoreArg_base_u32();
  result = MyLib_RunStateMachine_u8(NULL, 0U, NULL);

  MyLib_UpdateCounter_u8_ExpectAndReturn(100U, 0U);

  result = MyLib_RunStateMachine_u8(NULL, 50U, NULL);

  TEST_ASSERT_EQUAL_UINT8(0U, result);
}

/**
 * @brief Test: State 2 (Update counter) with add_u32 + l_LastAdjusted_u32 causing saturation → MyLib_UpdateCounter_u8 returns 2, expect return 2, state transitions to 0
 */
void test_State2_UpdateCounter_Saturation_Returns2_StateTransitionsTo0(void) {
  MyLib_record_t input_rec = {100U, 200U};
  uint8_t result;

  MyLib_UpdateGlobalRecord_Expect(NULL, &input_rec);
  MyLib_UpdateGlobalRecord_IgnoreArg_dest_p();
  result = MyLib_RunStateMachine_u8(&input_rec, 0U, NULL);

  MyLib_ProcessRecord_Expect(NULL, MYLIB_MULT_VALUE_U8);
  MyLib_ProcessRecord_IgnoreArg_rec_pc();
  MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(0U, NULL, 1000U);
  MyLib_ComputeAdjustedValue_u32_IgnoreArg_base_u32();
  result = MyLib_RunStateMachine_u8(NULL, 0U, NULL);

  MyLib_UpdateCounter_u8_ExpectAndReturn(2000U, 2U);

  result = MyLib_RunStateMachine_u8(NULL, 1000U, NULL);

  TEST_ASSERT_EQUAL_UINT8(2U, result);
}

/**
 * @brief Test: State 2 (Update counter) with add_u32 = UINT32_MAX and l_LastAdjusted_u32 = UINT32_MAX (wraparound) → MyLib_UpdateCounter_u8 processes wrapped value, expect return matches UpdateCounter result, state transitions to 0
 */
void test_State2_UpdateCounter_Wraparound_ReturnsUpdateCounterResult_StateTransitionsTo0(void) {
  MyLib_record_t input_rec = {100U, 200U};
  uint8_t result;

  MyLib_UpdateGlobalRecord_Expect(NULL, &input_rec);
  MyLib_UpdateGlobalRecord_IgnoreArg_dest_p();
  result = MyLib_RunStateMachine_u8(&input_rec, 0U, NULL);

  MyLib_ProcessRecord_Expect(NULL, MYLIB_MULT_VALUE_U8);
  MyLib_ProcessRecord_IgnoreArg_rec_pc();
  MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(0U, NULL, UINT32_MAX);
  MyLib_ComputeAdjustedValue_u32_IgnoreArg_base_u32();
  result = MyLib_RunStateMachine_u8(NULL, 0U, NULL);

  MyLib_UpdateCounter_u8_ExpectAndReturn(UINT32_MAX - 1U, 1U);

  result = MyLib_RunStateMachine_u8(NULL, UINT32_MAX, NULL);

  TEST_ASSERT_EQUAL_UINT8(1U, result);
}

/**
 * @brief Test: Invalid state (e.g., state = 3) → expect return 3, state reset to 0, l_LastAdjusted_u32 reset to 0
 */
void test_InvalidState3_Returns3_StateResetTo0_AdjustedResetTo0(void) {
  MyLib_record_t input_rec = {100U, 200U};
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
 * @brief Test: Invalid state (e.g., state = 255) → expect return 3, state reset to 0, l_LastAdjusted_u32 reset to 0
 */
void test_InvalidState255_Returns3_StateResetTo0_AdjustedResetTo0(void) {
  MyLib_record_t input_rec = {100U, 200U};
  uint8_t result;
  int i;

  MyLib_UpdateGlobalRecord_Expect(NULL, &input_rec);
  MyLib_UpdateGlobalRecord_IgnoreArg_dest_p();
  result = MyLib_RunStateMachine_u8(&input_rec, 0U, NULL);

  for(i = 0; i < 254; i++) {
    result = MyLib_RunStateMachine_u8(NULL, 0U, NULL);
  }

  TEST_ASSERT_EQUAL_UINT8(3U, result);
}

/**
 * @brief Test: Full valid sequence Init(valid rec_pc) → Process(valid delta) → Update(no saturation) → expect returns 0, 0, 0 and state cycles 0→1→2→0
 */
void test_FullSequence_InitProcessUpdate_NoSaturation_Returns000_StateCycles0to1to2to0(void) {
  MyLib_record_t input_rec = {100U, 200U};
  uint16_t delta = 25U;
  uint8_t result;

  MyLib_UpdateGlobalRecord_Expect(NULL, &input_rec);
  MyLib_UpdateGlobalRecord_IgnoreArg_dest_p();
  result = MyLib_RunStateMachine_u8(&input_rec, 0U, NULL);
  TEST_ASSERT_EQUAL_UINT8(0U, result);

  MyLib_ProcessRecord_Expect(NULL, MYLIB_MULT_VALUE_U8);
  MyLib_ProcessRecord_IgnoreArg_rec_pc();
  MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(0U, &delta, 300U);
  MyLib_ComputeAdjustedValue_u32_IgnoreArg_base_u32();
  result = MyLib_RunStateMachine_u8(NULL, 0U, &delta);
  TEST_ASSERT_EQUAL_UINT8(0U, result);

  MyLib_UpdateCounter_u8_ExpectAndReturn(350U, 0U);
  result = MyLib_RunStateMachine_u8(NULL, 50U, NULL);
  TEST_ASSERT_EQUAL_UINT8(0U, result);
}

/**
 * @brief Test: Full valid sequence Init(valid rec_pc) → Process(NULL delta) → Update(saturation) → expect returns 0, 0, 2 and state cycles 0→1→2→0
 */
void test_FullSequence_InitProcessUpdate_Saturation_Returns002_StateCycles0to1to2to0(void) {
  MyLib_record_t input_rec = {100U, 200U};
  uint8_t result;

  MyLib_UpdateGlobalRecord_Expect(NULL, &input_rec);
  MyLib_UpdateGlobalRecord_IgnoreArg_dest_p();
  result = MyLib_RunStateMachine_u8(&input_rec, 0U, NULL);
  TEST_ASSERT_EQUAL_UINT8(0U, result);

  MyLib_ProcessRecord_Expect(NULL, MYLIB_MULT_VALUE_U8);
  MyLib_ProcessRecord_IgnoreArg_rec_pc();
  MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(0U, NULL, 500U);
  MyLib_ComputeAdjustedValue_u32_IgnoreArg_base_u32();
  result = MyLib_RunStateMachine_u8(NULL, 0U, NULL);
  TEST_ASSERT_EQUAL_UINT8(0U, result);

  MyLib_UpdateCounter_u8_ExpectAndReturn(1500U, 2U);
  result = MyLib_RunStateMachine_u8(NULL, 1000U, NULL);
  TEST_ASSERT_EQUAL_UINT8(2U, result);
}

/**
 * @brief Test: Sequence Init(NULL rec_pc) → Init(valid rec_pc) → Process → Update → expect first call returns 1 (state remains 0), subsequent calls execute normally
 */
void test_Sequence_InitNullThenValid_ProcessUpdate_FirstReturns1_ThenNormal(void) {
  MyLib_record_t input_rec = {100U, 200U};
  uint8_t result;

  result = MyLib_RunStateMachine_u8(NULL, 0U, NULL);
  TEST_ASSERT_EQUAL_UINT8(1U, result);

  MyLib_UpdateGlobalRecord_Expect(NULL, &input_rec);
  MyLib_UpdateGlobalRecord_IgnoreArg_dest_p();
  result = MyLib_RunStateMachine_u8(&input_rec, 0U, NULL);
  TEST_ASSERT_EQUAL_UINT8(0U, result);

  MyLib_ProcessRecord_Expect(NULL, MYLIB_MULT_VALUE_U8);
  MyLib_ProcessRecord_IgnoreArg_rec_pc();
  MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(0U, NULL, 100U);
  MyLib_ComputeAdjustedValue_u32_IgnoreArg_base_u32();
  result = MyLib_RunStateMachine_u8(NULL, 0U, NULL);
  TEST_ASSERT_EQUAL_UINT8(0U, result);

  MyLib_UpdateCounter_u8_ExpectAndReturn(150U, 0U);
  result = MyLib_RunStateMachine_u8(NULL, 50U, NULL);
  TEST_ASSERT_EQUAL_UINT8(0U, result);
}

/**
 * @brief Test: State 0 (Init) called twice consecutively with valid rec_pc → expect both return 0, l_LastRecord updated on each call, state transitions to 1 after first call then resets and transitions again
 */
void test_State0_InitTwiceConsecutive_ValidRecPtr_BothReturn0_StateTransitions(void) {
  MyLib_record_t input_rec1 = {100U, 200U};
  MyLib_record_t input_rec2 = {150U, 250U};
  uint8_t result;

  MyLib_UpdateGlobalRecord_Expect(NULL, &input_rec1);
  MyLib_UpdateGlobalRecord_IgnoreArg_dest_p();
  result = MyLib_RunStateMachine_u8(&input_rec1, 0U, NULL);
  TEST_ASSERT_EQUAL_UINT8(0U, result);

  MyLib_ProcessRecord_Expect(NULL, MYLIB_MULT_VALUE_U8);
  MyLib_ProcessRecord_IgnoreArg_rec_pc();
  MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(0U, NULL, 100U);
  MyLib_ComputeAdjustedValue_u32_IgnoreArg_base_u32();
  result = MyLib_RunStateMachine_u8(NULL, 0U, NULL);

  MyLib_UpdateCounter_u8_ExpectAndReturn(100U, 0U);
  result = MyLib_RunStateMachine_u8(NULL, 0U, NULL);

  MyLib_UpdateGlobalRecord_Expect(NULL, &input_rec2);
  MyLib_UpdateGlobalRecord_IgnoreArg_dest_p();
  result = MyLib_RunStateMachine_u8(&input_rec2, 0U, NULL);
  TEST_ASSERT_EQUAL_UINT8(0U, result);
}

/**
 * @brief Test: State 2 (Update counter) with add_u32 = 1 and l_LastAdjusted_u32 = mid-range value → MyLib_UpdateCounter_u8 returns 0, expect return 0, state transitions to 0
 */
void test_State2_UpdateCounter_Add1_MidRangeAdjusted_Returns0_StateTransitionsTo0(void) {
  MyLib_record_t input_rec = {100U, 200U};
  uint8_t result;

  MyLib_UpdateGlobalRecord_Expect(NULL, &input_rec);
  MyLib_UpdateGlobalRecord_IgnoreArg_dest_p();
  result = MyLib_RunStateMachine_u8(&input_rec, 0U, NULL);

  MyLib_ProcessRecord_Expect(NULL, MYLIB_MULT_VALUE_U8);
  MyLib_ProcessRecord_IgnoreArg_rec_pc();
  MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(0U, NULL, 0x80000000U);
  MyLib_ComputeAdjustedValue_u32_IgnoreArg_base_u32();
  result = MyLib_RunStateMachine_u8(NULL, 0U, NULL);

  MyLib_UpdateCounter_u8_ExpectAndReturn(0x80000001U, 0U);
  result = MyLib_RunStateMachine_u8(NULL, 1U, NULL);

  TEST_ASSERT_EQUAL_UINT8(0U, result);
}

/**
 * @brief Test: State recovery from invalid state followed by valid Init → expect return 3 on invalid state call, then return 0 on Init with valid rec_pc, state machine resumes normal operation
 */
void test_StateRecovery_InvalidStateThenValidInit_Returns3Then0_ResumesNormal(void) {
  MyLib_record_t input_rec = {100U, 200U};
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

  MyLib_UpdateGlobalRecord_Expect(NULL, &input_rec);
  MyLib_UpdateGlobalRecord_IgnoreArg_dest_p();
  result = MyLib_RunStateMachine_u8(&input_rec, 0U, NULL);
  TEST_ASSERT_EQUAL_UINT8(0U, result);
}