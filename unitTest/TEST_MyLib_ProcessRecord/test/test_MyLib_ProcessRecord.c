#include "MyLib_ProcessRecord.h"
#include "mock_MyLib.h"
#include "unity.h"




void setUp(void)
{
}
void tearDown(void)
{
}
void test_NULL_pointer_no_side_effects(void)
{
    uint32_t initial_counter = g_counter_u32;

    MyLib_ProcessRecord(NULL, 5U);

    TEST_ASSERT_EQUAL_UINT32(initial_counter, g_counter_u32);
}
void test_multiplier_zero_no_accumulation(void)
{
    MyLib_record_t rec = {.id_u16 = 1U, .value_u32 = 100U};
    uint32_t initial_counter = g_counter_u32;

    MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(0U, (const uint16_t *)&(uint8_t){0U}, 0U);
    MyLib_ComputeAdjustedValue_u32_IgnoreArg_delta_pc_u16();

    MyLib_ProcessRecord(&rec, 0U);

    TEST_ASSERT_EQUAL_UINT32(initial_counter, g_counter_u32);
}
void test_multiplier_one_single_accumulation(void)
{
    MyLib_record_t rec = {.id_u16 = 2U, .value_u32 = 50U};
    uint32_t initial_counter = g_counter_u32;

    MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(50U, (const uint16_t *)&(uint8_t){1U}, 0U);
    MyLib_ComputeAdjustedValue_u32_IgnoreArg_delta_pc_u16();

    MyLib_ProcessRecord(&rec, 1U);

    TEST_ASSERT_EQUAL_UINT32(initial_counter + 50U, g_counter_u32);
}
void test_multiplier_two_bounded_loop(void)
{
    MyLib_record_t rec = {.id_u16 = 3U, .value_u32 = 25U};
    uint32_t initial_counter = g_counter_u32;

    MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(50U, (const uint16_t *)&(uint8_t){2U}, 0U);
    MyLib_ComputeAdjustedValue_u32_IgnoreArg_delta_pc_u16();

    MyLib_ProcessRecord(&rec, 2U);

    TEST_ASSERT_EQUAL_UINT32(initial_counter + 50U, g_counter_u32);
}
void test_multiplier_128_midrange(void)
{
    MyLib_record_t rec = {.id_u16 = 4U, .value_u32 = 10U};
    uint32_t initial_counter = g_counter_u32;
    uint32_t expected_acc = 128U * 10U;

    MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(expected_acc, (const uint16_t *)&(uint8_t){128U}, 0U);
    MyLib_ComputeAdjustedValue_u32_IgnoreArg_delta_pc_u16();

    MyLib_ProcessRecord(&rec, 128U);

    TEST_ASSERT_EQUAL_UINT32(initial_counter + expected_acc, g_counter_u32);
}
void test_multiplier_255_upper_boundary(void)
{
    MyLib_record_t rec = {.id_u16 = 5U, .value_u32 = 8U};
    uint32_t initial_counter = g_counter_u32;
    uint32_t expected_acc = 255U * 8U;

    MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(expected_acc, (const uint16_t *)&(uint8_t){255U}, 0U);
    MyLib_ComputeAdjustedValue_u32_IgnoreArg_delta_pc_u16();

    MyLib_ProcessRecord(&rec, 255U);

    TEST_ASSERT_EQUAL_UINT32(initial_counter + expected_acc, g_counter_u32);
}
void test_value_zero_multiplier_ten(void)
{
    MyLib_record_t rec = {.id_u16 = 6U, .value_u32 = 0U};
    uint32_t initial_counter = g_counter_u32;

    MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(0U, (const uint16_t *)&(uint8_t){10U}, 0U);
    MyLib_ComputeAdjustedValue_u32_IgnoreArg_delta_pc_u16();

    MyLib_ProcessRecord(&rec, 10U);

    TEST_ASSERT_EQUAL_UINT32(initial_counter, g_counter_u32);
}
void test_value_max_multiplier_one(void)
{
    MyLib_record_t rec = {.id_u16 = 7U, .value_u32 = UINT32_MAX};
    uint32_t initial_counter = g_counter_u32;

    MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(UINT32_MAX, (const uint16_t *)&(uint8_t){1U}, 0U);
    MyLib_ComputeAdjustedValue_u32_IgnoreArg_delta_pc_u16();

    MyLib_ProcessRecord(&rec, 1U);

    TEST_ASSERT_EQUAL_UINT32(initial_counter + UINT32_MAX, g_counter_u32);
}
void test_value_max_multiplier_two_wraparound(void)
{
    MyLib_record_t rec = {.id_u16 = 8U, .value_u32 = UINT32_MAX};
    uint32_t initial_counter = g_counter_u32;
    uint32_t expected_acc = UINT32_MAX + UINT32_MAX;

    MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(expected_acc, (const uint16_t *)&(uint8_t){2U}, 0U);
    MyLib_ComputeAdjustedValue_u32_IgnoreArg_delta_pc_u16();

    MyLib_ProcessRecord(&rec, 2U);

    TEST_ASSERT_EQUAL_UINT32(initial_counter + expected_acc, g_counter_u32);
}
void test_counter_wraparound_from_near_max(void)
{
    MyLib_record_t rec = {.id_u16 = 9U, .value_u32 = 100U};
    g_counter_u32 = UINT32_MAX - 50U;
    uint32_t initial_counter = g_counter_u32;

    MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(100U, (const uint16_t *)&(uint8_t){1U}, 0U);
    MyLib_ComputeAdjustedValue_u32_IgnoreArg_delta_pc_u16();

    MyLib_ProcessRecord(&rec, 1U);

    TEST_ASSERT_EQUAL_UINT32(initial_counter + 100U, g_counter_u32);
}
void test_minimal_increment_one(void)
{
    MyLib_record_t rec = {.id_u16 = 10U, .value_u32 = 1U};
    uint32_t initial_counter = g_counter_u32;

    MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(1U, (const uint16_t *)&(uint8_t){1U}, 0U);
    MyLib_ComputeAdjustedValue_u32_IgnoreArg_delta_pc_u16();

    MyLib_ProcessRecord(&rec, 1U);

    TEST_ASSERT_EQUAL_UINT32(initial_counter + 1U, g_counter_u32);
}
void test_multiplier_three_bounded_loop(void)
{
    MyLib_record_t rec = {.id_u16 = 11U, .value_u32 = 100U};
    uint32_t initial_counter = g_counter_u32;

    MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(300U, (const uint16_t *)&(uint8_t){3U}, 0U);
    MyLib_ComputeAdjustedValue_u32_IgnoreArg_delta_pc_u16();

    MyLib_ProcessRecord(&rec, 3U);

    TEST_ASSERT_EQUAL_UINT32(initial_counter + 300U, g_counter_u32);
}
