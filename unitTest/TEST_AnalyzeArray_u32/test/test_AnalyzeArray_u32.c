#include "mock_MyLib.h"
#include "unity.h"
#include <AnalyzeArray_u32.h>

void setUp(void) {
}
void tearDown(void) {
}
void test_values_pu16_NULL_returns_0(void) {
  uint32_t result_u32;

  result_u32 = AnalyzeArray_u32(NULL, 10U, 5U);

  TEST_ASSERT_EQUAL_UINT32(0U, result_u32);
}
void test_len_u32_zero_returns_0(void) {
  uint16_t values_au16[5] = {1U, 2U, 3U, 4U, 5U};
  uint32_t result_u32;

  result_u32 = AnalyzeArray_u32(values_au16, 0U, 5U);

  TEST_ASSERT_EQUAL_UINT32(0U, result_u32);
}
void test_values_pu16_NULL_and_len_u32_zero_returns_0(void) {
  uint32_t result_u32;

  result_u32 = AnalyzeArray_u32(NULL, 0U, 5U);

  TEST_ASSERT_EQUAL_UINT32(0U, result_u32);
}
void test_len_u32_1_factor_1_single_element(void) {
  uint16_t values_au16[1] = {10U};
  uint32_t result_u32;
  uint32_t expected_sum_u32 = 10U;

  MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(expected_sum_u32, NULL, expected_sum_u32);

  result_u32 = AnalyzeArray_u32(values_au16, 1U, 1U);

  TEST_ASSERT_EQUAL_UINT16(10U, values_au16[0]);
  TEST_ASSERT_EQUAL_UINT32(expected_sum_u32, result_u32);
}
void test_len_u32_2_factor_1_two_elements(void) {
  uint16_t values_au16[2] = {10U, 20U};
  uint32_t result_u32;
  uint32_t expected_sum_u32 = 30U;

  MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(expected_sum_u32, NULL, expected_sum_u32);

  result_u32 = AnalyzeArray_u32(values_au16, 2U, 1U);

  TEST_ASSERT_EQUAL_UINT16(10U, values_au16[0]);
  TEST_ASSERT_EQUAL_UINT16(20U, values_au16[1]);
  TEST_ASSERT_EQUAL_UINT32(expected_sum_u32, result_u32);
}
void test_len_u32_300_factor_1_mid_range(void) {
  uint16_t values_au16[300];
  uint32_t result_u32;
  uint32_t expected_sum_u32 = 0U;
  size_t i_u32;

  for(i_u32 = 0U; i_u32 < 300U; i_u32++) {
    values_au16[i_u32] = 2U;
    expected_sum_u32 += 2U;
  }

  MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(expected_sum_u32, NULL, expected_sum_u32);

  result_u32 = AnalyzeArray_u32(values_au16, 300U, 1U);

  for(i_u32 = 0U; i_u32 < 300U; i_u32++) {
    TEST_ASSERT_EQUAL_UINT16(2U, values_au16[i_u32]);
  }
  TEST_ASSERT_EQUAL_UINT32(expected_sum_u32, result_u32);
}
void test_len_u32_599_factor_1_just_inside_upper(void) {
  uint16_t values_au16[599];
  uint32_t result_u32;
  uint32_t expected_sum_u32 = 0U;
  size_t i_u32;

  for(i_u32 = 0U; i_u32 < 599U; i_u32++) {
    values_au16[i_u32] = 1U;
    expected_sum_u32 += 1U;
  }

  MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(expected_sum_u32, NULL, expected_sum_u32);

  result_u32 = AnalyzeArray_u32(values_au16, 599U, 1U);

  for(i_u32 = 0U; i_u32 < 599U; i_u32++) {
    TEST_ASSERT_EQUAL_UINT16(1U, values_au16[i_u32]);
  }
  TEST_ASSERT_EQUAL_UINT32(expected_sum_u32, result_u32);
}
void test_len_u32_600_factor_1_upper_boundary(void) {
  uint16_t values_au16[600];
  uint32_t result_u32;
  uint32_t expected_sum_u32 = 0U;
  size_t i_u32;

  for(i_u32 = 0U; i_u32 < 600U; i_u32++) {
    values_au16[i_u32] = 1U;
    expected_sum_u32 += 1U;
  }

  MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(expected_sum_u32, NULL, expected_sum_u32);

  result_u32 = AnalyzeArray_u32(values_au16, 600U, 1U);

  for(i_u32 = 0U; i_u32 < 600U; i_u32++) {
    TEST_ASSERT_EQUAL_UINT16(1U, values_au16[i_u32]);
  }
  TEST_ASSERT_EQUAL_UINT32(expected_sum_u32, result_u32);
}
void test_factor_u16_0_all_elements_zero(void) {
  uint16_t values_au16[5] = {10U, 20U, 30U, 40U, 50U};
  uint32_t result_u32;
  size_t i_u32;

  MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(0U, NULL, 0U);

  result_u32 = AnalyzeArray_u32(values_au16, 5U, 0U);

  for(i_u32 = 0U; i_u32 < 5U; i_u32++) {
    TEST_ASSERT_EQUAL_UINT16(0U, values_au16[i_u32]);
  }
  TEST_ASSERT_EQUAL_UINT32(0U, result_u32);
}
void test_factor_u16_1_elements_unchanged(void) {
  uint16_t values_au16[5] = {10U, 20U, 30U, 40U, 50U};
  uint32_t result_u32;
  uint32_t expected_sum_u32 = 150U;

  MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(expected_sum_u32, NULL, expected_sum_u32);

  result_u32 = AnalyzeArray_u32(values_au16, 5U, 1U);

  TEST_ASSERT_EQUAL_UINT16(10U, values_au16[0]);
  TEST_ASSERT_EQUAL_UINT16(20U, values_au16[1]);
  TEST_ASSERT_EQUAL_UINT16(30U, values_au16[2]);
  TEST_ASSERT_EQUAL_UINT16(40U, values_au16[3]);
  TEST_ASSERT_EQUAL_UINT16(50U, values_au16[4]);
  TEST_ASSERT_EQUAL_UINT32(expected_sum_u32, result_u32);
}
void test_factor_u16_32768_mid_range_scaling(void) {
  uint16_t values_au16[3] = {2U, 3U, 4U};
  uint32_t result_u32;
  uint32_t expected_sum_u32;

  expected_sum_u32 = (uint32_t)((uint16_t)(2U * 32768U)) + (uint32_t)((uint16_t)(3U * 32768U)) + (uint32_t)((uint16_t)(4U * 32768U));

  MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(expected_sum_u32, NULL, expected_sum_u32);

  result_u32 = AnalyzeArray_u32(values_au16, 3U, 32768U);

  TEST_ASSERT_EQUAL_UINT16((uint16_t)(2U * 32768U), values_au16[0]);
  TEST_ASSERT_EQUAL_UINT16((uint16_t)(3U * 32768U), values_au16[1]);
  TEST_ASSERT_EQUAL_UINT16((uint16_t)(4U * 32768U), values_au16[2]);
  TEST_ASSERT_EQUAL_UINT32(expected_sum_u32, result_u32);
}
void test_factor_u16_65534_near_max_scaling(void) {
  uint16_t values_au16[2] = {2U, 3U};
  uint32_t result_u32;
  uint32_t expected_sum_u32;

  expected_sum_u32 = (uint32_t)((uint16_t)(2U * 65534U)) + (uint32_t)((uint16_t)(3U * 65534U));

  MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(expected_sum_u32, NULL, expected_sum_u32);

  result_u32 = AnalyzeArray_u32(values_au16, 2U, 65534U);

  TEST_ASSERT_EQUAL_UINT16((uint16_t)(2U * 65534U), values_au16[0]);
  TEST_ASSERT_EQUAL_UINT16((uint16_t)(3U * 65534U), values_au16[1]);
  TEST_ASSERT_EQUAL_UINT32(expected_sum_u32, result_u32);
}
void test_factor_u16_65535_max_scaling(void) {
  uint16_t values_au16[2] = {2U, 3U};
  uint32_t result_u32;
  uint32_t expected_sum_u32;

  expected_sum_u32 = (uint32_t)((uint16_t)(2U * 65535U)) + (uint32_t)((uint16_t)(3U * 65535U));

  MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(expected_sum_u32, NULL, expected_sum_u32);

  result_u32 = AnalyzeArray_u32(values_au16, 2U, 65535U);

  TEST_ASSERT_EQUAL_UINT16((uint16_t)(2U * 65535U), values_au16[0]);
  TEST_ASSERT_EQUAL_UINT16((uint16_t)(3U * 65535U), values_au16[1]);
  TEST_ASSERT_EQUAL_UINT32(expected_sum_u32, result_u32);
}
void test_uint16_overflow_in_elements(void) {
  uint16_t values_au16[3] = {40000U, 50000U, 60000U};
  uint32_t result_u32;
  uint32_t expected_sum_u32;

  expected_sum_u32 = (uint32_t)((uint16_t)(40000U * 2U)) + (uint32_t)((uint16_t)(50000U * 2U)) + (uint32_t)((uint16_t)(60000U * 2U));

  MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(expected_sum_u32, NULL, expected_sum_u32);

  result_u32 = AnalyzeArray_u32(values_au16, 3U, 2U);

  TEST_ASSERT_EQUAL_UINT16((uint16_t)(40000U * 2U), values_au16[0]);
  TEST_ASSERT_EQUAL_UINT16((uint16_t)(50000U * 2U), values_au16[1]);
  TEST_ASSERT_EQUAL_UINT16((uint16_t)(60000U * 2U), values_au16[2]);
  TEST_ASSERT_EQUAL_UINT32(expected_sum_u32, result_u32);
}
void test_uint32_overflow_in_sum(void) {
  uint16_t values_au16[10];
  uint32_t result_u32;
  uint32_t expected_sum_u32 = 0U;
  size_t i_u32;

  for(i_u32 = 0U; i_u32 < 10U; i_u32++) {
    values_au16[i_u32] = 60000U;
  }

  for(i_u32 = 0U; i_u32 < 10U; i_u32++) {
    expected_sum_u32 += (uint32_t)((uint16_t)(60000U * 1000U));
  }

  MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(expected_sum_u32, NULL, expected_sum_u32);

  result_u32 = AnalyzeArray_u32(values_au16, 10U, 1000U);

  for(i_u32 = 0U; i_u32 < 10U; i_u32++) {
    TEST_ASSERT_EQUAL_UINT16((uint16_t)(60000U * 1000U), values_au16[i_u32]);
  }
  TEST_ASSERT_EQUAL_UINT32(expected_sum_u32, result_u32);
}
void test_in_place_modification_known_values(void) {
  uint16_t values_au16[5] = {1U, 2U, 3U, 4U, 5U};
  uint32_t result_u32;
  uint32_t expected_sum_u32 = 150U;

  MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(expected_sum_u32, NULL, expected_sum_u32);

  result_u32 = AnalyzeArray_u32(values_au16, 5U, 10U);

  TEST_ASSERT_EQUAL_UINT16(10U, values_au16[0]);
  TEST_ASSERT_EQUAL_UINT16(20U, values_au16[1]);
  TEST_ASSERT_EQUAL_UINT16(30U, values_au16[2]);
  TEST_ASSERT_EQUAL_UINT16(40U, values_au16[3]);
  TEST_ASSERT_EQUAL_UINT16(50U, values_au16[4]);
  TEST_ASSERT_EQUAL_UINT32(expected_sum_u32, result_u32);
}
void test_mix_zero_nonzero_values(void) {
  uint16_t values_au16[4] = {0U, 10U, 0U, 20U};
  uint32_t result_u32;
  uint32_t expected_sum_u32 = 150U;

  MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(expected_sum_u32, NULL, expected_sum_u32);

  result_u32 = AnalyzeArray_u32(values_au16, 4U, 5U);

  TEST_ASSERT_EQUAL_UINT16(0U, values_au16[0]);
  TEST_ASSERT_EQUAL_UINT16(50U, values_au16[1]);
  TEST_ASSERT_EQUAL_UINT16(0U, values_au16[2]);
  TEST_ASSERT_EQUAL_UINT16(100U, values_au16[3]);
  TEST_ASSERT_EQUAL_UINT32(expected_sum_u32, result_u32);
}
void test_single_element_max_uint16_factor_1(void) {
  uint16_t values_au16[1] = {65535U};
  uint32_t result_u32;
  uint32_t expected_sum_u32 = 65535U;

  MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(expected_sum_u32, NULL, expected_sum_u32);

  result_u32 = AnalyzeArray_u32(values_au16, 1U, 1U);

  TEST_ASSERT_EQUAL_UINT16(65535U, values_au16[0]);
  TEST_ASSERT_EQUAL_UINT32(expected_sum_u32, result_u32);
}
void test_single_element_max_uint16_factor_2_overflow(void) {
  uint16_t values_au16[1] = {65535U};
  uint32_t result_u32;
  uint32_t expected_sum_u32 = 65534U;

  MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(expected_sum_u32, NULL, expected_sum_u32);

  result_u32 = AnalyzeArray_u32(values_au16, 1U, 2U);

  TEST_ASSERT_EQUAL_UINT16(65534U, values_au16[0]);
  TEST_ASSERT_EQUAL_UINT32(expected_sum_u32, result_u32);
}
