#include "InternalHelper_u32.h"
#include "unity.h"

void setUp(void) {
  g_counter_u32 = 0U;
  g_record.id_u16 = 0U;
  g_record.value_u32 = 0U;
  g_systemReady_b = false;
}
void tearDown(void) {
}
void test_y_zero_returns_x_unchanged(void) {
  uint32_t result;
  uint32_t x_u32 = 42U;
  uint16_t y_u16 = 0U;

  result = InternalHelper_u32(x_u32, y_u16);

  TEST_ASSERT_EQUAL_UINT32(42U, result);
}
void test_y_one_adds_zero(void) {
  uint32_t result;
  uint32_t x_u32 = 100U;
  uint16_t y_u16 = 1U;

  result = InternalHelper_u32(x_u32, y_u16);

  TEST_ASSERT_EQUAL_UINT32(100U, result);
}
void test_y_ten_accumulates_correctly(void) {
  uint32_t result;
  uint32_t x_u32 = 0U;
  uint16_t y_u16 = 10U;
  uint32_t expected = 0U + (0U * 2U) + (1U * 2U) + (2U * 2U) + (3U * 2U) + (4U * 2U) + (5U * 2U) + (6U * 2U) + (7U * 2U) + (8U * 2U) + (9U * 2U);

  result = InternalHelper_u32(x_u32, y_u16);

  TEST_ASSERT_EQUAL_UINT32(expected, result);
}
void test_y_60534_large_iteration(void) {
  uint32_t result;
  uint32_t x_u32 = 0U;
  uint16_t y_u16 = 60534U;
  uint32_t expected = 0U;
  uint32_t l_i_u16;

  for(l_i_u16 = 0U; l_i_u16 < y_u16; l_i_u16++) {
    expected += (l_i_u16 * 2U);
  }

  result = InternalHelper_u32(x_u32, y_u16);

  TEST_ASSERT_EQUAL_UINT32(expected, result);
}
void test_y_60535_upper_boundary(void) {
  uint32_t result;
  uint32_t x_u32 = 0U;
  uint16_t y_u16 = 60535U;
  uint32_t expected = 0U;
  uint32_t l_i_u16;

  for(l_i_u16 = 0U; l_i_u16 < y_u16; l_i_u16++) {
    expected += (l_i_u16 * 2U);
  }

  result = InternalHelper_u32(x_u32, y_u16);

  TEST_ASSERT_EQUAL_UINT32(expected, result);
}
void test_x_zero_y_five(void) {
  uint32_t result;
  uint32_t x_u32 = 0U;
  uint16_t y_u16 = 5U;
  uint32_t expected = 0U + (0U * 2U) + (1U * 2U) + (2U * 2U) + (3U * 2U) + (4U * 2U);

  result = InternalHelper_u32(x_u32, y_u16);

  TEST_ASSERT_EQUAL_UINT32(expected, result);
}
void test_x_one_y_five(void) {
  uint32_t result;
  uint32_t x_u32 = 1U;
  uint16_t y_u16 = 5U;
  uint32_t expected = 1U + (0U * 2U) + (1U * 2U) + (2U * 2U) + (3U * 2U) + (4U * 2U);

  result = InternalHelper_u32(x_u32, y_u16);

  TEST_ASSERT_EQUAL_UINT32(expected, result);
}
void test_x_30000_y_ten(void) {
  uint32_t result;
  uint32_t x_u32 = 30000U;
  uint16_t y_u16 = 10U;
  uint32_t expected = 30000U + (0U * 2U) + (1U * 2U) + (2U * 2U) + (3U * 2U) + (4U * 2U) + (5U * 2U) + (6U * 2U) + (7U * 2U) + (8U * 2U) + (9U * 2U);

  result = InternalHelper_u32(x_u32, y_u16);

  TEST_ASSERT_EQUAL_UINT32(expected, result);
}
void test_x_60534_y_five(void) {
  uint32_t result;
  uint32_t x_u32 = 60534U;
  uint16_t y_u16 = 5U;
  uint32_t expected = 60534U + (0U * 2U) + (1U * 2U) + (2U * 2U) + (3U * 2U) + (4U * 2U);

  result = InternalHelper_u32(x_u32, y_u16);

  TEST_ASSERT_EQUAL_UINT32(expected, result);
}
void test_x_60535_y_five(void) {
  uint32_t result;
  uint32_t x_u32 = 60535U;
  uint16_t y_u16 = 5U;
  uint32_t expected = 60535U + (0U * 2U) + (1U * 2U) + (2U * 2U) + (3U * 2U) + (4U * 2U);

  result = InternalHelper_u32(x_u32, y_u16);

  TEST_ASSERT_EQUAL_UINT32(expected, result);
}
void test_x_max_uint32_y_one_wraparound(void) {
  uint32_t result;
  uint32_t x_u32 = 0xFFFFFFFFU;
  uint16_t y_u16 = 1U;
  uint32_t expected = 0xFFFFFFFFU + (0U * 2U);

  result = InternalHelper_u32(x_u32, y_u16);

  TEST_ASSERT_EQUAL_UINT32(expected, result);
}
void test_x_near_max_y_ten_wraparound(void) {
  uint32_t result;
  uint32_t x_u32 = 0xFFFFFFF0U;
  uint16_t y_u16 = 10U;
  uint32_t expected = 0xFFFFFFF0U;
  uint16_t l_i_u16;

  for(l_i_u16 = 0U; l_i_u16 < y_u16; l_i_u16++) {
    expected += (l_i_u16 * 2U);
  }

  result = InternalHelper_u32(x_u32, y_u16);

  TEST_ASSERT_EQUAL_UINT32(expected, result);
}
void test_golden_x_100_y_3(void) {
  uint32_t result;
  uint32_t x_u32 = 100U;
  uint16_t y_u16 = 3U;
  uint32_t expected = 106U;

  result = InternalHelper_u32(x_u32, y_u16);

  TEST_ASSERT_EQUAL_UINT32(expected, result);
}
void test_golden_x_50_y_4(void) {
  uint32_t result;
  uint32_t x_u32 = 50U;
  uint16_t y_u16 = 4U;
  uint32_t expected = 62U;

  result = InternalHelper_u32(x_u32, y_u16);

  TEST_ASSERT_EQUAL_UINT32(expected, result);
}
void test_x_zero_y_zero(void) {
  uint32_t result;
  uint32_t x_u32 = 0U;
  uint16_t y_u16 = 0U;

  result = InternalHelper_u32(x_u32, y_u16);

  TEST_ASSERT_EQUAL_UINT32(0U, result);
}
void test_x_60535_y_60535_max_boundary(void) {
  uint32_t result;
  uint32_t x_u32 = 60535U;
  uint16_t y_u16 = 60535U;
  uint32_t expected = 60535U;
  uint32_t l_i_u16;

  for(l_i_u16 = 0U; l_i_u16 < y_u16; l_i_u16++) {
    expected += (l_i_u16 * 2U);
  }

  result = InternalHelper_u32(x_u32, y_u16);

  TEST_ASSERT_EQUAL_UINT32(expected, result);
}
