#include "MyLib_RunStateMachine_u8.h"
#include "mock_MyLib.h"
#include "unity.h"




void setUp(void)
{
    g_counter_u32 = 0U;
    g_record.id_u16 = 0U;
    g_record.value_u32 = 0U;
    g_systemReady_b = false;
}
void tearDown(void)
{
}
void test_State0_NullRecPtr_Returns1_StateRemains0(void)
{
    uint8_t result;

    result = MyLib_RunStateMachine_u8(NULL, 0U, NULL);

    TEST_ASSERT_EQUAL_UINT8(1U, result);

    result = MyLib_RunStateMachine_u8(NULL, 0U, NULL);
    TEST_ASSERT_EQUAL_UINT8(1U, result);
}
void test_State0_ValidRecPtr_Returns0_StateTransitionsTo1(void)
{
    MyLib_record_t input_rec = {10U, 200U};
    MyLib_record_t expected_rec = {10U, 200U};
    uint8_t result;

    MyLib_UpdateGlobalRecord_Expect(NULL, &input_rec);
    MyLib_UpdateGlobalRecord_IgnoreArg_dest_p();

    result = MyLib_RunStateMachine_u8(&input_rec, 0U, NULL);

    TEST_ASSERT_EQUAL_UINT8(0U, result);

    MyLib_ProcessRecord_Expect(NULL, MYLIB_MULT_VALUE_U8);
    MyLib_ProcessRecord_IgnoreArg_rec_pc();
    MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(0U, NULL, 0U);
    MyLib_ComputeAdjustedValue_u32_IgnoreArg_base_u32();
    MyLib_ComputeAdjustedValue_u32_IgnoreArg_delta_pc_u16();

    result = MyLib_RunStateMachine_u8(NULL, 0U, NULL);
    TEST_ASSERT_EQUAL_UINT8(0U, result);
}
void test_State1_NullDelta_Returns0_StateTransitionsTo2(void)
{
    MyLib_record_t input_rec = {5U, 100U};
    uint8_t result;

    MyLib_UpdateGlobalRecord_Expect(NULL, &input_rec);
    MyLib_UpdateGlobalRecord_IgnoreArg_dest_p();
    result = MyLib_RunStateMachine_u8(&input_rec, 0U, NULL);
    TEST_ASSERT_EQUAL_UINT8(0U, result);

    MyLib_ProcessRecord_Expect(NULL, MYLIB_MULT_VALUE_U8);
    MyLib_ProcessRecord_IgnoreArg_rec_pc();
    MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(0U, NULL, 42U);
    MyLib_ComputeAdjustedValue_u32_IgnoreArg_base_u32();

    result = MyLib_RunStateMachine_u8(NULL, 0U, NULL);

    TEST_ASSERT_EQUAL_UINT8(0U, result);

    MyLib_UpdateCounter_u8_ExpectAndReturn(42U, 0U);

    result = MyLib_RunStateMachine_u8(NULL, 0U, NULL);
    TEST_ASSERT_EQUAL_UINT8(0U, result);
}
void test_State1_ValidDelta_Returns0_StateTransitionsTo2(void)
{
    MyLib_record_t input_rec = {7U, 150U};
    uint16_t delta = 25U;
    uint8_t result;

    MyLib_UpdateGlobalRecord_Expect(NULL, &input_rec);
    MyLib_UpdateGlobalRecord_IgnoreArg_dest_p();
    result = MyLib_RunStateMachine_u8(&input_rec, 0U, NULL);
    TEST_ASSERT_EQUAL_UINT8(0U, result);

    MyLib_ProcessRecord_Expect(NULL, MYLIB_MULT_VALUE_U8);
    MyLib_ProcessRecord_IgnoreArg_rec_pc();
    MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(0U, &delta, 175U);
    MyLib_ComputeAdjustedValue_u32_IgnoreArg_base_u32();

    result = MyLib_RunStateMachine_u8(NULL, 0U, &delta);

    TEST_ASSERT_EQUAL_UINT8(0U, result);

    MyLib_UpdateCounter_u8_ExpectAndReturn(175U, 0U);

    result = MyLib_RunStateMachine_u8(NULL, 0U, NULL);
    TEST_ASSERT_EQUAL_UINT8(0U, result);
}
void test_State2_AddZero_AdjustedZero_ReturnsFromUpdateCounter(void)
{
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
    MyLib_ComputeAdjustedValue_u32_IgnoreArg_delta_pc_u16();

    result = MyLib_RunStateMachine_u8(NULL, 0U, NULL);
    TEST_ASSERT_EQUAL_UINT8(0U, result);

    MyLib_UpdateCounter_u8_ExpectAndReturn(0U, 1U);

    result = MyLib_RunStateMachine_u8(NULL, 0U, NULL);

    TEST_ASSERT_EQUAL_UINT8(1U, result);

    result = MyLib_RunStateMachine_u8(NULL, 0U, NULL);
    TEST_ASSERT_EQUAL_UINT8(1U, result);
}
void test_State2_AddCausesSaturation_Returns2_StateTransitionsTo0(void)
{
    MyLib_record_t input_rec = {2U, 50U};
    uint8_t result;

    MyLib_UpdateGlobalRecord_Expect(NULL, &input_rec);
    MyLib_UpdateGlobalRecord_IgnoreArg_dest_p();
    result = MyLib_RunStateMachine_u8(&input_rec, 0U, NULL);
    TEST_ASSERT_EQUAL_UINT8(0U, result);

    MyLib_ProcessRecord_Expect(NULL, MYLIB_MULT_VALUE_U8);
    MyLib_ProcessRecord_IgnoreArg_rec_pc();
    MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(0U, NULL, 50U);
    MyLib_ComputeAdjustedValue_u32_IgnoreArg_base_u32();
    MyLib_ComputeAdjustedValue_u32_IgnoreArg_delta_pc_u16();

    result = MyLib_RunStateMachine_u8(NULL, 0U, NULL);
    TEST_ASSERT_EQUAL_UINT8(0U, result);

    MyLib_UpdateCounter_u8_ExpectAndReturn(150U, 2U);

    result = MyLib_RunStateMachine_u8(NULL, 100U, NULL);

    TEST_ASSERT_EQUAL_UINT8(2U, result);

    result = MyLib_RunStateMachine_u8(NULL, 0U, NULL);
    TEST_ASSERT_EQUAL_UINT8(1U, result);
}
void test_State2_MidRangeUpdate_ReturnsFromUpdateCounter_StateTransitionsTo0(void)
{
    MyLib_record_t input_rec = {3U, 30U};
    uint8_t result;

    MyLib_UpdateGlobalRecord_Expect(NULL, &input_rec);
    MyLib_UpdateGlobalRecord_IgnoreArg_dest_p();
    result = MyLib_RunStateMachine_u8(&input_rec, 0U, NULL);
    TEST_ASSERT_EQUAL_UINT8(0U, result);

    MyLib_ProcessRecord_Expect(NULL, MYLIB_MULT_VALUE_U8);
    MyLib_ProcessRecord_IgnoreArg_rec_pc();
    MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(0U, NULL, 30U);
    MyLib_ComputeAdjustedValue_u32_IgnoreArg_base_u32();
    MyLib_ComputeAdjustedValue_u32_IgnoreArg_delta_pc_u16();

    result = MyLib_RunStateMachine_u8(NULL, 0U, NULL);
    TEST_ASSERT_EQUAL_UINT8(0U, result);

    MyLib_UpdateCounter_u8_ExpectAndReturn(50U, 0U);

    result = MyLib_RunStateMachine_u8(NULL, 20U, NULL);

    TEST_ASSERT_EQUAL_UINT8(0U, result);

    result = MyLib_RunStateMachine_u8(NULL, 0U, NULL);
    TEST_ASSERT_EQUAL_UINT8(1U, result);
}
void test_FullCycle_ValidInputs_NoSaturation_Returns0_StateCycles(void)
{
    MyLib_record_t input_rec = {8U, 80U};
    uint16_t delta = 10U;
    uint8_t result;

    MyLib_UpdateGlobalRecord_Expect(NULL, &input_rec);
    MyLib_UpdateGlobalRecord_IgnoreArg_dest_p();
    result = MyLib_RunStateMachine_u8(&input_rec, 0U, NULL);
    TEST_ASSERT_EQUAL_UINT8(0U, result);

    MyLib_ProcessRecord_Expect(NULL, MYLIB_MULT_VALUE_U8);
    MyLib_ProcessRecord_IgnoreArg_rec_pc();
    MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(0U, &delta, 90U);
    MyLib_ComputeAdjustedValue_u32_IgnoreArg_base_u32();

    result = MyLib_RunStateMachine_u8(NULL, 0U, &delta);
    TEST_ASSERT_EQUAL_UINT8(0U, result);

    MyLib_UpdateCounter_u8_ExpectAndReturn(100U, 0U);

    result = MyLib_RunStateMachine_u8(NULL, 10U, NULL);
    TEST_ASSERT_EQUAL_UINT8(0U, result);

    result = MyLib_RunStateMachine_u8(NULL, 0U, NULL);
    TEST_ASSERT_EQUAL_UINT8(1U, result);
}
void test_FullCycle_ValidInputs_Saturation_Returns0_0_2_StateCycles(void)
{
    MyLib_record_t input_rec = {9U, 90U};
    uint16_t delta = 20U;
    uint8_t result;

    MyLib_UpdateGlobalRecord_Expect(NULL, &input_rec);
    MyLib_UpdateGlobalRecord_IgnoreArg_dest_p();
    result = MyLib_RunStateMachine_u8(&input_rec, 0U, NULL);
    TEST_ASSERT_EQUAL_UINT8(0U, result);

    MyLib_ProcessRecord_Expect(NULL, MYLIB_MULT_VALUE_U8);
    MyLib_ProcessRecord_IgnoreArg_rec_pc();
    MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(0U, &delta, 110U);
    MyLib_ComputeAdjustedValue_u32_IgnoreArg_base_u32();

    result = MyLib_RunStateMachine_u8(NULL, 0U, &delta);
    TEST_ASSERT_EQUAL_UINT8(0U, result);

    MyLib_UpdateCounter_u8_ExpectAndReturn(210U, 2U);

    result = MyLib_RunStateMachine_u8(NULL, 100U, NULL);
    TEST_ASSERT_EQUAL_UINT8(2U, result);

    result = MyLib_RunStateMachine_u8(NULL, 0U, NULL);
    TEST_ASSERT_EQUAL_UINT8(1U, result);
}
void test_State0_RejectionThenSuccess_Returns1_Then0_StateTransitions(void)
{
    MyLib_record_t input_rec = {11U, 110U};
    uint8_t result;

    result = MyLib_RunStateMachine_u8(NULL, 0U, NULL);
    TEST_ASSERT_EQUAL_UINT8(1U, result);

    MyLib_UpdateGlobalRecord_Expect(NULL, &input_rec);
    MyLib_UpdateGlobalRecord_IgnoreArg_dest_p();

    result = MyLib_RunStateMachine_u8(&input_rec, 0U, NULL);
    TEST_ASSERT_EQUAL_UINT8(0U, result);

    MyLib_ProcessRecord_Expect(NULL, MYLIB_MULT_VALUE_U8);
    MyLib_ProcessRecord_IgnoreArg_rec_pc();
    MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(0U, NULL, 0U);
    MyLib_ComputeAdjustedValue_u32_IgnoreArg_base_u32();
    MyLib_ComputeAdjustedValue_u32_IgnoreArg_delta_pc_u16();

    result = MyLib_RunStateMachine_u8(NULL, 0U, NULL);
    TEST_ASSERT_EQUAL_UINT8(0U, result);
}
void test_State2_AddLowerBoundary_ReturnsFromUpdateCounter_StateTransitionsTo0(void)
{
    MyLib_record_t input_rec = {12U, 10U};
    uint8_t result;

    MyLib_UpdateGlobalRecord_Expect(NULL, &input_rec);
    MyLib_UpdateGlobalRecord_IgnoreArg_dest_p();
    result = MyLib_RunStateMachine_u8(&input_rec, 0U, NULL);
    TEST_ASSERT_EQUAL_UINT8(0U, result);

    MyLib_ProcessRecord_Expect(NULL, MYLIB_MULT_VALUE_U8);
    MyLib_ProcessRecord_IgnoreArg_rec_pc();
    MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(0U, NULL, 15U);
    MyLib_ComputeAdjustedValue_u32_IgnoreArg_base_u32();
    MyLib_ComputeAdjustedValue_u32_IgnoreArg_delta_pc_u16();

    result = MyLib_RunStateMachine_u8(NULL, 0U, NULL);
    TEST_ASSERT_EQUAL_UINT8(0U, result);

    MyLib_UpdateCounter_u8_ExpectAndReturn(15U, 0U);

    result = MyLib_RunStateMachine_u8(NULL, 0U, NULL);

    TEST_ASSERT_EQUAL_UINT8(0U, result);

    result = MyLib_RunStateMachine_u8(NULL, 0U, NULL);
    TEST_ASSERT_EQUAL_UINT8(1U, result);
}
void test_State2_AddUpperBoundary_ReturnsFromUpdateCounter_StateTransitionsTo0(void)
{
    MyLib_record_t input_rec = {13U, 20U};
    uint8_t result;

    MyLib_UpdateGlobalRecord_Expect(NULL, &input_rec);
    MyLib_UpdateGlobalRecord_IgnoreArg_dest_p();
    result = MyLib_RunStateMachine_u8(&input_rec, 0U, NULL);
    TEST_ASSERT_EQUAL_UINT8(0U, result);

    MyLib_ProcessRecord_Expect(NULL, MYLIB_MULT_VALUE_U8);
    MyLib_ProcessRecord_IgnoreArg_rec_pc();
    MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(0U, NULL, 5U);
    MyLib_ComputeAdjustedValue_u32_IgnoreArg_base_u32();
    MyLib_ComputeAdjustedValue_u32_IgnoreArg_delta_pc_u16();

    result = MyLib_RunStateMachine_u8(NULL, 0U, NULL);
    TEST_ASSERT_EQUAL_UINT8(0U, result);

    MyLib_UpdateCounter_u8_ExpectAndReturn(4U, 2U);

    result = MyLib_RunStateMachine_u8(NULL, UINT32_MAX, NULL);

    TEST_ASSERT_EQUAL_UINT8(2U, result);

    result = MyLib_RunStateMachine_u8(NULL, 0U, NULL);
    TEST_ASSERT_EQUAL_UINT8(1U, result);
}
void test_State1_BoundaryValues_Returns0_AdjustedCorrectly_StateTransitionsTo2(void)
{
    MyLib_record_t input_rec = {14U, UINT32_MAX};
    uint16_t delta = UINT16_MAX;
    uint8_t result;

    MyLib_UpdateGlobalRecord_Expect(NULL, &input_rec);
    MyLib_UpdateGlobalRecord_IgnoreArg_dest_p();
    result = MyLib_RunStateMachine_u8(&input_rec, 0U, NULL);
    TEST_ASSERT_EQUAL_UINT8(0U, result);

    MyLib_ProcessRecord_Expect(NULL, MYLIB_MULT_VALUE_U8);
    MyLib_ProcessRecord_IgnoreArg_rec_pc();
    MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(0U, &delta, 999U);
    MyLib_ComputeAdjustedValue_u32_IgnoreArg_base_u32();

    result = MyLib_RunStateMachine_u8(NULL, 0U, &delta);

    TEST_ASSERT_EQUAL_UINT8(0U, result);

    MyLib_UpdateCounter_u8_ExpectAndReturn(999U, 0U);

    result = MyLib_RunStateMachine_u8(NULL, 0U, NULL);
    TEST_ASSERT_EQUAL_UINT8(0U, result);
}
void test_State0_MultipleNullCalls_EachReturns1_StateRemains0(void)
{
    uint8_t result;

    result = MyLib_RunStateMachine_u8(NULL, 0U, NULL);
    TEST_ASSERT_EQUAL_UINT8(1U, result);

    result = MyLib_RunStateMachine_u8(NULL, 0U, NULL);
    TEST_ASSERT_EQUAL_UINT8(1U, result);

    result = MyLib_RunStateMachine_u8(NULL, 0U, NULL);
    TEST_ASSERT_EQUAL_UINT8(1U, result);

    result = MyLib_RunStateMachine_u8(NULL, 0U, NULL);
    TEST_ASSERT_EQUAL_UINT8(1U, result);

    result = MyLib_RunStateMachine_u8(NULL, 0U, NULL);
    TEST_ASSERT_EQUAL_UINT8(1U, result);
}
void test_StateSequence_0_1_2_0_1_VerifyPersistence_ReturnsExpected(void)
{
    MyLib_record_t input_rec1 = {15U, 40U};
    MyLib_record_t input_rec2 = {16U, 60U};
    uint8_t result;

    MyLib_UpdateGlobalRecord_Expect(NULL, &input_rec1);
    MyLib_UpdateGlobalRecord_IgnoreArg_dest_p();
    result = MyLib_RunStateMachine_u8(&input_rec1, 0U, NULL);
    TEST_ASSERT_EQUAL_UINT8(0U, result);

    MyLib_ProcessRecord_Expect(NULL, MYLIB_MULT_VALUE_U8);
    MyLib_ProcessRecord_IgnoreArg_rec_pc();
    MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(0U, NULL, 40U);
    MyLib_ComputeAdjustedValue_u32_IgnoreArg_base_u32();
    MyLib_ComputeAdjustedValue_u32_IgnoreArg_delta_pc_u16();

    result = MyLib_RunStateMachine_u8(NULL, 0U, NULL);
    TEST_ASSERT_EQUAL_UINT8(0U, result);

    MyLib_UpdateCounter_u8_ExpectAndReturn(50U, 0U);

    result = MyLib_RunStateMachine_u8(NULL, 10U, NULL);
    TEST_ASSERT_EQUAL_UINT8(0U, result);

    MyLib_UpdateGlobalRecord_Expect(NULL, &input_rec2);
    MyLib_UpdateGlobalRecord_IgnoreArg_dest_p();
    result = MyLib_RunStateMachine_u8(&input_rec2, 0U, NULL);
    TEST_ASSERT_EQUAL_UINT8(0U, result);

    MyLib_ProcessRecord_Expect(NULL, MYLIB_MULT_VALUE_U8);
    MyLib_ProcessRecord_IgnoreArg_rec_pc();
    MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(0U, NULL, 60U);
    MyLib_ComputeAdjustedValue_u32_IgnoreArg_base_u32();
    MyLib_ComputeAdjustedValue_u32_IgnoreArg_delta_pc_u16();

    result = MyLib_RunStateMachine_u8(NULL, 0U, NULL);
    TEST_ASSERT_EQUAL_UINT8(0U, result);
}
