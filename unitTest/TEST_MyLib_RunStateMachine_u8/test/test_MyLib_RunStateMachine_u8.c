#include "MyLib_RunStateMachine_u8.h"
#include "unity.h"
#include "mock_MyLib.h"




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
void test_State0_NullRecPtr_Returns1_StateRemains0(void)
{
    uint8_t result;
    
    result = MyLib_RunStateMachine_u8(NULL, 0U, NULL);
    
    TEST_ASSERT_EQUAL_UINT8(1U, result);
    TEST_ASSERT_EQUAL_UINT8(0U, MyLib_RunStateMachine_u8_GetState_u8());
}

/**
 * @brief Test: State 0 (Init) with valid rec_pc → expect return 0, state transitions to 1, l_LastRecord updated
 */
void test_State0_ValidRecPtr_Returns0_StateTransitionsTo1(void)
{
    MyLib_record_t input_rec = {.id_u16 = 42U, .value_u32 = 1000U};
    MyLib_record_t expected_last_rec = {.id_u16 = 42U, .value_u32 = 1000U};
    uint8_t result;
    
    MyLib_UpdateGlobalRecord_Expect(NULL, &input_rec);
    MyLib_UpdateGlobalRecord_IgnoreArg_dest_p();
    
    result = MyLib_RunStateMachine_u8(&input_rec, 0U, NULL);
    
    TEST_ASSERT_EQUAL_UINT8(0U, result);
    TEST_ASSERT_EQUAL_UINT8(1U, MyLib_RunStateMachine_u8_GetState_u8());
}

/**
 * @brief Test: State 1 (Process) with delta_pc_u16 = NULL → expect return 0, state transitions to 2, l_LastAdjusted_u32 computed with default behavior
 */
void test_State1_NullDelta_Returns0_StateTransitionsTo2(void)
{
    MyLib_record_t last_rec = {.id_u16 = 10U, .value_u32 = 500U};
    uint8_t result;
    
    MyLib_RunStateMachine_u8_SetState_u8(1U);
    MyLib_RunStateMachine_u8_SetLastRecord(&last_rec);
    
    MyLib_ProcessRecord_Expect(NULL, MYLIB_MULT_VALUE_U8);
    MyLib_ProcessRecord_IgnoreArg_rec_pc();
    MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(500U, NULL, 750U);
    
    result = MyLib_RunStateMachine_u8(NULL, 0U, NULL);
    
    TEST_ASSERT_EQUAL_UINT8(0U, result);
    TEST_ASSERT_EQUAL_UINT8(2U, MyLib_RunStateMachine_u8_GetState_u8());
    TEST_ASSERT_EQUAL_UINT32(750U, MyLib_RunStateMachine_u8_GetLastAdjusted_u32());
}

/**
 * @brief Test: State 1 (Process) with valid delta_pc_u16 → expect return 0, state transitions to 2, l_LastAdjusted_u32 computed with delta applied
 */
void test_State1_ValidDelta_Returns0_StateTransitionsTo2(void)
{
    MyLib_record_t last_rec = {.id_u16 = 20U, .value_u32 = 800U};
    uint16_t delta = 100U;
    uint8_t result;
    
    MyLib_RunStateMachine_u8_SetState_u8(1U);
    MyLib_RunStateMachine_u8_SetLastRecord(&last_rec);
    
    MyLib_ProcessRecord_Expect(NULL, MYLIB_MULT_VALUE_U8);
    MyLib_ProcessRecord_IgnoreArg_rec_pc();
    MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(800U, &delta, 900U);
    
    result = MyLib_RunStateMachine_u8(NULL, 0U, &delta);
    
    TEST_ASSERT_EQUAL_UINT8(0U, result);
    TEST_ASSERT_EQUAL_UINT8(2U, MyLib_RunStateMachine_u8_GetState_u8());
    TEST_ASSERT_EQUAL_UINT32(900U, MyLib_RunStateMachine_u8_GetLastAdjusted_u32());
}

/**
 * @brief Test: State 2 (Update counter) with add_u32 = 0 and l_LastAdjusted_u32 = 0 → MyLib_UpdateCounter_u8 returns 0, expect return 0, state transitions to 0
 */
void test_State2_AddZero_AdjustedZero_Returns0_StateTransitionsTo0(void)
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
 * @brief Test: State 2 (Update counter) with add_u32 at boundary causing MyLib_UpdateCounter_u8 to return 2 (saturation) → expect return 2, state transitions to 0
 */
void test_State2_BoundaryAdd_Saturation_Returns2_StateTransitionsTo0(void)
{
    uint8_t result;
    
    MyLib_RunStateMachine_u8_SetState_u8(2U);
    MyLib_RunStateMachine_u8_SetLastAdjusted_u32(50U);
    
    MyLib_UpdateCounter_u8_ExpectAndReturn(UINT32_MAX, 2U);
    
    result = MyLib_RunStateMachine_u8(NULL, UINT32_MAX - 50U, NULL);
    
    TEST_ASSERT_EQUAL_UINT8(2U, result);
    TEST_ASSERT_EQUAL_UINT8(0U, MyLib_RunStateMachine_u8_GetState_u8());
}

/**
 * @brief Test: State 2 (Update counter) with add_u32 + l_LastAdjusted_u32 producing mid-range value → MyLib_UpdateCounter_u8 returns 0, expect return 0, state transitions to 0
 */
void test_State2_MidRangeValue_Returns0_StateTransitionsTo0(void)
{
    uint8_t result;
    
    MyLib_RunStateMachine_u8_SetState_u8(2U);
    MyLib_RunStateMachine_u8_SetLastAdjusted_u32(1000U);
    
    MyLib_UpdateCounter_u8_ExpectAndReturn(2000U, 0U);
    
    result = MyLib_RunStateMachine_u8(NULL, 1000U, NULL);
    
    TEST_ASSERT_EQUAL_UINT8(0U, result);
    TEST_ASSERT_EQUAL_UINT8(0U, MyLib_RunStateMachine_u8_GetState_u8());
}

/**
 * @brief Test: State 2 (Update counter) with add_u32 = UINT32_MAX and l_LastAdjusted_u32 = UINT32_MAX → verify wrap behavior, MyLib_UpdateCounter_u8 returns appropriate code, state transitions to 0
 */
void test_State2_MaxAdd_MaxAdjusted_WrapBehavior_StateTransitionsTo0(void)
{
    uint8_t result;
    uint32_t expected_wrapped = UINT32_MAX + UINT32_MAX;
    
    MyLib_RunStateMachine_u8_SetState_u8(2U);
    MyLib_RunStateMachine_u8_SetLastAdjusted_u32(UINT32_MAX);
    
    MyLib_UpdateCounter_u8_ExpectAndReturn(expected_wrapped, 2U);
    
    result = MyLib_RunStateMachine_u8(NULL, UINT32_MAX, NULL);
    
    TEST_ASSERT_EQUAL_UINT8(2U, result);
    TEST_ASSERT_EQUAL_UINT8(0U, MyLib_RunStateMachine_u8_GetState_u8());
}

/**
 * @brief Test: Invalid state (e.g., l_State_u8 = 3) → expect return 3, state reset to 0, l_LastAdjusted_u32 reset to 0
 */
void test_InvalidState3_Returns3_StateResetTo0_AdjustedResetTo0(void)
{
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
void test_InvalidState255_Returns3_StateResetTo0_AdjustedResetTo0(void)
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
 * @brief Test: Full state machine cycle (State 0 → 1 → 2 → 0) with valid inputs → verify each transition returns 0 and state progresses correctly
 */
void test_FullCycle_State0To1To2To0_AllReturns0(void)
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
    TEST_ASSERT_EQUAL_UINT32(2050U, MyLib_RunStateMachine_u8_GetLastAdjusted_u32());
    
    MyLib_UpdateCounter_u8_ExpectAndReturn(2150U, 0U);
    result = MyLib_RunStateMachine_u8(NULL, 100U, NULL);
    TEST_ASSERT_EQUAL_UINT8(0U, result);
    TEST_ASSERT_EQUAL_UINT8(0U, MyLib_RunStateMachine_u8_GetState_u8());
}

/**
 * @brief Test: State 0 (Init) with valid rec_pc, then State 1 (Process) with delta_pc_u16 pointing to boundary value (e.g., 0) → verify correct adjusted value computation and state transition
 */
void test_State0To1_DeltaZero_CorrectAdjustedValue(void)
{
    MyLib_record_t input_rec = {.id_u16 = 5U, .value_u32 = 300U};
    uint16_t delta = 0U;
    uint8_t result;
    
    MyLib_UpdateGlobalRecord_Expect(NULL, &input_rec);
    MyLib_UpdateGlobalRecord_IgnoreArg_dest_p();
    result = MyLib_RunStateMachine_u8(&input_rec, 0U, NULL);
    TEST_ASSERT_EQUAL_UINT8(0U, result);
    TEST_ASSERT_EQUAL_UINT8(1U, MyLib_RunStateMachine_u8_GetState_u8());
    
    MyLib_ProcessRecord_Expect(NULL, MYLIB_MULT_VALUE_U8);
    MyLib_ProcessRecord_IgnoreArg_rec_pc();
    MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(300U, &delta, 300U);
    result = MyLib_RunStateMachine_u8(NULL, 0U, &delta);
    TEST_ASSERT_EQUAL_UINT8(0U, result);
    TEST_ASSERT_EQUAL_UINT8(2U, MyLib_RunStateMachine_u8_GetState_u8());
    TEST_ASSERT_EQUAL_UINT32(300U, MyLib_RunStateMachine_u8_GetLastAdjusted_u32());
}

/**
 * @brief Test: State 0 (Init) with valid rec_pc, then State 1 (Process) with delta_pc_u16 pointing to boundary value (e.g., UINT16_MAX) → verify correct adjusted value computation and state transition
 */
void test_State0To1_DeltaUINT16MAX_CorrectAdjustedValue(void)
{
    MyLib_record_t input_rec = {.id_u16 = 7U, .value_u32 = 400U};
    uint16_t delta = UINT16_MAX;
    uint8_t result;
    
    MyLib_UpdateGlobalRecord_Expect(NULL, &input_rec);
    MyLib_UpdateGlobalRecord_IgnoreArg_dest_p();
    result = MyLib_RunStateMachine_u8(&input_rec, 0U, NULL);
    TEST_ASSERT_EQUAL_UINT8(0U, result);
    TEST_ASSERT_EQUAL_UINT8(1U, MyLib_RunStateMachine_u8_GetState_u8());
    
    MyLib_ProcessRecord_Expect(NULL, MYLIB_MULT_VALUE_U8);
    MyLib_ProcessRecord_IgnoreArg_rec_pc();
    MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(400U, &delta, 66000U);
    result = MyLib_RunStateMachine_u8(NULL, 0U, &delta);
    TEST_ASSERT_EQUAL_UINT8(0U, result);
    TEST_ASSERT_EQUAL_UINT8(2U, MyLib_RunStateMachine_u8_GetState_u8());
    TEST_ASSERT_EQUAL_UINT32(66000U, MyLib_RunStateMachine_u8_GetLastAdjusted_u32());
}

/**
 * @brief Test: State 0 (Init) with valid rec_pc, then State 1 (Process) with delta_pc_u16 pointing to mid-range value (e.g., 32768) → verify correct adjusted value computation and state transition
 */
void test_State0To1_DeltaMidRange_CorrectAdjustedValue(void)
{
    MyLib_record_t input_rec = {.id_u16 = 15U, .value_u32 = 600U};
    uint16_t delta = 32768U;
    uint8_t result;
    
    MyLib_UpdateGlobalRecord_Expect(NULL, &input_rec);
    MyLib_UpdateGlobalRecord_IgnoreArg_dest_p();
    result = MyLib_RunStateMachine_u8(&input_rec, 0U, NULL);
    TEST_ASSERT_EQUAL_UINT8(0U, result);
    TEST_ASSERT_EQUAL_UINT8(1U, MyLib_RunStateMachine_u8_GetState_u8());
    
    MyLib_ProcessRecord_Expect(NULL, MYLIB_MULT_VALUE_U8);
    MyLib_ProcessRecord_IgnoreArg_rec_pc();
    MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(600U, &delta, 33368U);
    result = MyLib_RunStateMachine_u8(NULL, 0U, &delta);
    TEST_ASSERT_EQUAL_UINT8(0U, result);
    TEST_ASSERT_EQUAL_UINT8(2U, MyLib_RunStateMachine_u8_GetState_u8());
    TEST_ASSERT_EQUAL_UINT32(33368U, MyLib_RunStateMachine_u8_GetLastAdjusted_u32());
}

/**
 * @brief Test: State 2 (Update counter) with add_u32 = 1 and l_LastAdjusted_u32 = 0 → verify l_UpdateValue_u32 = 1, MyLib_UpdateCounter_u8 called with 1, state transitions to 0
 */
void test_State2_Add1_Adjusted0_UpdateValueIs1(void)
{
    uint8_t result;
    
    MyLib_RunStateMachine_u8_SetState_u8(2U);
    MyLib_RunStateMachine_u8_SetLastAdjusted_u32(0U);
    
    MyLib_UpdateCounter_u8_ExpectAndReturn(1U, 0U);
    
    result = MyLib_RunStateMachine_u8(NULL, 1U, NULL);
    
    TEST_ASSERT_EQUAL_UINT8(0U, result);
    TEST_ASSERT_EQUAL_UINT8(0U, MyLib_RunStateMachine_u8_GetState_u8());
}

/**
 * @brief Test: State 2 (Update counter) with add_u32 = 0 and l_LastAdjusted_u32 = 1 → verify l_UpdateValue_u32 = 1, MyLib_UpdateCounter_u8 called with 1, state transitions to 0
 */
void test_State2_Add0_Adjusted1_UpdateValueIs1(void)
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
 * @brief Test: Multiple consecutive calls in State 0 with NULL rec_pc → verify each call returns 1 and state remains 0
 */
void test_State0_MultipleNullCalls_EachReturns1_StateRemains0(void)
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
 * @brief Test: State 0 (Init) with valid rec_pc, followed by immediate re-entry to State 0 with different rec_pc → verify l_LastRecord is updated with new record, state transitions to 1
 */
void test_State0_ValidRec_ThenReEntry_DifferentRec_UpdatesLastRecord(void)
{
    MyLib_record_t first_rec = {.id_u16 = 10U, .value_u32 = 100U};
    MyLib_record_t second_rec = {.id_u16 = 20U, .value_u32 = 200U};
    uint8_t result;
    
    MyLib_UpdateGlobalRecord_Expect(NULL, &first_rec);
    MyLib_UpdateGlobalRecord_IgnoreArg_dest_p();
    result = MyLib_RunStateMachine_u8(&first_rec, 0U, NULL);
    TEST_ASSERT_EQUAL_UINT8(0U, result);
    TEST_ASSERT_EQUAL_UINT8(1U, MyLib_RunStateMachine_u8_GetState_u8());
    
    MyLib_ProcessRecord_Expect(NULL, MYLIB_MULT_VALUE_U8);
    MyLib_ProcessRecord_IgnoreArg_rec_pc();
    MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(100U, NULL, 150U);
    result = MyLib_RunStateMachine_u8(NULL, 0U, NULL);
    TEST_ASSERT_EQUAL_UINT8(0U, result);
    TEST_ASSERT_EQUAL_UINT8(2U, MyLib_RunStateMachine_u8_GetState_u8());
    
    MyLib_UpdateCounter_u8_ExpectAndReturn(150U, 0U);
    result = MyLib_RunStateMachine_u8(NULL, 0U, NULL);
    TEST_ASSERT_EQUAL_UINT8(0U, result);
    TEST_ASSERT_EQUAL_UINT8(0U, MyLib_RunStateMachine_u8_GetState_u8());
    
    MyLib_UpdateGlobalRecord_Expect(NULL, &second_rec);
    MyLib_UpdateGlobalRecord_IgnoreArg_dest_p();
    result = MyLib_RunStateMachine_u8(&second_rec, 0U, NULL);
    TEST_ASSERT_EQUAL_UINT8(0U, result);
    TEST_ASSERT_EQUAL_UINT8(1U, MyLib_RunStateMachine_u8_GetState_u8());
}

/**
 * @brief Test: State 1 (Process) called twice consecutively (after valid Init) → verify second call processes with updated l_LastRecord, state transitions to 2
 */
void test_State1_CalledTwice_SecondCallProcesses_StateTransitionsTo2(void)
{
    MyLib_record_t input_rec = {.id_u16 = 30U, .value_u32 = 500U};
    uint8_t result;
    
    MyLib_UpdateGlobalRecord_Expect(NULL, &input_rec);
    MyLib_UpdateGlobalRecord_IgnoreArg_dest_p();
    result = MyLib_RunStateMachine_u8(&input_rec, 0U, NULL);
    TEST_ASSERT_EQUAL_UINT8(0U, result);
    TEST_ASSERT_EQUAL_UINT8(1U, MyLib_RunStateMachine_u8_GetState_u8());
    
    MyLib_ProcessRecord_Expect(NULL, MYLIB_MULT_VALUE_U8);
    MyLib_ProcessRecord_IgnoreArg_rec_pc();
    MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(500U, NULL, 600U);
    result = MyLib_RunStateMachine_u8(NULL, 0U, NULL);
    TEST_ASSERT_EQUAL_UINT8(0U, result);
    TEST_ASSERT_EQUAL_UINT8(2U, MyLib_RunStateMachine_u8_GetState_u8());
    
    MyLib_UpdateCounter_u8_ExpectAndReturn(600U, 0U);
    result = MyLib_RunStateMachine_u8(NULL, 0U, NULL);
    TEST_ASSERT_EQUAL_UINT8(0U, result);
    TEST_ASSERT_EQUAL_UINT8(0U, MyLib_RunStateMachine_u8_GetState_u8());
    
    MyLib_UpdateGlobalRecord_Expect(NULL, &input_rec);
    MyLib_UpdateGlobalRecord_IgnoreArg_dest_p();
    result = MyLib_RunStateMachine_u8(&input_rec, 0U, NULL);
    TEST_ASSERT_EQUAL_UINT8(0U, result);
    TEST_ASSERT_EQUAL_UINT8(1U, MyLib_RunStateMachine_u8_GetState_u8());
    
    MyLib_ProcessRecord_Expect(NULL, MYLIB_MULT_VALUE_U8);
    MyLib_ProcessRecord_IgnoreArg_rec_pc();
    MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(500U, NULL, 600U);
    result = MyLib_RunStateMachine_u8(NULL, 0U, NULL);
    TEST_ASSERT_EQUAL_UINT8(0U, result);
    TEST_ASSERT_EQUAL_UINT8(2U, MyLib_RunStateMachine_u8_GetState_u8());
}

/**
 * @brief Test: State machine recovery from invalid state during State 1 → manually corrupt l_State_u8 to invalid value, next call returns 3 and resets state
 */
void test_State1_CorruptToInvalid_NextCallReturns3_ResetsState(void)
{
    MyLib_record_t input_rec = {.id_u16 = 40U, .value_u32 = 700U};
    uint8_t result;
    
    MyLib_UpdateGlobalRecord_Expect(NULL, &input_rec);
    MyLib_UpdateGlobalRecord_IgnoreArg_dest_p();
    result = MyLib_RunStateMachine_u8(&input_rec, 0U, NULL);
    TEST_ASSERT_EQUAL_UINT8(0U, result);
    TEST_ASSERT_EQUAL_UINT8(1U, MyLib_RunStateMachine_u8_GetState_u8());
    
    MyLib_RunStateMachine_u8_SetState_u8(99U);
    MyLib_RunStateMachine_u8_SetLastAdjusted_u32(888U);
    
    result = MyLib_RunStateMachine_u8(NULL, 0U, NULL);
    TEST_ASSERT_EQUAL_UINT8(3U, result);
    TEST_ASSERT_EQUAL_UINT8(0U, MyLib_RunStateMachine_u8_GetState_u8());
    TEST_ASSERT_EQUAL_UINT32(0U, MyLib_RunStateMachine_u8_GetLastAdjusted_u32());
}

/**
 * @brief Test: State machine recovery from invalid state during State 2 → manually corrupt l_State_u8 to invalid value, next call returns 3 and resets state
 */
void test_State2_CorruptToInvalid_NextCallReturns3_ResetsState(void)
{
    MyLib_record_t input_rec = {.id_u16 = 50U, .value_u32 = 900U};
    uint8_t result;
    
    MyLib_UpdateGlobalRecord_Expect(NULL, &input_rec);
    MyLib_UpdateGlobalRecord_IgnoreArg_dest_p();
    result = MyLib_RunStateMachine_u8(&input_rec, 0U, NULL);
    TEST_ASSERT_EQUAL_UINT8(0U, result);
    TEST_ASSERT_EQUAL_UINT8(1U, MyLib_RunStateMachine_u8_GetState_u8());
    
    MyLib_ProcessRecord_Expect(NULL, MYLIB_MULT_VALUE_U8);
    MyLib_ProcessRecord_IgnoreArg_rec_pc();
    MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(900U, NULL, 1000U);
    result = MyLib_RunStateMachine_u8(NULL, 0U, NULL);
    TEST_ASSERT_EQUAL_UINT8(0U, result);
    TEST_ASSERT_EQUAL_UINT8(2U, MyLib_RunStateMachine_u8_GetState_u8());
    
    MyLib_RunStateMachine_u8_SetState_u8(200U);
    MyLib_RunStateMachine_u8_SetLastAdjusted_u32(7777U);
    
    result = MyLib_RunStateMachine_u8(NULL, 0U, NULL);
    TEST_ASSERT_EQUAL_UINT8(3U, result);
    TEST_ASSERT_EQUAL_UINT8(0U, MyLib_RunStateMachine_u8_GetState_u8());
    TEST_ASSERT_EQUAL_UINT32(0U, MyLib_RunStateMachine_u8_GetLastAdjusted_u32());
}