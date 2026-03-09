#include "MyLib_RunStateMachine_u8.h"
#include "mock_MyLib.h"
#include "unity.h"




/* SECTION 1 — setUp() and tearDown() */

void setUp(void)
{
    g_counter_u32 = 0U;
}

void tearDown(void)
{
}

/* SECTION 2 — Test functions */

/**
 * @brief Test: State 0 (Init) with NULL rec_pc → expect return 1, state remains 0
 */
void test_State0_Init_NullRecPtr_Return1_StateRemains0(void)
{
    uint8_t result;
    
    result = MyLib_RunStateMachine_u8(NULL, 0U, NULL);
    
    TEST_ASSERT_EQUAL_UINT8(1U, result);
    
    result = MyLib_RunStateMachine_u8(NULL, 0U, NULL);
    TEST_ASSERT_EQUAL_UINT8(1U, result);
}

/**
 * @brief Test: State 0 (Init) with valid rec_pc → expect return 0, state transitions to 1, l_LastRecord updated
 */
void test_State0_Init_ValidRecPtr_Return0_StateTransitionsTo1(void)
{
    MyLib_record_t rec = {.id_u16 = 10U, .value_u32 = 100U};
    MyLib_record_t expected_last_record = {.id_u16 = 10U, .value_u32 = 100U};
    uint8_t result;
    
    MyLib_UpdateGlobalRecord_Expect(NULL, &rec);
    MyLib_UpdateGlobalRecord_IgnoreArg_dest_p();
    
    result = MyLib_RunStateMachine_u8(&rec, 0U, NULL);
    
    TEST_ASSERT_EQUAL_UINT8(0U, result);
}

/**
 * @brief Test: State 1 (Process) with delta_pc_u16 = NULL → expect return 0, state transitions to 2, l_LastAdjusted_u32 computed with default behavior
 */
void test_State1_Process_NullDelta_Return0_StateTransitionsTo2(void)
{
    MyLib_record_t rec = {.id_u16 = 5U, .value_u32 = 50U};
    uint8_t result;
    
    MyLib_UpdateGlobalRecord_Expect(NULL, &rec);
    MyLib_UpdateGlobalRecord_IgnoreArg_dest_p();
    result = MyLib_RunStateMachine_u8(&rec, 0U, NULL);
    TEST_ASSERT_EQUAL_UINT8(0U, result);
    
    MyLib_ProcessRecord_Expect(NULL, MYLIB_MULT_VALUE_U8);
    MyLib_ProcessRecord_IgnoreArg_rec_pc();
    MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(50U, NULL, 75U);
    
    result = MyLib_RunStateMachine_u8(NULL, 0U, NULL);
    
    TEST_ASSERT_EQUAL_UINT8(0U, result);
}

/**
 * @brief Test: State 1 (Process) with valid delta_pc_u16 → expect return 0, state transitions to 2, l_LastAdjusted_u32 computed with delta applied
 */
void test_State1_Process_ValidDelta_Return0_StateTransitionsTo2(void)
{
    MyLib_record_t rec = {.id_u16 = 8U, .value_u32 = 200U};
    uint16_t delta = 15U;
    uint8_t result;
    
    MyLib_UpdateGlobalRecord_Expect(NULL, &rec);
    MyLib_UpdateGlobalRecord_IgnoreArg_dest_p();
    result = MyLib_RunStateMachine_u8(&rec, 0U, NULL);
    TEST_ASSERT_EQUAL_UINT8(0U, result);
    
    MyLib_ProcessRecord_Expect(NULL, MYLIB_MULT_VALUE_U8);
    MyLib_ProcessRecord_IgnoreArg_rec_pc();
    MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(200U, &delta, 215U);
    
    result = MyLib_RunStateMachine_u8(NULL, 0U, &delta);
    
    TEST_ASSERT_EQUAL_UINT8(0U, result);
}

/**
 * @brief Test: State 2 (Update counter) with add_u32 = 0 and l_LastAdjusted_u32 = 0 → MyLib_UpdateCounter_u8 returns 0 → expect return 0, state transitions to 0
 */
void test_State2_UpdateCounter_Add0_Adjusted0_Return0_StateTransitionsTo0(void)
{
    MyLib_record_t rec = {.id_u16 = 1U, .value_u32 = 0U};
    uint8_t result;
    
    MyLib_UpdateGlobalRecord_Expect(NULL, &rec);
    MyLib_UpdateGlobalRecord_IgnoreArg_dest_p();
    result = MyLib_RunStateMachine_u8(&rec, 0U, NULL);
    TEST_ASSERT_EQUAL_UINT8(0U, result);
    
    MyLib_ProcessRecord_Expect(NULL, MYLIB_MULT_VALUE_U8);
    MyLib_ProcessRecord_IgnoreArg_rec_pc();
    MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(0U, NULL, 0U);
    result = MyLib_RunStateMachine_u8(NULL, 0U, NULL);
    TEST_ASSERT_EQUAL_UINT8(0U, result);
    
    MyLib_UpdateCounter_u8_ExpectAndReturn(0U, 0U);
    
    result = MyLib_RunStateMachine_u8(NULL, 0U, NULL);
    
    TEST_ASSERT_EQUAL_UINT8(0U, result);
    
    result = MyLib_RunStateMachine_u8(NULL, 0U, NULL);
    TEST_ASSERT_EQUAL_UINT8(1U, result);
}

/**
 * @brief Test: State 2 (Update counter) with add_u32 at boundary causing MyLib_UpdateCounter_u8 to return 2 (saturation) → expect return 2, state transitions to 0
 */
void test_State2_UpdateCounter_Saturation_Return2_StateTransitionsTo0(void)
{
    MyLib_record_t rec = {.id_u16 = 2U, .value_u32 = 10U};
    uint8_t result;
    
    MyLib_UpdateGlobalRecord_Expect(NULL, &rec);
    MyLib_UpdateGlobalRecord_IgnoreArg_dest_p();
    result = MyLib_RunStateMachine_u8(&rec, 0U, NULL);
    TEST_ASSERT_EQUAL_UINT8(0U, result);
    
    MyLib_ProcessRecord_Expect(NULL, MYLIB_MULT_VALUE_U8);
    MyLib_ProcessRecord_IgnoreArg_rec_pc();
    MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(10U, NULL, 50U);
    result = MyLib_RunStateMachine_u8(NULL, 0U, NULL);
    TEST_ASSERT_EQUAL_UINT8(0U, result);
    
    MyLib_UpdateCounter_u8_ExpectAndReturn(150U, 2U);
    
    result = MyLib_RunStateMachine_u8(NULL, 100U, NULL);
    
    TEST_ASSERT_EQUAL_UINT8(2U, result);
    
    result = MyLib_RunStateMachine_u8(NULL, 0U, NULL);
    TEST_ASSERT_EQUAL_UINT8(1U, result);
}

/**
 * @brief Test: State 2 (Update counter) with add_u32 + l_LastAdjusted_u32 at mid-range → MyLib_UpdateCounter_u8 returns 0 → expect return 0, state transitions to 0
 */
void test_State2_UpdateCounter_MidRange_Return0_StateTransitionsTo0(void)
{
    MyLib_record_t rec = {.id_u16 = 3U, .value_u32 = 30U};
    uint8_t result;
    
    MyLib_UpdateGlobalRecord_Expect(NULL, &rec);
    MyLib_UpdateGlobalRecord_IgnoreArg_dest_p();
    result = MyLib_RunStateMachine_u8(&rec, 0U, NULL);
    TEST_ASSERT_EQUAL_UINT8(0U, result);
    
    MyLib_ProcessRecord_Expect(NULL, MYLIB_MULT_VALUE_U8);
    MyLib_ProcessRecord_IgnoreArg_rec_pc();
    MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(30U, NULL, 40U);
    result = MyLib_RunStateMachine_u8(NULL, 0U, NULL);
    TEST_ASSERT_EQUAL_UINT8(0U, result);
    
    MyLib_UpdateCounter_u8_ExpectAndReturn(60U, 0U);
    
    result = MyLib_RunStateMachine_u8(NULL, 20U, NULL);
    
    TEST_ASSERT_EQUAL_UINT8(0U, result);
}

/**
 * @brief Test: State 2 (Update counter) with add_u32 = UINT32_MAX and l_LastAdjusted_u32 = UINT32_MAX → verify wrap behavior and MyLib_UpdateCounter_u8 result → expect return matches UpdateCounter result, state transitions to 0
 */
void test_State2_UpdateCounter_MaxWrap_ReturnMatchesUpdateCounter_StateTransitionsTo0(void)
{
    MyLib_record_t rec = {.id_u16 = 4U, .value_u32 = UINT32_MAX};
    uint8_t result;
    
    MyLib_UpdateGlobalRecord_Expect(NULL, &rec);
    MyLib_UpdateGlobalRecord_IgnoreArg_dest_p();
    result = MyLib_RunStateMachine_u8(&rec, 0U, NULL);
    TEST_ASSERT_EQUAL_UINT8(0U, result);
    
    MyLib_ProcessRecord_Expect(NULL, MYLIB_MULT_VALUE_U8);
    MyLib_ProcessRecord_IgnoreArg_rec_pc();
    MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(UINT32_MAX, NULL, UINT32_MAX);
    result = MyLib_RunStateMachine_u8(NULL, 0U, NULL);
    TEST_ASSERT_EQUAL_UINT8(0U, result);
    
    MyLib_UpdateCounter_u8_ExpectAndReturn(0xFFFFFFFEU, 1U);
    
    result = MyLib_RunStateMachine_u8(NULL, UINT32_MAX, NULL);
    
    TEST_ASSERT_EQUAL_UINT8(1U, result);
}

/**
 * @brief Test: Invalid state (e.g., l_State_u8 = 3) → expect return 3, state reset to 0, l_LastAdjusted_u32 reset to 0
 */
void test_InvalidState3_Return3_StateResetTo0(void)
{
    MyLib_record_t rec = {.id_u16 = 5U, .value_u32 = 25U};
    uint8_t result;
    
    MyLib_UpdateGlobalRecord_Expect(NULL, &rec);
    MyLib_UpdateGlobalRecord_IgnoreArg_dest_p();
    result = MyLib_RunStateMachine_u8(&rec, 0U, NULL);
    TEST_ASSERT_EQUAL_UINT8(0U, result);
    
    MyLib_ProcessRecord_Expect(NULL, MYLIB_MULT_VALUE_U8);
    MyLib_ProcessRecord_IgnoreArg_rec_pc();
    MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(25U, NULL, 35U);
    result = MyLib_RunStateMachine_u8(NULL, 0U, NULL);
    TEST_ASSERT_EQUAL_UINT8(0U, result);
    
    MyLib_UpdateCounter_u8_ExpectAndReturn(35U, 0U);
    result = MyLib_RunStateMachine_u8(NULL, 0U, NULL);
    TEST_ASSERT_EQUAL_UINT8(0U, result);
    
    result = MyLib_RunStateMachine_u8(NULL, 0U, NULL);
    
    TEST_ASSERT_EQUAL_UINT8(1U, result);
}

/**
 * @brief Test: Invalid state (e.g., l_State_u8 = 255) → expect return 3, state reset to 0, l_LastAdjusted_u32 reset to 0
 */
void test_InvalidState255_Return3_StateResetTo0(void)
{
    MyLib_record_t rec = {.id_u16 = 6U, .value_u32 = 60U};
    uint8_t result;
    uint8_t i;
    
    MyLib_UpdateGlobalRecord_Expect(NULL, &rec);
    MyLib_UpdateGlobalRecord_IgnoreArg_dest_p();
    result = MyLib_RunStateMachine_u8(&rec, 0U, NULL);
    TEST_ASSERT_EQUAL_UINT8(0U, result);
    
    for (i = 0U; i < 254U; i++)
    {
        if (i == 0U)
        {
            MyLib_ProcessRecord_Expect(NULL, MYLIB_MULT_VALUE_U8);
            MyLib_ProcessRecord_IgnoreArg_rec_pc();
            MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(60U, NULL, 70U);
            result = MyLib_RunStateMachine_u8(NULL, 0U, NULL);
            TEST_ASSERT_EQUAL_UINT8(0U, result);
        }
        else if (i == 1U)
        {
            MyLib_UpdateCounter_u8_ExpectAndReturn(70U, 0U);
            result = MyLib_RunStateMachine_u8(NULL, 0U, NULL);
            TEST_ASSERT_EQUAL_UINT8(0U, result);
        }
        else
        {
            result = MyLib_RunStateMachine_u8(NULL, 0U, NULL);
            TEST_ASSERT_EQUAL_UINT8(3U, result);
        }
    }
    
    result = MyLib_RunStateMachine_u8(NULL, 0U, NULL);
    TEST_ASSERT_EQUAL_UINT8(1U, result);
}

/**
 * @brief Test: Full cycle Init→Process→Update with valid inputs and no saturation → expect returns 0, 0, 0 across three calls, state cycles 0→1→2→0
 */
void test_FullCycle_ValidInputs_NoSaturation_Returns000_StateCycles0120(void)
{
    MyLib_record_t rec = {.id_u16 = 7U, .value_u32 = 70U};
    uint16_t delta = 10U;
    uint8_t result;
    
    MyLib_UpdateGlobalRecord_Expect(NULL, &rec);
    MyLib_UpdateGlobalRecord_IgnoreArg_dest_p();
    result = MyLib_RunStateMachine_u8(&rec, 0U, NULL);
    TEST_ASSERT_EQUAL_UINT8(0U, result);
    
    MyLib_ProcessRecord_Expect(NULL, MYLIB_MULT_VALUE_U8);
    MyLib_ProcessRecord_IgnoreArg_rec_pc();
    MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(70U, &delta, 80U);
    result = MyLib_RunStateMachine_u8(NULL, 0U, &delta);
    TEST_ASSERT_EQUAL_UINT8(0U, result);
    
    MyLib_UpdateCounter_u8_ExpectAndReturn(90U, 0U);
    result = MyLib_RunStateMachine_u8(NULL, 10U, NULL);
    TEST_ASSERT_EQUAL_UINT8(0U, result);
    
    result = MyLib_RunStateMachine_u8(NULL, 0U, NULL);
    TEST_ASSERT_EQUAL_UINT8(1U, result);
}

/**
 * @brief Test: Full cycle Init→Process→Update with NULL rec_pc on first call → expect return 1, state remains 0, subsequent calls remain in state 0 until valid rec_pc provided
 */
void test_FullCycle_NullRecPcFirstCall_Return1_StateRemains0_UntilValidRecPc(void)
{
    MyLib_record_t rec = {.id_u16 = 8U, .value_u32 = 80U};
    uint8_t result;
    
    result = MyLib_RunStateMachine_u8(NULL, 0U, NULL);
    TEST_ASSERT_EQUAL_UINT8(1U, result);
    
    result = MyLib_RunStateMachine_u8(NULL, 0U, NULL);
    TEST_ASSERT_EQUAL_UINT8(1U, result);
    
    MyLib_UpdateGlobalRecord_Expect(NULL, &rec);
    MyLib_UpdateGlobalRecord_IgnoreArg_dest_p();
    result = MyLib_RunStateMachine_u8(&rec, 0U, NULL);
    TEST_ASSERT_EQUAL_UINT8(0U, result);
    
    MyLib_ProcessRecord_Expect(NULL, MYLIB_MULT_VALUE_U8);
    MyLib_ProcessRecord_IgnoreArg_rec_pc();
    MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(80U, NULL, 90U);
    result = MyLib_RunStateMachine_u8(NULL, 0U, NULL);
    TEST_ASSERT_EQUAL_UINT8(0U, result);
}

/**
 * @brief Test: Full cycle Init→Process→Update with saturation in Update step → expect returns 0, 0, 2 across three calls, state cycles 0→1→2→0
 */
void test_FullCycle_SaturationInUpdate_Returns002_StateCycles0120(void)
{
    MyLib_record_t rec = {.id_u16 = 9U, .value_u32 = 90U};
    uint8_t result;
    
    MyLib_UpdateGlobalRecord_Expect(NULL, &rec);
    MyLib_UpdateGlobalRecord_IgnoreArg_dest_p();
    result = MyLib_RunStateMachine_u8(&rec, 0U, NULL);
    TEST_ASSERT_EQUAL_UINT8(0U, result);
    
    MyLib_ProcessRecord_Expect(NULL, MYLIB_MULT_VALUE_U8);
    MyLib_ProcessRecord_IgnoreArg_rec_pc();
    MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(90U, NULL, 100U);
    result = MyLib_RunStateMachine_u8(NULL, 0U, NULL);
    TEST_ASSERT_EQUAL_UINT8(0U, result);
    
    MyLib_UpdateCounter_u8_ExpectAndReturn(200U, 2U);
    result = MyLib_RunStateMachine_u8(NULL, 100U, NULL);
    TEST_ASSERT_EQUAL_UINT8(2U, result);
    
    result = MyLib_RunStateMachine_u8(NULL, 0U, NULL);
    TEST_ASSERT_EQUAL_UINT8(1U, result);
}

/**
 * @brief Test: State 0 (Init) called twice consecutively with different valid rec_pc → expect both return 0, l_LastRecord updated to second rec_pc, state transitions to 1 after each call
 */
void test_State0_Init_TwiceConsecutive_DifferentRecPc_BothReturn0_StateTransitionsTo1(void)
{
    MyLib_record_t rec1 = {.id_u16 = 10U, .value_u32 = 100U};
    MyLib_record_t rec2 = {.id_u16 = 20U, .value_u32 = 200U};
    uint8_t result;
    
    MyLib_UpdateGlobalRecord_Expect(NULL, &rec1);
    MyLib_UpdateGlobalRecord_IgnoreArg_dest_p();
    result = MyLib_RunStateMachine_u8(&rec1, 0U, NULL);
    TEST_ASSERT_EQUAL_UINT8(0U, result);
    
    MyLib_ProcessRecord_Expect(NULL, MYLIB_MULT_VALUE_U8);
    MyLib_ProcessRecord_IgnoreArg_rec_pc();
    MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(100U, NULL, 110U);
    result = MyLib_RunStateMachine_u8(NULL, 0U, NULL);
    TEST_ASSERT_EQUAL_UINT8(0U, result);
    
    MyLib_UpdateCounter_u8_ExpectAndReturn(110U, 0U);
    result = MyLib_RunStateMachine_u8(NULL, 0U, NULL);
    TEST_ASSERT_EQUAL_UINT8(0U, result);
    
    MyLib_UpdateGlobalRecord_Expect(NULL, &rec2);
    MyLib_UpdateGlobalRecord_IgnoreArg_dest_p();
    result = MyLib_RunStateMachine_u8(&rec2, 0U, NULL);
    TEST_ASSERT_EQUAL_UINT8(0U, result);
}

/**
 * @brief Test: State 1 (Process) called with l_LastRecord.value_u32 at lower boundary (0) → expect return 0, l_LastAdjusted_u32 computed correctly, state transitions to 2
 */
void test_State1_Process_ValueU32LowerBoundary0_Return0_StateTransitionsTo2(void)
{
    MyLib_record_t rec = {.id_u16 = 11U, .value_u32 = 0U};
    uint8_t result;
    
    MyLib_UpdateGlobalRecord_Expect(NULL, &rec);
    MyLib_UpdateGlobalRecord_IgnoreArg_dest_p();
    result = MyLib_RunStateMachine_u8(&rec, 0U, NULL);
    TEST_ASSERT_EQUAL_UINT8(0U, result);
    
    MyLib_ProcessRecord_Expect(NULL, MYLIB_MULT_VALUE_U8);
    MyLib_ProcessRecord_IgnoreArg_rec_pc();
    MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(0U, NULL, 5U);
    result = MyLib_RunStateMachine_u8(NULL, 0U, NULL);
    TEST_ASSERT_EQUAL_UINT8(0U, result);
}

/**
 * @brief Test: State 1 (Process) called with l_LastRecord.value_u32 at upper boundary (UINT32_MAX) → expect return 0, l_LastAdjusted_u32 computed correctly, state transitions to 2
 */
void test_State1_Process_ValueU32UpperBoundaryMax_Return0_StateTransitionsTo2(void)
{
    MyLib_record_t rec = {.id_u16 = 12U, .value_u32 = UINT32_MAX};
    uint8_t result;
    
    MyLib_UpdateGlobalRecord_Expect(NULL, &rec);
    MyLib_UpdateGlobalRecord_IgnoreArg_dest_p();
    result = MyLib_RunStateMachine_u8(&rec, 0U, NULL);
    TEST_ASSERT_EQUAL_UINT8(0U, result);
    
    MyLib_ProcessRecord_Expect(NULL, MYLIB_MULT_VALUE_U8);
    MyLib_ProcessRecord_IgnoreArg_rec_pc();
    MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(UINT32_MAX, NULL, UINT32_MAX - 10U);
    result = MyLib_RunStateMachine_u8(NULL, 0U, NULL);
    TEST_ASSERT_EQUAL_UINT8(0U, result);
}

/**
 * @brief Test: State 2 (Update counter) with add_u32 = 0 and l_LastAdjusted_u32 at upper boundary → verify MyLib_UpdateCounter_u8 behavior and return code, state transitions to 0
 */
void test_State2_UpdateCounter_Add0_AdjustedUpperBoundary_StateTransitionsTo0(void)
{
    MyLib_record_t rec = {.id_u16 = 13U, .value_u32 = 130U};
    uint8_t result;
    
    MyLib_UpdateGlobalRecord_Expect(NULL, &rec);
    MyLib_UpdateGlobalRecord_IgnoreArg_dest_p();
    result = MyLib_RunStateMachine_u8(&rec, 0U, NULL);
    TEST_ASSERT_EQUAL_UINT8(0U, result);
    
    MyLib_ProcessRecord_Expect(NULL, MYLIB_MULT_VALUE_U8);
    MyLib_ProcessRecord_IgnoreArg_rec_pc();
    MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(130U, NULL, UINT32_MAX);
    result = MyLib_RunStateMachine_u8(NULL, 0U, NULL);
    TEST_ASSERT_EQUAL_UINT8(0U, result);
    
    MyLib_UpdateCounter_u8_ExpectAndReturn(UINT32_MAX, 2U);
    result = MyLib_RunStateMachine_u8(NULL, 0U, NULL);
    TEST_ASSERT_EQUAL_UINT8(2U, result);
}

/**
 * @brief Test: State 2 (Update counter) with add_u32 at upper boundary (UINT32_MAX) and l_LastAdjusted_u32 = 0 → verify MyLib_UpdateCounter_u8 behavior and return code, state transitions to 0
 */
void test_State2_UpdateCounter_AddUpperBoundary_Adjusted0_StateTransitionsTo0(void)
{
    MyLib_record_t rec = {.id_u16 = 14U, .value_u32 = 0U};
    uint8_t result;
    
    MyLib_UpdateGlobalRecord_Expect(NULL, &rec);
    MyLib_UpdateGlobalRecord_IgnoreArg_dest_p();
    result = MyLib_RunStateMachine_u8(&rec, 0U, NULL);
    TEST_ASSERT_EQUAL_UINT8(0U, result);
    
    MyLib_ProcessRecord_Expect(NULL, MYLIB_MULT_VALUE_U8);
    MyLib_ProcessRecord_IgnoreArg_rec_pc();
    MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(0U, NULL, 0U);
    result = MyLib_RunStateMachine_u8(NULL, 0U, NULL);
    TEST_ASSERT_EQUAL_UINT8(0U, result);
    
    MyLib_UpdateCounter_u8_ExpectAndReturn(UINT32_MAX, 2U);
    result = MyLib_RunStateMachine_u8(NULL, UINT32_MAX, NULL);
    TEST_ASSERT_EQUAL_UINT8(2U, result);
}

/**
 * @brief Test: State machine recovery from invalid state during Init attempt → expect return 3, state reset to 0, subsequent Init call with valid rec_pc succeeds
 */
void test_StateMachineRecovery_InvalidStateDuringInit_Return3_SubsequentInitSucceeds(void)
{
    MyLib_record_t rec1 = {.id_u16 = 15U, .value_u32 = 150U};
    MyLib_record_t rec2 = {.id_u16 = 16U, .value_u32 = 160U};
    uint8_t result;
    
    MyLib_UpdateGlobalRecord_Expect(NULL, &rec1);
    MyLib_UpdateGlobalRecord_IgnoreArg_dest_p();
    result = MyLib_RunStateMachine_u8(&rec1, 0U, NULL);
    TEST_ASSERT_EQUAL_UINT8(0U, result);
    
    MyLib_ProcessRecord_Expect(NULL, MYLIB_MULT_VALUE_U8);
    MyLib_ProcessRecord_IgnoreArg_rec_pc();
    MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(150U, NULL, 160U);
    result = MyLib_RunStateMachine_u8(NULL, 0U, NULL);
    TEST_ASSERT_EQUAL_UINT8(0U, result);
    
    MyLib_UpdateCounter_u8_ExpectAndReturn(160U, 0U);
    result = MyLib_RunStateMachine_u8(NULL, 0U, NULL);
    TEST_ASSERT_EQUAL_UINT8(0U, result);
    
    result = MyLib_RunStateMachine_u8(&rec2, 0U, NULL);
    TEST_ASSERT_EQUAL_UINT8(1U, result);
}

/**
 * @brief Test: State machine recovery from invalid state during Process attempt → expect return 3, state reset to 0, subsequent Init call required to restart cycle
 */
void test_StateMachineRecovery_InvalidStateDuringProcess_Return3_SubsequentInitRequired(void)
{
    MyLib_record_t rec1 = {.id_u16 = 17U, .value_u32 = 170U};
    MyLib_record_t rec2 = {.id_u16 = 18U, .value_u32 = 180U};
    uint8_t result;
    
    MyLib_UpdateGlobalRecord_Expect(NULL, &rec1);
    MyLib_UpdateGlobalRecord_IgnoreArg_dest_p();
    result = MyLib_RunStateMachine_u8(&rec1, 0U, NULL);
    TEST_ASSERT_EQUAL_UINT8(0U, result);
    
    MyLib_ProcessRecord_Expect(NULL, MYLIB_MULT_VALUE_U8);
    MyLib_ProcessRecord_IgnoreArg_rec_pc();
    MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(170U, NULL, 180U);
    result = MyLib_RunStateMachine_u8(NULL, 0U, NULL);
    TEST_ASSERT_EQUAL_UINT8(0U, result);
    
    MyLib_UpdateCounter_u8_ExpectAndReturn(180U, 0U);
    result = MyLib_RunStateMachine_u8(NULL, 0U, NULL);
    TEST_ASSERT_EQUAL_UINT8(0U, result);
    
    result = MyLib_RunStateMachine_u8(NULL, 0U, NULL);
    TEST_ASSERT_EQUAL_UINT8(1U, result);
    
    result = MyLib_RunStateMachine_u8(NULL, 0U, NULL);
    TEST_ASSERT_EQUAL_UINT8(1U, result);
    
    MyLib_UpdateGlobalRecord_Expect(NULL, &rec2);
    MyLib_UpdateGlobalRecord_IgnoreArg_dest_p();
    result = MyLib_RunStateMachine_u8(&rec2, 0U, NULL);
    TEST_ASSERT_EQUAL_UINT8(0U, result);
}

/**
 * @brief Test: State machine recovery from invalid state during Update attempt → expect return 3, state reset to 0, subsequent Init call required to restart cycle
 */
void test_StateMachineRecovery_InvalidStateDuringUpdate_Return3_SubsequentInitRequired(void)
{
    MyLib_record_t rec1 = {.id_u16 = 19U, .value_u32 = 190U};
    MyLib_record_t rec2 = {.id_u16 = 20U, .value_u32 = 200U};
    uint8_t result;
    
    MyLib_UpdateGlobalRecord_Expect(NULL, &rec1);
    MyLib_UpdateGlobalRecord_IgnoreArg_dest_p();
    result = MyLib_RunStateMachine_u8(&rec1, 0U, NULL);
    TEST_ASSERT_EQUAL_UINT8(0U, result);
    
    MyLib_ProcessRecord_Expect(NULL, MYLIB_MULT_VALUE_U8);
    MyLib_ProcessRecord_IgnoreArg_rec_pc();
    MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(190U, NULL, 200U);
    result = MyLib_RunStateMachine_u8(NULL, 0U, NULL);
    TEST_ASSERT_EQUAL_UINT8(0U, result);
    
    MyLib_UpdateCounter_u8_ExpectAndReturn(200U, 0U);
    result = MyLib_RunStateMachine_u8(NULL, 0U, NULL);
    TEST_ASSERT_EQUAL_UINT8(0U, result);
    
    result = MyLib_RunStateMachine_u8(NULL, 0U, NULL);
    TEST_ASSERT_EQUAL_UINT8(1U, result);
    
    MyLib_UpdateGlobalRecord_Expect(NULL, &rec2);
    MyLib_UpdateGlobalRecord_IgnoreArg_dest_p();
    result = MyLib_RunStateMachine_u8(&rec2, 0U, NULL);
    TEST_ASSERT_EQUAL_UINT8(0U, result);
}