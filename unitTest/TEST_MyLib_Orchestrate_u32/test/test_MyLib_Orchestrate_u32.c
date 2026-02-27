#include "MyLib_Orchestrate_u32.h"
#include "mock_MyLib.h"
#include "unity.h"
#include <stdbool.h>
#include <stdint.h>




static uint32_t stub_base_value;
static uint16_t stub_delta_value;
static int InternalHelper_call_count;

static uint32_t InternalHelper_u32_Callback(uint32_t x_u32, uint16_t y_u16, int call_count)
{
    InternalHelper_call_count = call_count;
    stub_delta_value = y_u16;
    return stub_base_value;
}

void setUp(void)
{
    stub_base_value = 0;
    stub_delta_value = 0;
    InternalHelper_call_count = 0;
    g_counter_u32 = 0;
}

void tearDown(void)
{
}

void test_start_0_delta_NULL_verify_return_and_ProcessRecord(void)
{
    uint32_t result;
    MyLib_record_t expected_rec;
    
    stub_base_value = 42;
    g_counter_u32 = 10;
    
    InternalHelper_u32_Stub(InternalHelper_u32_Callback);
    
    expected_rec.id_u16 = (uint16_t)(stub_base_value & 0xFFFF);
    expected_rec.value_u32 = stub_base_value / 2;
    
    MyLib_ProcessRecord_Expect(&expected_rec, MYLIB_MULT_VALUE_U8);
    MyLib_ProcessRecord_IgnoreArg_rec_pc();
    
    result = MyLib_Orchestrate_u32(0, NULL);
    
    TEST_ASSERT_EQUAL_UINT32(stub_base_value + g_counter_u32, result);
    TEST_ASSERT_EQUAL_UINT16(0, stub_delta_value);
}

void test_start_0_delta_valid_0_verify_return_and_ProcessRecord(void)
{
    uint32_t result;
    uint16_t delta = 0;
    MyLib_record_t expected_rec;
    
    stub_base_value = 50;
    g_counter_u32 = 20;
    
    InternalHelper_u32_Stub(InternalHelper_u32_Callback);
    
    expected_rec.id_u16 = (uint16_t)(stub_base_value & 0xFFFF);
    expected_rec.value_u32 = stub_base_value / 2;
    
    MyLib_ProcessRecord_Expect(&expected_rec, MYLIB_MULT_VALUE_U8);
    MyLib_ProcessRecord_IgnoreArg_rec_pc();
    
    result = MyLib_Orchestrate_u32(0, &delta);
    
    TEST_ASSERT_EQUAL_UINT32(stub_base_value + g_counter_u32, result);
    TEST_ASSERT_EQUAL_UINT16(0, stub_delta_value);
}

void test_start_1_delta_NULL_verify_return_and_ProcessRecord(void)
{
    uint32_t result;
    MyLib_record_t expected_rec;
    
    stub_base_value = 100;
    g_counter_u32 = 30;
    
    InternalHelper_u32_Stub(InternalHelper_u32_Callback);
    
    expected_rec.id_u16 = (uint16_t)(stub_base_value & 0xFFFF);
    expected_rec.value_u32 = stub_base_value / 2;
    
    MyLib_ProcessRecord_Expect(&expected_rec, MYLIB_MULT_VALUE_U8);
    MyLib_ProcessRecord_IgnoreArg_rec_pc();
    
    result = MyLib_Orchestrate_u32(1, NULL);
    
    TEST_ASSERT_EQUAL_UINT32(stub_base_value + g_counter_u32, result);
    TEST_ASSERT_EQUAL_UINT16(0, stub_delta_value);
}

void test_start_100_delta_NULL_verify_return_and_ProcessRecord(void)
{
    uint32_t result;
    MyLib_record_t expected_rec;
    
    stub_base_value = 150;
    g_counter_u32 = 50;
    
    InternalHelper_u32_Stub(InternalHelper_u32_Callback);
    
    expected_rec.id_u16 = (uint16_t)(stub_base_value & 0xFFFF);
    expected_rec.value_u32 = stub_base_value / 2;
    
    MyLib_ProcessRecord_Expect(&expected_rec, MYLIB_MULT_VALUE_U8);
    MyLib_ProcessRecord_IgnoreArg_rec_pc();
    
    result = MyLib_Orchestrate_u32(100, NULL);
    
    TEST_ASSERT_EQUAL_UINT32(stub_base_value + g_counter_u32, result);
    TEST_ASSERT_EQUAL_UINT16(0, stub_delta_value);
}

void test_start_199_delta_NULL_verify_return_and_ProcessRecord(void)
{
    uint32_t result;
    MyLib_record_t expected_rec;
    
    stub_base_value = 199;
    g_counter_u32 = 100;
    
    InternalHelper_u32_Stub(InternalHelper_u32_Callback);
    
    expected_rec.id_u16 = (uint16_t)(stub_base_value & 0xFFFF);
    expected_rec.value_u32 = stub_base_value / 2;
    
    MyLib_ProcessRecord_Expect(&expected_rec, MYLIB_MULT_VALUE_U8);
    MyLib_ProcessRecord_IgnoreArg_rec_pc();
    
    result = MyLib_Orchestrate_u32(199, NULL);
    
    TEST_ASSERT_EQUAL_UINT32(stub_base_value + g_counter_u32, result);
    TEST_ASSERT_EQUAL_UINT16(0, stub_delta_value);
}

void test_start_200_delta_NULL_verify_return_and_ProcessRecord(void)
{
    uint32_t result;
    MyLib_record_t expected_rec;
    
    stub_base_value = 200;
    g_counter_u32 = 150;
    
    InternalHelper_u32_Stub(InternalHelper_u32_Callback);
    
    expected_rec.id_u16 = (uint16_t)(stub_base_value & 0xFFFF);
    expected_rec.value_u32 = stub_base_value / 2;
    
    MyLib_ProcessRecord_Expect(&expected_rec, MYLIB_MULT_VALUE_U8);
    MyLib_ProcessRecord_IgnoreArg_rec_pc();
    
    result = MyLib_Orchestrate_u32(200, NULL);
    
    TEST_ASSERT_EQUAL_UINT32(stub_base_value + g_counter_u32, result);
    TEST_ASSERT_EQUAL_UINT16(0, stub_delta_value);
}

void test_start_0_delta_0_verify_return_and_ProcessRecord(void)
{
    uint32_t result;
    uint16_t delta = 0;
    MyLib_record_t expected_rec;
    
    stub_base_value = 80;
    g_counter_u32 = 40;
    
    InternalHelper_u32_Stub(InternalHelper_u32_Callback);
    
    expected_rec.id_u16 = (uint16_t)(stub_base_value & 0xFFFF);
    expected_rec.value_u32 = stub_base_value / 2;
    
    MyLib_ProcessRecord_Expect(&expected_rec, MYLIB_MULT_VALUE_U8);
    MyLib_ProcessRecord_IgnoreArg_rec_pc();
    
    result = MyLib_Orchestrate_u32(0, &delta);
    
    TEST_ASSERT_EQUAL_UINT32(stub_base_value + g_counter_u32, result);
    TEST_ASSERT_EQUAL_UINT16(0, stub_delta_value);
}

void test_start_0_delta_1_verify_return_and_ProcessRecord(void)
{
    uint32_t result;
    uint16_t delta = 1;
    MyLib_record_t expected_rec;
    
    stub_base_value = 90;
    g_counter_u32 = 60;
    
    InternalHelper_u32_Stub(InternalHelper_u32_Callback);
    
    expected_rec.id_u16 = (uint16_t)(stub_base_value & 0xFFFF);
    expected_rec.value_u32 = stub_base_value / 2;
    
    MyLib_ProcessRecord_Expect(&expected_rec, MYLIB_MULT_VALUE_U8);
    MyLib_ProcessRecord_IgnoreArg_rec_pc();
    
    result = MyLib_Orchestrate_u32(0, &delta);
    
    TEST_ASSERT_EQUAL_UINT32(stub_base_value + g_counter_u32, result);
    TEST_ASSERT_EQUAL_UINT16(1, stub_delta_value);
}

void test_start_0_delta_32767_verify_return_and_ProcessRecord(void)
{
    uint32_t result;
    uint16_t delta = 32767;
    MyLib_record_t expected_rec;
    
    stub_base_value = 120;
    g_counter_u32 = 70;
    
    InternalHelper_u32_Stub(InternalHelper_u32_Callback);
    
    expected_rec.id_u16 = (uint16_t)(stub_base_value & 0xFFFF);
    expected_rec.value_u32 = stub_base_value / 2;
    
    MyLib_ProcessRecord_Expect(&expected_rec, MYLIB_MULT_VALUE_U8);
    MyLib_ProcessRecord_IgnoreArg_rec_pc();
    
    result = MyLib_Orchestrate_u32(0, &delta);
    
    TEST_ASSERT_EQUAL_UINT32(stub_base_value + g_counter_u32, result);
    TEST_ASSERT_EQUAL_UINT16(32767, stub_delta_value);
}

void test_start_0_delta_65534_verify_return_and_ProcessRecord(void)
{
    uint32_t result;
    uint16_t delta = 65534;
    MyLib_record_t expected_rec;
    
    stub_base_value = 130;
    g_counter_u32 = 80;
    
    InternalHelper_u32_Stub(InternalHelper_u32_Callback);
    
    expected_rec.id_u16 = (uint16_t)(stub_base_value & 0xFFFF);
    expected_rec.value_u32 = stub_base_value / 2;
    
    MyLib_ProcessRecord_Expect(&expected_rec, MYLIB_MULT_VALUE_U8);
    MyLib_ProcessRecord_IgnoreArg_rec_pc();
    
    result = MyLib_Orchestrate_u32(0, &delta);
    
    TEST_ASSERT_EQUAL_UINT32(stub_base_value + g_counter_u32, result);
    TEST_ASSERT_EQUAL_UINT16(65534, stub_delta_value);
}

void test_start_0_delta_65535_verify_return_and_ProcessRecord(void)
{
    uint32_t result;
    uint16_t delta = 65535;
    MyLib_record_t expected_rec;
    
    stub_base_value = 140;
    g_counter_u32 = 90;
    
    InternalHelper_u32_Stub(InternalHelper_u32_Callback);
    
    expected_rec.id_u16 = (uint16_t)(stub_base_value & 0xFFFF);
    expected_rec.value_u32 = stub_base_value / 2;
    
    MyLib_ProcessRecord_Expect(&expected_rec, MYLIB_MULT_VALUE_U8);
    MyLib_ProcessRecord_IgnoreArg_rec_pc();
    
    result = MyLib_Orchestrate_u32(0, &delta);
    
    TEST_ASSERT_EQUAL_UINT32(stub_base_value + g_counter_u32, result);
    TEST_ASSERT_EQUAL_UINT16(65535, stub_delta_value);
}

void test_start_200_delta_0_verify_return_and_ProcessRecord(void)
{
    uint32_t result;
    uint16_t delta = 0;
    MyLib_record_t expected_rec;
    
    stub_base_value = 160;
    g_counter_u32 = 110;
    
    InternalHelper_u32_Stub(InternalHelper_u32_Callback);
    
    expected_rec.id_u16 = (uint16_t)(stub_base_value & 0xFFFF);
    expected_rec.value_u32 = stub_base_value / 2;
    
    MyLib_ProcessRecord_Expect(&expected_rec, MYLIB_MULT_VALUE_U8);
    MyLib_ProcessRecord_IgnoreArg_rec_pc();
    
    result = MyLib_Orchestrate_u32(200, &delta);
    
    TEST_ASSERT_EQUAL_UINT32(stub_base_value + g_counter_u32, result);
    TEST_ASSERT_EQUAL_UINT16(0, stub_delta_value);
}

void test_start_200_delta_65535_verify_return_and_ProcessRecord(void)
{
    uint32_t result;
    uint16_t delta = 65535;
    MyLib_record_t expected_rec;
    
    stub_base_value = 170;
    g_counter_u32 = 120;
    
    InternalHelper_u32_Stub(InternalHelper_u32_Callback);
    
    expected_rec.id_u16 = (uint16_t)(stub_base_value & 0xFFFF);
    expected_rec.value_u32 = stub_base_value / 2;
    
    MyLib_ProcessRecord_Expect(&expected_rec, MYLIB_MULT_VALUE_U8);
    MyLib_ProcessRecord_IgnoreArg_rec_pc();
    
    result = MyLib_Orchestrate_u32(200, &delta);
    
    TEST_ASSERT_EQUAL_UINT32(stub_base_value + g_counter_u32, result);
    TEST_ASSERT_EQUAL_UINT16(65535, stub_delta_value);
}

void test_start_100_delta_32767_verify_return_and_ProcessRecord(void)
{
    uint32_t result;
    uint16_t delta = 32767;
    MyLib_record_t expected_rec;
    
    stub_base_value = 180;
    g_counter_u32 = 130;
    
    InternalHelper_u32_Stub(InternalHelper_u32_Callback);
    
    expected_rec.id_u16 = (uint16_t)(stub_base_value & 0xFFFF);
    expected_rec.value_u32 = stub_base_value / 2;
    
    MyLib_ProcessRecord_Expect(&expected_rec, MYLIB_MULT_VALUE_U8);
    MyLib_ProcessRecord_IgnoreArg_rec_pc();
    
    result = MyLib_Orchestrate_u32(100, &delta);
    
    TEST_ASSERT_EQUAL_UINT32(stub_base_value + g_counter_u32, result);
    TEST_ASSERT_EQUAL_UINT16(32767, stub_delta_value);
}

void test_NULL_delta_branch_coverage_start_50(void)
{
    uint32_t result;
    MyLib_record_t expected_rec;
    
    stub_base_value = 75;
    g_counter_u32 = 25;
    
    InternalHelper_u32_Stub(InternalHelper_u32_Callback);
    
    expected_rec.id_u16 = (uint16_t)(stub_base_value & 0xFFFF);
    expected_rec.value_u32 = stub_base_value / 2;
    
    MyLib_ProcessRecord_Expect(&expected_rec, MYLIB_MULT_VALUE_U8);
    MyLib_ProcessRecord_IgnoreArg_rec_pc();
    
    result = MyLib_Orchestrate_u32(50, NULL);
    
    TEST_ASSERT_EQUAL_UINT32(stub_base_value + g_counter_u32, result);
    TEST_ASSERT_EQUAL_UINT16(0, stub_delta_value);
}

void test_non_NULL_delta_branch_coverage_start_50_delta_100(void)
{
    uint32_t result;
    uint16_t delta = 100;
    MyLib_record_t expected_rec;
    
    stub_base_value = 85;
    g_counter_u32 = 35;
    
    InternalHelper_u32_Stub(InternalHelper_u32_Callback);
    
    expected_rec.id_u16 = (uint16_t)(stub_base_value & 0xFFFF);
    expected_rec.value_u32 = stub_base_value / 2;
    
    MyLib_ProcessRecord_Expect(&expected_rec, MYLIB_MULT_VALUE_U8);
    MyLib_ProcessRecord_IgnoreArg_rec_pc();
    
    result = MyLib_Orchestrate_u32(50, &delta);
    
    TEST_ASSERT_EQUAL_UINT32(stub_base_value + g_counter_u32, result);
    TEST_ASSERT_EQUAL_UINT16(100, stub_delta_value);
}

void test_id_u16_mask_base_0x12345678(void)
{
    uint32_t result;
    MyLib_record_t expected_rec;
    
    stub_base_value = 0x12345678;
    g_counter_u32 = 0;
    
    InternalHelper_u32_Stub(InternalHelper_u32_Callback);
    
    expected_rec.id_u16 = 0x5678;
    expected_rec.value_u32 = stub_base_value / 2;
    
    MyLib_ProcessRecord_Expect(&expected_rec, MYLIB_MULT_VALUE_U8);
    MyLib_ProcessRecord_IgnoreArg_rec_pc();
    
    result = MyLib_Orchestrate_u32(0, NULL);
    
    TEST_ASSERT_EQUAL_UINT32(stub_base_value + g_counter_u32, result);
}

void test_value_u32_division_base_100(void)
{
    uint32_t result;
    MyLib_record_t expected_rec;
    
    stub_base_value = 100;
    g_counter_u32 = 0;
    
    InternalHelper_u32_Stub(InternalHelper_u32_Callback);
    
    expected_rec.id_u16 = (uint16_t)(stub_base_value & 0xFFFF);
    expected_rec.value_u32 = 50;
    
    MyLib_ProcessRecord_Expect(&expected_rec, MYLIB_MULT_VALUE_U8);
    MyLib_ProcessRecord_IgnoreArg_rec_pc();
    
    result = MyLib_Orchestrate_u32(0, NULL);
    
    TEST_ASSERT_EQUAL_UINT32(stub_base_value + g_counter_u32, result);
}

void test_value_u32_division_base_101_odd(void)
{
    uint32_t result;
    MyLib_record_t expected_rec;
    
    stub_base_value = 101;
    g_counter_u32 = 0;
    
    InternalHelper_u32_Stub(InternalHelper_u32_Callback);
    
    expected_rec.id_u16 = (uint16_t)(stub_base_value & 0xFFFF);
    expected_rec.value_u32 = 50;
    
    MyLib_ProcessRecord_Expect(&expected_rec, MYLIB_MULT_VALUE_U8);
    MyLib_ProcessRecord_IgnoreArg_rec_pc();
    
    result = MyLib_Orchestrate_u32(0, NULL);
    
    TEST_ASSERT_EQUAL_UINT32(stub_base_value + g_counter_u32, result);
}

void test_ProcessRecord_called_with_correct_params(void)
{
    uint32_t result;
    MyLib_record_t expected_rec;
    
    stub_base_value = 200;
    g_counter_u32 = 50;
    
    InternalHelper_u32_Stub(InternalHelper_u32_Callback);
    
    expected_rec.id_u16 = (uint16_t)(stub_base_value & 0xFFFF);
    expected_rec.value_u32 = stub_base_value / 2;
    
    MyLib_ProcessRecord_Expect(&expected_rec, MYLIB_MULT_VALUE_U8);
    MyLib_ProcessRecord_IgnoreArg_rec_pc();
    
    result = MyLib_Orchestrate_u32(0, NULL);
    
    TEST_ASSERT_EQUAL_UINT32(stub_base_value + g_counter_u32, result);
}

void test_return_lower_boundary_base_0_counter_0(void)
{
    uint32_t result;
    MyLib_record_t expected_rec;
    
    stub_base_value = 0;
    g_counter_u32 = 0;
    
    InternalHelper_u32_Stub(InternalHelper_u32_Callback);
    
    expected_rec.id_u16 = (uint16_t)(stub_base_value & 0xFFFF);
    expected_rec.value_u32 = stub_base_value / 2;
    
    MyLib_ProcessRecord_Expect(&expected_rec, MYLIB_MULT_VALUE_U8);
    MyLib_ProcessRecord_IgnoreArg_rec_pc();
    
    result = MyLib_Orchestrate_u32(0, NULL);
    
    TEST_ASSERT_EQUAL_UINT32(0, result);
}

void test_return_upper_boundary_base_200_counter_200(void)
{
    uint32_t result;
    MyLib_record_t expected_rec;
    
    stub_base_value = 200;
    g_counter_u32 = 200;
    
    InternalHelper_u32_Stub(InternalHelper_u32_Callback);
    
    expected_rec.id_u16 = (uint16_t)(stub_base_value & 0xFFFF);
    expected_rec.value_u32 = stub_base_value / 2;
    
    MyLib_ProcessRecord_Expect(&expected_rec, MYLIB_MULT_VALUE_U8);
    MyLib_ProcessRecord_IgnoreArg_rec_pc();
    
    result = MyLib_Orchestrate_u32(0, NULL);
    
    TEST_ASSERT_EQUAL_UINT32(400, result);
}

void test_return_base_150_counter_250(void)
{
    uint32_t result;
    MyLib_record_t expected_rec;
    
    stub_base_value = 150;
    g_counter_u32 = 250;
    
    InternalHelper_u32_Stub(InternalHelper_u32_Callback);
    
    expected_rec.id_u16 = (uint16_t)(stub_base_value & 0xFFFF);
    expected_rec.value_u32 = stub_base_value / 2;
    
    MyLib_ProcessRecord_Expect(&expected_rec, MYLIB_MULT_VALUE_U8);
    MyLib_ProcessRecord_IgnoreArg_rec_pc();
    
    result = MyLib_Orchestrate_u32(0, NULL);
    
    TEST_ASSERT_EQUAL_UINT32(400, result);
}

void test_return_base_100_counter_100(void)
{
    uint32_t result;
    MyLib_record_t expected_rec;
    
    stub_base_value = 100;
    g_counter_u32 = 100;
    
    InternalHelper_u32_Stub(InternalHelper_u32_Callback);
    
    expected_rec.id_u16 = (uint16_t)(stub_base_value & 0xFFFF);
    expected_rec.value_u32 = stub_base_value / 2;
    
    MyLib_ProcessRecord_Expect(&expected_rec, MYLIB_MULT_VALUE_U8);
    MyLib_ProcessRecord_IgnoreArg_rec_pc();
    
    result = MyLib_Orchestrate_u32(0, NULL);
    
    TEST_ASSERT_EQUAL_UINT32(200, result);
}

void test_combo_start_0_delta_NULL_counter_0(void)
{
    uint32_t result;
    MyLib_record_t expected_rec;
    
    stub_base_value = 0;
    g_counter_u32 = 0;
    
    InternalHelper_u32_Stub(InternalHelper_u32_Callback);
    
    expected_rec.id_u16 = (uint16_t)(stub_base_value & 0xFFFF);
    expected_rec.value_u32 = stub_base_value / 2;
    
    MyLib_ProcessRecord_Expect(&expected_rec, MYLIB_MULT_VALUE_U8);
    MyLib_ProcessRecord_IgnoreArg_rec_pc();
    
    result = MyLib_Orchestrate_u32(0, NULL);
    
    TEST_ASSERT_EQUAL_UINT32(0, result);
    TEST_ASSERT_EQUAL_UINT16(0, stub_delta_value);
}

void test_combo_start_200_delta_65535_counter_500(void)
{
    uint32_t result;
    uint16_t delta = 65535;
    MyLib_record_t expected_rec;
    
    stub_base_value = 100;
    g_counter_u32 = 500;
    
    InternalHelper_u32_Stub(InternalHelper_u32_Callback);
    
    expected_rec.id_u16 = (uint16_t)(stub_base_value & 0xFFFF);
    expected_rec.value_u32 = stub_base_value / 2;
    
    MyLib_ProcessRecord_Expect(&expected_rec, MYLIB_MULT_VALUE_U8);
    MyLib_ProcessRecord_IgnoreArg_rec_pc();
    
    result = MyLib_Orchestrate_u32(200, &delta);
    
    TEST_ASSERT_LESS_OR_EQUAL_UINT32(400, result);
    TEST_ASSERT_EQUAL_UINT16(65535, stub_delta_value);
}

void test_combo_start_100_delta_1000_counter_250(void)
{
    uint32_t result;
    uint16_t delta = 1000;
    MyLib_record_t expected_rec;
    
    stub_base_value = 125;
    g_counter_u32 = 250;
    
    InternalHelper_u32_Stub(InternalHelper_u32_Callback);
    
    expected_rec.id_u16 = (uint16_t)(stub_base_value & 0xFFFF);
    expected_rec.value_u32 = stub_base_value / 2;
    
    MyLib_ProcessRecord_Expect(&expected_rec, MYLIB_MULT_VALUE_U8);
    MyLib_ProcessRecord_IgnoreArg_rec_pc();
    
    result = MyLib_Orchestrate_u32(100, &delta);
    
    TEST_ASSERT_EQUAL_UINT32(stub_base_value + g_counter_u32, result);
    TEST_ASSERT_EQUAL_UINT16(1000, stub_delta_value);
}