#include "InternalHelper_u32.h"
#include "unity.h"




void setUp(void)
{
}
void tearDown(void)
{
}
void test_y_zero_returns_x_unchanged(void)
{
    uint32_t result_u32;
    uint32_t seed_u32 = 12345U;
    uint16_t iterations_u16 = 0U;

    result_u32 = InternalHelper_u32(seed_u32, iterations_u16);

    TEST_ASSERT_EQUAL_UINT32(seed_u32, result_u32);
}
void test_y_one_adds_zero_returns_x(void)
{
    uint32_t result_u32;
    uint32_t seed_u32 = 500U;
    uint16_t iterations_u16 = 1U;

    result_u32 = InternalHelper_u32(seed_u32, iterations_u16);

    TEST_ASSERT_EQUAL_UINT32(seed_u32, result_u32);
}
void test_y_ten_x_hundred_accumulates_correctly(void)
{
    uint32_t result_u32;
    uint32_t seed_u32 = 100U;
    uint16_t iterations_u16 = 10U;
    uint32_t expected_u32 = 100U + 0U + 2U + 4U + 6U + 8U + 10U + 12U + 14U + 16U + 18U;

    result_u32 = InternalHelper_u32(seed_u32, iterations_u16);

    TEST_ASSERT_EQUAL_UINT32(expected_u32, result_u32);
}
void test_y_max_x_zero_accumulates_at_boundary(void)
{
    uint32_t result_u32;
    uint32_t seed_u32 = 0U;
    uint16_t iterations_u16 = 60535U;
    uint32_t expected_u32 = 0U;
    uint32_t i_u32;

    for (i_u32 = 0U; i_u32 < iterations_u16; i_u32++)
    {
        expected_u32 += (i_u32 * 2U);
    }

    result_u32 = InternalHelper_u32(seed_u32, iterations_u16);

    TEST_ASSERT_EQUAL_UINT32(expected_u32, result_u32);
}
void test_x_zero_y_five_accumulates_from_zero(void)
{
    uint32_t result_u32;
    uint32_t seed_u32 = 0U;
    uint16_t iterations_u16 = 5U;
    uint32_t expected_u32 = 0U + 0U + 2U + 4U + 6U + 8U;

    result_u32 = InternalHelper_u32(seed_u32, iterations_u16);

    TEST_ASSERT_EQUAL_UINT32(expected_u32, result_u32);
}
void test_x_one_y_three_initializes_correctly(void)
{
    uint32_t result_u32;
    uint32_t seed_u32 = 1U;
    uint16_t iterations_u16 = 3U;
    uint32_t expected_u32 = 1U + 0U + 2U + 4U;

    result_u32 = InternalHelper_u32(seed_u32, iterations_u16);

    TEST_ASSERT_EQUAL_UINT32(expected_u32, result_u32);
}
void test_x_midrange_y_twenty_typical_operation(void)
{
    uint32_t result_u32;
    uint32_t seed_u32 = 30000U;
    uint16_t iterations_u16 = 20U;
    uint32_t expected_u32 = seed_u32;
    uint16_t i_u16;

    for (i_u16 = 0U; i_u16 < iterations_u16; i_u16++)
    {
        expected_u32 += (i_u16 * 2U);
    }

    result_u32 = InternalHelper_u32(seed_u32, iterations_u16);

    TEST_ASSERT_EQUAL_UINT32(expected_u32, result_u32);
}
void test_x_max_y_two_accumulates_from_max_seed(void)
{
    uint32_t result_u32;
    uint32_t seed_u32 = 60535U;
    uint16_t iterations_u16 = 2U;
    uint32_t expected_u32 = 60535U + 0U + 2U;

    result_u32 = InternalHelper_u32(seed_u32, iterations_u16);

    TEST_ASSERT_EQUAL_UINT32(expected_u32, result_u32);
}
void test_x_max_uint32_y_one_wraps_around(void)
{
    uint32_t result_u32;
    uint32_t seed_u32 = 0xFFFFFFFFU;
    uint16_t iterations_u16 = 1U;
    uint32_t expected_u32 = seed_u32 + 0U;

    result_u32 = InternalHelper_u32(seed_u32, iterations_u16);

    TEST_ASSERT_EQUAL_UINT32(expected_u32, result_u32);
}
void test_x_near_max_y_ten_wraps_multiple_times(void)
{
    uint32_t result_u32;
    uint32_t seed_u32 = 0xFFFFFFF0U;
    uint16_t iterations_u16 = 10U;
    uint32_t expected_u32 = seed_u32;
    uint16_t i_u16;

    for (i_u16 = 0U; i_u16 < iterations_u16; i_u16++)
    {
        expected_u32 += (i_u16 * 2U);
    }

    result_u32 = InternalHelper_u32(seed_u32, iterations_u16);

    TEST_ASSERT_EQUAL_UINT32(expected_u32, result_u32);
}
void test_golden_vector_x_fifty_y_ten(void)
{
    uint32_t result_u32;
    uint32_t seed_u32 = 50U;
    uint16_t iterations_u16 = 10U;
    uint32_t expected_u32 = 140U;

    result_u32 = InternalHelper_u32(seed_u32, iterations_u16);

    TEST_ASSERT_EQUAL_UINT32(expected_u32, result_u32);
}
