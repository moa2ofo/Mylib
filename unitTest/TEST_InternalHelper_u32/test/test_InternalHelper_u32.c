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
    uint32_t result;
    uint32_t seed = 12345U;

    result = InternalHelper_u32(seed, 0U);

    TEST_ASSERT_EQUAL_UINT32(seed, result);
}
void test_y_one_adds_zero(void)
{
    uint32_t result;
    uint32_t seed = 100U;

    result = InternalHelper_u32(seed, 1U);

    TEST_ASSERT_EQUAL_UINT32(100U, result);
}
void test_y_ten_accumulates_ninety(void)
{
    uint32_t result;
    uint32_t seed = 50U;
    uint32_t expected = 50U + 90U;

    result = InternalHelper_u32(seed, 10U);

    TEST_ASSERT_EQUAL_UINT32(expected, result);
}
void test_y_60534_large_accumulation(void)
{
    uint32_t result;
    uint32_t seed = 0U;
    uint32_t expected_sum = 0U;
    uint32_t i;

    for (i = 0U; i < 60534U; i++)
    {
        expected_sum += (i * 2U);
    }

    result = InternalHelper_u32(seed, 60534U);

    TEST_ASSERT_EQUAL_UINT32(expected_sum, result);
}
void test_y_60535_max_iterations(void)
{
    uint32_t result;
    uint32_t seed = 0U;
    uint32_t expected_sum = 0U;
    uint32_t i;

    for (i = 0U; i < 60535U; i++)
    {
        expected_sum += (i * 2U);
    }

    result = InternalHelper_u32(seed, 60535U);

    TEST_ASSERT_EQUAL_UINT32(expected_sum, result);
}
void test_x_zero_y_five_returns_twenty(void)
{
    uint32_t result;

    result = InternalHelper_u32(0U, 5U);

    TEST_ASSERT_EQUAL_UINT32(20U, result);
}
void test_x_one_y_five_returns_twentyone(void)
{
    uint32_t result;

    result = InternalHelper_u32(1U, 5U);

    TEST_ASSERT_EQUAL_UINT32(21U, result);
}
void test_x_30000_y_ten_returns_30090(void)
{
    uint32_t result;

    result = InternalHelper_u32(30000U, 10U);

    TEST_ASSERT_EQUAL_UINT32(30090U, result);
}
void test_x_60534_y_one_returns_60534(void)
{
    uint32_t result;

    result = InternalHelper_u32(60534U, 1U);

    TEST_ASSERT_EQUAL_UINT32(60534U, result);
}
void test_x_60535_y_zero_returns_60535(void)
{
    uint32_t result;

    result = InternalHelper_u32(60535U, 0U);

    TEST_ASSERT_EQUAL_UINT32(60535U, result);
}
void test_x_near_max_y_ten_wraparound(void)
{
    uint32_t result;
    uint32_t seed = 0xFFFFFFF0U;
    uint32_t expected = seed;
    uint16_t i;

    for (i = 0U; i < 10U; i++)
    {
        expected += (i * 2U);
    }

    result = InternalHelper_u32(seed, 10U);

    TEST_ASSERT_EQUAL_UINT32(expected, result);
}
void test_x_max_y_one_no_overflow(void)
{
    uint32_t result;

    result = InternalHelper_u32(0xFFFFFFFFU, 1U);

    TEST_ASSERT_EQUAL_UINT32(0xFFFFFFFFU, result);
}
void test_x_max_y_two_wraps_to_one(void)
{
    uint32_t result;
    uint32_t expected = 0xFFFFFFFFU;

    expected += 0U;
    expected += 2U;

    result = InternalHelper_u32(0xFFFFFFFFU, 2U);

    TEST_ASSERT_EQUAL_UINT32(expected, result);
}
void test_golden_vector_x_100_y_5(void)
{
    uint32_t result;

    result = InternalHelper_u32(100U, 5U);

    TEST_ASSERT_EQUAL_UINT32(120U, result);
}
