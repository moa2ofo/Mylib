#include "MyLib_Orchestrate_u32.h"
#include "mock_MyLib.h"
#include "unity.h"
#include <stdbool.h>
#include <stdint.h>




void setUp(void)
{
    g_counter_u32 = 0U;
}
void tearDown(void)
{
}
void test_start_at_lower_boundary_with_null_delta(void)
{
    uint32_t l_start_u32 = 0U;
    const uint16_t *l_delta_pc_u16 = NULL;
    uint32_t l_expected_base_u32 = 42U;
    uint32_t l_result_u32;
    MyLib_record_t l_expected_record;

    g_counter_u32 = 10U;

    InternalHelper_u32_ExpectAndReturn(l_start_u32, 0U, l_expected_base_u32);

    l_expected_record.id_u16 = (uint16_t)(l_expected_base_u32 & 0xFFFFU);
    l_expected_record.value_u32 = l_expected_base_u32 / 2U;

    MyLib_ProcessRecord_ExpectWithArray(&l_expected_record, 1, MYLIB_MULT_VALUE_U8);

    l_result_u32 = MyLib_Orchestrate_u32(l_start_u32, l_delta_pc_u16);

    TEST_ASSERT_EQUAL_UINT32(l_expected_base_u32 + g_counter_u32, l_result_u32);
}
void test_start_at_lower_boundary_with_delta_zero(void)
{
    uint32_t l_start_u32 = 0U;
    uint16_t l_delta_u16 = 0U;
    const uint16_t *l_delta_pc_u16 = &l_delta_u16;
    uint32_t l_expected_base_u32 = 42U;
    uint32_t l_result_u32;
    MyLib_record_t l_expected_record;

    g_counter_u32 = 10U;

    InternalHelper_u32_ExpectAndReturn(l_start_u32, 0U, l_expected_base_u32);

    l_expected_record.id_u16 = (uint16_t)(l_expected_base_u32 & 0xFFFFU);
    l_expected_record.value_u32 = l_expected_base_u32 / 2U;

    MyLib_ProcessRecord_ExpectWithArray(&l_expected_record, 1, MYLIB_MULT_VALUE_U8);

    l_result_u32 = MyLib_Orchestrate_u32(l_start_u32, l_delta_pc_u16);

    TEST_ASSERT_EQUAL_UINT32(l_expected_base_u32 + g_counter_u32, l_result_u32);
}
void test_start_just_inside_lower_boundary_with_null_delta(void)
{
    uint32_t l_start_u32 = 1U;
    const uint16_t *l_delta_pc_u16 = NULL;
    uint32_t l_expected_base_u32 = 50U;
    uint32_t l_result_u32;
    MyLib_record_t l_expected_record;

    g_counter_u32 = 15U;

    InternalHelper_u32_ExpectAndReturn(l_start_u32, 0U, l_expected_base_u32);

    l_expected_record.id_u16 = (uint16_t)(l_expected_base_u32 & 0xFFFFU);
    l_expected_record.value_u32 = l_expected_base_u32 / 2U;

    MyLib_ProcessRecord_ExpectWithArray(&l_expected_record, 1, MYLIB_MULT_VALUE_U8);

    l_result_u32 = MyLib_Orchestrate_u32(l_start_u32, l_delta_pc_u16);

    TEST_ASSERT_EQUAL_UINT32(l_expected_base_u32 + g_counter_u32, l_result_u32);
}
void test_start_at_mid_range_with_null_delta(void)
{
    uint32_t l_start_u32 = 100U;
    const uint16_t *l_delta_pc_u16 = NULL;
    uint32_t l_expected_base_u32 = 200U;
    uint32_t l_result_u32;
    MyLib_record_t l_expected_record;

    g_counter_u32 = 50U;

    InternalHelper_u32_ExpectAndReturn(l_start_u32, 0U, l_expected_base_u32);

    l_expected_record.id_u16 = (uint16_t)(l_expected_base_u32 & 0xFFFFU);
    l_expected_record.value_u32 = l_expected_base_u32 / 2U;

    MyLib_ProcessRecord_ExpectWithArray(&l_expected_record, 1, MYLIB_MULT_VALUE_U8);

    l_result_u32 = MyLib_Orchestrate_u32(l_start_u32, l_delta_pc_u16);

    TEST_ASSERT_EQUAL_UINT32(l_expected_base_u32 + g_counter_u32, l_result_u32);
}
void test_start_just_inside_upper_boundary_with_null_delta(void)
{
    uint32_t l_start_u32 = 199U;
    const uint16_t *l_delta_pc_u16 = NULL;
    uint32_t l_expected_base_u32 = 300U;
    uint32_t l_result_u32;
    MyLib_record_t l_expected_record;

    g_counter_u32 = 75U;

    InternalHelper_u32_ExpectAndReturn(l_start_u32, 0U, l_expected_base_u32);

    l_expected_record.id_u16 = (uint16_t)(l_expected_base_u32 & 0xFFFFU);
    l_expected_record.value_u32 = l_expected_base_u32 / 2U;

    MyLib_ProcessRecord_ExpectWithArray(&l_expected_record, 1, MYLIB_MULT_VALUE_U8);

    l_result_u32 = MyLib_Orchestrate_u32(l_start_u32, l_delta_pc_u16);

    TEST_ASSERT_EQUAL_UINT32(l_expected_base_u32 + g_counter_u32, l_result_u32);
}
void test_start_at_upper_boundary_with_null_delta(void)
{
    uint32_t l_start_u32 = 200U;
    const uint16_t *l_delta_pc_u16 = NULL;
    uint32_t l_expected_base_u32 = 350U;
    uint32_t l_result_u32;
    MyLib_record_t l_expected_record;

    g_counter_u32 = 100U;

    InternalHelper_u32_ExpectAndReturn(l_start_u32, 0U, l_expected_base_u32);

    l_expected_record.id_u16 = (uint16_t)(l_expected_base_u32 & 0xFFFFU);
    l_expected_record.value_u32 = l_expected_base_u32 / 2U;

    MyLib_ProcessRecord_ExpectWithArray(&l_expected_record, 1, MYLIB_MULT_VALUE_U8);

    l_result_u32 = MyLib_Orchestrate_u32(l_start_u32, l_delta_pc_u16);

    TEST_ASSERT_EQUAL_UINT32(l_expected_base_u32 + g_counter_u32, l_result_u32);
}
void test_start_mid_range_with_delta_at_lower_boundary(void)
{
    uint32_t l_start_u32 = 100U;
    uint16_t l_delta_u16 = 0U;
    const uint16_t *l_delta_pc_u16 = &l_delta_u16;
    uint32_t l_expected_base_u32 = 200U;
    uint32_t l_result_u32;
    MyLib_record_t l_expected_record;

    g_counter_u32 = 50U;

    InternalHelper_u32_ExpectAndReturn(l_start_u32, 0U, l_expected_base_u32);

    l_expected_record.id_u16 = (uint16_t)(l_expected_base_u32 & 0xFFFFU);
    l_expected_record.value_u32 = l_expected_base_u32 / 2U;

    MyLib_ProcessRecord_ExpectWithArray(&l_expected_record, 1, MYLIB_MULT_VALUE_U8);

    l_result_u32 = MyLib_Orchestrate_u32(l_start_u32, l_delta_pc_u16);

    TEST_ASSERT_EQUAL_UINT32(l_expected_base_u32 + g_counter_u32, l_result_u32);
}
void test_start_mid_range_with_delta_just_inside_lower(void)
{
    uint32_t l_start_u32 = 100U;
    uint16_t l_delta_u16 = 1U;
    const uint16_t *l_delta_pc_u16 = &l_delta_u16;
    uint32_t l_expected_base_u32 = 201U;
    uint32_t l_result_u32;
    MyLib_record_t l_expected_record;

    g_counter_u32 = 50U;

    InternalHelper_u32_ExpectAndReturn(l_start_u32, 1U, l_expected_base_u32);

    l_expected_record.id_u16 = (uint16_t)(l_expected_base_u32 & 0xFFFFU);
    l_expected_record.value_u32 = l_expected_base_u32 / 2U;

    MyLib_ProcessRecord_ExpectWithArray(&l_expected_record, 1, MYLIB_MULT_VALUE_U8);

    l_result_u32 = MyLib_Orchestrate_u32(l_start_u32, l_delta_pc_u16);

    TEST_ASSERT_EQUAL_UINT32(l_expected_base_u32 + g_counter_u32, l_result_u32);
}
void test_start_mid_range_with_delta_at_mid_range(void)
{
    uint32_t l_start_u32 = 100U;
    uint16_t l_delta_u16 = 32768U;
    const uint16_t *l_delta_pc_u16 = &l_delta_u16;
    uint32_t l_expected_base_u32 = 32868U;
    uint32_t l_result_u32;
    MyLib_record_t l_expected_record;

    g_counter_u32 = 50U;

    InternalHelper_u32_ExpectAndReturn(l_start_u32, 32768U, l_expected_base_u32);

    l_expected_record.id_u16 = (uint16_t)(l_expected_base_u32 & 0xFFFFU);
    l_expected_record.value_u32 = l_expected_base_u32 / 2U;

    MyLib_ProcessRecord_ExpectWithArray(&l_expected_record, 1, MYLIB_MULT_VALUE_U8);

    l_result_u32 = MyLib_Orchestrate_u32(l_start_u32, l_delta_pc_u16);

    TEST_ASSERT_EQUAL_UINT32(l_expected_base_u32 + g_counter_u32, l_result_u32);
}
void test_start_mid_range_with_delta_just_inside_upper(void)
{
    uint32_t l_start_u32 = 100U;
    uint16_t l_delta_u16 = 65534U;
    const uint16_t *l_delta_pc_u16 = &l_delta_u16;
    uint32_t l_expected_base_u32 = 65634U;
    uint32_t l_result_u32;
    MyLib_record_t l_expected_record;

    g_counter_u32 = 50U;

    InternalHelper_u32_ExpectAndReturn(l_start_u32, 65534U, l_expected_base_u32);

    l_expected_record.id_u16 = (uint16_t)(l_expected_base_u32 & 0xFFFFU);
    l_expected_record.value_u32 = l_expected_base_u32 / 2U;

    MyLib_ProcessRecord_ExpectWithArray(&l_expected_record, 1, MYLIB_MULT_VALUE_U8);

    l_result_u32 = MyLib_Orchestrate_u32(l_start_u32, l_delta_pc_u16);

    TEST_ASSERT_EQUAL_UINT32(l_expected_base_u32 + g_counter_u32, l_result_u32);
}
void test_start_mid_range_with_delta_at_upper_boundary(void)
{
    uint32_t l_start_u32 = 100U;
    uint16_t l_delta_u16 = 65535U;
    const uint16_t *l_delta_pc_u16 = &l_delta_u16;
    uint32_t l_expected_base_u32 = 65635U;
    uint32_t l_result_u32;
    MyLib_record_t l_expected_record;

    g_counter_u32 = 50U;

    InternalHelper_u32_ExpectAndReturn(l_start_u32, 65535U, l_expected_base_u32);

    l_expected_record.id_u16 = (uint16_t)(l_expected_base_u32 & 0xFFFFU);
    l_expected_record.value_u32 = l_expected_base_u32 / 2U;

    MyLib_ProcessRecord_ExpectWithArray(&l_expected_record, 1, MYLIB_MULT_VALUE_U8);

    l_result_u32 = MyLib_Orchestrate_u32(l_start_u32, l_delta_pc_u16);

    TEST_ASSERT_EQUAL_UINT32(l_expected_base_u32 + g_counter_u32, l_result_u32);
}
void test_start_upper_with_delta_at_upper_boundary(void)
{
    uint32_t l_start_u32 = 200U;
    uint16_t l_delta_u16 = 65535U;
    const uint16_t *l_delta_pc_u16 = &l_delta_u16;
    uint32_t l_expected_base_u32 = 65735U;
    uint32_t l_result_u32;
    MyLib_record_t l_expected_record;

    g_counter_u32 = 100U;

    InternalHelper_u32_ExpectAndReturn(l_start_u32, 65535U, l_expected_base_u32);

    l_expected_record.id_u16 = (uint16_t)(l_expected_base_u32 & 0xFFFFU);
    l_expected_record.value_u32 = l_expected_base_u32 / 2U;

    MyLib_ProcessRecord_ExpectWithArray(&l_expected_record, 1, MYLIB_MULT_VALUE_U8);

    l_result_u32 = MyLib_Orchestrate_u32(l_start_u32, l_delta_pc_u16);

    TEST_ASSERT_EQUAL_UINT32(l_expected_base_u32 + g_counter_u32, l_result_u32);
}
void test_start_lower_with_delta_at_upper_boundary(void)
{
    uint32_t l_start_u32 = 0U;
    uint16_t l_delta_u16 = 65535U;
    const uint16_t *l_delta_pc_u16 = &l_delta_u16;
    uint32_t l_expected_base_u32 = 65535U;
    uint32_t l_result_u32;
    MyLib_record_t l_expected_record;

    g_counter_u32 = 0U;

    InternalHelper_u32_ExpectAndReturn(l_start_u32, 65535U, l_expected_base_u32);

    l_expected_record.id_u16 = (uint16_t)(l_expected_base_u32 & 0xFFFFU);
    l_expected_record.value_u32 = l_expected_base_u32 / 2U;

    MyLib_ProcessRecord_ExpectWithArray(&l_expected_record, 1, MYLIB_MULT_VALUE_U8);

    l_result_u32 = MyLib_Orchestrate_u32(l_start_u32, l_delta_pc_u16);

    TEST_ASSERT_EQUAL_UINT32(l_expected_base_u32 + g_counter_u32, l_result_u32);
}
void test_record_id_masking_with_upper_bits_set(void)
{
    uint32_t l_start_u32 = 100U;
    const uint16_t *l_delta_pc_u16 = NULL;
    uint32_t l_expected_base_u32 = 0x12345678U;
    uint32_t l_result_u32;
    MyLib_record_t l_expected_record;

    g_counter_u32 = 50U;

    InternalHelper_u32_ExpectAndReturn(l_start_u32, 0U, l_expected_base_u32);

    l_expected_record.id_u16 = 0x5678U;
    l_expected_record.value_u32 = l_expected_base_u32 / 2U;

    MyLib_ProcessRecord_ExpectWithArray(&l_expected_record, 1, MYLIB_MULT_VALUE_U8);

    l_result_u32 = MyLib_Orchestrate_u32(l_start_u32, l_delta_pc_u16);

    TEST_ASSERT_EQUAL_UINT32(l_expected_base_u32 + g_counter_u32, l_result_u32);
}
void test_record_value_division_even_base(void)
{
    uint32_t l_start_u32 = 100U;
    const uint16_t *l_delta_pc_u16 = NULL;
    uint32_t l_expected_base_u32 = 1000U;
    uint32_t l_result_u32;
    MyLib_record_t l_expected_record;

    g_counter_u32 = 50U;

    InternalHelper_u32_ExpectAndReturn(l_start_u32, 0U, l_expected_base_u32);

    l_expected_record.id_u16 = (uint16_t)(l_expected_base_u32 & 0xFFFFU);
    l_expected_record.value_u32 = 500U;

    MyLib_ProcessRecord_ExpectWithArray(&l_expected_record, 1, MYLIB_MULT_VALUE_U8);

    l_result_u32 = MyLib_Orchestrate_u32(l_start_u32, l_delta_pc_u16);

    TEST_ASSERT_EQUAL_UINT32(l_expected_base_u32 + g_counter_u32, l_result_u32);
}
void test_record_value_division_odd_base(void)
{
    uint32_t l_start_u32 = 100U;
    const uint16_t *l_delta_pc_u16 = NULL;
    uint32_t l_expected_base_u32 = 1001U;
    uint32_t l_result_u32;
    MyLib_record_t l_expected_record;

    g_counter_u32 = 50U;

    InternalHelper_u32_ExpectAndReturn(l_start_u32, 0U, l_expected_base_u32);

    l_expected_record.id_u16 = (uint16_t)(l_expected_base_u32 & 0xFFFFU);
    l_expected_record.value_u32 = 500U;

    MyLib_ProcessRecord_ExpectWithArray(&l_expected_record, 1, MYLIB_MULT_VALUE_U8);

    l_result_u32 = MyLib_Orchestrate_u32(l_start_u32, l_delta_pc_u16);

    TEST_ASSERT_EQUAL_UINT32(l_expected_base_u32 + g_counter_u32, l_result_u32);
}
void test_process_record_called_with_correct_params(void)
{
    uint32_t l_start_u32 = 100U;
    const uint16_t *l_delta_pc_u16 = NULL;
    uint32_t l_expected_base_u32 = 200U;
    uint32_t l_result_u32;
    MyLib_record_t l_expected_record;

    g_counter_u32 = 50U;

    InternalHelper_u32_ExpectAndReturn(l_start_u32, 0U, l_expected_base_u32);

    l_expected_record.id_u16 = (uint16_t)(l_expected_base_u32 & 0xFFFFU);
    l_expected_record.value_u32 = l_expected_base_u32 / 2U;

    MyLib_ProcessRecord_ExpectWithArray(&l_expected_record, 1, MYLIB_MULT_VALUE_U8);

    l_result_u32 = MyLib_Orchestrate_u32(l_start_u32, l_delta_pc_u16);

    TEST_ASSERT_EQUAL_UINT32(l_expected_base_u32 + g_counter_u32, l_result_u32);
}
void test_return_value_with_counter_at_lower_boundary(void)
{
    uint32_t l_start_u32 = 100U;
    const uint16_t *l_delta_pc_u16 = NULL;
    uint32_t l_expected_base_u32 = 200U;
    uint32_t l_result_u32;
    MyLib_record_t l_expected_record;

    g_counter_u32 = 0U;

    InternalHelper_u32_ExpectAndReturn(l_start_u32, 0U, l_expected_base_u32);

    l_expected_record.id_u16 = (uint16_t)(l_expected_base_u32 & 0xFFFFU);
    l_expected_record.value_u32 = l_expected_base_u32 / 2U;

    MyLib_ProcessRecord_ExpectWithArray(&l_expected_record, 1, MYLIB_MULT_VALUE_U8);

    l_result_u32 = MyLib_Orchestrate_u32(l_start_u32, l_delta_pc_u16);

    TEST_ASSERT_EQUAL_UINT32(200U, l_result_u32);
}
void test_return_value_with_counter_at_mid_range(void)
{
    uint32_t l_start_u32 = 100U;
    const uint16_t *l_delta_pc_u16 = NULL;
    uint32_t l_expected_base_u32 = 200U;
    uint32_t l_result_u32;
    MyLib_record_t l_expected_record;

    g_counter_u32 = 250U;

    InternalHelper_u32_ExpectAndReturn(l_start_u32, 0U, l_expected_base_u32);

    l_expected_record.id_u16 = (uint16_t)(l_expected_base_u32 & 0xFFFFU);
    l_expected_record.value_u32 = l_expected_base_u32 / 2U;

    MyLib_ProcessRecord_ExpectWithArray(&l_expected_record, 1, MYLIB_MULT_VALUE_U8);

    l_result_u32 = MyLib_Orchestrate_u32(l_start_u32, l_delta_pc_u16);

    TEST_ASSERT_EQUAL_UINT32(450U, l_result_u32);
}
void test_return_value_with_counter_at_upper_boundary(void)
{
    uint32_t l_start_u32 = 100U;
    const uint16_t *l_delta_pc_u16 = NULL;
    uint32_t l_expected_base_u32 = 200U;
    uint32_t l_result_u32;
    MyLib_record_t l_expected_record;

    g_counter_u32 = 500U;

    InternalHelper_u32_ExpectAndReturn(l_start_u32, 0U, l_expected_base_u32);

    l_expected_record.id_u16 = (uint16_t)(l_expected_base_u32 & 0xFFFFU);
    l_expected_record.value_u32 = l_expected_base_u32 / 2U;

    MyLib_ProcessRecord_ExpectWithArray(&l_expected_record, 1, MYLIB_MULT_VALUE_U8);

    l_result_u32 = MyLib_Orchestrate_u32(l_start_u32, l_delta_pc_u16);

    TEST_ASSERT_EQUAL_UINT32(700U, l_result_u32);
}
void test_max_return_value_orchestration(void)
{
    uint32_t l_start_u32 = 200U;
    const uint16_t *l_delta_pc_u16 = NULL;
    uint32_t l_expected_base_u32 = 400U;
    uint32_t l_result_u32;
    MyLib_record_t l_expected_record;

    g_counter_u32 = 500U;

    InternalHelper_u32_ExpectAndReturn(l_start_u32, 0U, l_expected_base_u32);

    l_expected_record.id_u16 = (uint16_t)(l_expected_base_u32 & 0xFFFFU);
    l_expected_record.value_u32 = l_expected_base_u32 / 2U;

    MyLib_ProcessRecord_ExpectWithArray(&l_expected_record, 1, MYLIB_MULT_VALUE_U8);

    l_result_u32 = MyLib_Orchestrate_u32(l_start_u32, l_delta_pc_u16);

    TEST_ASSERT_EQUAL_UINT32(900U, l_result_u32);
}
