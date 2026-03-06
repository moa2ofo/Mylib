#include "InternalHelper_u32.h"
#include "unity.h"




/* SECTION 1 — setUp() and tearDown() */

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

/* SECTION 2 — Test functions */

/**
 * @brief Test: y_u16 = 0 (lower boundary) → loop never executes, return x_u32 unchanged
 */
void test_y_zero_returns_x_unchanged(void)
{
    uint32_t result;
    uint32_t seed = 12345U;
    uint16_t iterations = 0U;

    result = InternalHelper_u32(seed, iterations);

    TEST_ASSERT_EQUAL_UINT32(seed, result);
}

/**
 * @brief Test: y_u16 = 1 (just inside lower boundary) → single iteration adds 0, return x_u32 + 0
 */
void test_y_one_adds_zero(void)
{
    uint32_t result;
    uint32_t seed = 100U;
    uint16_t iterations = 1U;
    uint32_t expected = seed + 0U;

    result = InternalHelper_u32(seed, iterations);

    TEST_ASSERT_EQUAL_UINT32(expected, result);
}

/**
 * @brief Test: y_u16 = 10 (mid-range) → accumulates sum of 2*(0+1+...+9), verify correct arithmetic
 */
void test_y_ten_accumulates_correctly(void)
{
    uint32_t result;
    uint32_t seed = 50U;
    uint16_t iterations = 10U;
    uint32_t expected = seed + (0U + 2U + 4U + 6U + 8U + 10U + 12U + 14U + 16U + 18U);

    result = InternalHelper_u32(seed, iterations);

    TEST_ASSERT_EQUAL_UINT32(expected, result);
}

/**
 * @brief Test: x_u32 = 0 (lower boundary seed) with y_u16 = 5 → verify accumulation starts from zero
 */
void test_x_zero_with_y_five(void)
{
    uint32_t result;
    uint32_t seed = 0U;
    uint16_t iterations = 5U;
    uint32_t expected = 0U + 0U + 2U + 4U + 6U + 8U;

    result = InternalHelper_u32(seed, iterations);

    TEST_ASSERT_EQUAL_UINT32(expected, result);
}

/**
 * @brief Test: x_u32 = 60535 (upper boundary seed) with y_u16 = 1 → verify seed at maximum valid range
 */
void test_x_max_with_y_one(void)
{
    uint32_t result;
    uint32_t seed = 60535U;
    uint16_t iterations = 1U;
    uint32_t expected = seed + 0U;

    result = InternalHelper_u32(seed, iterations);

    TEST_ASSERT_EQUAL_UINT32(expected, result);
}

/**
 * @brief Test: x_u32 = 1 (just inside lower boundary seed) with y_u16 = 3 → verify minimal non-zero seed
 */
void test_x_one_with_y_three(void)
{
    uint32_t result;
    uint32_t seed = 1U;
    uint16_t iterations = 3U;
    uint32_t expected = 1U + 0U + 2U + 4U;

    result = InternalHelper_u32(seed, iterations);

    TEST_ASSERT_EQUAL_UINT32(expected, result);
}

/**
 * @brief Test: x_u32 = 30000 (mid-range seed) with y_u16 = 8 → verify typical operational values
 */
void test_x_midrange_with_y_eight(void)
{
    uint32_t result;
    uint32_t seed = 30000U;
    uint16_t iterations = 8U;
    uint32_t expected = seed + (0U + 2U + 4U + 6U + 8U + 10U + 12U + 14U);

    result = InternalHelper_u32(seed, iterations);

    TEST_ASSERT_EQUAL_UINT32(expected, result);
}

/**
 * @brief Test: x_u32 = 60534 (just inside upper boundary seed) with y_u16 = 2 → verify near-maximum seed behavior
 */
void test_x_near_max_with_y_two(void)
{
    uint32_t result;
    uint32_t seed = 60534U;
    uint16_t iterations = 2U;
    uint32_t expected = seed + 0U + 2U;

    result = InternalHelper_u32(seed, iterations);

    TEST_ASSERT_EQUAL_UINT32(expected, result);
}

/**
 * @brief Test: y_u16 = 60535 (upper boundary iterations) with x_u32 = 0 → verify maximum loop count, expect 32-bit wrap-around
 */
void test_y_max_with_x_zero_wraparound(void)
{
    uint32_t result;
    uint32_t seed = 0U;
    uint16_t iterations = 60535U;
    uint32_t accumulator = seed;
    
    for (uint16_t i = 0U; i < iterations; i++)
    {
        accumulator += (uint32_t)(i * 2U);
    }
    uint32_t expected = accumulator;

    result = InternalHelper_u32(seed, iterations);

    TEST_ASSERT_EQUAL_UINT32(expected, result);
}

/**
 * @brief Test: y_u16 = 60534 (just inside upper boundary iterations) with x_u32 = 1 → verify near-maximum iterations
 */
void test_y_near_max_with_x_one(void)
{
    uint32_t result;
    uint32_t seed = 1U;
    uint16_t iterations = 60534U;
    uint32_t accumulator = seed;
    
    for (uint16_t i = 0U; i < iterations; i++)
    {
        accumulator += (uint32_t)(i * 2U);
    }
    uint32_t expected = accumulator;

    result = InternalHelper_u32(seed, iterations);

    TEST_ASSERT_EQUAL_UINT32(expected, result);
}

/**
 * @brief Test: x_u32 = 0xFFFFFFFF (maximum uint32_t) with y_u16 = 1 → verify wrap-around on first addition
 */
void test_x_max_uint32_with_y_one_wraparound(void)
{
    uint32_t result;
    uint32_t seed = 0xFFFFFFFFU;
    uint16_t iterations = 1U;
    uint32_t expected = seed + 0U;

    result = InternalHelper_u32(seed, iterations);

    TEST_ASSERT_EQUAL_UINT32(expected, result);
}

/**
 * @brief Test: x_u32 = 0xFFFFFFFE (one below maximum uint32_t) with y_u16 = 2 → verify wrap-around during iteration
 */
void test_x_near_max_uint32_with_y_two_wraparound(void)
{
    uint32_t result;
    uint32_t seed = 0xFFFFFFFEU;
    uint16_t iterations = 2U;
    uint32_t accumulator = seed;
    accumulator += 0U;
    accumulator += 2U;
    uint32_t expected = accumulator;

    result = InternalHelper_u32(seed, iterations);

    TEST_ASSERT_EQUAL_UINT32(expected, result);
}

/**
 * @brief Test: x_u32 = 60535, y_u16 = 60535 (both at upper boundary) → verify behavior at combined maximum valid inputs, expect wrap-around
 */
void test_x_max_y_max_wraparound(void)
{
    uint32_t result;
    uint32_t seed = 60535U;
    uint16_t iterations = 60535U;
    uint32_t accumulator = seed;
    
    for (uint16_t i = 0U; i < iterations; i++)
    {
        accumulator += (uint32_t)(i * 2U);
    }
    uint32_t expected = accumulator;

    result = InternalHelper_u32(seed, iterations);

    TEST_ASSERT_EQUAL_UINT32(expected, result);
}

/**
 * @brief Test: Golden vector - x_u32 = 100, y_u16 = 5 → independently compute expected result (100 + 0 + 2 + 4 + 6 + 8 = 120) and verify
 */
void test_golden_vector_x100_y5(void)
{
    uint32_t result;
    uint32_t seed = 100U;
    uint16_t iterations = 5U;
    uint32_t expected = 120U;

    result = InternalHelper_u32(seed, iterations);

    TEST_ASSERT_EQUAL_UINT32(expected, result);
}

/**
 * @brief Test: Golden vector - x_u32 = 50, y_u16 = 4 → independently compute expected result (50 + 0 + 2 + 4 + 6 = 62) and verify
 */
void test_golden_vector_x50_y4(void)
{
    uint32_t result;
    uint32_t seed = 50U;
    uint16_t iterations = 4U;
    uint32_t expected = 62U;

    result = InternalHelper_u32(seed, iterations);

    TEST_ASSERT_EQUAL_UINT32(expected, result);
}