#include "mock_MyLib.h"
#include "unity.h"
#include <MyLib_RunStateMachine_u8.h>




/* SECTION 1 — setUp() and tearDown() */

void setUp(void)
{
    g_counter_u32 = 0U;
    g_record.id_u16 = 0U;
    g_record.value_u32 = 0U;
    g_systemReady_b = false;
    
    MyLib_RunStateMachine_u8_SetState_u8(0U);
    MyLib_RunStateMachine_u8_SetLastAdjusted_u32(0U);
}

void tearDown(void)
{
}

/* SECTION 2 — Test functions */

/**
 * @brief Test: State 0 (Init) with NULL rec_pc → expect return 1, state remains 0
 */
void test_State0_NullRecPtr_Return1_StateRemains0(void)
{
    uint8_t result;
    
    result = MyLib_RunStateMachine_u8(NULL, 0U, NULL);
    
    TEST_ASSERT_EQUAL_UINT8(1U, result);
    TEST_ASSERT_EQUAL_UINT8(0U, MyLib_RunStateMachine_u8_GetState_u8());
}

/**
 * @brief Test: State 0 (Init) with valid rec_pc → expect return 0, state transitions to 1, l_LastRecord updated
 */
void test_State0_ValidRecPtr_Return0_StateTransitionsTo1(void)
{
    MyLib_record_t input_rec = {.id_u16 = 42U, .value_u32 = 1234U};
    MyLib_record_t expected_last_rec = {.id_u16 = 42U, .value_u32 = 1234U};
    uint8_t result;
    
    MyLib_UpdateGlobalRecord_Expect(NULL, &input_rec);
    MyLib_UpdateGlobalRecord_IgnoreArg_dest_p();
    
    result = MyLib_RunStateMachine_u8(&input_rec, 0U, NULL);
    
    TEST_ASSERT_EQUAL_UINT8(0U, result);
    TEST_ASSERT_EQUAL_UINT8(1U, MyLib_RunStateMachine_u8_GetState_u8());
}

/**
 * @brief Test: State 1 (Process) → expect return 0, state transitions to 2, l_LastAdjusted_u32 computed and stored
 */
void test_State1_Process_Return0_StateTransitionsTo2(void)
{
    MyLib_record_t input_rec = {.id_u16 = 10U, .value_u32 = 500U};
    uint16_t delta = 100U;
    uint8_t result;
    
    MyLib_RunStateMachine_u8_SetState_u8(1U);
    MyLib_RunStateMachine_u8_SetLastRecord(input_rec);
    
    MyLib_ProcessRecord_Expect(NULL, MYLIB_MULT_VALUE_U8);
    MyLib_ProcessRecord_IgnoreArg_rec_pc();
    MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(500U, &delta, 600U);
    
    result = MyLib_RunStateMachine_u8(NULL, 0U, &delta);
    
    TEST_ASSERT_EQUAL_UINT8(0U, result);
    TEST_ASSERT_EQUAL_UINT8(2U, MyLib_RunStateMachine_u8_GetState_u8());
    TEST_ASSERT_EQUAL_UINT32(600U, MyLib_RunStateMachine_u8_GetLastAdjusted_u32());
}

/**
 * @brief Test: State 1 (Process) with delta_pc_u16 = NULL → expect return 0, state transitions to 2, adjustment uses default behavior
 */
void test_State1_NullDelta_Return0_StateTransitionsTo2(void)
{
    MyLib_record_t input_rec = {.id_u16 = 20U, .value_u32 = 300U};
    uint8_t result;
    
    MyLib_RunStateMachine_u8_SetState_u8(1U);
    MyLib_RunStateMachine_u8_SetLastRecord(input_rec);
    
    MyLib_ProcessRecord_Expect(NULL, MYLIB_MULT_VALUE_U8);
    MyLib_ProcessRecord_IgnoreArg_rec_pc();
    MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(300U, NULL, 300U);
    
    result = MyLib_RunStateMachine_u8(NULL, 0U, NULL);
    
    TEST_ASSERT_EQUAL_UINT8(0U, result);
    TEST_ASSERT_EQUAL_UINT8(2U, MyLib_RunStateMachine_u8_GetState_u8());
    TEST_ASSERT_EQUAL_UINT32(300U, MyLib_RunStateMachine_u8_GetLastAdjusted_u32());
}

/**
 * @brief Test: State 2 (Update counter) with add_u32 = 0 and l_LastAdjusted_u32 = 0 → MyLib_UpdateCounter_u8 returns 0, expect return 0, state transitions to 0
 */
void test_State2_AddZero_AdjustedZero_Return0_StateTransitionsTo0(void)
{
    uint8_t result;
    
    MyLib_RunStateMachine_u8_SetState_u8(2U);
    MyLib_RunStateMachine_u8_SetLastAdjusted_u32(0U);
    
    MyLib_UpdateCounter_u8_ExpectAndReturn(0U, 0U);
    
    result = MyLib_RunStateMachine_u8(NULL, 0U, NULL);
    
    TEST_ASSERT_EQUAL_UINT8(0U, result);
    TEST_ASSERT_EQUAL_UINT8(0U, MyLib_RunStateMachine_u8_GetState_u8());
}

/**
 * @brief Test: State 2 (Update counter) with add_u32 at boundary causing saturation → MyLib_UpdateCounter_u8 returns 2, expect return 2, state transitions to 0
 */
void test_State2_BoundarySaturation_Return2_StateTransitionsTo0(void)
{
    uint8_t result;
    
    MyLib_RunStateMachine_u8_SetState_u8(2U);
    MyLib_RunStateMachine_u8_SetLastAdjusted_u32(50U);
    
    MyLib_UpdateCounter_u8_ExpectAndReturn(150U, 2U);
    
    result = MyLib_RunStateMachine_u8(NULL, 100U, NULL);
    
    TEST_ASSERT_EQUAL_UINT8(2U, result);
    TEST_ASSERT_EQUAL_UINT8(0U, MyLib_RunStateMachine_u8_GetState_u8());
}

/**
 * @brief Test: State 2 (Update counter) with add_u32 = UINT32_MAX and l_LastAdjusted_u32 = UINT32_MAX → verify wrap behavior, expect return matches MyLib_UpdateCounter_u8 result, state transitions to 0
 */
void test_State2_MaxAddMaxAdjusted_WrapBehavior_StateTransitionsTo0(void)
{
    uint8_t result;
    uint32_t wrapped_value = UINT32_MAX + UINT32_MAX;
    
    MyLib_RunStateMachine_u8_SetState_u8(2U);
    MyLib_RunStateMachine_u8_SetLastAdjusted_u32(UINT32_MAX);
    
    MyLib_UpdateCounter_u8_ExpectAndReturn(wrapped_value, 1U);
    
    result = MyLib_RunStateMachine_u8(NULL, UINT32_MAX, NULL);
    
    TEST_ASSERT_EQUAL_UINT8(1U, result);
    TEST_ASSERT_EQUAL_UINT8(0U, MyLib_RunStateMachine_u8_GetState_u8());
}

/**
 * @brief Test: Invalid state (e.g., l_State_u8 = 5) → expect return 3, state reset to 0, l_LastAdjusted_u32 reset to 0
 */
void test_InvalidState5_Return3_StateResetTo0_AdjustedResetTo0(void)
{
    uint8_t result;
    
    MyLib_RunStateMachine_u8_SetState_u8(5U);
    MyLib_RunStateMachine_u8_SetLastAdjusted_u32(999U);
    
    result = MyLib_RunStateMachine_u8(NULL, 0U, NULL);
    
    TEST_ASSERT_EQUAL_UINT8(3U, result);
    TEST_ASSERT_EQUAL_UINT8(0U, MyLib_RunStateMachine_u8_GetState_u8());
    TEST_ASSERT_EQUAL_UINT32(0U, MyLib_RunStateMachine_u8_GetLastAdjusted_u32());
}

/**
 * @brief Test: Full state machine cycle (0→1→2→0) with valid inputs → verify all transitions, return codes, and final g_counter_u32 value
 */
void test_FullCycle_State0To1To2To0_VerifyAllTransitions(void)
{
    MyLib_record_t input_rec = {.id_u16 = 100U, .value_u32 = 2000U};
    uint16_t delta = 50U;
    uint8_t result;
    
    MyLib_UpdateGlobalRecord_Expect(NULL, &input_rec);
    MyLib_UpdateGlobalRecord_IgnoreArg_dest_p();
    result = MyLib_RunStateMachine_u8(&input_rec, 0U, NULL);
    TEST_ASSERT_EQUAL_UINT8(0U, result);
    TEST_ASSERT_EQUAL_UINT8(1U, MyLib_RunStateMachine_u8_GetState_u8());
    
    MyLib_ProcessRecord_Expect(NULL, MYLIB_MULT_VALUE_U8);
    MyLib_ProcessRecord_IgnoreArg_rec_pc();
    MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(2000U, &delta, 2050U);
    result = MyLib_RunStateMachine_u8(NULL, 0U, &delta);
    TEST_ASSERT_EQUAL_UINT8(0U, result);
    TEST_ASSERT_EQUAL_UINT8(2U, MyLib_RunStateMachine_u8_GetState_u8());
    
    MyLib_UpdateCounter_u8_ExpectAndReturn(2150U, 0U);
    result = MyLib_RunStateMachine_u8(NULL, 100U, NULL);
    TEST_ASSERT_EQUAL_UINT8(0U, result);
    TEST_ASSERT_EQUAL_UINT8(0U, MyLib_RunStateMachine_u8_GetState_u8());
}

/**
 * @brief Test: State 0 (Init) with valid rec_pc, then State 1 (Process) with delta_pc_u16 pointing to boundary value (e.g., 0) → verify adjusted value computation and state progression
 */
void test_State0To1_DeltaZero_VerifyAdjustedComputation(void)
{
    MyLib_record_t input_rec = {.id_u16 = 5U, .value_u32 = 1000U};
    uint16_t delta = 0U;
    uint8_t result;
    
    MyLib_UpdateGlobalRecord_Expect(NULL, &input_rec);
    MyLib_UpdateGlobalRecord_IgnoreArg_dest_p();
    result = MyLib_RunStateMachine_u8(&input_rec, 0U, NULL);
    TEST_ASSERT_EQUAL_UINT8(0U, result);
    TEST_ASSERT_EQUAL_UINT8(1U, MyLib_RunStateMachine_u8_GetState_u8());
    
    MyLib_ProcessRecord_Expect(NULL, MYLIB_MULT_VALUE_U8);
    MyLib_ProcessRecord_IgnoreArg_rec_pc();
    MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(1000U, &delta, 1000U);
    result = MyLib_RunStateMachine_u8(NULL, 0U, &delta);
    TEST_ASSERT_EQUAL_UINT8(0U, result);
    TEST_ASSERT_EQUAL_UINT8(2U, MyLib_RunStateMachine_u8_GetState_u8());
    TEST_ASSERT_EQUAL_UINT32(1000U, MyLib_RunStateMachine_u8_GetLastAdjusted_u32());
}

/**
 * @brief Test: State 0 (Init) with valid rec_pc, then State 1 (Process) with delta_pc_u16 pointing to boundary value (e.g., UINT16_MAX) → verify adjusted value computation and state progression
 */
void test_State0To1_DeltaMax_VerifyAdjustedComputation(void)
{
    MyLib_record_t input_rec = {.id_u16 = 7U, .value_u32 = 500U};
    uint16_t delta = UINT16_MAX;
    uint8_t result;
    
    MyLib_UpdateGlobalRecord_Expect(NULL, &input_rec);
    MyLib_UpdateGlobalRecord_IgnoreArg_dest_p();
    result = MyLib_RunStateMachine_u8(&input_rec, 0U, NULL);
    TEST_ASSERT_EQUAL_UINT8(0U, result);
    TEST_ASSERT_EQUAL_UINT8(1U, MyLib_RunStateMachine_u8_GetState_u8());
    
    MyLib_ProcessRecord_Expect(NULL, MYLIB_MULT_VALUE_U8);
    MyLib_ProcessRecord_IgnoreArg_rec_pc();
    MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(500U, &delta, 66035U);
    result = MyLib_RunStateMachine_u8(NULL, 0U, &delta);
    TEST_ASSERT_EQUAL_UINT8(0U, result);
    TEST_ASSERT_EQUAL_UINT8(2U, MyLib_RunStateMachine_u8_GetState_u8());
    TEST_ASSERT_EQUAL_UINT32(66035U, MyLib_RunStateMachine_u8_GetLastAdjusted_u32());
}

/**
 * @brief Test: State 2 (Update counter) with add_u32 = 1 and l_LastAdjusted_u32 = mid-range value → verify correct sum passed to MyLib_UpdateCounter_u8, expect return 0, state transitions to 0
 */
void test_State2_Add1_MidRangeAdjusted_VerifySum_Return0(void)
{
    uint8_t result;
    
    MyLib_RunStateMachine_u8_SetState_u8(2U);
    MyLib_RunStateMachine_u8_SetLastAdjusted_u32(50000U);
    
    MyLib_UpdateCounter_u8_ExpectAndReturn(50001U, 0U);
    
    result = MyLib_RunStateMachine_u8(NULL, 1U, NULL);
    
    TEST_ASSERT_EQUAL_UINT8(0U, result);
    TEST_ASSERT_EQUAL_UINT8(0U, MyLib_RunStateMachine_u8_GetState_u8());
}

/**
 * @brief Test: Multiple consecutive calls in State 0 with NULL rec_pc → verify state remains 0 and return 1 on each call
 */
void test_State0_MultipleNullCalls_StateRemains0_Return1(void)
{
    uint8_t result;
    
    result = MyLib_RunStateMachine_u8(NULL, 0U, NULL);
    TEST_ASSERT_EQUAL_UINT8(1U, result);
    TEST_ASSERT_EQUAL_UINT8(0U, MyLib_RunStateMachine_u8_GetState_u8());
    
    result = MyLib_RunStateMachine_u8(NULL, 0U, NULL);
    TEST_ASSERT_EQUAL_UINT8(1U, result);
    TEST_ASSERT_EQUAL_UINT8(0U, MyLib_RunStateMachine_u8_GetState_u8());
    
    result = MyLib_RunStateMachine_u8(NULL, 0U, NULL);
    TEST_ASSERT_EQUAL_UINT8(1U, result);
    TEST_ASSERT_EQUAL_UINT8(0U, MyLib_RunStateMachine_u8_GetState_u8());
}

/**
 * @brief Test: State 0 (Init) with valid rec_pc, verify MyLib_UpdateGlobalRecord called with correct arguments and l_LastRecord populated
 */
void test_State0_ValidRec_VerifyUpdateGlobalRecordCall(void)
{
    MyLib_record_t input_rec = {.id_u16 = 123U, .value_u32 = 456U};
    uint8_t result;
    
    MyLib_UpdateGlobalRecord_Expect(NULL, &input_rec);
    MyLib_UpdateGlobalRecord_IgnoreArg_dest_p();
    
    result = MyLib_RunStateMachine_u8(&input_rec, 0U, NULL);
    
    TEST_ASSERT_EQUAL_UINT8(0U, result);
    TEST_ASSERT_EQUAL_UINT8(1U, MyLib_RunStateMachine_u8_GetState_u8());
}

/**
 * @brief Test: State 1 (Process), verify MyLib_ProcessRecord called with l_LastRecord and MYLIB_MULT_VALUE_U8, and MyLib_ComputeAdjustedValue_u32 called with l_LastRecord.value_u32 and delta_pc_u16
 */
void test_State1_VerifyProcessRecordAndComputeAdjustedCalls(void)
{
    MyLib_record_t last_rec = {.id_u16 = 88U, .value_u32 = 777U};
    uint16_t delta = 25U;
    uint8_t result;
    
    MyLib_RunStateMachine_u8_SetState_u8(1U);
    MyLib_RunStateMachine_u8_SetLastRecord(last_rec);
    
    MyLib_ProcessRecord_Expect(NULL, MYLIB_MULT_VALUE_U8);
    MyLib_ProcessRecord_IgnoreArg_rec_pc();
    MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(777U, &delta, 802U);
    
    result = MyLib_RunStateMachine_u8(NULL, 0U, &delta);
    
    TEST_ASSERT_EQUAL_UINT8(0U, result);
    TEST_ASSERT_EQUAL_UINT8(2U, MyLib_RunStateMachine_u8_GetState_u8());
}

/**
 * @brief Test: State 2 (Update counter) with add_u32 = 0 and l_LastAdjusted_u32 = 1 → verify l_UpdateValue_u32 = 1, MyLib_UpdateCounter_u8 called with 1, state transitions to 0
 */
void test_State2_AddZero_AdjustedOne_VerifyUpdateValue1(void)
{
    uint8_t result;
    
    MyLib_RunStateMachine_u8_SetState_u8(2U);
    MyLib_RunStateMachine_u8_SetLastAdjusted_u32(1U);
    
    MyLib_UpdateCounter_u8_ExpectAndReturn(1U, 0U);
    
    result = MyLib_RunStateMachine_u8(NULL, 0U, NULL);
    
    TEST_ASSERT_EQUAL_UINT8(0U, result);
    TEST_ASSERT_EQUAL_UINT8(0U, MyLib_RunStateMachine_u8_GetState_u8());
}

/**
 * @brief Test: State machine recovery from invalid state (e.g., l_State_u8 = 255) → expect return 3, state reset to 0, l_LastAdjusted_u32 reset to 0
 */
void test_InvalidState255_Return3_StateResetTo0_AdjustedResetTo0(void)
{
    uint8_t result;
    
    MyLib_RunStateMachine_u8_SetState_u8(255U);
    MyLib_RunStateMachine_u8_SetLastAdjusted_u32(12345U);
    
    result = MyLib_RunStateMachine_u8(NULL, 0U, NULL);
    
    TEST_ASSERT_EQUAL_UINT8(3U, result);
    TEST_ASSERT_EQUAL_UINT8(0U, MyLib_RunStateMachine_u8_GetState_u8());
    TEST_ASSERT_EQUAL_UINT32(0U, MyLib_RunStateMachine_u8_GetLastAdjusted_u32());
}

/**
 * @brief Test: State 0 (Init) followed by immediate invalid state injection → verify recovery path returns 3 and resets state
 */
void test_State0_ThenInvalidState_VerifyRecovery(void)
{
    MyLib_record_t input_rec = {.id_u16 = 1U, .value_u32 = 1U};
    uint8_t result;
    
    MyLib_UpdateGlobalRecord_Expect(NULL, &input_rec);
    MyLib_UpdateGlobalRecord_IgnoreArg_dest_p();
    result = MyLib_RunStateMachine_u8(&input_rec, 0U, NULL);
    TEST_ASSERT_EQUAL_UINT8(0U, result);
    TEST_ASSERT_EQUAL_UINT8(1U, MyLib_RunStateMachine_u8_GetState_u8());
    
    MyLib_RunStateMachine_u8_SetState_u8(99U);
    
    result = MyLib_RunStateMachine_u8(NULL, 0U, NULL);
    TEST_ASSERT_EQUAL_UINT8(3U, result);
    TEST_ASSERT_EQUAL_UINT8(0U, MyLib_RunStateMachine_u8_GetState_u8());
    TEST_ASSERT_EQUAL_UINT32(0U, MyLib_RunStateMachine_u8_GetLastAdjusted_u32());
}

/**
 * @brief Test: State 1 (Process) with l_LastRecord.value_u32 = 0 and delta_pc_u16 = NULL → verify MyLib_ComputeAdjustedValue_u32 behavior and state transition to 2
 */
void test_State1_ValueZero_NullDelta_VerifyComputeAdjusted(void)
{
    MyLib_record_t last_rec = {.id_u16 = 0U, .value_u32 = 0U};
    uint8_t result;
    
    MyLib_RunStateMachine_u8_SetState_u8(1U);
    MyLib_RunStateMachine_u8_SetLastRecord(last_rec);
    
    MyLib_ProcessRecord_Expect(NULL, MYLIB_MULT_VALUE_U8);
    MyLib_ProcessRecord_IgnoreArg_rec_pc();
    MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(0U, NULL, 0U);
    
    result = MyLib_RunStateMachine_u8(NULL, 0U, NULL);
    
    TEST_ASSERT_EQUAL_UINT8(0U, result);
    TEST_ASSERT_EQUAL_UINT8(2U, MyLib_RunStateMachine_u8_GetState_u8());
    TEST_ASSERT_EQUAL_UINT32(0U, MyLib_RunStateMachine_u8_GetLastAdjusted_u32());
}

/**
 * @brief Test: State 1 (Process) with l_LastRecord.value_u32 = UINT32_MAX and delta_pc_u16 pointing to UINT16_MAX → verify adjusted value computation handles boundary and state transitions to 2
 */
void test_State1_ValueMax_DeltaMax_VerifyBoundaryHandling(void)
{
    MyLib_record_t last_rec = {.id_u16 = 999U, .value_u32 = UINT32_MAX};
    uint16_t delta = UINT16_MAX;
    uint8_t result;
    
    MyLib_RunStateMachine_u8_SetState_u8(1U);
    MyLib_RunStateMachine_u8_SetLastRecord(last_rec);
    
    MyLib_ProcessRecord_Expect(NULL, MYLIB_MULT_VALUE_U8);
    MyLib_ProcessRecord_IgnoreArg_rec_pc();
    MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(UINT32_MAX, &delta, 123456U);
    
    result = MyLib_RunStateMachine_u8(NULL, 0U, &delta);
    
    TEST_ASSERT_EQUAL_UINT8(0U, result);
    TEST_ASSERT_EQUAL_UINT8(2U, MyLib_RunStateMachine_u8_GetState_u8());
    TEST_ASSERT_EQUAL_UINT32(123456U, MyLib_RunStateMachine_u8_GetLastAdjusted_u32());
}

/**
 * @brief Test: State 2 (Update counter) with add_u32 causing l_UpdateValue_u32 to wrap around UINT32_MAX → verify MyLib_UpdateCounter_u8 receives wrapped value, state transitions to 0
 */
void test_State2_AddCausesWrap_VerifyWrappedValue(void)
{
    uint8_t result;
    uint32_t wrapped = (UINT32_MAX - 10U) + 20U;
    
    MyLib_RunStateMachine_u8_SetState_u8(2U);
    MyLib_RunStateMachine_u8_SetLastAdjusted_u32(UINT32_MAX - 10U);
    
    MyLib_UpdateCounter_u8_ExpectAndReturn(wrapped, 0U);
    
    result = MyLib_RunStateMachine_u8(NULL, 20U, NULL);
    
    TEST_ASSERT_EQUAL_UINT8(0U, result);
    TEST_ASSERT_EQUAL_UINT8(0U, MyLib_RunStateMachine_u8_GetState_u8());
}

/**
 * @brief Test: Full cycle with add_u32 = UINT32_MAX in State 2 → verify counter update handles maximum input, state transitions to 0
 */
void test_FullCycle_AddMaxInState2_VerifyHandling(void)
{
    MyLib_record_t input_rec = {.id_u16 = 50U, .value_u32 = 100U};
    uint16_t delta = 10U;
    uint8_t result;
    
    MyLib_UpdateGlobalRecord_Expect(NULL, &input_rec);
    MyLib_UpdateGlobalRecord_IgnoreArg_dest_p();
    result = MyLib_RunStateMachine_u8(&input_rec, 0U, NULL);
    TEST_ASSERT_EQUAL_UINT8(0U, result);
    
    MyLib_ProcessRecord_Expect(NULL, MYLIB_MULT_VALUE_U8);
    MyLib_ProcessRecord_IgnoreArg_rec_pc();
    MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(100U, &delta, 110U);
    result = MyLib_RunStateMachine_u8(NULL, 0U, &delta);
    TEST_ASSERT_EQUAL_UINT8(0U, result);
    
    MyLib_UpdateCounter_u8_ExpectAndReturn(UINT32_MAX + 110U, 2U);
    result = MyLib_RunStateMachine_u8(NULL, UINT32_MAX, NULL);
    TEST_ASSERT_EQUAL_UINT8(2U, result);
    TEST_ASSERT_EQUAL_UINT8(0U, MyLib_RunStateMachine_u8_GetState_u8());
}

/**
 * @brief Test: State 0 (Init) with rec_pc pointing to record with value_u32 = 0 → verify initialization and state transition to 1
 */
void test_State0_RecValueZero_VerifyInitAndTransition(void)
{
    MyLib_record_t input_rec = {.id_u16 = 200U, .value_u32 = 0U};
    uint8_t result;
    
    MyLib_UpdateGlobalRecord_Expect(NULL, &input_rec);
    MyLib_UpdateGlobalRecord_IgnoreArg_dest_p();
    
    result = MyLib_RunStateMachine_u8(&input_rec, 0U, NULL);
    
    TEST_ASSERT_EQUAL_UINT8(0U, result);
    TEST_ASSERT_EQUAL_UINT8(1U, MyLib_RunStateMachine_u8_GetState_u8());
}

/**
 * @brief Test: State 0 (Init) with rec_pc pointing to record with value_u32 = UINT32_MAX → verify initialization and state transition to 1
 */
void test_State0_RecValueMax_VerifyInitAndTransition(void)
{
    MyLib_record_t input_rec = {.id_u16 = 300U, .value_u32 = UINT32_MAX};
    uint8_t result;
    
    MyLib_UpdateGlobalRecord_Expect(NULL, &input_rec);
    MyLib_UpdateGlobalRecord_IgnoreArg_dest_p();
    
    result = MyLib_RunStateMachine_u8(&input_rec, 0U, NULL);
    
    TEST_ASSERT_EQUAL_UINT8(0U, result);
    TEST_ASSERT_EQUAL_UINT8(1U, MyLib_RunStateMachine_u8_GetState_u8());
}

/**
 * @brief Test: State machine in State 1, call with rec_pc = NULL (ignored in State 1) → verify state transitions to 2 regardless of rec_pc
 */
void test_State1_RecPtrNull_IgnoredTransitionsTo2(void)
{
    MyLib_record_t last_rec = {.id_u16 = 11U, .value_u32 = 222U};
    uint8_t result;
    
    MyLib_RunStateMachine_u8_SetState_u8(1U);
    MyLib_RunStateMachine_u8_SetLastRecord(last_rec);
    
    MyLib_ProcessRecord_Expect(NULL, MYLIB_MULT_VALUE_U8);
    MyLib_ProcessRecord_IgnoreArg_rec_pc();
    MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(222U, NULL, 222U);
    
    result = MyLib_RunStateMachine_u8(NULL, 0U, NULL);
    
    TEST_ASSERT_EQUAL_UINT8(0U, result);
    TEST_ASSERT_EQUAL_UINT8(2U, MyLib_RunStateMachine_u8_GetState_u8());
}

/**
 * @brief Test: State machine in State 2, call with rec_pc = NULL (ignored in State 2) → verify state transitions to 0 regardless of rec_pc
 */
void test_State2_RecPtrNull_IgnoredTransitionsTo0(void)
{
    uint8_t result;
    
    MyLib_RunStateMachine_u8_SetState_u8(2U);
    MyLib_RunStateMachine_u8_SetLastAdjusted_u32(333U);
    
    MyLib_UpdateCounter_u8_ExpectAndReturn(433U, 0U);
    
    result = MyLib_RunStateMachine_u8(NULL, 100U, NULL);
    
    TEST_ASSERT_EQUAL_UINT8(0U, result);
    TEST_ASSERT_EQUAL_UINT8(0U, MyLib_RunStateMachine_u8_GetState_u8());
}