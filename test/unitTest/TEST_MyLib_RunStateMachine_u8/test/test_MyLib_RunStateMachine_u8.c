#include "MyLib_RunStateMachine_u8.h"
#include "unity.h"
#include "mock_MyLib.h"




#include "unity.h"
#include "MyLib_RunStateMachine_u8.h"
#include "mock_MyLib.h"
void setUp(void)
{
}
void tearDown(void)
{
}
void test_State0_NullRecPtr_Return1_StateRemains0(void)
{
    uint8_t result;
    
    result = MyLib_RunStateMachine_u8(NULL, 0, NULL);
    
    TEST_ASSERT_EQUAL_UINT8(1, result);
    
    result = MyLib_RunStateMachine_u8(NULL, 0, NULL);
    TEST_ASSERT_EQUAL_UINT8(1, result);
}
void test_State0_ValidRecPtr_Return0_TransitionTo1(void)
{
    MyLib_record_t input_rec = {10, 100};
    uint8_t result;
    
    MyLib_UpdateGlobalRecord_Expect(NULL, &input_rec);
    MyLib_UpdateGlobalRecord_IgnoreArg_dest_p();
    
    result = MyLib_RunStateMachine_u8(&input_rec, 0, NULL);
    
    TEST_ASSERT_EQUAL_UINT8(0, result);
}
void test_State1_NullDelta_Return0_TransitionTo2(void)
{
    MyLib_record_t input_rec = {10, 100};
    uint8_t result;
    
    MyLib_UpdateGlobalRecord_Expect(NULL, &input_rec);
    MyLib_UpdateGlobalRecord_IgnoreArg_dest_p();
    result = MyLib_RunStateMachine_u8(&input_rec, 0, NULL);
    TEST_ASSERT_EQUAL_UINT8(0, result);
    
    MyLib_ProcessRecord_Expect(NULL, MYLIB_MULT_VALUE_U8);
    MyLib_ProcessRecord_IgnoreArg_rec_pc();
    MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(0, NULL, 50);
    MyLib_ComputeAdjustedValue_u32_IgnoreArg_base_u32();
    
    result = MyLib_RunStateMachine_u8(NULL, 0, NULL);
    
    TEST_ASSERT_EQUAL_UINT8(0, result);
}
void test_State1_ValidDelta_Return0_TransitionTo2(void)
{
    MyLib_record_t input_rec = {10, 100};
    uint16_t delta = 20;
    uint8_t result;
    
    MyLib_UpdateGlobalRecord_Expect(NULL, &input_rec);
    MyLib_UpdateGlobalRecord_IgnoreArg_dest_p();
    result = MyLib_RunStateMachine_u8(&input_rec, 0, NULL);
    TEST_ASSERT_EQUAL_UINT8(0, result);
    
    MyLib_ProcessRecord_Expect(NULL, MYLIB_MULT_VALUE_U8);
    MyLib_ProcessRecord_IgnoreArg_rec_pc();
    MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(0, &delta, 120);
    MyLib_ComputeAdjustedValue_u32_IgnoreArg_base_u32();
    
    result = MyLib_RunStateMachine_u8(NULL, 0, &delta);
    
    TEST_ASSERT_EQUAL_UINT8(0, result);
}
void test_State2_AddZero_AdjustedZero_ReturnFromUpdateCounter(void)
{
    MyLib_record_t input_rec = {10, 0};
    uint8_t result;
    
    MyLib_UpdateGlobalRecord_Expect(NULL, &input_rec);
    MyLib_UpdateGlobalRecord_IgnoreArg_dest_p();
    result = MyLib_RunStateMachine_u8(&input_rec, 0, NULL);
    
    MyLib_ProcessRecord_Expect(NULL, MYLIB_MULT_VALUE_U8);
    MyLib_ProcessRecord_IgnoreArg_rec_pc();
    MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(0, NULL, 0);
    MyLib_ComputeAdjustedValue_u32_IgnoreArg_base_u32();
    result = MyLib_RunStateMachine_u8(NULL, 0, NULL);
    
    MyLib_UpdateCounter_u8_ExpectAndReturn(0, 0);
    
    result = MyLib_RunStateMachine_u8(NULL, 0, NULL);
    
    TEST_ASSERT_EQUAL_UINT8(0, result);
}
void test_State2_NoSaturation_Return0_TransitionTo0(void)
{
    MyLib_record_t input_rec = {10, 100};
    uint8_t result;
    
    MyLib_UpdateGlobalRecord_Expect(NULL, &input_rec);
    MyLib_UpdateGlobalRecord_IgnoreArg_dest_p();
    result = MyLib_RunStateMachine_u8(&input_rec, 0, NULL);
    
    MyLib_ProcessRecord_Expect(NULL, MYLIB_MULT_VALUE_U8);
    MyLib_ProcessRecord_IgnoreArg_rec_pc();
    MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(0, NULL, 50);
    MyLib_ComputeAdjustedValue_u32_IgnoreArg_base_u32();
    result = MyLib_RunStateMachine_u8(NULL, 0, NULL);
    
    MyLib_UpdateCounter_u8_ExpectAndReturn(60, 0);
    
    result = MyLib_RunStateMachine_u8(NULL, 10, NULL);
    
    TEST_ASSERT_EQUAL_UINT8(0, result);
}
void test_State2_Saturation_Return2_TransitionTo0(void)
{
    MyLib_record_t input_rec = {10, 100};
    uint8_t result;
    
    MyLib_UpdateGlobalRecord_Expect(NULL, &input_rec);
    MyLib_UpdateGlobalRecord_IgnoreArg_dest_p();
    result = MyLib_RunStateMachine_u8(&input_rec, 0, NULL);
    
    MyLib_ProcessRecord_Expect(NULL, MYLIB_MULT_VALUE_U8);
    MyLib_ProcessRecord_IgnoreArg_rec_pc();
    MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(0, NULL, 200);
    MyLib_ComputeAdjustedValue_u32_IgnoreArg_base_u32();
    result = MyLib_RunStateMachine_u8(NULL, 0, NULL);
    
    MyLib_UpdateCounter_u8_ExpectAndReturn(300, 2);
    
    result = MyLib_RunStateMachine_u8(NULL, 100, NULL);
    
    TEST_ASSERT_EQUAL_UINT8(2, result);
}
void test_State2_AddMaxUint32_AdjustedZero_ReturnFromUpdateCounter(void)
{
    MyLib_record_t input_rec = {10, 0};
    uint8_t result;
    
    MyLib_UpdateGlobalRecord_Expect(NULL, &input_rec);
    MyLib_UpdateGlobalRecord_IgnoreArg_dest_p();
    result = MyLib_RunStateMachine_u8(&input_rec, 0, NULL);
    
    MyLib_ProcessRecord_Expect(NULL, MYLIB_MULT_VALUE_U8);
    MyLib_ProcessRecord_IgnoreArg_rec_pc();
    MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(0, NULL, 0);
    MyLib_ComputeAdjustedValue_u32_IgnoreArg_base_u32();
    result = MyLib_RunStateMachine_u8(NULL, 0, NULL);
    
    MyLib_UpdateCounter_u8_ExpectAndReturn(UINT32_MAX, 2);
    
    result = MyLib_RunStateMachine_u8(NULL, UINT32_MAX, NULL);
    
    TEST_ASSERT_EQUAL_UINT8(2, result);
}
void test_State2_AddZero_AdjustedMaxUint32_ReturnFromUpdateCounter(void)
{
    MyLib_record_t input_rec = {10, UINT32_MAX};
    uint8_t result;
    
    MyLib_UpdateGlobalRecord_Expect(NULL, &input_rec);
    MyLib_UpdateGlobalRecord_IgnoreArg_dest_p();
    result = MyLib_RunStateMachine_u8(&input_rec, 0, NULL);
    
    MyLib_ProcessRecord_Expect(NULL, MYLIB_MULT_VALUE_U8);
    MyLib_ProcessRecord_IgnoreArg_rec_pc();
    MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(UINT32_MAX, NULL, UINT32_MAX);
    
    result = MyLib_RunStateMachine_u8(NULL, 0, NULL);
    
    MyLib_UpdateCounter_u8_ExpectAndReturn(UINT32_MAX, 2);
    
    result = MyLib_RunStateMachine_u8(NULL, 0, NULL);
    
    TEST_ASSERT_EQUAL_UINT8(2, result);
}
void test_State2_MidRangeValues_ReturnFromUpdateCounter(void)
{
    MyLib_record_t input_rec = {10, 50000};
    uint8_t result;
    
    MyLib_UpdateGlobalRecord_Expect(NULL, &input_rec);
    MyLib_UpdateGlobalRecord_IgnoreArg_dest_p();
    result = MyLib_RunStateMachine_u8(&input_rec, 0, NULL);
    
    MyLib_ProcessRecord_Expect(NULL, MYLIB_MULT_VALUE_U8);
    MyLib_ProcessRecord_IgnoreArg_rec_pc();
    MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(50000, NULL, 60000);
    
    result = MyLib_RunStateMachine_u8(NULL, 0, NULL);
    
    MyLib_UpdateCounter_u8_ExpectAndReturn(110000, 0);
    
    result = MyLib_RunStateMachine_u8(NULL, 50000, NULL);
    
    TEST_ASSERT_EQUAL_UINT8(0, result);
}
void test_FullCycle_ValidInit_NullDelta_NoSaturation(void)
{
    MyLib_record_t input_rec = {10, 100};
    uint8_t result;
    
    MyLib_UpdateGlobalRecord_Expect(NULL, &input_rec);
    MyLib_UpdateGlobalRecord_IgnoreArg_dest_p();
    result = MyLib_RunStateMachine_u8(&input_rec, 5, NULL);
    TEST_ASSERT_EQUAL_UINT8(0, result);
    
    MyLib_ProcessRecord_Expect(NULL, MYLIB_MULT_VALUE_U8);
    MyLib_ProcessRecord_IgnoreArg_rec_pc();
    MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(0, NULL, 50);
    MyLib_ComputeAdjustedValue_u32_IgnoreArg_base_u32();
    result = MyLib_RunStateMachine_u8(NULL, 5, NULL);
    TEST_ASSERT_EQUAL_UINT8(0, result);
    
    MyLib_UpdateCounter_u8_ExpectAndReturn(55, 0);
    result = MyLib_RunStateMachine_u8(NULL, 5, NULL);
    TEST_ASSERT_EQUAL_UINT8(0, result);
    
    MyLib_UpdateGlobalRecord_Expect(NULL, &input_rec);
    MyLib_UpdateGlobalRecord_IgnoreArg_dest_p();
    result = MyLib_RunStateMachine_u8(&input_rec, 0, NULL);
    TEST_ASSERT_EQUAL_UINT8(0, result);
}
void test_FullCycle_ValidInit_ValidDelta_Saturation(void)
{
    MyLib_record_t input_rec = {10, 100};
    uint16_t delta = 20;
    uint8_t result;
    
    MyLib_UpdateGlobalRecord_Expect(NULL, &input_rec);
    MyLib_UpdateGlobalRecord_IgnoreArg_dest_p();
    result = MyLib_RunStateMachine_u8(&input_rec, 0, &delta);
    TEST_ASSERT_EQUAL_UINT8(0, result);
    
    MyLib_ProcessRecord_Expect(NULL, MYLIB_MULT_VALUE_U8);
    MyLib_ProcessRecord_IgnoreArg_rec_pc();
    MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(0, &delta, 150);
    MyLib_ComputeAdjustedValue_u32_IgnoreArg_base_u32();
    result = MyLib_RunStateMachine_u8(NULL, 0, &delta);
    TEST_ASSERT_EQUAL_UINT8(0, result);
    
    MyLib_UpdateCounter_u8_ExpectAndReturn(250, 2);
    result = MyLib_RunStateMachine_u8(NULL, 100, &delta);
    TEST_ASSERT_EQUAL_UINT8(2, result);
    
    MyLib_UpdateGlobalRecord_Expect(NULL, &input_rec);
    MyLib_UpdateGlobalRecord_IgnoreArg_dest_p();
    result = MyLib_RunStateMachine_u8(&input_rec, 0, NULL);
    TEST_ASSERT_EQUAL_UINT8(0, result);
}
void test_RepeatedInitRejection_NullRecPtr_StateRemains0(void)
{
    uint8_t result;
    
    result = MyLib_RunStateMachine_u8(NULL, 0, NULL);
    TEST_ASSERT_EQUAL_UINT8(1, result);
    
    result = MyLib_RunStateMachine_u8(NULL, 10, NULL);
    TEST_ASSERT_EQUAL_UINT8(1, result);
    
    result = MyLib_RunStateMachine_u8(NULL, 100, NULL);
    TEST_ASSERT_EQUAL_UINT8(1, result);
    
    result = MyLib_RunStateMachine_u8(NULL, UINT32_MAX, NULL);
    TEST_ASSERT_EQUAL_UINT8(1, result);
}
void test_State0_ValidRecPtr_VerifyUpdateGlobalRecordCall(void)
{
    MyLib_record_t input_rec = {123, 456};
    uint8_t result;
    
    MyLib_UpdateGlobalRecord_Expect(NULL, &input_rec);
    MyLib_UpdateGlobalRecord_IgnoreArg_dest_p();
    
    result = MyLib_RunStateMachine_u8(&input_rec, 0, NULL);
    
    TEST_ASSERT_EQUAL_UINT8(0, result);
}
void test_State1_VerifyProcessRecordCall(void)
{
    MyLib_record_t input_rec = {10, 100};
    uint8_t result;
    
    MyLib_UpdateGlobalRecord_Expect(NULL, &input_rec);
    MyLib_UpdateGlobalRecord_IgnoreArg_dest_p();
    result = MyLib_RunStateMachine_u8(&input_rec, 0, NULL);
    
    MyLib_ProcessRecord_Expect(NULL, MYLIB_MULT_VALUE_U8);
    MyLib_ProcessRecord_IgnoreArg_rec_pc();
    MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(0, NULL, 50);
    MyLib_ComputeAdjustedValue_u32_IgnoreArg_base_u32();
    
    result = MyLib_RunStateMachine_u8(NULL, 0, NULL);
    
    TEST_ASSERT_EQUAL_UINT8(0, result);
}
void test_State1_VerifyComputeAdjustedValueCall(void)
{
    MyLib_record_t input_rec = {10, 200};
    uint16_t delta = 30;
    uint8_t result;
    
    MyLib_UpdateGlobalRecord_Expect(NULL, &input_rec);
    MyLib_UpdateGlobalRecord_IgnoreArg_dest_p();
    result = MyLib_RunStateMachine_u8(&input_rec, 0, NULL);
    
    MyLib_ProcessRecord_Expect(NULL, MYLIB_MULT_VALUE_U8);
    MyLib_ProcessRecord_IgnoreArg_rec_pc();
    MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(200, &delta, 230);
    
    result = MyLib_RunStateMachine_u8(NULL, 0, &delta);
    
    TEST_ASSERT_EQUAL_UINT8(0, result);
}
void test_State2_VerifyUpdateValueComputation(void)
{
    MyLib_record_t input_rec = {10, 100};
    uint8_t result;
    
    MyLib_UpdateGlobalRecord_Expect(NULL, &input_rec);
    MyLib_UpdateGlobalRecord_IgnoreArg_dest_p();
    result = MyLib_RunStateMachine_u8(&input_rec, 0, NULL);
    
    MyLib_ProcessRecord_Expect(NULL, MYLIB_MULT_VALUE_U8);
    MyLib_ProcessRecord_IgnoreArg_rec_pc();
    MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(0, NULL, 75);
    MyLib_ComputeAdjustedValue_u32_IgnoreArg_base_u32();
    result = MyLib_RunStateMachine_u8(NULL, 0, NULL);
    
    MyLib_UpdateCounter_u8_ExpectAndReturn(100, 0);
    
    result = MyLib_RunStateMachine_u8(NULL, 25, NULL);
    
    TEST_ASSERT_EQUAL_UINT8(0, result);
}
void test_State2_VerifyUpdateCounterCallAndReturnPropagation(void)
{
    MyLib_record_t input_rec = {10, 100};
    uint8_t result;
    
    MyLib_UpdateGlobalRecord_Expect(NULL, &input_rec);
    MyLib_UpdateGlobalRecord_IgnoreArg_dest_p();
    result = MyLib_RunStateMachine_u8(&input_rec, 0, NULL);
    
    MyLib_ProcessRecord_Expect(NULL, MYLIB_MULT_VALUE_U8);
    MyLib_ProcessRecord_IgnoreArg_rec_pc();
    MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(0, NULL, 50);
    MyLib_ComputeAdjustedValue_u32_IgnoreArg_base_u32();
    result = MyLib_RunStateMachine_u8(NULL, 0, NULL);
    
    MyLib_UpdateCounter_u8_ExpectAndReturn(150, 2);
    
    result = MyLib_RunStateMachine_u8(NULL, 100, NULL);
    
    TEST_ASSERT_EQUAL_UINT8(2, result);
}
void test_State0To1_RecordValueZero_VerifyInit(void)
{
    MyLib_record_t input_rec = {5, 0};
    uint8_t result;
    
    MyLib_UpdateGlobalRecord_Expect(NULL, &input_rec);
    MyLib_UpdateGlobalRecord_IgnoreArg_dest_p();
    
    result = MyLib_RunStateMachine_u8(&input_rec, 0, NULL);
    
    TEST_ASSERT_EQUAL_UINT8(0, result);
}
void test_State0To1_RecordValueMaxUint32_VerifyInit(void)
{
    MyLib_record_t input_rec = {5, UINT32_MAX};
    uint8_t result;
    
    MyLib_UpdateGlobalRecord_Expect(NULL, &input_rec);
    MyLib_UpdateGlobalRecord_IgnoreArg_dest_p();
    
    result = MyLib_RunStateMachine_u8(&input_rec, 0, NULL);
    
    TEST_ASSERT_EQUAL_UINT8(0, result);
}
void test_State1To2_DeltaZero_VerifyAdjustedValue(void)
{
    MyLib_record_t input_rec = {10, 100};
    uint16_t delta = 0;
    uint8_t result;
    
    MyLib_UpdateGlobalRecord_Expect(NULL, &input_rec);
    MyLib_UpdateGlobalRecord_IgnoreArg_dest_p();
    result = MyLib_RunStateMachine_u8(&input_rec, 0, NULL);
    
    MyLib_ProcessRecord_Expect(NULL, MYLIB_MULT_VALUE_U8);
    MyLib_ProcessRecord_IgnoreArg_rec_pc();
    MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(0, &delta, 100);
    MyLib_ComputeAdjustedValue_u32_IgnoreArg_base_u32();
    
    result = MyLib_RunStateMachine_u8(NULL, 0, &delta);
    
    TEST_ASSERT_EQUAL_UINT8(0, result);
}
void test_State1To2_DeltaMaxUint16_VerifyAdjustedValue(void)
{
    MyLib_record_t input_rec = {10, 100};
    uint16_t delta = UINT16_MAX;
    uint8_t result;
    
    MyLib_UpdateGlobalRecord_Expect(NULL, &input_rec);
    MyLib_UpdateGlobalRecord_IgnoreArg_dest_p();
    result = MyLib_RunStateMachine_u8(&input_rec, 0, NULL);
    
    MyLib_ProcessRecord_Expect(NULL, MYLIB_MULT_VALUE_U8);
    MyLib_ProcessRecord_IgnoreArg_rec_pc();
    MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(0, &delta, 65635);
    MyLib_ComputeAdjustedValue_u32_IgnoreArg_base_u32();
    
    result = MyLib_RunStateMachine_u8(NULL, 0, &delta);
    
    TEST_ASSERT_EQUAL_UINT8(0, result);
}
void test_StateMachineReset_AfterState2_NextCallStartsInState0(void)
{
    MyLib_record_t input_rec = {10, 100};
    uint8_t result;
    
    MyLib_UpdateGlobalRecord_Expect(NULL, &input_rec);
    MyLib_UpdateGlobalRecord_IgnoreArg_dest_p();
    result = MyLib_RunStateMachine_u8(&input_rec, 0, NULL);
    
    MyLib_ProcessRecord_Expect(NULL, MYLIB_MULT_VALUE_U8);
    MyLib_ProcessRecord_IgnoreArg_rec_pc();
    MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(0, NULL, 50);
    MyLib_ComputeAdjustedValue_u32_IgnoreArg_base_u32();
    result = MyLib_RunStateMachine_u8(NULL, 0, NULL);
    
    MyLib_UpdateCounter_u8_ExpectAndReturn(50, 0);
    result = MyLib_RunStateMachine_u8(NULL, 0, NULL);
    TEST_ASSERT_EQUAL_UINT8(0, result);
    
    result = MyLib_RunStateMachine_u8(NULL, 0, NULL);
    TEST_ASSERT_EQUAL_UINT8(1, result);
}
void test_InvalidState_VerifyBehavior(void)
{
    MyLib_record_t input_rec = {10, 100};
    uint8_t result;
    
    MyLib_UpdateGlobalRecord_Expect(NULL, &input_rec);
    MyLib_UpdateGlobalRecord_IgnoreArg_dest_p();
    result = MyLib_RunStateMachine_u8(&input_rec, 0, NULL);
    
    MyLib_ProcessRecord_Expect(NULL, MYLIB_MULT_VALUE_U8);
    MyLib_ProcessRecord_IgnoreArg_rec_pc();
    MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(0, NULL, 50);
    MyLib_ComputeAdjustedValue_u32_IgnoreArg_base_u32();
    result = MyLib_RunStateMachine_u8(NULL, 0, NULL);
    
    MyLib_UpdateCounter_u8_ExpectAndReturn(50, 0);
    result = MyLib_RunStateMachine_u8(NULL, 0, NULL);
    
    MyLib_UpdateGlobalRecord_Expect(NULL, &input_rec);
    MyLib_UpdateGlobalRecord_IgnoreArg_dest_p();
    result = MyLib_RunStateMachine_u8(&input_rec, 0, NULL);
    TEST_ASSERT_EQUAL_UINT8(0, result);
}
