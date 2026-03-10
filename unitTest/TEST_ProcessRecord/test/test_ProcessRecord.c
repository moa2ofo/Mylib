#include "mock_MyLib.h"
#include "unity.h"
#include <ProcessRecord.h>




void setUp(void)
{
}
void tearDown(void)
{
}
void test_NULL_pointer_returns_immediately_no_side_effects(void)
{
    uint32_t initial_counter = g_counter_u32;

    ProcessRecord(NULL, 5U);

    TEST_ASSERT_EQUAL_UINT32(initial_counter, g_counter_u32);
}
void test_multiplier_zero_no_accumulation(void)
{
    MyLib_record_t rec = {.id_u16 = 1U, .value_u32 = 100U};
    uint32_t initial_counter = g_counter_u32;

    MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(0U, (const uint16_t *)&(uint8_t){0U}, 0U);
    MyLib_ComputeAdjustedValue_u32_IgnoreArg_delta_pc_u16();

    ProcessRecord(&rec, 0U);

    TEST_ASSERT_EQUAL_UINT32(initial_counter, g_counter_u32);
}
void test_multiplier_one_value_zero(void)
{
    MyLib_record_t rec = {.id_u16 = 2U, .value_u32 = 0U};
    uint32_t initial_counter = g_counter_u32;

    MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(0U, (const uint16_t *)&(uint8_t){1U}, 0U);
    MyLib_ComputeAdjustedValue_u32_IgnoreArg_delta_pc_u16();

    ProcessRecord(&rec, 1U);

    TEST_ASSERT_EQUAL_UINT32(initial_counter, g_counter_u32);
}
void test_multiplier_one_value_100(void)
{
    MyLib_record_t rec = {.id_u16 = 3U, .value_u32 = 100U};
    uint32_t initial_counter = g_counter_u32;

    MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(100U, (const uint16_t *)&(uint8_t){1U}, 0U);
    MyLib_ComputeAdjustedValue_u32_IgnoreArg_delta_pc_u16();

    ProcessRecord(&rec, 1U);

    TEST_ASSERT_EQUAL_UINT32(initial_counter + 100U, g_counter_u32);
}
void test_multiplier_one_value_max_wraps(void)
{
    MyLib_record_t rec = {.id_u16 = 4U, .value_u32 = UINT32_MAX};
    g_counter_u32 = 0U;

    MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(UINT32_MAX, (const uint16_t *)&(uint8_t){1U}, 0U);
    MyLib_ComputeAdjustedValue_u32_IgnoreArg_delta_pc_u16();

    ProcessRecord(&rec, 1U);

    TEST_ASSERT_EQUAL_UINT32(UINT32_MAX, g_counter_u32);
}
void test_multiplier_two_value_50(void)
{
    MyLib_record_t rec = {.id_u16 = 5U, .value_u32 = 50U};
    uint32_t initial_counter = g_counter_u32;

    MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(100U, (const uint16_t *)&(uint8_t){2U}, 0U);
    MyLib_ComputeAdjustedValue_u32_IgnoreArg_delta_pc_u16();

    ProcessRecord(&rec, 2U);

    TEST_ASSERT_EQUAL_UINT32(initial_counter + 100U, g_counter_u32);
}
void test_multiplier_two_value_zero(void)
{
    MyLib_record_t rec = {.id_u16 = 6U, .value_u32 = 0U};
    uint32_t initial_counter = g_counter_u32;

    MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(0U, (const uint16_t *)&(uint8_t){2U}, 0U);
    MyLib_ComputeAdjustedValue_u32_IgnoreArg_delta_pc_u16();

    ProcessRecord(&rec, 2U);

    TEST_ASSERT_EQUAL_UINT32(initial_counter, g_counter_u32);
}
void test_multiplier_128_value_10(void)
{
    MyLib_record_t rec = {.id_u16 = 7U, .value_u32 = 10U};
    uint32_t initial_counter = g_counter_u32;

    MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(1280U, (const uint16_t *)&(uint8_t){128U}, 0U);
    MyLib_ComputeAdjustedValue_u32_IgnoreArg_delta_pc_u16();

    ProcessRecord(&rec, 128U);

    TEST_ASSERT_EQUAL_UINT32(initial_counter + 1280U, g_counter_u32);
}
void test_multiplier_254_value_1(void)
{
    MyLib_record_t rec = {.id_u16 = 8U, .value_u32 = 1U};
    uint32_t initial_counter = g_counter_u32;

    MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(254U, (const uint16_t *)&(uint8_t){254U}, 0U);
    MyLib_ComputeAdjustedValue_u32_IgnoreArg_delta_pc_u16();

    ProcessRecord(&rec, 254U);

    TEST_ASSERT_EQUAL_UINT32(initial_counter + 254U, g_counter_u32);
}
void test_multiplier_255_value_1(void)
{
    MyLib_record_t rec = {.id_u16 = 9U, .value_u32 = 1U};
    uint32_t initial_counter = g_counter_u32;

    MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(255U, (const uint16_t *)&(uint8_t){255U}, 0U);
    MyLib_ComputeAdjustedValue_u32_IgnoreArg_delta_pc_u16();

    ProcessRecord(&rec, 255U);

    TEST_ASSERT_EQUAL_UINT32(initial_counter + 255U, g_counter_u32);
}
void test_multiplier_255_value_max_wraps(void)
{
    MyLib_record_t rec = {.id_u16 = 10U, .value_u32 = UINT32_MAX};
    g_counter_u32 = 0U;
    uint32_t expected_acc = (uint32_t)(255ULL * UINT32_MAX);

    MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(expected_acc, (const uint16_t *)&(uint8_t){255U}, 0U);
    MyLib_ComputeAdjustedValue_u32_IgnoreArg_delta_pc_u16();

    ProcessRecord(&rec, 255U);

    TEST_ASSERT_EQUAL_UINT32(expected_acc, g_counter_u32);
}
void test_multiplier_10_intermediate_wrap(void)
{
    MyLib_record_t rec = {.id_u16 = 11U, .value_u32 = 0xFFFFFFFFU / 5U + 1U};
    g_counter_u32 = 0U;
    uint32_t expected_acc = (uint32_t)((uint64_t)rec.value_u32 * 10ULL);

    MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(expected_acc, (const uint16_t *)&(uint8_t){10U}, 0U);
    MyLib_ComputeAdjustedValue_u32_IgnoreArg_delta_pc_u16();

    ProcessRecord(&rec, 10U);

    TEST_ASSERT_EQUAL_UINT32(expected_acc, g_counter_u32);
}
void test_counter_at_max_wraps_to_zero(void)
{
    MyLib_record_t rec = {.id_u16 = 12U, .value_u32 = 1U};
    g_counter_u32 = UINT32_MAX;

    MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(1U, (const uint16_t *)&(uint8_t){1U}, 0U);
    MyLib_ComputeAdjustedValue_u32_IgnoreArg_delta_pc_u16();

    ProcessRecord(&rec, 1U);

    TEST_ASSERT_EQUAL_UINT32(0U, g_counter_u32);
}
