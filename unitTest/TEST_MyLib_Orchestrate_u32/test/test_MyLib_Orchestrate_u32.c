#include "MyLib_Orchestrate_u32.h"
#include "mock_MyLib.h"
#include "unity.h"
#include <stdbool.h>
#include <stdint.h>




static uint32_t mock_InternalHelper_result;
static uint32_t mock_InternalHelper_call_count;
static uint32_t mock_InternalHelper_last_x;
static uint16_t mock_InternalHelper_last_y;

static uint32_t InternalHelper_u32_MockCallback(uint32_t x_u32, uint16_t y_u16, int call_count)
{
    mock_InternalHelper_call_count++;
    mock_InternalHelper_last_x = x_u32;
    mock_InternalHelper_last_y = y_u16;
    return mock_InternalHelper_result;
}

static const MyLib_record_t *captured_record_ptr;
static uint8_t captured_multiplier;
static uint32_t MyLib_ProcessRecord_call_count;

static void MyLib_ProcessRecord_MockCallback(const MyLib_record_t *rec_pc, uint8_t multiplier_u8, int call_count)
{
    MyLib_ProcessRecord_call_count++;
    captured_record_ptr = rec_pc;
    captured_multiplier = multiplier_u8;
}

void setUp(void)
{
    mock_InternalHelper_result = 0;
    mock_InternalHelper_call_count = 0;
    mock_InternalHelper_last_x = 0;
    mock_InternalHelper_last_y = 0;
    captured_record_ptr = NULL;
    captured_multiplier = 0;
    MyLib_ProcessRecord_call_count = 0;
    g_counter_u32 = 0;
}

void tearDown(void)
{
}

void test_start_0_delta_NULL(void)
{
    g_counter_u32 = 50;
    mock_InternalHelper_result = 100;
    
    InternalHelper_u32_CMockStubWithCallback(InternalHelper_u32_MockCallback);
    MyLib_ProcessRecord_CMockStubWithCallback(MyLib_ProcessRecord_MockCallback);
    
    uint32_t result = MyLib_Orchestrate_u32(0, NULL);
    
    TEST_ASSERT_EQUAL_UINT32(1, mock_InternalHelper_call_count);
    TEST_ASSERT_EQUAL_UINT32(0, mock_InternalHelper_last_x);
    TEST_ASSERT_EQUAL_UINT16(0, mock_InternalHelper_last_y);
    TEST_ASSERT_EQUAL_UINT32(150, result);
}

void test_start_0_delta_valid_0(void)
{
    uint16_t delta = 0;
    g_counter_u32 = 75;
    mock_InternalHelper_result = 200;
    
    InternalHelper_u32_CMockStubWithCallback(InternalHelper_u32_MockCallback);
    MyLib_ProcessRecord_CMockStubWithCallback(MyLib_ProcessRecord_MockCallback);
    
    uint32_t result = MyLib_Orchestrate_u32(0, &delta);
    
    TEST_ASSERT_EQUAL_UINT32(1, mock_InternalHelper_call_count);
    TEST_ASSERT_EQUAL_UINT32(0, mock_InternalHelper_last_x);
    TEST_ASSERT_EQUAL_UINT16(0, mock_InternalHelper_last_y);
    TEST_ASSERT_EQUAL_UINT32(275, result);
}

void test_start_1_delta_NULL(void)
{
    g_counter_u32 = 10;
    mock_InternalHelper_result = 50;
    
    InternalHelper_u32_CMockStubWithCallback(InternalHelper_u32_MockCallback);
    MyLib_ProcessRecord_CMockStubWithCallback(MyLib_ProcessRecord_MockCallback);
    
    uint32_t result = MyLib_Orchestrate_u32(1, NULL);
    
    TEST_ASSERT_EQUAL_UINT32(1, mock_InternalHelper_call_count);
    TEST_ASSERT_EQUAL_UINT32(1, mock_InternalHelper_last_x);
    TEST_ASSERT_EQUAL_UINT16(0, mock_InternalHelper_last_y);
    TEST_ASSERT_EQUAL_UINT32(60, result);
}

void test_start_100_delta_NULL(void)
{
    g_counter_u32 = 100;
    mock_InternalHelper_result = 150;
    
    InternalHelper_u32_CMockStubWithCallback(InternalHelper_u32_MockCallback);
    MyLib_ProcessRecord_CMockStubWithCallback(MyLib_ProcessRecord_MockCallback);
    
    uint32_t result = MyLib_Orchestrate_u32(100, NULL);
    
    TEST_ASSERT_EQUAL_UINT32(1, mock_InternalHelper_call_count);
    TEST_ASSERT_EQUAL_UINT32(100, mock_InternalHelper_last_x);
    TEST_ASSERT_EQUAL_UINT16(0, mock_InternalHelper_last_y);
    TEST_ASSERT_EQUAL_UINT32(250, result);
}

void test_start_200_delta_NULL(void)
{
    g_counter_u32 = 200;
    mock_InternalHelper_result = 300;
    
    InternalHelper_u32_CMockStubWithCallback(InternalHelper_u32_MockCallback);
    MyLib_ProcessRecord_CMockStubWithCallback(MyLib_ProcessRecord_MockCallback);
    
    uint32_t result = MyLib_Orchestrate_u32(200, NULL);
    
    TEST_ASSERT_EQUAL_UINT32(1, mock_InternalHelper_call_count);
    TEST_ASSERT_EQUAL_UINT32(200, mock_InternalHelper_last_x);
    TEST_ASSERT_EQUAL_UINT16(0, mock_InternalHelper_last_y);
    TEST_ASSERT_EQUAL_UINT32(500, result);
}

void test_start_200_delta_valid_200(void)
{
    uint16_t delta = 200;
    g_counter_u32 = 150;
    mock_InternalHelper_result = 250;
    
    InternalHelper_u32_CMockStubWithCallback(InternalHelper_u32_MockCallback);
    MyLib_ProcessRecord_CMockStubWithCallback(MyLib_ProcessRecord_MockCallback);
    
    uint32_t result = MyLib_Orchestrate_u32(200, &delta);
    
    TEST_ASSERT_EQUAL_UINT32(1, mock_InternalHelper_call_count);
    TEST_ASSERT_EQUAL_UINT32(200, mock_InternalHelper_last_x);
    TEST_ASSERT_EQUAL_UINT16(200, mock_InternalHelper_last_y);
    TEST_ASSERT_EQUAL_UINT32(400, result);
}

void test_start_100_delta_valid_0(void)
{
    uint16_t delta = 0;
    g_counter_u32 = 50;
    mock_InternalHelper_result = 100;
    
    InternalHelper_u32_CMockStubWithCallback(InternalHelper_u32_MockCallback);
    MyLib_ProcessRecord_CMockStubWithCallback(MyLib_ProcessRecord_MockCallback);
    
    uint32_t result = MyLib_Orchestrate_u32(100, &delta);
    
    TEST_ASSERT_EQUAL_UINT32(1, mock_InternalHelper_call_count);
    TEST_ASSERT_EQUAL_UINT32(100, mock_InternalHelper_last_x);
    TEST_ASSERT_EQUAL_UINT16(0, mock_InternalHelper_last_y);
    TEST_ASSERT_EQUAL_UINT32(150, result);
}

void test_start_100_delta_valid_1(void)
{
    uint16_t delta = 1;
    g_counter_u32 = 25;
    mock_InternalHelper_result = 125;
    
    InternalHelper_u32_CMockStubWithCallback(InternalHelper_u32_MockCallback);
    MyLib_ProcessRecord_CMockStubWithCallback(MyLib_ProcessRecord_MockCallback);
    
    uint32_t result = MyLib_Orchestrate_u32(100, &delta);
    
    TEST_ASSERT_EQUAL_UINT32(1, mock_InternalHelper_call_count);
    TEST_ASSERT_EQUAL_UINT32(100, mock_InternalHelper_last_x);
    TEST_ASSERT_EQUAL_UINT16(1, mock_InternalHelper_last_y);
    TEST_ASSERT_EQUAL_UINT32(150, result);
}

void test_start_100_delta_valid_32767(void)
{
    uint16_t delta = 32767;
    g_counter_u32 = 100;
    mock_InternalHelper_result = 50000;
    
    InternalHelper_u32_CMockStubWithCallback(InternalHelper_u32_MockCallback);
    MyLib_ProcessRecord_CMockStubWithCallback(MyLib_ProcessRecord_MockCallback);
    
    uint32_t result = MyLib_Orchestrate_u32(100, &delta);
    
    TEST_ASSERT_EQUAL_UINT32(1, mock_InternalHelper_call_count);
    TEST_ASSERT_EQUAL_UINT32(100, mock_InternalHelper_last_x);
    TEST_ASSERT_EQUAL_UINT16(32767, mock_InternalHelper_last_y);
    TEST_ASSERT_EQUAL_UINT32(50100, result);
}

void test_start_100_delta_valid_65535(void)
{
    uint16_t delta = 65535;
    g_counter_u32 = 200;
    mock_InternalHelper_result = 80000;
    
    InternalHelper_u32_CMockStubWithCallback(InternalHelper_u32_MockCallback);
    MyLib_ProcessRecord_CMockStubWithCallback(MyLib_ProcessRecord_MockCallback);
    
    uint32_t result = MyLib_Orchestrate_u32(100, &delta);
    
    TEST_ASSERT_EQUAL_UINT32(1, mock_InternalHelper_call_count);
    TEST_ASSERT_EQUAL_UINT32(100, mock_InternalHelper_last_x);
    TEST_ASSERT_EQUAL_UINT16(65535, mock_InternalHelper_last_y);
    TEST_ASSERT_EQUAL_UINT32(80200, result);
}

void test_start_0_delta_valid_65535(void)
{
    uint16_t delta = 65535;
    g_counter_u32 = 300;
    mock_InternalHelper_result = 70000;
    
    InternalHelper_u32_CMockStubWithCallback(InternalHelper_u32_MockCallback);
    MyLib_ProcessRecord_CMockStubWithCallback(MyLib_ProcessRecord_MockCallback);
    
    uint32_t result = MyLib_Orchestrate_u32(0, &delta);
    
    TEST_ASSERT_EQUAL_UINT32(1, mock_InternalHelper_call_count);
    TEST_ASSERT_EQUAL_UINT32(0, mock_InternalHelper_last_x);
    TEST_ASSERT_EQUAL_UINT16(65535, mock_InternalHelper_last_y);
    TEST_ASSERT_EQUAL_UINT32(70300, result);
}

void test_start_200_delta_valid_0(void)
{
    uint16_t delta = 0;
    g_counter_u32 = 50;
    mock_InternalHelper_result = 350;
    
    InternalHelper_u32_CMockStubWithCallback(InternalHelper_u32_MockCallback);
    MyLib_ProcessRecord_CMockStubWithCallback(MyLib_ProcessRecord_MockCallback);
    
    uint32_t result = MyLib_Orchestrate_u32(200, &delta);
    
    TEST_ASSERT_EQUAL_UINT32(1, mock_InternalHelper_call_count);
    TEST_ASSERT_EQUAL_UINT32(200, mock_InternalHelper_last_x);
    TEST_ASSERT_EQUAL_UINT16(0, mock_InternalHelper_last_y);
    TEST_ASSERT_EQUAL_UINT32(400, result);
}

void test_record_id_lower_16bits(void)
{
    g_counter_u32 = 0;
    mock_InternalHelper_result = 0x12345678;
    
    InternalHelper_u32_CMockStubWithCallback(InternalHelper_u32_MockCallback);
    MyLib_ProcessRecord_CMockStubWithCallback(MyLib_ProcessRecord_MockCallback);
    
    uint32_t result = MyLib_Orchestrate_u32(100, NULL);
    
    TEST_ASSERT_EQUAL_UINT32(1, MyLib_ProcessRecord_call_count);
    TEST_ASSERT_NOT_NULL(captured_record_ptr);
    TEST_ASSERT_EQUAL_UINT16(0x5678, captured_record_ptr->id_u16);
}

void test_record_value_odd_base(void)
{
    g_counter_u32 = 0;
    mock_InternalHelper_result = 101;
    
    InternalHelper_u32_CMockStubWithCallback(InternalHelper_u32_MockCallback);
    MyLib_ProcessRecord_CMockStubWithCallback(MyLib_ProcessRecord_MockCallback);
    
    uint32_t result = MyLib_Orchestrate_u32(1, NULL);
    
    TEST_ASSERT_EQUAL_UINT32(1, MyLib_ProcessRecord_call_count);
    TEST_ASSERT_NOT_NULL(captured_record_ptr);
    TEST_ASSERT_EQUAL_UINT32(50, captured_record_ptr->value_u32);
}

void test_record_value_even_base(void)
{
    g_counter_u32 = 0;
    mock_InternalHelper_result = 200;
    
    InternalHelper_u32_CMockStubWithCallback(InternalHelper_u32_MockCallback);
    MyLib_ProcessRecord_CMockStubWithCallback(MyLib_ProcessRecord_MockCallback);
    
    uint32_t result = MyLib_Orchestrate_u32(100, NULL);
    
    TEST_ASSERT_EQUAL_UINT32(1, MyLib_ProcessRecord_call_count);
    TEST_ASSERT_NOT_NULL(captured_record_ptr);
    TEST_ASSERT_EQUAL_UINT32(100, captured_record_ptr->value_u32);
}

void test_ProcessRecord_called_correctly(void)
{
    g_counter_u32 = 0;
    mock_InternalHelper_result = 1000;
    
    InternalHelper_u32_CMockStubWithCallback(InternalHelper_u32_MockCallback);
    MyLib_ProcessRecord_CMockStubWithCallback(MyLib_ProcessRecord_MockCallback);
    
    uint32_t result = MyLib_Orchestrate_u32(50, NULL);
    
    TEST_ASSERT_EQUAL_UINT32(1, MyLib_ProcessRecord_call_count);
    TEST_ASSERT_NOT_NULL(captured_record_ptr);
    TEST_ASSERT_EQUAL_UINT8(MYLIB_MULT_VALUE_U8, captured_multiplier);
}

void test_counter_lower_boundary(void)
{
    g_counter_u32 = 0;
    mock_InternalHelper_result = 150;
    
    InternalHelper_u32_CMockStubWithCallback(InternalHelper_u32_MockCallback);
    MyLib_ProcessRecord_CMockStubWithCallback(MyLib_ProcessRecord_MockCallback);
    
    uint32_t result = MyLib_Orchestrate_u32(100, NULL);
    
    TEST_ASSERT_EQUAL_UINT32(150, result);
}

void test_counter_mid_range(void)
{
    g_counter_u32 = 250;
    mock_InternalHelper_result = 150;
    
    InternalHelper_u32_CMockStubWithCallback(InternalHelper_u32_MockCallback);
    MyLib_ProcessRecord_CMockStubWithCallback(MyLib_ProcessRecord_MockCallback);
    
    uint32_t result = MyLib_Orchestrate_u32(100, NULL);
    
    TEST_ASSERT_EQUAL_UINT32(400, result);
}

void test_counter_upper_boundary(void)
{
    g_counter_u32 = 500;
    mock_InternalHelper_result = 150;
    
    InternalHelper_u32_CMockStubWithCallback(InternalHelper_u32_MockCallback);
    MyLib_ProcessRecord_CMockStubWithCallback(MyLib_ProcessRecord_MockCallback);
    
    uint32_t result = MyLib_Orchestrate_u32(100, NULL);
    
    TEST_ASSERT_EQUAL_UINT32(650, result);
}

void test_full_sequence_lower_boundaries(void)
{
    g_counter_u32 = 0;
    mock_InternalHelper_result = 100;
    
    InternalHelper_u32_CMockStubWithCallback(InternalHelper_u32_MockCallback);
    MyLib_ProcessRecord_CMockStubWithCallback(MyLib_ProcessRecord_MockCallback);
    
    uint32_t result = MyLib_Orchestrate_u32(0, NULL);
    
    TEST_ASSERT_EQUAL_UINT32(1, mock_InternalHelper_call_count);
    TEST_ASSERT_EQUAL_UINT32(0, mock_InternalHelper_last_x);
    TEST_ASSERT_EQUAL_UINT16(0, mock_InternalHelper_last_y);
    TEST_ASSERT_EQUAL_UINT32(1, MyLib_ProcessRecord_call_count);
    TEST_ASSERT_NOT_NULL(captured_record_ptr);
    TEST_ASSERT_EQUAL_UINT16(100, captured_record_ptr->id_u16);
    TEST_ASSERT_EQUAL_UINT32(50, captured_record_ptr->value_u32);
    TEST_ASSERT_EQUAL_UINT8(MYLIB_MULT_VALUE_U8, captured_multiplier);
    TEST_ASSERT_EQUAL_UINT32(100, result);
}

void test_full_sequence_upper_boundaries(void)
{
    uint16_t delta = 65535;
    g_counter_u32 = 500;
    mock_InternalHelper_result = 90000;
    
    InternalHelper_u32_CMockStubWithCallback(InternalHelper_u32_MockCallback);
    MyLib_ProcessRecord_CMockStubWithCallback(MyLib_ProcessRecord_MockCallback);
    
    uint32_t result = MyLib_Orchestrate_u32(200, &delta);
    
    TEST_ASSERT_EQUAL_UINT32(1, mock_InternalHelper_call_count);
    TEST_ASSERT_EQUAL_UINT32(200, mock_InternalHelper_last_x);
    TEST_ASSERT_EQUAL_UINT16(65535, mock_InternalHelper_last_y);
    TEST_ASSERT_EQUAL_UINT32(1, MyLib_ProcessRecord_call_count);
    TEST_ASSERT_NOT_NULL(captured_record_ptr);
    TEST_ASSERT_EQUAL_UINT16(24464, captured_record_ptr->id_u16);
    TEST_ASSERT_EQUAL_UINT32(45000, captured_record_ptr->value_u32);
    TEST_ASSERT_EQUAL_UINT8(MYLIB_MULT_VALUE_U8, captured_multiplier);
    TEST_ASSERT_EQUAL_UINT32(90500, result);
}