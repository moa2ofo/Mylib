#include "MyLib_RunStateMachine_u8.h"
#include "mock_MyLib.h"
#include "unity.h"
#include "MyLib_RunStateMachine_u8.h"
#include "mock_MyLib.h"
#include "unity.h"




void setUp(void)
{
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
void test_State0_ValidRecPtr_Returns0_TransitionsTo1(void)
{
    MyLib_record_t input_rec = {10U, 200U};
    uint8_t result;
    
    MyLib_UpdateGlobalRecord_Expect(NULL, &input_rec);
    MyLib_UpdateGlobalRecord_IgnoreArg_dest_p();
    
    result = MyLib_RunStateMachine_u8(&input_rec, 0U, NULL);
    
    TEST_ASSERT_EQUAL_UINT8(0U, result);
}
void test_State1_NullDelta_Returns0_TransitionsTo2(void)
{
    MyLib_record_t input_rec = {10U, 200U};
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
}
void test_State1_ValidDelta_Returns0_TransitionsTo2(void)
{
    MyLib_record_t input_rec = {10U, 200U};
    uint16_t delta = 50U;
    uint8_t result;
    
    MyLib_UpdateGlobalRecord_Expect(NULL, &input_rec);
    MyLib_UpdateGlobalRecord_IgnoreArg_dest_p();
    result = MyLib_RunStateMachine_u8(&input_rec, 0U, &delta);
    TEST_ASSERT_EQUAL_UINT8(0U, result);
    
    MyLib_ProcessRecord_Expect(NULL, MYLIB_MULT_VALUE_U8);
    MyLib_ProcessRecord_IgnoreArg_rec_pc();
    MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(0U, &delta, 250U);
    MyLib_ComputeAdjustedValue_u32_IgnoreArg_base_u32();
    
    result = MyLib_RunStateMachine_u8(NULL, 0U, &delta);
    
    TEST_ASSERT_EQUAL_UINT8(0U, result);
}
void test_State2_AddZero_AdjustedZero_CallsUpdateWith0(void)
{
    MyLib_record_t input_rec = {10U, 0U};
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
void test_State2_AddZero_AdjustedNonZero_CallsUpdateWithSum(void)
{
    MyLib_record_t input_rec = {10U, 100U};
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
void test_State2_AddMaxUint32_AdjustedZero_CallsUpdateWithMax(void)
{
    MyLib_record_t input_rec = {10U, 0U};
    uint8_t result;
    
    MyLib_UpdateGlobalRecord_Expect(NULL, &input_rec);
    MyLib_UpdateGlobalRecord_IgnoreArg_dest_p();
    result = MyLib_RunStateMachine_u8(&input_rec, UINT32_MAX, NULL);
    
    MyLib_ProcessRecord_Expect(NULL, MYLIB_MULT_VALUE_U8);
    MyLib_ProcessRecord_IgnoreArg_rec_pc();
    MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(0U, NULL, 0U);
    MyLib_ComputeAdjustedValue_u32_IgnoreArg_base_u32();
    result = MyLib_RunStateMachine_u8(NULL, UINT32_MAX, NULL);
    
    MyLib_UpdateCounter_u8_ExpectAndReturn(UINT32_MAX, 0U);
    
    result = MyLib_RunStateMachine_u8(NULL, UINT32_MAX, NULL);
    
    TEST_ASSERT_EQUAL_UINT8(0U, result);
}
void test_State2_AddAndAdjustedCauseWrap_CallsUpdateWithWrapped(void)
{
    MyLib_record_t input_rec = {10U, 100U};
    uint8_t result;
    uint32_t add_val = UINT32_MAX - 50U;
    
    MyLib_UpdateGlobalRecord_Expect(NULL, &input_rec);
    MyLib_UpdateGlobalRecord_IgnoreArg_dest_p();
    result = MyLib_RunStateMachine_u8(&input_rec, add_val, NULL);
    
    MyLib_ProcessRecord_Expect(NULL, MYLIB_MULT_VALUE_U8);
    MyLib_ProcessRecord_IgnoreArg_rec_pc();
    MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(0U, NULL, 100U);
    MyLib_ComputeAdjustedValue_u32_IgnoreArg_base_u32();
    result = MyLib_RunStateMachine_u8(NULL, add_val, NULL);
    
    uint32_t expected_sum = add_val + 100U;
    MyLib_UpdateCounter_u8_ExpectAndReturn(expected_sum, 0U);
    
    result = MyLib_RunStateMachine_u8(NULL, add_val, NULL);
    
    TEST_ASSERT_EQUAL_UINT8(0U, result);
}
void test_State2_UpdateCounterReturns0_Returns0_TransitionsTo0(void)
{
    MyLib_record_t input_rec = {10U, 50U};
    uint8_t result;
    
    MyLib_UpdateGlobalRecord_Expect(NULL, &input_rec);
    MyLib_UpdateGlobalRecord_IgnoreArg_dest_p();
    result = MyLib_RunStateMachine_u8(&input_rec, 10U, NULL);
    
    MyLib_ProcessRecord_Expect(NULL, MYLIB_MULT_VALUE_U8);
    MyLib_ProcessRecord_IgnoreArg_rec_pc();
    MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(0U, NULL, 30U);
    MyLib_ComputeAdjustedValue_u32_IgnoreArg_base_u32();
    result = MyLib_RunStateMachine_u8(NULL, 10U, NULL);
    
    MyLib_UpdateCounter_u8_ExpectAndReturn(40U, 0U);
    
    result = MyLib_RunStateMachine_u8(NULL, 10U, NULL);
    
    TEST_ASSERT_EQUAL_UINT8(0U, result);
}
void test_State2_UpdateCounterReturns2_Returns2_TransitionsTo0(void)
{
    MyLib_record_t input_rec = {10U, 50U};
    uint8_t result;
    
    MyLib_UpdateGlobalRecord_Expect(NULL, &input_rec);
    MyLib_UpdateGlobalRecord_IgnoreArg_dest_p();
    result = MyLib_RunStateMachine_u8(&input_rec, 10U, NULL);
    
    MyLib_ProcessRecord_Expect(NULL, MYLIB_MULT_VALUE_U8);
    MyLib_ProcessRecord_IgnoreArg_rec_pc();
    MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(0U, NULL, 30U);
    MyLib_ComputeAdjustedValue_u32_IgnoreArg_base_u32();
    result = MyLib_RunStateMachine_u8(NULL, 10U, NULL);
    
    MyLib_UpdateCounter_u8_ExpectAndReturn(40U, 2U);
    
    result = MyLib_RunStateMachine_u8(NULL, 10U, NULL);
    
    TEST_ASSERT_EQUAL_UINT8(2U, result);
}
void test_FullCycle_ValidInputs_NoSaturation_Returns0AtEachStep(void)
{
    MyLib_record_t input_rec = {15U, 300U};
    uint16_t delta = 25U;
    uint8_t result;
    
    MyLib_UpdateGlobalRecord_Expect(NULL, &input_rec);
    MyLib_UpdateGlobalRecord_IgnoreArg_dest_p();
    result = MyLib_RunStateMachine_u8(&input_rec, 50U, &delta);
    TEST_ASSERT_EQUAL_UINT8(0U, result);
    
    MyLib_ProcessRecord_Expect(NULL, MYLIB_MULT_VALUE_U8);
    MyLib_ProcessRecord_IgnoreArg_rec_pc();
    MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(0U, &delta, 325U);
    MyLib_ComputeAdjustedValue_u32_IgnoreArg_base_u32();
    result = MyLib_RunStateMachine_u8(NULL, 50U, &delta);
    TEST_ASSERT_EQUAL_UINT8(0U, result);
    
    MyLib_UpdateCounter_u8_ExpectAndReturn(375U, 0U);
    result = MyLib_RunStateMachine_u8(NULL, 50U, &delta);
    TEST_ASSERT_EQUAL_UINT8(0U, result);
}
void test_FullCycle_ValidInputs_SaturationAtUpdate_Returns2AtUpdate(void)
{
    MyLib_record_t input_rec = {20U, 500U};
    uint8_t result;
    
    MyLib_UpdateGlobalRecord_Expect(NULL, &input_rec);
    MyLib_UpdateGlobalRecord_IgnoreArg_dest_p();
    result = MyLib_RunStateMachine_u8(&input_rec, 100U, NULL);
    TEST_ASSERT_EQUAL_UINT8(0U, result);
    
    MyLib_ProcessRecord_Expect(NULL, MYLIB_MULT_VALUE_U8);
    MyLib_ProcessRecord_IgnoreArg_rec_pc();
    MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(0U, NULL, 600U);
    MyLib_ComputeAdjustedValue_u32_IgnoreArg_base_u32();
    result = MyLib_RunStateMachine_u8(NULL, 100U, NULL);
    TEST_ASSERT_EQUAL_UINT8(0U, result);
    
    MyLib_UpdateCounter_u8_ExpectAndReturn(700U, 2U);
    result = MyLib_RunStateMachine_u8(NULL, 100U, NULL);
    TEST_ASSERT_EQUAL_UINT8(2U, result);
}
void test_RepeatedInitRejection_NullRecPtr_Returns1EachTime(void)
{
    uint8_t result;
    
    result = MyLib_RunStateMachine_u8(NULL, 0U, NULL);
    TEST_ASSERT_EQUAL_UINT8(1U, result);
    
    result = MyLib_RunStateMachine_u8(NULL, 0U, NULL);
    TEST_ASSERT_EQUAL_UINT8(1U, result);
    
    result = MyLib_RunStateMachine_u8(NULL, 0U, NULL);
    TEST_ASSERT_EQUAL_UINT8(1U, result);
}
void test_State0_ValidRecPtr_VerifyUpdateGlobalRecordCalled(void)
{
    MyLib_record_t input_rec = {123U, 456U};
    uint8_t result;
    
    MyLib_UpdateGlobalRecord_Expect(NULL, &input_rec);
    MyLib_UpdateGlobalRecord_IgnoreArg_dest_p();
    
    result = MyLib_RunStateMachine_u8(&input_rec, 0U, NULL);
    
    TEST_ASSERT_EQUAL_UINT8(0U, result);
}
void test_State1_VerifyProcessRecordCalledWithCorrectArgs(void)
{
    MyLib_record_t input_rec = {100U, 200U};
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
void test_State1_VerifyComputeAdjustedValueCalledCorrectly(void)
{
    MyLib_record_t input_rec = {50U, 1000U};
    uint16_t delta = 100U;
    uint8_t result;
    
    MyLib_UpdateGlobalRecord_Expect(NULL, &input_rec);
    MyLib_UpdateGlobalRecord_IgnoreArg_dest_p();
    result = MyLib_RunStateMachine_u8(&input_rec, 0U, &delta);
    
    MyLib_ProcessRecord_Expect(NULL, MYLIB_MULT_VALUE_U8);
    MyLib_ProcessRecord_IgnoreArg_rec_pc();
    MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(0U, &delta, 1100U);
    MyLib_ComputeAdjustedValue_u32_IgnoreArg_base_u32();
    
    result = MyLib_RunStateMachine_u8(NULL, 0U, &delta);
    
    TEST_ASSERT_EQUAL_UINT8(0U, result);
}
void test_State2_MidRangeAdd_CallsUpdateWithCorrectSum(void)
{
    MyLib_record_t input_rec = {30U, 400U};
    uint32_t mid_range_add = 0x80000000U;
    uint8_t result;
    
    MyLib_UpdateGlobalRecord_Expect(NULL, &input_rec);
    MyLib_UpdateGlobalRecord_IgnoreArg_dest_p();
    result = MyLib_RunStateMachine_u8(&input_rec, mid_range_add, NULL);
    
    MyLib_ProcessRecord_Expect(NULL, MYLIB_MULT_VALUE_U8);
    MyLib_ProcessRecord_IgnoreArg_rec_pc();
    MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(0U, NULL, 500U);
    MyLib_ComputeAdjustedValue_u32_IgnoreArg_base_u32();
    result = MyLib_RunStateMachine_u8(NULL, mid_range_add, NULL);
    
    uint32_t expected_sum = mid_range_add + 500U;
    MyLib_UpdateCounter_u8_ExpectAndReturn(expected_sum, 0U);
    
    result = MyLib_RunStateMachine_u8(NULL, mid_range_add, NULL);
    
    TEST_ASSERT_EQUAL_UINT8(0U, result);
}
void test_StateMachineResetAfterFullCycle_ReinitializesFromState0(void)
{
    MyLib_record_t input_rec1 = {10U, 100U};
    MyLib_record_t input_rec2 = {20U, 200U};
    uint8_t result;
    
    MyLib_UpdateGlobalRecord_Expect(NULL, &input_rec1);
    MyLib_UpdateGlobalRecord_IgnoreArg_dest_p();
    result = MyLib_RunStateMachine_u8(&input_rec1, 10U, NULL);
    TEST_ASSERT_EQUAL_UINT8(0U, result);
    
    MyLib_ProcessRecord_Expect(NULL, MYLIB_MULT_VALUE_U8);
    MyLib_ProcessRecord_IgnoreArg_rec_pc();
    MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(0U, NULL, 150U);
    MyLib_ComputeAdjustedValue_u32_IgnoreArg_base_u32();
    result = MyLib_RunStateMachine_u8(NULL, 10U, NULL);
    TEST_ASSERT_EQUAL_UINT8(0U, result);
    
    MyLib_UpdateCounter_u8_ExpectAndReturn(160U, 0U);
    result = MyLib_RunStateMachine_u8(NULL, 10U, NULL);
    TEST_ASSERT_EQUAL_UINT8(0U, result);
    
    MyLib_UpdateGlobalRecord_Expect(NULL, &input_rec2);
    MyLib_UpdateGlobalRecord_IgnoreArg_dest_p();
    result = MyLib_RunStateMachine_u8(&input_rec2, 20U, NULL);
    TEST_ASSERT_EQUAL_UINT8(0U, result);
}
