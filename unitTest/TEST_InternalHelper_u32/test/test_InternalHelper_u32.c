#include "InternalHelper_u32.h"
#include "unity.h"

/* SECTION 1 — setUp() and tearDown() */

void setUp(void) {
  g_counter_u32 = 0U;
  g_record.id_u16 = 0U;
  g_record.value_u32 = 0U;
  g_systemReady_b = false;
}

void tearDown(void) {
}

/* SECTION 2 — Test functions */

/**
 * @brief Test: y_u16 = 0 (lower boundary) → no loop iterations, return x_u32 unchanged
 */
void test_y_zero_returns_x_unchanged(void) {
  uint32_t result;
  uint32_t seed = 12345U;
  uint16_t iterations = 0U;

  result = InternalHelper_u32(seed, iterations);

  TEST_ASSERT_EQUAL_UINT32(12345U, result);
}

/**
 * @brief Test: y_u16 = 1 (one step inside lower boundary) → single iteration adds 0, return x_u32 + 0
 */
void test_y_one_adds_zero_returns_x(void) {
  uint32_t result;
  uint32_t seed = 100U;
  uint16_t iterations = 1U;

  result = InternalHelper_u32(seed, iterations);

  TEST_ASSERT_EQUAL_UINT32(100U, result);
}

/**
 * @brief Test: y_u16 = mid-range value (e.g., 30000) → accumulates sum of even sequence, verify correct arithmetic
 */
void test_y_midrange_accumulates_correctly(void) {
  uint32_t result;
  uint32_t seed = 1000U;
  uint16_t iterations = 30000U;
  uint32_t expected;

  expected = seed + (30000U * 29999U);

  result = InternalHelper_u32(seed, iterations);

  TEST_ASSERT_EQUAL_UINT32(expected, result);
}

/**
 * @brief Test: y_u16 = 60534 (one step inside upper boundary) → accumulates large even sequence, verify correct result
 */
void test_y_one_below_upper_boundary(void) {
  uint32_t result;
  uint32_t seed = 500U;
  uint16_t iterations = 60534U;
  uint32_t expected;

  expected = seed + (60534U * 60533U);

  result = InternalHelper_u32(seed, iterations);

  TEST_ASSERT_EQUAL_UINT32(expected, result);
}

/**
 * @brief Test: y_u16 = 60535 (upper boundary) → maximum loop iterations, verify correct accumulated result
 */
void test_y_upper_boundary_max_iterations(void) {
  uint32_t result;
  uint32_t seed = 250U;
  uint16_t iterations = 60535U;
  uint32_t expected;

  expected = seed + (60535U * 60534U);

  result = InternalHelper_u32(seed, iterations);

  TEST_ASSERT_EQUAL_UINT32(expected, result);
}

/**
 * @brief Test: x_u32 = 0 (lower boundary seed) with y_u16 = 0 → return 0
 */
void test_x_zero_y_zero_returns_zero(void) {
  uint32_t result;

  result = InternalHelper_u32(0U, 0U);

  TEST_ASSERT_EQUAL_UINT32(0U, result);
}

/**
 * @brief Test: x_u32 = 0 (lower boundary seed) with y_u16 = 10 → return sum of even sequence 0+2+4+...+18 = 90
 */
void test_x_zero_y_ten_returns_ninety(void) {
  uint32_t result;

  result = InternalHelper_u32(0U, 10U);

  TEST_ASSERT_EQUAL_UINT32(90U, result);
}

/**
 * @brief Test: x_u32 = 1 (one step inside lower boundary seed) with y_u16 = 5 → return 1 + (0+2+4+6+8) = 21
 */
void test_x_one_y_five_returns_twentyone(void) {
  uint32_t result;

  result = InternalHelper_u32(1U, 5U);

  TEST_ASSERT_EQUAL_UINT32(21U, result);
}

/**
 * @brief Test: x_u32 = mid-range seed (e.g., 30000) with y_u16 = 100 → verify correct accumulation from non-zero seed
 */
void test_x_midrange_y_hundred(void) {
  uint32_t result;
  uint32_t seed = 30000U;
  uint16_t iterations = 100U;
  uint32_t expected;

  expected = 30000U + (100U * 99U);

  result = InternalHelper_u32(seed, iterations);

  TEST_ASSERT_EQUAL_UINT32(expected, result);
}

/**
 * @brief Test: x_u32 = 60534 (one step inside upper boundary seed) with y_u16 = 10 → verify correct accumulation from high seed
 */
void test_x_one_below_upper_y_ten(void) {
  uint32_t result;
  uint32_t seed = 60534U;
  uint16_t iterations = 10U;
  uint32_t expected;

  expected = 60534U + 90U;

  result = InternalHelper_u32(seed, iterations);

  TEST_ASSERT_EQUAL_UINT32(expected, result);
}

/**
 * @brief Test: x_u32 = 60535 (upper boundary seed) with y_u16 = 1 → return 60535 + 0 = 60535
 */
void test_x_upper_boundary_y_one(void) {
  uint32_t result;

  result = InternalHelper_u32(60535U, 1U);

  TEST_ASSERT_EQUAL_UINT32(60535U, result);
}

/**
 * @brief Test: x_u32 = 60535 (upper boundary seed) with y_u16 = 60535 (both at upper boundary) → verify 32-bit wrap-around behavior
 */
void test_x_upper_y_upper_wraparound(void) {
  uint32_t result;
  uint32_t seed = 60535U;
  uint16_t iterations = 60535U;
  uint32_t expected;

  expected = seed + (60535U * 60534U);

  result = InternalHelper_u32(seed, iterations);

  TEST_ASSERT_EQUAL_UINT32(expected, result);
}

/**
 * @brief Test: x_u32 = 0xFFFFFFF0 (near uint32_t max) with y_u16 = 10 → verify 32-bit overflow wrap-around
 */
void test_x_near_max_y_ten_overflow(void) {
  uint32_t result;
  uint32_t seed = 0xFFFFFFF0U;
  uint16_t iterations = 10U;
  uint32_t expected;

  expected = seed + 90U;

  result = InternalHelper_u32(seed, iterations);

  TEST_ASSERT_EQUAL_UINT32(expected, result);
}

/**
 * @brief Test: x_u32 = 0xFFFFFFFF (uint32_t max) with y_u16 = 1 → verify wrap-around on first iteration
 */
void test_x_max_y_one_wraparound(void) {
  uint32_t result;
  uint32_t seed = 0xFFFFFFFFU;
  uint16_t iterations = 1U;
  uint32_t expected;

  expected = 0xFFFFFFFFU + 0U;

  result = InternalHelper_u32(seed, iterations);

  TEST_ASSERT_EQUAL_UINT32(expected, result);
}

/**
 * @brief Test: Golden vector - x_u32 = 100, y_u16 = 10 → expected return = 100 + (0+2+4+6+8+10+12+14+16+18) = 100 + 90 = 190
 */
void test_golden_x100_y10_returns_190(void) {
  uint32_t result;

  result = InternalHelper_u32(100U, 10U);

  TEST_ASSERT_EQUAL_UINT32(190U, result);
}

/**
 * @brief Test: Golden vector - x_u32 = 50, y_u16 = 5 → expected return = 50 + (0+2+4+6+8) = 50 + 20 = 70
 */
void test_golden_x50_y5_returns_70(void) {
  uint32_t result;

  result = InternalHelper_u32(50U, 5U);

  TEST_ASSERT_EQUAL_UINT32(70U, result);
}

/**
 * @brief Test: Loop boundary - y_u16 = 2 → two iterations add 0 and 2, verify l_i_u16 increments correctly
 */
void test_y_two_iterations_adds_zero_and_two(void) {
  uint32_t result;
  uint32_t seed = 10U;
  uint16_t iterations = 2U;
  uint32_t expected;

  expected = 10U + 0U + 2U;

  result = InternalHelper_u32(seed, iterations);

  TEST_ASSERT_EQUAL_UINT32(expected, result);
}

/**
 * @brief Test: Loop boundary - y_u16 = 65535 (uint16_t max, outside documented range) → verify behavior with maximum possible loop count and potential overflow
 */
void test_y_uint16_max_overflow_behavior(void) {
  uint32_t result;
  uint32_t seed = 100U;
  uint16_t iterations = 65535U;
  uint32_t expected;

  expected = seed + (65535U * 65534U);

  result = InternalHelper_u32(seed, iterations);

  TEST_ASSERT_EQUAL_UINT32(expected, result);
}