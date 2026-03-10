#include "mock_MyLib.h"
#include "unity.h"
#include <AnalyzeArray_u32.h>

void setUp(void) {
}
void tearDown(void) {
}
void test_NULL_pointer_returns_zero(void) {
  uint32_t result_u32;

  result_u32 = AnalyzeArray_u32(NULL, 10U, 5U);

  TEST_ASSERT_EQUAL_UINT32(0U, result_u32);
}
void test_zero_length_returns_zero(void) {
  uint16_t values_au16[5] = {1U, 2U, 3U, 4U, 5U};
  uint32_t result_u32;

  result_u32 = AnalyzeArray_u32(values_au16, 0U, 5U);

  TEST_ASSERT_EQUAL_UINT32(0U, result_u32);
}
void test_NULL_pointer_and_zero_length_returns_zero(void) {
  uint32_t result_u32;

  result_u32 = AnalyzeArray_u32(NULL, 0U, 5U);

  TEST_ASSERT_EQUAL_UINT32(0U, result_u32);
}
void test_single_element_factor_one(void) {
  uint16_t values_au16[1] = {42U};
  uint32_t result_u32;
  uint32_t expected_sum_u32 = 42U;

  MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(expected_sum_u32, NULL, expected_sum_u32);
  MyLib_ComputeAdjustedValue_u32_IgnoreArg_delta_pc_u16();

  result_u32 = AnalyzeArray_u32(values_au16, 1U, 1U);

  TEST_ASSERT_EQUAL_UINT16(42U, values_au16[0]);
  TEST_ASSERT_EQUAL_UINT32(expected_sum_u32, result_u32);
}
void test_two_elements_factor_one(void) {
  uint16_t values_au16[2] = {10U, 20U};
  uint32_t result_u32;
  uint32_t expected_sum_u32 = 30U;

  MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(expected_sum_u32, NULL, expected_sum_u32);
  MyLib_ComputeAdjustedValue_u32_IgnoreArg_delta_pc_u16();

  result_u32 = AnalyzeArray_u32(values_au16, 2U, 1U);

  TEST_ASSERT_EQUAL_UINT16(10U, values_au16[0]);
  TEST_ASSERT_EQUAL_UINT16(20U, values_au16[1]);
  TEST_ASSERT_EQUAL_UINT32(expected_sum_u32, result_u32);
}
void test_midrange_300_elements_factor_one(void) {
  uint16_t values_au16[300];
  uint32_t result_u32;
  uint32_t expected_sum_u32 = 0U;
  size_t i_u32;

  for(i_u32 = 0U; i_u32 < 300U; i_u32++) {
    values_au16[i_u32] = 1U;
    expected_sum_u32 += 1U;
  }

  MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(expected_sum_u32, NULL, expected_sum_u32);
  MyLib_ComputeAdjustedValue_u32_IgnoreArg_delta_pc_u16();

  result_u32 = AnalyzeArray_u32(values_au16, 300U, 1U);

  for(i_u32 = 0U; i_u32 < 300U; i_u32++) {
    TEST_ASSERT_EQUAL_UINT16(1U, values_au16[i_u32]);
  }
  TEST_ASSERT_EQUAL_UINT32(expected_sum_u32, result_u32);
}
void test_599_elements_factor_one(void) {
  uint16_t values_au16[599];
  uint32_t result_u32;
  uint32_t expected_sum_u32 = 0U;
  size_t i_u32;

  for(i_u32 = 0U; i_u32 < 599U; i_u32++) {
    values_au16[i_u32] = 2U;
    expected_sum_u32 += 2U;
  }

  MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(expected_sum_u32, NULL, expected_sum_u32);
  MyLib_ComputeAdjustedValue_u32_IgnoreArg_delta_pc_u16();

  result_u32 = AnalyzeArray_u32(values_au16, 599U, 1U);

  for(i_u32 = 0U; i_u32 < 599U; i_u32++) {
    TEST_ASSERT_EQUAL_UINT16(2U, values_au16[i_u32]);
  }
  TEST_ASSERT_EQUAL_UINT32(expected_sum_u32, result_u32);
}
void test_600_elements_factor_one(void) {
  uint16_t values_au16[600];
  uint32_t result_u32;
  uint32_t expected_sum_u32 = 0U;
  size_t i_u32;

  for(i_u32 = 0U; i_u32 < 600U; i_u32++) {
    values_au16[i_u32] = 3U;
    expected_sum_u32 += 3U;
  }

  MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(expected_sum_u32, NULL, expected_sum_u32);
  MyLib_ComputeAdjustedValue_u32_IgnoreArg_delta_pc_u16();

  result_u32 = AnalyzeArray_u32(values_au16, 600U, 1U);

  for(i_u32 = 0U; i_u32 < 600U; i_u32++) {
    TEST_ASSERT_EQUAL_UINT16(3U, values_au16[i_u32]);
  }
  TEST_ASSERT_EQUAL_UINT32(expected_sum_u32, result_u32);
}
void test_factor_zero_all_elements_become_zero(void) {
  uint16_t values_au16[5] = {10U, 20U, 30U, 40U, 50U};
  uint32_t result_u32;
  size_t i_u32;

  MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(0U, NULL, 0U);
  MyLib_ComputeAdjustedValue_u32_IgnoreArg_delta_pc_u16();

  result_u32 = AnalyzeArray_u32(values_au16, 5U, 0U);

  for(i_u32 = 0U; i_u32 < 5U; i_u32++) {
    TEST_ASSERT_EQUAL_UINT16(0U, values_au16[i_u32]);
  }
  TEST_ASSERT_EQUAL_UINT32(0U, result_u32);
}
void test_factor_one_elements_unchanged(void) {
  uint16_t values_au16[5] = {5U, 10U, 15U, 20U, 25U};
  uint32_t result_u32;
  uint32_t expected_sum_u32 = 75U;

  MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(expected_sum_u32, NULL, expected_sum_u32);
  MyLib_ComputeAdjustedValue_u32_IgnoreArg_delta_pc_u16();

  result_u32 = AnalyzeArray_u32(values_au16, 5U, 1U);

  TEST_ASSERT_EQUAL_UINT16(5U, values_au16[0]);
  TEST_ASSERT_EQUAL_UINT16(10U, values_au16[1]);
  TEST_ASSERT_EQUAL_UINT16(15U, values_au16[2]);
  TEST_ASSERT_EQUAL_UINT16(20U, values_au16[3]);
  TEST_ASSERT_EQUAL_UINT16(25U, values_au16[4]);
  TEST_ASSERT_EQUAL_UINT32(expected_sum_u32, result_u32);
}
void test_factor_midrange_32768(void) {
  uint16_t values_au16[3] = {1U, 2U, 3U};
  uint32_t result_u32;
  uint32_t expected_sum_u32;
  uint16_t expected_val0_u16;
  uint16_t expected_val1_u16;
  uint16_t expected_val2_u16;

  expected_val0_u16 = (uint16_t)(1U * 32768U);
  expected_val1_u16 = (uint16_t)(2U * 32768U);
  expected_val2_u16 = (uint16_t)(3U * 32768U);
  expected_sum_u32 = (uint32_t)expected_val0_u16 + (uint32_t)expected_val1_u16 + (uint32_t)expected_val2_u16;

  MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(expected_sum_u32, NULL, expected_sum_u32);
  MyLib_ComputeAdjustedValue_u32_IgnoreArg_delta_pc_u16();

  result_u32 = AnalyzeArray_u32(values_au16, 3U, 32768U);

  TEST_ASSERT_EQUAL_UINT16(expected_val0_u16, values_au16[0]);
  TEST_ASSERT_EQUAL_UINT16(expected_val1_u16, values_au16[1]);
  TEST_ASSERT_EQUAL_UINT16(expected_val2_u16, values_au16[2]);
  TEST_ASSERT_EQUAL_UINT32(expected_sum_u32, result_u32);
}
void test_factor_65534(void) {
  uint16_t values_au16[2] = {2U, 3U};
  uint32_t result_u32;
  uint32_t expected_sum_u32;
  uint16_t expected_val0_u16;
  uint16_t expected_val1_u16;

  expected_val0_u16 = (uint16_t)(2U * 65534U);
  expected_val1_u16 = (uint16_t)(3U * 65534U);
  expected_sum_u32 = (uint32_t)expected_val0_u16 + (uint32_t)expected_val1_u16;

  MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(expected_sum_u32, NULL, expected_sum_u32);
  MyLib_ComputeAdjustedValue_u32_IgnoreArg_delta_pc_u16();

  result_u32 = AnalyzeArray_u32(values_au16, 2U, 65534U);

  TEST_ASSERT_EQUAL_UINT16(expected_val0_u16, values_au16[0]);
  TEST_ASSERT_EQUAL_UINT16(expected_val1_u16, values_au16[1]);
  TEST_ASSERT_EQUAL_UINT32(expected_sum_u32, result_u32);
}
void test_factor_65535_upper_boundary(void) {
  uint16_t values_au16[2] = {1U, 2U};
  uint32_t result_u32;
  uint32_t expected_sum_u32;
  uint16_t expected_val0_u16;
  uint16_t expected_val1_u16;

  expected_val0_u16 = (uint16_t)(1U * 65535U);
  expected_val1_u16 = (uint16_t)(2U * 65535U);
  expected_sum_u32 = (uint32_t)expected_val0_u16 + (uint32_t)expected_val1_u16;

  MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(expected_sum_u32, NULL, expected_sum_u32);
  MyLib_ComputeAdjustedValue_u32_IgnoreArg_delta_pc_u16();

  result_u32 = AnalyzeArray_u32(values_au16, 2U, 65535U);

  TEST_ASSERT_EQUAL_UINT16(expected_val0_u16, values_au16[0]);
  TEST_ASSERT_EQUAL_UINT16(expected_val1_u16, values_au16[1]);
  TEST_ASSERT_EQUAL_UINT32(expected_sum_u32, result_u32);
}
void test_element_overflow_during_scaling(void) {
  uint16_t values_au16[1] = {65535U};
  uint32_t result_u32;
  uint16_t expected_val_u16;
  uint32_t expected_sum_u32;

  expected_val_u16 = (uint16_t)(65535U * 2U);
  expected_sum_u32 = (uint32_t)expected_val_u16;

  MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(expected_sum_u32, NULL, expected_sum_u32);
  MyLib_ComputeAdjustedValue_u32_IgnoreArg_delta_pc_u16();

  result_u32 = AnalyzeArray_u32(values_au16, 1U, 2U);

  TEST_ASSERT_EQUAL_UINT16(expected_val_u16, values_au16[0]);
  TEST_ASSERT_EQUAL_UINT32(expected_sum_u32, result_u32);
}
void test_sum_overflow_during_accumulation(void) {
  uint16_t values_au16[10];
  uint32_t result_u32;
  uint32_t expected_sum_u32 = 0U;
  uint16_t scaled_val_u16;
  size_t i_u32;

  for(i_u32 = 0U; i_u32 < 10U; i_u32++) {
    values_au16[i_u32] = 65535U;
  }

  scaled_val_u16 = (uint16_t)(65535U * 65535U);

  for(i_u32 = 0U; i_u32 < 10U; i_u32++) {
    expected_sum_u32 += (uint32_t)scaled_val_u16;
  }

  MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(expected_sum_u32, NULL, expected_sum_u32);
  MyLib_ComputeAdjustedValue_u32_IgnoreArg_delta_pc_u16();

  result_u32 = AnalyzeArray_u32(values_au16, 10U, 65535U);

  for(i_u32 = 0U; i_u32 < 10U; i_u32++) {
    TEST_ASSERT_EQUAL_UINT16(scaled_val_u16, values_au16[i_u32]);
  }
  TEST_ASSERT_EQUAL_UINT32(expected_sum_u32, result_u32);
}
void test_golden_vector_scaling_and_sum(void) {
  uint16_t values_au16[5] = {1U, 2U, 3U, 4U, 5U};
  uint32_t result_u32;
  uint32_t expected_sum_u32;

  expected_sum_u32 = 10U + 20U + 30U + 40U + 50U;

  MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(expected_sum_u32, NULL, expected_sum_u32);
  MyLib_ComputeAdjustedValue_u32_IgnoreArg_delta_pc_u16();

  result_u32 = AnalyzeArray_u32(values_au16, 5U, 10U);

  TEST_ASSERT_EQUAL_UINT16(10U, values_au16[0]);
  TEST_ASSERT_EQUAL_UINT16(20U, values_au16[1]);
  TEST_ASSERT_EQUAL_UINT16(30U, values_au16[2]);
  TEST_ASSERT_EQUAL_UINT16(40U, values_au16[3]);
  TEST_ASSERT_EQUAL_UINT16(50U, values_au16[4]);
  TEST_ASSERT_EQUAL_UINT32(expected_sum_u32, result_u32);
}
void test_all_zero_elements_remain_zero(void) {
  uint16_t values_au16[3] = {0U, 0U, 0U};
  uint32_t result_u32;

  MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(0U, NULL, 0U);
  MyLib_ComputeAdjustedValue_u32_IgnoreArg_delta_pc_u16();

  result_u32 = AnalyzeArray_u32(values_au16, 3U, 100U);

  TEST_ASSERT_EQUAL_UINT16(0U, values_au16[0]);
  TEST_ASSERT_EQUAL_UINT16(0U, values_au16[1]);
  TEST_ASSERT_EQUAL_UINT16(0U, values_au16[2]);
  TEST_ASSERT_EQUAL_UINT32(0U, result_u32);
}
void test_mixed_zero_and_nonzero_elements(void) {
  uint16_t values_au16[4] = {0U, 10U, 0U, 20U};
  uint32_t result_u32;
  uint32_t expected_sum_u32;

  expected_sum_u32 = 0U + 50U + 0U + 100U;

  MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(expected_sum_u32, NULL, expected_sum_u32);
  MyLib_ComputeAdjustedValue_u32_IgnoreArg_delta_pc_u16();

  result_u32 = AnalyzeArray_u32(values_au16, 4U, 5U);

  TEST_ASSERT_EQUAL_UINT16(0U, values_au16[0]);
  TEST_ASSERT_EQUAL_UINT16(50U, values_au16[1]);
  TEST_ASSERT_EQUAL_UINT16(0U, values_au16[2]);
  TEST_ASSERT_EQUAL_UINT16(100U, values_au16[3]);
  TEST_ASSERT_EQUAL_UINT32(expected_sum_u32, result_u32);
}
