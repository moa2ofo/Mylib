#include "MyLib_Orchestrate_u32.h"
#include "mock_MyLib.h"
#include "unity.h"
#include <stdbool.h>
#include <stdint.h>




static uint32_t InternalHelper_u32_fake_retval;

static uint32_t InternalHelper_u32_Callback(uint32_t x_u32, uint16_t y_u16, int call_count)
{
    (void)call_count;
    (void)x_u32;
    (void)y_u16;
    return InternalHelper_u32_fake_retval;
}

static MyLib_record_t captured_record;
static uint8_t captured_multiplier;
static int MyLib_ProcessRecord_call_count;

static void MyLib_ProcessRecord_Callback(const MyLib_record_t *rec_pc, uint8_t multiplier_u8, int call_count)
{
    (void)call_count;
    MyLib_ProcessRecord_call_count++;
    captured_record.id_u16 = rec_pc->id_u16;
    captured_record.value_u32 = rec_pc->value_u32;
    captured_multiplier = multiplier_u8;
}

void setUp(void)
{
    g_counter_u32 = 0;
    InternalHelper_u32_fake_retval = 0;
    captured_record.id_u16 = 0;
    captured_record.value_u32 = 0;
    captured_multiplier = 0;
    MyLib_ProcessRecord_call_count = 0;
}

void tearDown(void)
{
}

void test_start_0_delta_NULL(void)
{
    g_counter_u32 = 50;
    InternalHelper_u32_fake_retval = 100;
    
    InternalHelper_u32_Stub(InternalHelper_u32_Callback);
    MyLib_ProcessRecord_Stub(MyLib_ProcessRecord_Callback);
    
    uint32_t result = MyLib_Orchestrate_u32(0, NULL);
    
    TEST_ASSERT_EQUAL_UINT32(150, result);
}

void test_start_0_delta_0(void)
{
    uint16_t delta = 0;
    g_counter_u32 = 50;
    InternalHelper_u32_fake_retval = 100;
    
    InternalHelper_u32_Stub(InternalHelper_u32_Callback);
    MyLib_ProcessRecord_Stub(MyLib_ProcessRecord_Callback);
    
    uint32_t result = MyLib_Orchestrate_u32(0, &delta);
    
    TEST_ASSERT_EQUAL_UINT32(150, result);
}

void test_start_1_delta_NULL(void)
{
    g_counter_u32 = 50;
    InternalHelper_u32_fake_retval = 100;
    
    InternalHelper_u32_Stub(InternalHelper_u32_Callback);
    MyLib_ProcessRecord_Stub(MyLib_ProcessRecord_Callback);
    
    uint32_t result = MyLib_Orchestrate_u32(1, NULL);
    
    TEST_ASSERT_EQUAL_UINT32(150, result);
}

void test_start_100_delta_NULL(void)
{
    g_counter_u32 = 50;
    InternalHelper_u32_fake_retval = 100;
    
    InternalHelper_u32_Stub(InternalHelper_u32_Callback);
    MyLib_ProcessRecord_Stub(MyLib_ProcessRecord_Callback);
    
    uint32_t result = MyLib_Orchestrate_u32(100, NULL);
    
    TEST_ASSERT_EQUAL_UINT32(150, result);
}

void test_start_200_delta_NULL(void)
{
    g_counter_u32 = 50;
    InternalHelper_u32_fake_retval = 100;
    
    InternalHelper_u32_Stub(InternalHelper_u32_Callback);
    MyLib_ProcessRecord_Stub(MyLib_ProcessRecord_Callback);
    
    uint32_t result = MyLib_Orchestrate_u32(200, NULL);
    
    TEST_ASSERT_EQUAL_UINT32(150, result);
}

void test_start_200_delta_65535(void)
{
    uint16_t delta = 65535;
    g_counter_u32 = 50;
    InternalHelper_u32_fake_retval = 100;
    
    InternalHelper_u32_Stub(InternalHelper_u32_Callback);
    MyLib_ProcessRecord_Stub(MyLib_ProcessRecord_Callback);
    
    uint32_t result = MyLib_Orchestrate_u32(200, &delta);
    
    TEST_ASSERT_EQUAL_UINT32(150, result);
}

void test_start_100_delta_0_valid(void)
{
    uint16_t delta = 0;
    g_counter_u32 = 50;
    InternalHelper_u32_fake_retval = 100;
    
    InternalHelper_u32_Stub(InternalHelper_u32_Callback);
    MyLib_ProcessRecord_Stub(MyLib_ProcessRecord_Callback);
    
    uint32_t result = MyLib_Orchestrate_u32(100, &delta);
    
    TEST_ASSERT_EQUAL_UINT32(150, result);
}

void test_start_100_delta_1(void)
{
    uint16_t delta = 1;
    g_counter_u32 = 50;
    InternalHelper_u32_fake_retval = 100;
    
    InternalHelper_u32_Stub(InternalHelper_u32_Callback);
    MyLib_ProcessRecord_Stub(MyLib_ProcessRecord_Callback);
    
    uint32_t result = MyLib_Orchestrate_u32(100, &delta);
    
    TEST_ASSERT_EQUAL_UINT32(150, result);
}

void test_start_100_delta_32767(void)
{
    uint16_t delta = 32767;
    g_counter_u32 = 50;
    InternalHelper_u32_fake_retval = 100;
    
    InternalHelper_u32_Stub(InternalHelper_u32_Callback);
    MyLib_ProcessRecord_Stub(MyLib_ProcessRecord_Callback);
    
    uint32_t result = MyLib_Orchestrate_u32(100, &delta);
    
    TEST_ASSERT_EQUAL_UINT32(150, result);
}

void test_start_100_delta_65535_valid(void)
{
    uint16_t delta = 65535;
    g_counter_u32 = 50;
    InternalHelper_u32_fake_retval = 100;
    
    InternalHelper_u32_Stub(InternalHelper_u32_Callback);
    MyLib_ProcessRecord_Stub(MyLib_ProcessRecord_Callback);
    
    uint32_t result = MyLib_Orchestrate_u32(100, &delta);
    
    TEST_ASSERT_EQUAL_UINT32(150, result);
}

void test_delta_NULL_calls_helper_with_0(void)
{
    uint32_t captured_x = 0xFFFFFFFF;
    uint16_t captured_y = 0xFFFF;
    
    InternalHelper_u32_fake_retval = 100;
    g_counter_u32 = 0;
    
    InternalHelper_u32_ExpectAndReturn(50, 0, 100);
    MyLib_ProcessRecord_Stub(MyLib_ProcessRecord_Callback);
    
    MyLib_Orchestrate_u32(50, NULL);
}

void test_delta_valid_calls_helper_with_value(void)
{
    uint16_t delta = 123;
    InternalHelper_u32_fake_retval = 100;
    g_counter_u32 = 0;
    
    InternalHelper_u32_ExpectAndReturn(50, 123, 100);
    MyLib_ProcessRecord_Stub(MyLib_ProcessRecord_Callback);
    
    MyLib_Orchestrate_u32(50, &delta);
}

void test_record_id_lower_16bits(void)
{
    InternalHelper_u32_fake_retval = 0x12345678;
    g_counter_u32 = 0;
    
    InternalHelper_u32_Stub(InternalHelper_u32_Callback);
    MyLib_ProcessRecord_Stub(MyLib_ProcessRecord_Callback);
    
    MyLib_Orchestrate_u32(0, NULL);
    
    TEST_ASSERT_EQUAL_UINT16(0x5678, captured_record.id_u16);
}

void test_record_value_even_division(void)
{
    InternalHelper_u32_fake_retval = 100;
    g_counter_u32 = 0;
    
    InternalHelper_u32_Stub(InternalHelper_u32_Callback);
    MyLib_ProcessRecord_Stub(MyLib_ProcessRecord_Callback);
    
    MyLib_Orchestrate_u32(0, NULL);
    
    TEST_ASSERT_EQUAL_UINT32(50, captured_record.value_u32);
}

void test_record_value_odd_division(void)
{
    InternalHelper_u32_fake_retval = 101;
    g_counter_u32 = 0;
    
    InternalHelper_u32_Stub(InternalHelper_u32_Callback);
    MyLib_ProcessRecord_Stub(MyLib_ProcessRecord_Callback);
    
    MyLib_Orchestrate_u32(0, NULL);
    
    TEST_ASSERT_EQUAL_UINT32(50, captured_record.value_u32);
}

void test_process_record_called_correctly(void)
{
    InternalHelper_u32_fake_retval = 100;
    g_counter_u32 = 0;
    
    InternalHelper_u32_Stub(InternalHelper_u32_Callback);
    MyLib_ProcessRecord_Stub(MyLib_ProcessRecord_Callback);
    
    MyLib_Orchestrate_u32(0, NULL);
    
    TEST_ASSERT_EQUAL_INT(1, MyLib_ProcessRecord_call_count);
    TEST_ASSERT_EQUAL_UINT8(MYLIB_MULT_VALUE_U8, captured_multiplier);
}

void test_counter_lower_boundary(void)
{
    g_counter_u32 = 0;
    InternalHelper_u32_fake_retval = 100;
    
    InternalHelper_u32_Stub(InternalHelper_u32_Callback);
    MyLib_ProcessRecord_Stub(MyLib_ProcessRecord_Callback);
    
    uint32_t result = MyLib_Orchestrate_u32(0, NULL);
    
    TEST_ASSERT_EQUAL_UINT32(100, result);
}

void test_counter_mid_range(void)
{
    g_counter_u32 = 250;
    InternalHelper_u32_fake_retval = 100;
    
    InternalHelper_u32_Stub(InternalHelper_u32_Callback);
    MyLib_ProcessRecord_Stub(MyLib_ProcessRecord_Callback);
    
    uint32_t result = MyLib_Orchestrate_u32(0, NULL);
    
    TEST_ASSERT_EQUAL_UINT32(350, result);
}

void test_counter_upper_boundary(void)
{
    g_counter_u32 = 500;
    InternalHelper_u32_fake_retval = 100;
    
    InternalHelper_u32_Stub(InternalHelper_u32_Callback);
    MyLib_ProcessRecord_Stub(MyLib_ProcessRecord_Callback);
    
    uint32_t result = MyLib_Orchestrate_u32(0, NULL);
    
    TEST_ASSERT_EQUAL_UINT32(600, result);
}

void test_full_sequence_lower_bounds(void)
{
    g_counter_u32 = 0;
    InternalHelper_u32_fake_retval = 0;
    
    InternalHelper_u32_ExpectAndReturn(0, 0, 0);
    MyLib_ProcessRecord_Stub(MyLib_ProcessRecord_Callback);
    
    uint32_t result = MyLib_Orchestrate_u32(0, NULL);
    
    TEST_ASSERT_EQUAL_UINT32(0, result);
    TEST_ASSERT_EQUAL_UINT16(0, captured_record.id_u16);
    TEST_ASSERT_EQUAL_UINT32(0, captured_record.value_u32);
    TEST_ASSERT_EQUAL_UINT8(MYLIB_MULT_VALUE_U8, captured_multiplier);
}

void test_full_sequence_upper_bounds(void)
{
    uint16_t delta = 65535;
    g_counter_u32 = 500;
    InternalHelper_u32_fake_retval = 0;
    
    InternalHelper_u32_ExpectAndReturn(200, 65535, 0);
    MyLib_ProcessRecord_Stub(MyLib_ProcessRecord_Callback);
    
    uint32_t result = MyLib_Orchestrate_u32(200, &delta);
    
    TEST_ASSERT_EQUAL_UINT32(500, result);
}

void test_return_not_exceed_upper_boundary(void)
{
    g_counter_u32 = 500;
    InternalHelper_u32_fake_retval = 0;
    
    InternalHelper_u32_Stub(InternalHelper_u32_Callback);
    MyLib_ProcessRecord_Stub(MyLib_ProcessRecord_Callback);
    
    uint32_t result = MyLib_Orchestrate_u32(200, NULL);
    
    TEST_ASSERT_LESS_OR_EQUAL_UINT32(400, result);
}

void test_return_within_lower_boundary(void)
{
    g_counter_u32 = 0;
    InternalHelper_u32_fake_retval = 0;
    
    InternalHelper_u32_Stub(InternalHelper_u32_Callback);
    MyLib_ProcessRecord_Stub(MyLib_ProcessRecord_Callback);
    
    uint32_t result = MyLib_Orchestrate_u32(0, NULL);
    
    TEST_ASSERT_GREATER_OR_EQUAL_UINT32(0, result);
}