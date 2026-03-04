#include "MyLib_ProcessRecord.h"
#include "mock_MyLib.h"
#include "unity.h"




/* SECTION 1 — Mock callbacks */

/* No mock callbacks required for this test suite */

/* SECTION 2 — setUp() and tearDown() */

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

/* SECTION 3 — Test functions */

/**
 * @brief Test: NULL pointer input – function returns immediately with no side effects, g_counter_u32 unchanged, MyLib_ComputeAdjustedValue_u32 not called.
 */
void test_MyLib_ProcessRecord_null_pointer_returns_immediately_no_side_effects(void)
{
    uint32_t initial_counter = 42U;
    g_counter_u32 = initial_counter;

    MyLib_ProcessRecord(NULL, 5U);

    TEST_ASSERT_EQUAL_UINT32(initial_counter, g_counter_u32);
}

/**
 * @brief Test: multiplier_u8 = 0 with valid record – l_acc_u32 = 0, g_counter_u32 unchanged, MyLib_ComputeAdjustedValue_u32 called with l_acc_u32=0.
 */
void test_MyLib_ProcessRecord_multiplier_zero_no_accumulation(void)
{
    MyLib_record_t record;
    record.id_u16 = 1U;
    record.value_u32 = 100U;

    uint32_t initial_counter = 50U;
    g_counter_u32 = initial_counter;

    MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(0U, (const uint16_t *)&(uint8_t){0U}, 0U);
    MyLib_ComputeAdjustedValue_u32_IgnoreArg_delta_pc_u16();

    MyLib_ProcessRecord(&record, 0U);

    TEST_ASSERT_EQUAL_UINT32(initial_counter, g_counter_u32);
}

/**
 * @brief Test: multiplier_u8 = 1 with valid record – l_acc_u32 = rec_pc->value_u32, g_counter_u32 incremented by rec_pc->value_u32, MyLib_ComputeAdjustedValue_u32 called with l_acc_u32.
 */
void test_MyLib_ProcessRecord_multiplier_one_single_accumulation(void)
{
    MyLib_record_t record;
    record.id_u16 = 2U;
    record.value_u32 = 75U;

    uint32_t initial_counter = 25U;
    g_counter_u32 = initial_counter;

    MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(75U, (const uint16_t *)&(uint8_t){1U}, 0U);
    MyLib_ComputeAdjustedValue_u32_IgnoreArg_delta_pc_u16();

    MyLib_ProcessRecord(&record, 1U);

    TEST_ASSERT_EQUAL_UINT32(initial_counter + 75U, g_counter_u32);
}

/**
 * @brief Test: multiplier_u8 = 2 with valid record – bounded loop executes twice, l_acc_u32 = 2 * rec_pc->value_u32, g_counter_u32 incremented accordingly, MyLib_ComputeAdjustedValue_u32 called.
 */
void test_MyLib_ProcessRecord_multiplier_two_bounded_loop_twice(void)
{
    MyLib_record_t record;
    record.id_u16 = 3U;
    record.value_u32 = 50U;

    uint32_t initial_counter = 10U;
    g_counter_u32 = initial_counter;

    uint32_t expected_acc = 2U * 50U;

    MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(expected_acc, (const uint16_t *)&(uint8_t){2U}, 0U);
    MyLib_ComputeAdjustedValue_u32_IgnoreArg_delta_pc_u16();

    MyLib_ProcessRecord(&record, 2U);

    TEST_ASSERT_EQUAL_UINT32(initial_counter + expected_acc, g_counter_u32);
}

/**
 * @brief Test: multiplier_u8 = 255 (upper boundary) with valid record – bounded loop executes 255 times, l_acc_u32 = 255 * rec_pc->value_u32, g_counter_u32 incremented accordingly, MyLib_ComputeAdjustedValue_u32 called.
 */
void test_MyLib_ProcessRecord_multiplier_255_upper_boundary(void)
{
    MyLib_record_t record;
    record.id_u16 = 4U;
    record.value_u32 = 1000U;

    uint32_t initial_counter = 500U;
    g_counter_u32 = initial_counter;

    uint32_t expected_acc = 255U * 1000U;

    MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(expected_acc, (const uint16_t *)&(uint8_t){255U}, 0U);
    MyLib_ComputeAdjustedValue_u32_IgnoreArg_delta_pc_u16();

    MyLib_ProcessRecord(&record, 255U);

    TEST_ASSERT_EQUAL_UINT32(initial_counter + expected_acc, g_counter_u32);
}

/**
 * @brief Test: multiplier_u8 = 128 (mid-range default case) with valid record – bounded loop executes 128 times, l_acc_u32 = 128 * rec_pc->value_u32, g_counter_u32 incremented accordingly, MyLib_ComputeAdjustedValue_u32 called.
 */
void test_MyLib_ProcessRecord_multiplier_128_mid_range_default_case(void)
{
    MyLib_record_t record;
    record.id_u16 = 5U;
    record.value_u32 = 200U;

    uint32_t initial_counter = 1000U;
    g_counter_u32 = initial_counter;

    uint32_t expected_acc = 128U * 200U;

    MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(expected_acc, (const uint16_t *)&(uint8_t){128U}, 0U);
    MyLib_ComputeAdjustedValue_u32_IgnoreArg_delta_pc_u16();

    MyLib_ProcessRecord(&record, 128U);

    TEST_ASSERT_EQUAL_UINT32(initial_counter + expected_acc, g_counter_u32);
}

/**
 * @brief Test: rec_pc->value_u32 = 0 with multiplier_u8 = 1 – l_acc_u32 = 0, g_counter_u32 unchanged, MyLib_ComputeAdjustedValue_u32 called with 0.
 */
void test_MyLib_ProcessRecord_record_value_zero_multiplier_one(void)
{
    MyLib_record_t record;
    record.id_u16 = 6U;
    record.value_u32 = 0U;

    uint32_t initial_counter = 100U;
    g_counter_u32 = initial_counter;

    MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(0U, (const uint16_t *)&(uint8_t){1U}, 0U);
    MyLib_ComputeAdjustedValue_u32_IgnoreArg_delta_pc_u16();

    MyLib_ProcessRecord(&record, 1U);

    TEST_ASSERT_EQUAL_UINT32(initial_counter, g_counter_u32);
}

/**
 * @brief Test: rec_pc->value_u32 = 1 with multiplier_u8 = 1 – l_acc_u32 = 1, g_counter_u32 incremented by 1, MyLib_ComputeAdjustedValue_u32 called with 1.
 */
void test_MyLib_ProcessRecord_record_value_one_multiplier_one(void)
{
    MyLib_record_t record;
    record.id_u16 = 7U;
    record.value_u32 = 1U;

    uint32_t initial_counter = 99U;
    g_counter_u32 = initial_counter;

    MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(1U, (const uint16_t *)&(uint8_t){1U}, 0U);
    MyLib_ComputeAdjustedValue_u32_IgnoreArg_delta_pc_u16();

    MyLib_ProcessRecord(&record, 1U);

    TEST_ASSERT_EQUAL_UINT32(initial_counter + 1U, g_counter_u32);
}

/**
 * @brief Test: rec_pc->value_u32 = 0xFFFFFFFF (upper boundary) with multiplier_u8 = 1 – l_acc_u32 = 0xFFFFFFFF, g_counter_u32 incremented by 0xFFFFFFFF, MyLib_ComputeAdjustedValue_u32 called.
 */
void test_MyLib_ProcessRecord_record_value_max_uint32_multiplier_one(void)
{
    MyLib_record_t record;
    record.id_u16 = 8U;
    record.value_u32 = 0xFFFFFFFFU;

    uint32_t initial_counter = 10U;
    g_counter_u32 = initial_counter;

    MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(0xFFFFFFFFU, (const uint16_t *)&(uint8_t){1U}, 0U);
    MyLib_ComputeAdjustedValue_u32_IgnoreArg_delta_pc_u16();

    MyLib_ProcessRecord(&record, 1U);

    TEST_ASSERT_EQUAL_UINT32(initial_counter + 0xFFFFFFFFU, g_counter_u32);
}

/**
 * @brief Test: rec_pc->value_u32 = 0x80000000 (mid-range) with multiplier_u8 = 1 – l_acc_u32 = 0x80000000, g_counter_u32 incremented by 0x80000000, MyLib_ComputeAdjustedValue_u32 called.
 */
void test_MyLib_ProcessRecord_record_value_mid_range_multiplier_one(void)
{
    MyLib_record_t record;
    record.id_u16 = 9U;
    record.value_u32 = 0x80000000U;

    uint32_t initial_counter = 0x10000000U;
    g_counter_u32 = initial_counter;

    MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(0x80000000U, (const uint16_t *)&(uint8_t){1U}, 0U);
    MyLib_ComputeAdjustedValue_u32_IgnoreArg_delta_pc_u16();

    MyLib_ProcessRecord(&record, 1U);

    TEST_ASSERT_EQUAL_UINT32(initial_counter + 0x80000000U, g_counter_u32);
}

/**
 * @brief Test: uint32_t wrap-around on accumulation – rec_pc->value_u32 = 0xFFFFFFFF, multiplier_u8 = 2, l_acc_u32 wraps to 0xFFFFFFFE, g_counter_u32 incremented accordingly, MyLib_ComputeAdjustedValue_u32 called.
 */
void test_MyLib_ProcessRecord_accumulation_wraparound(void)
{
    MyLib_record_t record;
    record.id_u16 = 10U;
    record.value_u32 = 0xFFFFFFFFU;

    uint32_t initial_counter = 100U;
    g_counter_u32 = initial_counter;

    uint32_t expected_acc = 0xFFFFFFFEU;

    MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(expected_acc, (const uint16_t *)&(uint8_t){2U}, 0U);
    MyLib_ComputeAdjustedValue_u32_IgnoreArg_delta_pc_u16();

    MyLib_ProcessRecord(&record, 2U);

    TEST_ASSERT_EQUAL_UINT32(initial_counter + expected_acc, g_counter_u32);
}

/**
 * @brief Test: uint32_t wrap-around on g_counter_u32 increment – g_counter_u32 near maximum, l_acc_u32 causes wrap, final g_counter_u32 wraps correctly, MyLib_ComputeAdjustedValue_u32 called.
 */
void test_MyLib_ProcessRecord_counter_wraparound(void)
{
    MyLib_record_t record;
    record.id_u16 = 11U;
    record.value_u32 = 10U;

    uint32_t initial_counter = 0xFFFFFFFAU;
    g_counter_u32 = initial_counter;

    uint32_t expected_acc = 10U;
    uint32_t expected_counter = initial_counter + expected_acc;

    MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(expected_acc, (const uint16_t *)&(uint8_t){1U}, 0U);
    MyLib_ComputeAdjustedValue_u32_IgnoreArg_delta_pc_u16();

    MyLib_ProcessRecord(&record, 1U);

    TEST_ASSERT_EQUAL_UINT32(expected_counter, g_counter_u32);
}

/**
 * @brief Test: multiplier_u8 = 0 with rec_pc->value_u32 = 0xFFFFFFFF – l_acc_u32 = 0 regardless of record value, g_counter_u32 unchanged, MyLib_ComputeAdjustedValue_u32 called with 0.
 */
void test_MyLib_ProcessRecord_multiplier_zero_with_max_record_value(void)
{
    MyLib_record_t record;
    record.id_u16 = 12U;
    record.value_u32 = 0xFFFFFFFFU;

    uint32_t initial_counter = 500U;
    g_counter_u32 = initial_counter;

    MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(0U, (const uint16_t *)&(uint8_t){0U}, 0U);
    MyLib_ComputeAdjustedValue_u32_IgnoreArg_delta_pc_u16();

    MyLib_ProcessRecord(&record, 0U);

    TEST_ASSERT_EQUAL_UINT32(initial_counter, g_counter_u32);
}

/**
 * @brief Test: multiplier_u8 = 255 with rec_pc->value_u32 = 0xFFFFFFFF – bounded loop executes 255 times, l_acc_u32 wraps multiple times, final l_acc_u32 computed correctly, g_counter_u32 incremented, MyLib_ComputeAdjustedValue_u32 called.
 */
void test_MyLib_ProcessRecord_multiplier_255_with_max_record_value_multiple_wraparounds(void)
{
    MyLib_record_t record;
    record.id_u16 = 13U;
    record.value_u32 = 0xFFFFFFFFU;

    uint32_t initial_counter = 1000U;
    g_counter_u32 = initial_counter;

    uint32_t expected_acc = 0xFFFFFF01U;

    MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(expected_acc, (const uint16_t *)&(uint8_t){255U}, 0U);
    MyLib_ComputeAdjustedValue_u32_IgnoreArg_delta_pc_u16();

    MyLib_ProcessRecord(&record, 255U);

    TEST_ASSERT_EQUAL_UINT32(initial_counter + expected_acc, g_counter_u32);
}