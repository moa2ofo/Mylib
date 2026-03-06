#include "unity.h"
#include <MyLib_RunStateMachine_u8.h>
#include "mock_MyLib.h"




/* SECTION 1 — setUp() and tearDown() */

void setUp(void)
{
    g_counter_u32 = 0U;
    g_record.id_u16 = 0U;
    g_record.value_u32 = 0U;
    g_systemReady_b = false;
    
    MyLib_RunStateMachine_u8_SetState(0U);
    MyLib_RunStateMachine_u8_SetLastAdjusted(0U);
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
    TEST_ASSERT_EQUAL_UINT8(0U, MyLib_RunStateMachine_u8_GetState());
}

/**
 * @brief Test: State 0 (Init) with valid rec_pc → expect return 0, state transitions to 1, l_LastRecord updated via MyLib_UpdateGlobalRecord
 */
void test_State0_ValidRecPtr_Returns0_StateTransitionsTo1(void)
{
    MyLib_record_t input_rec = {.id_u16 = 42U, .value_u32 = 1000U};
    uint8_t result;
    
    MyLib_UpdateGlobalRecord_Expect(NULL, &input_rec);
    MyLib_UpdateGlobalRecord_IgnoreArg_dest_p();
    
    result = MyLib_RunStateMachine_u8(&input_rec, 0U, NULL);
    
    TEST_ASSERT_EQUAL_UINT8(0U, result);
    TEST_ASSERT_EQUAL_UINT8(1U, MyLib_RunStateMachine_u8_GetState());
}

/**
 * @brief Test: State 1 (Process) with NULL delta_pc_u16 → expect return 0, state transitions to 2, MyLib_ProcessRecord and MyLib_ComputeAdjustedValue_u32 invoked with NULL delta
 */
void test_State1_NullDelta_Returns0_StateTransitionsTo2(void)
{
    MyLib_record_t input_rec = {.id_u16 = 10U, .value_u32 = 500U};
    uint8_t result;
    
    MyLib_RunStateMachine_u8_SetState(1U);
    
    MyLib_ProcessRecord_Expect(NULL, MYLIB_MULT_VALUE_U8);
    MyLib_ProcessRecord_IgnoreArg_rec_pc();
    
    MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(0U, NULL, 250U);
    MyLib_ComputeAdjustedValue_u32_IgnoreArg_base_u32();
    
    result = MyLib_RunStateMachine_u8(&input_rec, 0U, NULL);
    
    TEST_ASSERT_EQUAL_UINT8(0U, result);
    TEST_ASSERT_EQUAL_UINT8(2U, MyLib_RunStateMachine_u8_GetState());
    TEST_ASSERT_EQUAL_UINT32(250U, MyLib_RunStateMachine_u8_GetLastAdjusted());
}

/**
 * @brief Test: State 1 (Process) with valid delta_pc_u16 → expect return 0, state transitions to 2, MyLib_ProcessRecord and MyLib_ComputeAdjustedValue_u32 invoked with valid delta
 */
void test_State1_ValidDelta_Returns0_StateTransitionsTo2(void)
{
    MyLib_record_t input_rec = {.id_u16 = 20U, .value_u32 = 800U};
    uint16_t delta = 50U;
    uint8_t result;
    
    MyLib_RunStateMachine_u8_SetState(1U);
    
    MyLib_ProcessRecord_Expect(NULL, MYLIB_MULT_VALUE_U8);
    MyLib_ProcessRecord_IgnoreArg_rec_pc();
    
    MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(0U, &delta, 350U);
    MyLib_ComputeAdjustedValue_u32_IgnoreArg_base_u32();
    
    result = MyLib_RunStateMachine_u8(&input_rec, 0U, &delta);
    
    TEST_ASSERT_EQUAL_UINT8(0U, result);
    TEST_ASSERT_EQUAL_UINT8(2U, MyLib_RunStateMachine_u8_GetState());
    TEST_ASSERT_EQUAL_UINT32(350U, MyLib_RunStateMachine_u8_GetLastAdjusted());
}

/**
 * @brief Test: State 2 (Update counter) with add_u32=0 and l_LastAdjusted_u32=0 → MyLib_UpdateCounter_u8 returns 0 → expect return 0, state transitions to 0
 */
void test_State2_AddZero_AdjustedZero_Returns0_StateTransitionsTo0(void)
{
    uint8_t result;
    
    MyLib_RunStateMachine_u8_SetState(2U);
    MyLib_RunStateMachine_u8_SetLastAdjusted(0U);
    
    MyLib_UpdateCounter_u8_ExpectAndReturn(0U, 0U);
    
    result = MyLib_RunStateMachine_u8(NULL, 0U, NULL);
    
    TEST_ASSERT_EQUAL_UINT8(0U, result);
    TEST_ASSERT_EQUAL_UINT8(0U, MyLib_RunStateMachine_u8_GetState());
}

/**
 * @brief Test: State 2 (Update counter) with add_u32 and l_LastAdjusted_u32 summing to a value causing MyLib_UpdateCounter_u8 to return 2 (saturation) → expect return 2, state transitions to 0
 */
void test_State2_SaturationCase_Returns2_StateTransitionsTo0(void)
{
    uint8_t result;
    
    MyLib_RunStateMachine_u8_SetState(2U);
    MyLib_RunStateMachine_u8_SetLastAdjusted(500U);
    
    MyLib_UpdateCounter_u8_ExpectAndReturn(700U, 2U);
    
    result = MyLib_RunStateMachine_u8(NULL, 200U, NULL);
    
    TEST_ASSERT_EQUAL_UINT8(2U, result);
    TEST_ASSERT_EQUAL_UINT8(0U, MyLib_RunStateMachine_u8_GetState());
}

/**
 * @brief Test: State 2 (Update counter) with add_u32=UINT32_MAX and l_LastAdjusted_u32=1 causing wrap → MyLib_UpdateCounter_u8 invoked with wrapped sum, returns 0 → expect return 0, state transitions to 0
 */
void test_State2_WrapMaxPlus1_Returns0_StateTransitionsTo0(void)
{
    uint8_t result;
    
    MyLib_RunStateMachine_u8_SetState(2U);
    MyLib_RunStateMachine_u8_SetLastAdjusted(1U);
    
    MyLib_UpdateCounter_u8_ExpectAndReturn(0U, 0U);
    
    result = MyLib_RunStateMachine_u8(NULL, UINT32_MAX, NULL);
    
    TEST_ASSERT_EQUAL_UINT8(0U, result);
    TEST_ASSERT_EQUAL_UINT8(0U, MyLib_RunStateMachine_u8_GetState());
}

/**
 * @brief Test: State 2 (Update counter) with add_u32=1 and l_LastAdjusted_u32=UINT32_MAX causing wrap → MyLib_UpdateCounter_u8 invoked with wrapped sum, returns 0 → expect return 0, state transitions to 0
 */
void test_State2_Wrap1PlusMax_Returns0_StateTransitionsTo0(void)
{
    uint8_t result;
    
    MyLib_RunStateMachine_u8_SetState(2U);
    MyLib_RunStateMachine_u8_SetLastAdjusted(UINT32_MAX);
    
    MyLib_UpdateCounter_u8_ExpectAndReturn(0U, 0U);
    
    result = MyLib_RunStateMachine_u8(NULL, 1U, NULL);
    
    TEST_ASSERT_EQUAL_UINT8(0U, result);
    TEST_ASSERT_EQUAL_UINT8(0U, MyLib_RunStateMachine_u8_GetState());
}

/**
 * @brief Test: Invalid state (e.g., l_State_u8=3) → expect return 3, state reset to 0, l_LastAdjusted_u32 reset to 0
 */
void test_InvalidState3_Returns3_StateResetTo0_AdjustedResetTo0(void)
{
    uint8_t result;
    
    MyLib_RunStateMachine_u8_SetState(3U);
    MyLib_RunStateMachine_u8_SetLastAdjusted(999U);
    
    result = MyLib_RunStateMachine_u8(NULL, 0U, NULL);
    
    TEST_ASSERT_EQUAL_UINT8(3U, result);
    TEST_ASSERT_EQUAL_UINT8(0U, MyLib_RunStateMachine_u8_GetState());
    TEST_ASSERT_EQUAL_UINT32(0U, MyLib_RunStateMachine_u8_GetLastAdjusted());
}

/**
 * @brief Test: Invalid state (e.g., l_State_u8=255) → expect return 3, state reset to 0, l_LastAdjusted_u32 reset to 0
 */
void test_InvalidState255_Returns3_StateResetTo0_AdjustedResetTo0(void)
{
    uint8_t result;
    
    MyLib_RunStateMachine_u8_SetState(255U);
    MyLib_RunStateMachine_u8_SetLastAdjusted(12345U);
    
    result = MyLib_RunStateMachine_u8(NULL, 0U, NULL);
    
    TEST_ASSERT_EQUAL_UINT8(3U, result);
    TEST_ASSERT_EQUAL_UINT8(0U, MyLib_RunStateMachine_u8_GetState());
    TEST_ASSERT_EQUAL_UINT32(0U, MyLib_RunStateMachine_u8_GetLastAdjusted());
}

/**
 * @brief Test: Full state machine cycle (State 0 → 1 → 2 → 0) with valid inputs and MyLib_UpdateCounter_u8 returning 0 → verify correct sequence of return codes (0, 0, 0) and final state 0
 */
void test_FullCycle_UpdateReturns0_VerifySequence000_FinalState0(void)
{
    MyLib_record_t input_rec = {.id_u16 = 100U, .value_u32 = 2000U};
    uint16_t delta = 10U;
    uint8_t result1, result2, result3;
    
    MyLib_UpdateGlobalRecord_Expect(NULL, &input_rec);
    MyLib_UpdateGlobalRecord_IgnoreArg_dest_p();
    result1 = MyLib_RunStateMachine_u8(&input_rec, 50U, &delta);
    
    MyLib_ProcessRecord_Expect(NULL, MYLIB_MULT_VALUE_U8);
    MyLib_ProcessRecord_IgnoreArg_rec_pc();
    MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(0U, &delta, 1500U);
    MyLib_ComputeAdjustedValue_u32_IgnoreArg_base_u32();
    result2 = MyLib_RunStateMachine_u8(&input_rec, 50U, &delta);
    
    MyLib_UpdateCounter_u8_ExpectAndReturn(1550U, 0U);
    result3 = MyLib_RunStateMachine_u8(&input_rec, 50U, &delta);
    
    TEST_ASSERT_EQUAL_UINT8(0U, result1);
    TEST_ASSERT_EQUAL_UINT8(0U, result2);
    TEST_ASSERT_EQUAL_UINT8(0U, result3);
    TEST_ASSERT_EQUAL_UINT8(0U, MyLib_RunStateMachine_u8_GetState());
}

/**
 * @brief Test: Full state machine cycle (State 0 → 1 → 2 → 0) with valid inputs and MyLib_UpdateCounter_u8 returning 2 → verify correct sequence of return codes (0, 0, 2) and final state 0
 */
void test_FullCycle_UpdateReturns2_VerifySequence002_FinalState0(void)
{
    MyLib_record_t input_rec = {.id_u16 = 200U, .value_u32 = 3000U};
    uint8_t result1, result2, result3;
    
    MyLib_UpdateGlobalRecord_Expect(NULL, &input_rec);
    MyLib_UpdateGlobalRecord_IgnoreArg_dest_p();
    result1 = MyLib_RunStateMachine_u8(&input_rec, 100U, NULL);
    
    MyLib_ProcessRecord_Expect(NULL, MYLIB_MULT_VALUE_U8);
    MyLib_ProcessRecord_IgnoreArg_rec_pc();
    MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(0U, NULL, 2500U);
    MyLib_ComputeAdjustedValue_u32_IgnoreArg_base_u32();
    result2 = MyLib_RunStateMachine_u8(&input_rec, 100U, NULL);
    
    MyLib_UpdateCounter_u8_ExpectAndReturn(2600U, 2U);
    result3 = MyLib_RunStateMachine_u8(&input_rec, 100U, NULL);
    
    TEST_ASSERT_EQUAL_UINT8(0U, result1);
    TEST_ASSERT_EQUAL_UINT8(0U, result2);
    TEST_ASSERT_EQUAL_UINT8(2U, result3);
    TEST_ASSERT_EQUAL_UINT8(0U, MyLib_RunStateMachine_u8_GetState());
}

/**
 * @brief Test: State 0 (Init) rejection followed by valid initialization → first call returns 1, second call with valid rec_pc returns 0 and transitions to state 1
 */
void test_State0_RejectionThenValid_FirstReturns1_SecondReturns0_TransitionsTo1(void)
{
    MyLib_record_t input_rec = {.id_u16 = 50U, .value_u32 = 750U};
    uint8_t result1, result2;
    
    result1 = MyLib_RunStateMachine_u8(NULL, 0U, NULL);
    
    MyLib_UpdateGlobalRecord_Expect(NULL, &input_rec);
    MyLib_UpdateGlobalRecord_IgnoreArg_dest_p();
    result2 = MyLib_RunStateMachine_u8(&input_rec, 0U, NULL);
    
    TEST_ASSERT_EQUAL_UINT8(1U, result1);
    TEST_ASSERT_EQUAL_UINT8(0U, MyLib_RunStateMachine_u8_GetState());
    TEST_ASSERT_EQUAL_UINT8(0U, result2);
    TEST_ASSERT_EQUAL_UINT8(1U, MyLib_RunStateMachine_u8_GetState());
}

/**
 * @brief Test: State 2 (Update counter) with add_u32 at lower boundary (0) and l_LastAdjusted_u32 at lower boundary (0) → MyLib_UpdateCounter_u8 invoked with 0, returns 0 → expect return 0
 */
void test_State2_LowerBoundaries_Returns0(void)
{
    uint8_t result;
    
    MyLib_RunStateMachine_u8_SetState(2U);
    MyLib_RunStateMachine_u8_SetLastAdjusted(0U);
    
    MyLib_UpdateCounter_u8_ExpectAndReturn(0U, 0U);
    
    result = MyLib_RunStateMachine_u8(NULL, 0U, NULL);
    
    TEST_ASSERT_EQUAL_UINT8(0U, result);
}

/**
 * @brief Test: State 2 (Update counter) with add_u32 at upper boundary (UINT32_MAX) and l_LastAdjusted_u32=0 → MyLib_UpdateCounter_u8 invoked with UINT32_MAX, returns status → expect return matches MyLib_UpdateCounter_u8 result
 */
void test_State2_AddUpperBoundary_AdjustedZero_ReturnsMatchesUpdate(void)
{
    uint8_t result;
    
    MyLib_RunStateMachine_u8_SetState(2U);
    MyLib_RunStateMachine_u8_SetLastAdjusted(0U);
    
    MyLib_UpdateCounter_u8_ExpectAndReturn(UINT32_MAX, 1U);
    
    result = MyLib_RunStateMachine_u8(NULL, UINT32_MAX, NULL);
    
    TEST_ASSERT_EQUAL_UINT8(1U, result);
    TEST_ASSERT_EQUAL_UINT8(0U, MyLib_RunStateMachine_u8_GetState());
}

/**
 * @brief Test: State 2 (Update counter) with add_u32=0 and l_LastAdjusted_u32 at upper boundary (UINT32_MAX) → MyLib_UpdateCounter_u8 invoked with UINT32_MAX, returns status → expect return matches MyLib_UpdateCounter_u8 result
 */
void test_State2_AddZero_AdjustedUpperBoundary_ReturnsMatchesUpdate(void)
{
    uint8_t result;
    
    MyLib_RunStateMachine_u8_SetState(2U);
    MyLib_RunStateMachine_u8_SetLastAdjusted(UINT32_MAX);
    
    MyLib_UpdateCounter_u8_ExpectAndReturn(UINT32_MAX, 2U);
    
    result = MyLib_RunStateMachine_u8(NULL, 0U, NULL);
    
    TEST_ASSERT_EQUAL_UINT8(2U, result);
    TEST_ASSERT_EQUAL_UINT8(0U, MyLib_RunStateMachine_u8_GetState());
}

/**
 * @brief Test: State 2 (Update counter) with mid-range add_u32 (e.g., 0x80000000) and mid-range l_LastAdjusted_u32 (e.g., 0x40000000) → MyLib_UpdateCounter_u8 invoked with sum, returns 0 → expect return 0
 */
void test_State2_MidRangeValues_Returns0(void)
{
    uint8_t result;
    
    MyLib_RunStateMachine_u8_SetState(2U);
    MyLib_RunStateMachine_u8_SetLastAdjusted(0x40000000U);
    
    MyLib_UpdateCounter_u8_ExpectAndReturn(0xC0000000U, 0U);
    
    result = MyLib_RunStateMachine_u8(NULL, 0x80000000U, NULL);
    
    TEST_ASSERT_EQUAL_UINT8(0U, result);
    TEST_ASSERT_EQUAL_UINT8(0U, MyLib_RunStateMachine_u8_GetState());
}

/**
 * @brief Test: State machine recovery from invalid state followed by valid initialization → invalid state call returns 3 and resets to 0, next call with valid rec_pc returns 0 and transitions to 1
 */
void test_RecoveryFromInvalidState_ThenValidInit_VerifySequence(void)
{
    MyLib_record_t input_rec = {.id_u16 = 77U, .value_u32 = 888U};
    uint8_t result1, result2;
    
    MyLib_RunStateMachine_u8_SetState(10U);
    MyLib_RunStateMachine_u8_SetLastAdjusted(5555U);
    
    result1 = MyLib_RunStateMachine_u8(NULL, 0U, NULL);
    
    TEST_ASSERT_EQUAL_UINT8(3U, result1);
    TEST_ASSERT_EQUAL_UINT8(0U, MyLib_RunStateMachine_u8_GetState());
    TEST_ASSERT_EQUAL_UINT32(0U, MyLib_RunStateMachine_u8_GetLastAdjusted());
    
    MyLib_UpdateGlobalRecord_Expect(NULL, &input_rec);
    MyLib_UpdateGlobalRecord_IgnoreArg_dest_p();
    result2 = MyLib_RunStateMachine_u8(&input_rec, 0U, NULL);
    
    TEST_ASSERT_EQUAL_UINT8(0U, result2);
    TEST_ASSERT_EQUAL_UINT8(1U, MyLib_RunStateMachine_u8_GetState());
}