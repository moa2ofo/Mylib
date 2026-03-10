#include "MyLib_Orchestrate_u32.h"
#include "mock_MyLib.h"
#include "unity.h"
#include <stdbool.h>
#include <stdint.h>




void setUp(void)
{
}
void tearDown(void)
{
}
void test_start_0_delta_NULL_verify_return_and_call(void)
{
    uint32_t l_base_u32 = 42U;
    MyLib_record_t expected_rec;
    uint32_t result;

    g_counter_u32 = 10U;

    InternalHelper_u32_ExpectAndReturn(0U, 0U, l_base_u32);

    expected_rec.id_u16 = (uint16_t)(l_base_u32 & 0xFFFFU);
    expected_rec.value_u32 = l_base_u32 / 2U;

    MyLib_ProcessRecord_Expect(&expected_rec, MYLIB_MULT_VALUE_U8);
    MyLib_ProcessRecord_IgnoreArg_rec_pc();

    result = MyLib_Orchestrate_u32(0U, NULL);

    TEST_ASSERT_EQUAL_UINT32(l_base_u32 + g_counter_u32, result);
}
void test_start_0_delta_ptr_0_verify_return_and_call(void)
{
    uint16_t delta = 0U;
    uint32_t l_base_u32 = 50U;
    MyLib_record_t expected_rec;
    uint32_t result;

    g_counter_u32 = 15U;

    InternalHelper_u32_ExpectAndReturn(0U, 0U, l_base_u32);

    expected_rec.id_u16 = (uint16_t)(l_base_u32 & 0xFFFFU);
    expected_rec.value_u32 = l_base_u32 / 2U;

    MyLib_ProcessRecord_Expect(&expected_rec, MYLIB_MULT_VALUE_U8);
    MyLib_ProcessRecord_IgnoreArg_rec_pc();

    result = MyLib_Orchestrate_u32(0U, &delta);

    TEST_ASSERT_EQUAL_UINT32(l_base_u32 + g_counter_u32, result);
}
void test_start_1_delta_NULL_verify_return_and_call(void)
{
    uint32_t l_base_u32 = 100U;
    MyLib_record_t expected_rec;
    uint32_t result;

    g_counter_u32 = 20U;

    InternalHelper_u32_ExpectAndReturn(1U, 0U, l_base_u32);

    expected_rec.id_u16 = (uint16_t)(l_base_u32 & 0xFFFFU);
    expected_rec.value_u32 = l_base_u32 / 2U;

    MyLib_ProcessRecord_Expect(&expected_rec, MYLIB_MULT_VALUE_U8);
    MyLib_ProcessRecord_IgnoreArg_rec_pc();

    result = MyLib_Orchestrate_u32(1U, NULL);

    TEST_ASSERT_EQUAL_UINT32(l_base_u32 + g_counter_u32, result);
}
void test_start_100_delta_NULL_verify_return_and_call(void)
{
    uint32_t l_base_u32 = 200U;
    MyLib_record_t expected_rec;
    uint32_t result;

    g_counter_u32 = 50U;

    InternalHelper_u32_ExpectAndReturn(100U, 0U, l_base_u32);

    expected_rec.id_u16 = (uint16_t)(l_base_u32 & 0xFFFFU);
    expected_rec.value_u32 = l_base_u32 / 2U;

    MyLib_ProcessRecord_Expect(&expected_rec, MYLIB_MULT_VALUE_U8);
    MyLib_ProcessRecord_IgnoreArg_rec_pc();

    result = MyLib_Orchestrate_u32(100U, NULL);

    TEST_ASSERT_EQUAL_UINT32(l_base_u32 + g_counter_u32, result);
}
void test_start_199_delta_NULL_verify_return_and_call(void)
{
    uint32_t l_base_u32 = 300U;
    MyLib_record_t expected_rec;
    uint32_t result;

    g_counter_u32 = 75U;

    InternalHelper_u32_ExpectAndReturn(199U, 0U, l_base_u32);

    expected_rec.id_u16 = (uint16_t)(l_base_u32 & 0xFFFFU);
    expected_rec.value_u32 = l_base_u32 / 2U;

    MyLib_ProcessRecord_Expect(&expected_rec, MYLIB_MULT_VALUE_U8);
    MyLib_ProcessRecord_IgnoreArg_rec_pc();

    result = MyLib_Orchestrate_u32(199U, NULL);

    TEST_ASSERT_EQUAL_UINT32(l_base_u32 + g_counter_u32, result);
}
void test_start_200_delta_NULL_verify_return_and_call(void)
{
    uint32_t l_base_u32 = 350U;
    MyLib_record_t expected_rec;
    uint32_t result;

    g_counter_u32 = 100U;

    InternalHelper_u32_ExpectAndReturn(200U, 0U, l_base_u32);

    expected_rec.id_u16 = (uint16_t)(l_base_u32 & 0xFFFFU);
    expected_rec.value_u32 = l_base_u32 / 2U;

    MyLib_ProcessRecord_Expect(&expected_rec, MYLIB_MULT_VALUE_U8);
    MyLib_ProcessRecord_IgnoreArg_rec_pc();

    result = MyLib_Orchestrate_u32(200U, NULL);

    TEST_ASSERT_EQUAL_UINT32(l_base_u32 + g_counter_u32, result);
}
void test_start_0_delta_ptr_0_lower_bound(void)
{
    uint16_t delta = 0U;
    uint32_t l_base_u32 = 60U;
    MyLib_record_t expected_rec;
    uint32_t result;

    g_counter_u32 = 25U;

    InternalHelper_u32_ExpectAndReturn(0U, 0U, l_base_u32);

    expected_rec.id_u16 = (uint16_t)(l_base_u32 & 0xFFFFU);
    expected_rec.value_u32 = l_base_u32 / 2U;

    MyLib_ProcessRecord_Expect(&expected_rec, MYLIB_MULT_VALUE_U8);
    MyLib_ProcessRecord_IgnoreArg_rec_pc();

    result = MyLib_Orchestrate_u32(0U, &delta);

    TEST_ASSERT_EQUAL_UINT32(l_base_u32 + g_counter_u32, result);
}
void test_start_0_delta_ptr_1_verify_return_and_call(void)
{
    uint16_t delta = 1U;
    uint32_t l_base_u32 = 70U;
    MyLib_record_t expected_rec;
    uint32_t result;

    g_counter_u32 = 30U;

    InternalHelper_u32_ExpectAndReturn(0U, 1U, l_base_u32);

    expected_rec.id_u16 = (uint16_t)(l_base_u32 & 0xFFFFU);
    expected_rec.value_u32 = l_base_u32 / 2U;

    MyLib_ProcessRecord_Expect(&expected_rec, MYLIB_MULT_VALUE_U8);
    MyLib_ProcessRecord_IgnoreArg_rec_pc();

    result = MyLib_Orchestrate_u32(0U, &delta);

    TEST_ASSERT_EQUAL_UINT32(l_base_u32 + g_counter_u32, result);
}
void test_start_0_delta_ptr_32767_verify_return_and_call(void)
{
    uint16_t delta = 32767U;
    uint32_t l_base_u32 = 80U;
    MyLib_record_t expected_rec;
    uint32_t result;

    g_counter_u32 = 35U;

    InternalHelper_u32_ExpectAndReturn(0U, 32767U, l_base_u32);

    expected_rec.id_u16 = (uint16_t)(l_base_u32 & 0xFFFFU);
    expected_rec.value_u32 = l_base_u32 / 2U;

    MyLib_ProcessRecord_Expect(&expected_rec, MYLIB_MULT_VALUE_U8);
    MyLib_ProcessRecord_IgnoreArg_rec_pc();

    result = MyLib_Orchestrate_u32(0U, &delta);

    TEST_ASSERT_EQUAL_UINT32(l_base_u32 + g_counter_u32, result);
}
void test_start_0_delta_ptr_65534_verify_return_and_call(void)
{
    uint16_t delta = 65534U;
    uint32_t l_base_u32 = 90U;
    MyLib_record_t expected_rec;
    uint32_t result;

    g_counter_u32 = 40U;

    InternalHelper_u32_ExpectAndReturn(0U, 65534U, l_base_u32);

    expected_rec.id_u16 = (uint16_t)(l_base_u32 & 0xFFFFU);
    expected_rec.value_u32 = l_base_u32 / 2U;

    MyLib_ProcessRecord_Expect(&expected_rec, MYLIB_MULT_VALUE_U8);
    MyLib_ProcessRecord_IgnoreArg_rec_pc();

    result = MyLib_Orchestrate_u32(0U, &delta);

    TEST_ASSERT_EQUAL_UINT32(l_base_u32 + g_counter_u32, result);
}
void test_start_0_delta_ptr_65535_verify_return_and_call(void)
{
    uint16_t delta = 65535U;
    uint32_t l_base_u32 = 110U;
    MyLib_record_t expected_rec;
    uint32_t result;

    g_counter_u32 = 45U;

    InternalHelper_u32_ExpectAndReturn(0U, 65535U, l_base_u32);

    expected_rec.id_u16 = (uint16_t)(l_base_u32 & 0xFFFFU);
    expected_rec.value_u32 = l_base_u32 / 2U;

    MyLib_ProcessRecord_Expect(&expected_rec, MYLIB_MULT_VALUE_U8);
    MyLib_ProcessRecord_IgnoreArg_rec_pc();

    result = MyLib_Orchestrate_u32(0U, &delta);

    TEST_ASSERT_EQUAL_UINT32(l_base_u32 + g_counter_u32, result);
}
void test_start_100_delta_ptr_32767_verify_return_and_call(void)
{
    uint16_t delta = 32767U;
    uint32_t l_base_u32 = 150U;
    MyLib_record_t expected_rec;
    uint32_t result;

    g_counter_u32 = 60U;

    InternalHelper_u32_ExpectAndReturn(100U, 32767U, l_base_u32);

    expected_rec.id_u16 = (uint16_t)(l_base_u32 & 0xFFFFU);
    expected_rec.value_u32 = l_base_u32 / 2U;

    MyLib_ProcessRecord_Expect(&expected_rec, MYLIB_MULT_VALUE_U8);
    MyLib_ProcessRecord_IgnoreArg_rec_pc();

    result = MyLib_Orchestrate_u32(100U, &delta);

    TEST_ASSERT_EQUAL_UINT32(l_base_u32 + g_counter_u32, result);
}
void test_start_200_delta_ptr_65535_verify_return_and_call(void)
{
    uint16_t delta = 65535U;
    uint32_t l_base_u32 = 250U;
    MyLib_record_t expected_rec;
    uint32_t result;

    g_counter_u32 = 80U;

    InternalHelper_u32_ExpectAndReturn(200U, 65535U, l_base_u32);

    expected_rec.id_u16 = (uint16_t)(l_base_u32 & 0xFFFFU);
    expected_rec.value_u32 = l_base_u32 / 2U;

    MyLib_ProcessRecord_Expect(&expected_rec, MYLIB_MULT_VALUE_U8);
    MyLib_ProcessRecord_IgnoreArg_rec_pc();

    result = MyLib_Orchestrate_u32(200U, &delta);

    TEST_ASSERT_EQUAL_UINT32(l_base_u32 + g_counter_u32, result);
}
void test_start_100_delta_ptr_0_verify_return_and_call(void)
{
    uint16_t delta = 0U;
    uint32_t l_base_u32 = 180U;
    MyLib_record_t expected_rec;
    uint32_t result;

    g_counter_u32 = 70U;

    InternalHelper_u32_ExpectAndReturn(100U, 0U, l_base_u32);

    expected_rec.id_u16 = (uint16_t)(l_base_u32 & 0xFFFFU);
    expected_rec.value_u32 = l_base_u32 / 2U;

    MyLib_ProcessRecord_Expect(&expected_rec, MYLIB_MULT_VALUE_U8);
    MyLib_ProcessRecord_IgnoreArg_rec_pc();

    result = MyLib_Orchestrate_u32(100U, &delta);

    TEST_ASSERT_EQUAL_UINT32(l_base_u32 + g_counter_u32, result);
}
void test_start_200_delta_ptr_0_verify_return_and_call(void)
{
    uint16_t delta = 0U;
    uint32_t l_base_u32 = 280U;
    MyLib_record_t expected_rec;
    uint32_t result;

    g_counter_u32 = 90U;

    InternalHelper_u32_ExpectAndReturn(200U, 0U, l_base_u32);

    expected_rec.id_u16 = (uint16_t)(l_base_u32 & 0xFFFFU);
    expected_rec.value_u32 = l_base_u32 / 2U;

    MyLib_ProcessRecord_Expect(&expected_rec, MYLIB_MULT_VALUE_U8);
    MyLib_ProcessRecord_IgnoreArg_rec_pc();

    result = MyLib_Orchestrate_u32(200U, &delta);

    TEST_ASSERT_EQUAL_UINT32(l_base_u32 + g_counter_u32, result);
}
void test_start_100_delta_ptr_65535_verify_return_and_call(void)
{
    uint16_t delta = 65535U;
    uint32_t l_base_u32 = 220U;
    MyLib_record_t expected_rec;
    uint32_t result;

    g_counter_u32 = 85U;

    InternalHelper_u32_ExpectAndReturn(100U, 65535U, l_base_u32);

    expected_rec.id_u16 = (uint16_t)(l_base_u32 & 0xFFFFU);
    expected_rec.value_u32 = l_base_u32 / 2U;

    MyLib_ProcessRecord_Expect(&expected_rec, MYLIB_MULT_VALUE_U8);
    MyLib_ProcessRecord_IgnoreArg_rec_pc();

    result = MyLib_Orchestrate_u32(100U, &delta);

    TEST_ASSERT_EQUAL_UINT32(l_base_u32 + g_counter_u32, result);
}
void test_g_counter_0_start_100_delta_NULL_verify_return(void)
{
    uint32_t l_base_u32 = 120U;
    MyLib_record_t expected_rec;
    uint32_t result;

    g_counter_u32 = 0U;

    InternalHelper_u32_ExpectAndReturn(100U, 0U, l_base_u32);

    expected_rec.id_u16 = (uint16_t)(l_base_u32 & 0xFFFFU);
    expected_rec.value_u32 = l_base_u32 / 2U;

    MyLib_ProcessRecord_Expect(&expected_rec, MYLIB_MULT_VALUE_U8);
    MyLib_ProcessRecord_IgnoreArg_rec_pc();

    result = MyLib_Orchestrate_u32(100U, NULL);

    TEST_ASSERT_EQUAL_UINT32(l_base_u32 + 0U, result);
}
void test_g_counter_1_start_100_delta_NULL_verify_return(void)
{
    uint32_t l_base_u32 = 130U;
    MyLib_record_t expected_rec;
    uint32_t result;

    g_counter_u32 = 1U;

    InternalHelper_u32_ExpectAndReturn(100U, 0U, l_base_u32);

    expected_rec.id_u16 = (uint16_t)(l_base_u32 & 0xFFFFU);
    expected_rec.value_u32 = l_base_u32 / 2U;

    MyLib_ProcessRecord_Expect(&expected_rec, MYLIB_MULT_VALUE_U8);
    MyLib_ProcessRecord_IgnoreArg_rec_pc();

    result = MyLib_Orchestrate_u32(100U, NULL);

    TEST_ASSERT_EQUAL_UINT32(l_base_u32 + 1U, result);
}
void test_g_counter_250_start_100_delta_NULL_verify_return(void)
{
    uint32_t l_base_u32 = 140U;
    MyLib_record_t expected_rec;
    uint32_t result;

    g_counter_u32 = 250U;

    InternalHelper_u32_ExpectAndReturn(100U, 0U, l_base_u32);

    expected_rec.id_u16 = (uint16_t)(l_base_u32 & 0xFFFFU);
    expected_rec.value_u32 = l_base_u32 / 2U;

    MyLib_ProcessRecord_Expect(&expected_rec, MYLIB_MULT_VALUE_U8);
    MyLib_ProcessRecord_IgnoreArg_rec_pc();

    result = MyLib_Orchestrate_u32(100U, NULL);

    TEST_ASSERT_EQUAL_UINT32(l_base_u32 + 250U, result);
}
void test_g_counter_499_start_100_delta_NULL_verify_return(void)
{
    uint32_t l_base_u32 = 160U;
    MyLib_record_t expected_rec;
    uint32_t result;

    g_counter_u32 = 499U;

    InternalHelper_u32_ExpectAndReturn(100U, 0U, l_base_u32);

    expected_rec.id_u16 = (uint16_t)(l_base_u32 & 0xFFFFU);
    expected_rec.value_u32 = l_base_u32 / 2U;

    MyLib_ProcessRecord_Expect(&expected_rec, MYLIB_MULT_VALUE_U8);
    MyLib_ProcessRecord_IgnoreArg_rec_pc();

    result = MyLib_Orchestrate_u32(100U, NULL);

    TEST_ASSERT_EQUAL_UINT32(l_base_u32 + 499U, result);
}
void test_g_counter_500_start_100_delta_NULL_verify_return(void)
{
    uint32_t l_base_u32 = 170U;
    MyLib_record_t expected_rec;
    uint32_t result;

    g_counter_u32 = 500U;

    InternalHelper_u32_ExpectAndReturn(100U, 0U, l_base_u32);

    expected_rec.id_u16 = (uint16_t)(l_base_u32 & 0xFFFFU);
    expected_rec.value_u32 = l_base_u32 / 2U;

    MyLib_ProcessRecord_Expect(&expected_rec, MYLIB_MULT_VALUE_U8);
    MyLib_ProcessRecord_IgnoreArg_rec_pc();

    result = MyLib_Orchestrate_u32(100U, NULL);

    TEST_ASSERT_EQUAL_UINT32(l_base_u32 + 500U, result);
}
void test_record_id_lower_16_bits_all_zero(void)
{
    uint32_t l_base_u32 = 0x00010000U;
    MyLib_record_t expected_rec;
    uint32_t result;

    g_counter_u32 = 10U;

    InternalHelper_u32_ExpectAndReturn(50U, 0U, l_base_u32);

    expected_rec.id_u16 = 0x0000U;
    expected_rec.value_u32 = l_base_u32 / 2U;

    MyLib_ProcessRecord_Expect(&expected_rec, MYLIB_MULT_VALUE_U8);
    MyLib_ProcessRecord_IgnoreArg_rec_pc();

    result = MyLib_Orchestrate_u32(50U, NULL);

    TEST_ASSERT_EQUAL_UINT32(l_base_u32 + g_counter_u32, result);
}
void test_record_id_lower_16_bits_all_ones(void)
{
    uint32_t l_base_u32 = 0x0001FFFFU;
    MyLib_record_t expected_rec;
    uint32_t result;

    g_counter_u32 = 15U;

    InternalHelper_u32_ExpectAndReturn(60U, 0U, l_base_u32);

    expected_rec.id_u16 = 0xFFFFU;
    expected_rec.value_u32 = l_base_u32 / 2U;

    MyLib_ProcessRecord_Expect(&expected_rec, MYLIB_MULT_VALUE_U8);
    MyLib_ProcessRecord_IgnoreArg_rec_pc();

    result = MyLib_Orchestrate_u32(60U, NULL);

    TEST_ASSERT_EQUAL_UINT32(l_base_u32 + g_counter_u32, result);
}
void test_record_value_even_base(void)
{
    uint32_t l_base_u32 = 100U;
    MyLib_record_t expected_rec;
    uint32_t result;

    g_counter_u32 = 20U;

    InternalHelper_u32_ExpectAndReturn(70U, 0U, l_base_u32);

    expected_rec.id_u16 = (uint16_t)(l_base_u32 & 0xFFFFU);
    expected_rec.value_u32 = 50U;

    MyLib_ProcessRecord_Expect(&expected_rec, MYLIB_MULT_VALUE_U8);
    MyLib_ProcessRecord_IgnoreArg_rec_pc();

    result = MyLib_Orchestrate_u32(70U, NULL);

    TEST_ASSERT_EQUAL_UINT32(l_base_u32 + g_counter_u32, result);
}
void test_record_value_odd_base(void)
{
    uint32_t l_base_u32 = 101U;
    MyLib_record_t expected_rec;
    uint32_t result;

    g_counter_u32 = 25U;

    InternalHelper_u32_ExpectAndReturn(80U, 0U, l_base_u32);

    expected_rec.id_u16 = (uint16_t)(l_base_u32 & 0xFFFFU);
    expected_rec.value_u32 = 50U;

    MyLib_ProcessRecord_Expect(&expected_rec, MYLIB_MULT_VALUE_U8);
    MyLib_ProcessRecord_IgnoreArg_rec_pc();

    result = MyLib_Orchestrate_u32(80U, NULL);

    TEST_ASSERT_EQUAL_UINT32(l_base_u32 + g_counter_u32, result);
}
void test_record_multiplier_constant(void)
{
    uint32_t l_base_u32 = 200U;
    MyLib_record_t expected_rec;
    uint32_t result;

    g_counter_u32 = 30U;

    InternalHelper_u32_ExpectAndReturn(90U, 0U, l_base_u32);

    expected_rec.id_u16 = (uint16_t)(l_base_u32 & 0xFFFFU);
    expected_rec.value_u32 = l_base_u32 / 2U;

    MyLib_ProcessRecord_Expect(&expected_rec, MYLIB_MULT_VALUE_U8);
    MyLib_ProcessRecord_IgnoreArg_rec_pc();

    result = MyLib_Orchestrate_u32(90U, NULL);

    TEST_ASSERT_EQUAL_UINT32(l_base_u32 + g_counter_u32, result);
}
void test_upper_boundaries_all_params(void)
{
    uint16_t delta = 65535U;
    uint32_t l_base_u32 = 300U;
    MyLib_record_t expected_rec;
    uint32_t result;

    g_counter_u32 = 500U;

    InternalHelper_u32_ExpectAndReturn(200U, 65535U, l_base_u32);

    expected_rec.id_u16 = (uint16_t)(l_base_u32 & 0xFFFFU);
    expected_rec.value_u32 = l_base_u32 / 2U;

    MyLib_ProcessRecord_Expect(&expected_rec, MYLIB_MULT_VALUE_U8);
    MyLib_ProcessRecord_IgnoreArg_rec_pc();

    result = MyLib_Orchestrate_u32(200U, &delta);

    TEST_ASSERT_EQUAL_UINT32(l_base_u32 + g_counter_u32, result);
}
