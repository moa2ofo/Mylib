#include "MyLib_AnalyzeArray_u32.h"
#include "mock_MyLib.h"
#include "unity.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>

void setUp(void) {
  /* Initialize global variables to their default state */
  g_counter_u32 = 0U;
  g_record.id_u16 = 0U;
  g_record.value_u32 = 0U;
  g_systemReady_b = false;
}
void tearDown(void) {
  /* No cleanup required */
}
void test_NULL_ptr_len0_factor0_returns_0(void) {
  uint32_t result;

  result = MyLib_AnalyzeArray_u32(NULL, 0U, 0U);

  TEST_ASSERT_EQUAL_UINT32(0U, result);
}
void test_NULL_ptr_len1_factor1_returns_0(void) {
  uint32_t result;

  result = MyLib_AnalyzeArray_u32(NULL, 1U, 1U);

  TEST_ASSERT_EQUAL_UINT32(0U, result);
}
void test_valid_ptr_len0_factor1_returns_0(void) {
  uint16_t array[1] = {100U};
  uint32_t result;

  result = MyLib_AnalyzeArray_u32(array, 0U, 1U);

  TEST_ASSERT_EQUAL_UINT32(0U, result);
  TEST_ASSERT_EQUAL_UINT16(100U, array[0]);
}
void test_len1_factor0_val100_becomes_0_returns_0(void) {
  uint16_t array[1] = {100U};
  uint32_t result;

  MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(0U, NULL, 0U);
  MyLib_ComputeAdjustedValue_u32_IgnoreArg_delta_pc_u16();

  result = MyLib_AnalyzeArray_u32(array, 1U, 0U);

  TEST_ASSERT_EQUAL_UINT16(0U, array[0]);
  TEST_ASSERT_EQUAL_UINT32(0U, result);
}
void test_len1_factor1_val50_remains_50_returns_50(void) {
  uint16_t array[1] = {50U};
  uint32_t result;

  MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(50U, NULL, 0U);
  MyLib_ComputeAdjustedValue_u32_IgnoreArg_delta_pc_u16();

  result = MyLib_AnalyzeArray_u32(array, 1U, 1U);

  TEST_ASSERT_EQUAL_UINT16(50U, array[0]);
  TEST_ASSERT_EQUAL_UINT32(50U, result);
}
void test_len1_factor2_val100_becomes_200_returns_200(void) {
  uint16_t array[1] = {100U};
  uint32_t result;

  MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(200U, NULL, 0U);
  MyLib_ComputeAdjustedValue_u32_IgnoreArg_delta_pc_u16();

  result = MyLib_AnalyzeArray_u32(array, 1U, 2U);

  TEST_ASSERT_EQUAL_UINT16(200U, array[0]);
  TEST_ASSERT_EQUAL_UINT32(200U, result);
}
void test_len1_factor65535_val1_becomes_65535_returns_65535(void) {
  uint16_t array[1] = {1U};
  uint32_t result;

  MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(65535U, NULL, 0U);
  MyLib_ComputeAdjustedValue_u32_IgnoreArg_delta_pc_u16();

  result = MyLib_AnalyzeArray_u32(array, 1U, 65535U);

  TEST_ASSERT_EQUAL_UINT16(65535U, array[0]);
  TEST_ASSERT_EQUAL_UINT32(65535U, result);
}
/**
 * @brief Test: valid pointer with len_u32=2, factor_u16=1, initial values={10, 20} → array becomes {10, 20}, return 30
 */
void test_len2_factor1_vals_10_20_remain_returns_30(void) {
  uint16_t array[2] = {10U, 20U};
  uint32_t result;

  MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(30U, NULL, 0U);
  MyLib_ComputeAdjustedValue_u32_IgnoreArg_delta_pc_u16();

  result = MyLib_AnalyzeArray_u32(array, 2U, 1U);

  TEST_ASSERT_EQUAL_UINT16(10U, array[0]);
  TEST_ASSERT_EQUAL_UINT16(20U, array[1]);
  TEST_ASSERT_EQUAL_UINT32(30U, result);
}
/**
 * @brief Test: valid pointer with len_u32=2, factor_u16=3, initial values={5, 10} → array becomes {15, 30}, return 45
 */
void test_len2_factor3_vals_5_10_become_15_30_returns_45(void) {
  uint16_t array[2] = {5U, 10U};
  uint32_t result;

  MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(45U, NULL, 0U);
  MyLib_ComputeAdjustedValue_u32_IgnoreArg_delta_pc_u16();

  result = MyLib_AnalyzeArray_u32(array, 2U, 3U);

  TEST_ASSERT_EQUAL_UINT16(15U, array[0]);
  TEST_ASSERT_EQUAL_UINT16(30U, array[1]);
  TEST_ASSERT_EQUAL_UINT32(45U, result);
}
void test_len300_factor1_all_1_remain_1_returns_300(void) {
  uint16_t array[300];
  uint32_t result;
  size_t i;

  for(i = 0U; i < 300U; i++) {
    array[i] = 1U;
  }

  MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(300U, NULL, 0U);
  MyLib_ComputeAdjustedValue_u32_IgnoreArg_delta_pc_u16();

  result = MyLib_AnalyzeArray_u32(array, 300U, 1U);

  for(i = 0U; i < 300U; i++) {
    TEST_ASSERT_EQUAL_UINT16(1U, array[i]);
  }
  TEST_ASSERT_EQUAL_UINT32(300U, result);
}
void test_len599_factor1_all_1_remain_1_returns_599(void) {
  uint16_t array[599];
  uint32_t result;
  size_t i;

  for(i = 0U; i < 599U; i++) {
    array[i] = 1U;
  }

  MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(599U, NULL, 0U);
  MyLib_ComputeAdjustedValue_u32_IgnoreArg_delta_pc_u16();

  result = MyLib_AnalyzeArray_u32(array, 599U, 1U);

  for(i = 0U; i < 599U; i++) {
    TEST_ASSERT_EQUAL_UINT16(1U, array[i]);
  }
  TEST_ASSERT_EQUAL_UINT32(599U, result);
}
void test_len600_factor1_all_1_remain_1_returns_600(void) {
  uint16_t array[600];
  uint32_t result;
  size_t i;

  for(i = 0U; i < 600U; i++) {
    array[i] = 1U;
  }

  MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(600U, NULL, 0U);
  MyLib_ComputeAdjustedValue_u32_IgnoreArg_delta_pc_u16();

  result = MyLib_AnalyzeArray_u32(array, 600U, 1U);

  for(i = 0U; i < 600U; i++) {
    TEST_ASSERT_EQUAL_UINT16(1U, array[i]);
  }
  TEST_ASSERT_EQUAL_UINT32(600U, result);
}
/**
 * @brief Test: valid pointer with len_u32=3, factor_u16=2, initial values={100, 200, 300} → array becomes {200, 400, 600}, return 1200
 */
void test_len3_factor2_vals_100_200_300_become_200_400_600_returns_1200(void) {
  uint16_t array[3] = {100U, 200U, 300U};
  uint32_t result;

  MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(1200U, NULL, 0U);
  MyLib_ComputeAdjustedValue_u32_IgnoreArg_delta_pc_u16();

  result = MyLib_AnalyzeArray_u32(array, 3U, 2U);

  TEST_ASSERT_EQUAL_UINT16(200U, array[0]);
  TEST_ASSERT_EQUAL_UINT16(400U, array[1]);
  TEST_ASSERT_EQUAL_UINT16(600U, array[2]);
  TEST_ASSERT_EQUAL_UINT32(1200U, result);
}
/**
 * @brief Test: valid pointer with len_u32=2, factor_u16=2, initial values={32767, 32768} → array becomes {65534, 0} (wrap-around on second element), return 65534
 */
void test_len2_factor2_vals_32767_32768_become_65534_0_returns_65534(void) {
  uint16_t array[2] = {32767U, 32768U};
  uint32_t result;

  MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(65534U, NULL, 0U);
  MyLib_ComputeAdjustedValue_u32_IgnoreArg_delta_pc_u16();

  result = MyLib_AnalyzeArray_u32(array, 2U, 2U);

  TEST_ASSERT_EQUAL_UINT16(65534U, array[0]);
  TEST_ASSERT_EQUAL_UINT16(0U, array[1]);
  TEST_ASSERT_EQUAL_UINT32(65534U, result);
}
/**
 * @brief Test: valid pointer with len_u32=3, factor_u16=10, initial values={6553, 6554, 6555} → array becomes {65530, 65540→4, 65550→14} (wrap-around), verify sum wraps correctly
 */
void test_len3_factor10_vals_6553_6554_6555_wrap_verify_sum(void) {
  uint16_t array[3] = {6553U, 6554U, 6555U};
  uint32_t result;
  uint32_t expected_sum;

  expected_sum = 65530U + 4U + 14U;

  MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(expected_sum, NULL, 0U);
  MyLib_ComputeAdjustedValue_u32_IgnoreArg_delta_pc_u16();

  result = MyLib_AnalyzeArray_u32(array, 3U, 10U);

  TEST_ASSERT_EQUAL_UINT16(65530U, array[0]);
  TEST_ASSERT_EQUAL_UINT16(4U, array[1]);
  TEST_ASSERT_EQUAL_UINT16(14U, array[2]);
  TEST_ASSERT_EQUAL_UINT32(expected_sum, result);
}
/**
 * @brief Test: valid pointer with len_u32=4, factor_u16=65535, initial values={1, 1, 1, 1} → array becomes {65535, 65535, 65535, 65535}, return wraps to 65532 (4*65535 mod 2^32)
 */
void test_len4_factor65535_all_1_become_65535_sum_wraps_to_65532(void) {
  uint16_t array[4] = {1U, 1U, 1U, 1U};
  uint32_t result;
  uint32_t expected_sum;

  expected_sum = (uint32_t)(4U * 65535U);

  MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(expected_sum, NULL, 0U);
  MyLib_ComputeAdjustedValue_u32_IgnoreArg_delta_pc_u16();

  result = MyLib_AnalyzeArray_u32(array, 4U, 65535U);

  TEST_ASSERT_EQUAL_UINT16(65535U, array[0]);
  TEST_ASSERT_EQUAL_UINT16(65535U, array[1]);
  TEST_ASSERT_EQUAL_UINT16(65535U, array[2]);
  TEST_ASSERT_EQUAL_UINT16(65535U, array[3]);
  TEST_ASSERT_EQUAL_UINT32(expected_sum, result);
}
void test_len10_factor1000_all_100_wrap_to_34464_sum_wraps(void) {
  uint16_t array[10];
  uint32_t result;
  uint32_t expected_sum;
  size_t i;

  for(i = 0U; i < 10U; i++) {
    array[i] = 100U;
  }

  expected_sum = 10U * 34464U;

  MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(expected_sum, NULL, 0U);
  MyLib_ComputeAdjustedValue_u32_IgnoreArg_delta_pc_u16();

  result = MyLib_AnalyzeArray_u32(array, 10U, 1000U);

  for(i = 0U; i < 10U; i++) {
    TEST_ASSERT_EQUAL_UINT16(34464U, array[i]);
  }
  TEST_ASSERT_EQUAL_UINT32(expected_sum, result);
}
void test_len1_factor32768_val2_wraps_to_0_returns_0(void) {
  uint16_t array[1] = {2U};
  uint32_t result;

  MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(0U, NULL, 0U);
  MyLib_ComputeAdjustedValue_u32_IgnoreArg_delta_pc_u16();

  result = MyLib_AnalyzeArray_u32(array, 1U, 32768U);

  TEST_ASSERT_EQUAL_UINT16(0U, array[0]);
  TEST_ASSERT_EQUAL_UINT32(0U, result);
}
/**
 * @brief Test: valid pointer with len_u32=5, factor_u16=1, initial values={0, 1, 100, 500, 65535} → array unchanged, return 66136
 */
void test_len5_factor1_vals_0_1_100_500_65535_unchanged_returns_66136(void) {
  uint16_t array[5] = {0U, 1U, 100U, 500U, 65535U};
  uint32_t result;

  MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(66136U, NULL, 0U);
  MyLib_ComputeAdjustedValue_u32_IgnoreArg_delta_pc_u16();

  result = MyLib_AnalyzeArray_u32(array, 5U, 1U);

  TEST_ASSERT_EQUAL_UINT16(0U, array[0]);
  TEST_ASSERT_EQUAL_UINT16(1U, array[1]);
  TEST_ASSERT_EQUAL_UINT16(100U, array[2]);
  TEST_ASSERT_EQUAL_UINT16(500U, array[3]);
  TEST_ASSERT_EQUAL_UINT16(65535U, array[4]);
  TEST_ASSERT_EQUAL_UINT32(66136U, result);
}
/**
 * @brief Test: valid pointer with len_u32=5, factor_u16=2, initial values={0, 1, 100, 500, 32767} → array becomes {0, 2, 200, 1000, 65534}, return 66736
 */
void test_len5_factor2_vals_0_1_100_500_32767_become_0_2_200_1000_65534_returns_66736(void) {
  uint16_t array[5] = {0U, 1U, 100U, 500U, 32767U};
  uint32_t result;

  MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(66736U, NULL, 0U);
  MyLib_ComputeAdjustedValue_u32_IgnoreArg_delta_pc_u16();

  result = MyLib_AnalyzeArray_u32(array, 5U, 2U);

  TEST_ASSERT_EQUAL_UINT16(0U, array[0]);
  TEST_ASSERT_EQUAL_UINT16(2U, array[1]);
  TEST_ASSERT_EQUAL_UINT16(200U, array[2]);
  TEST_ASSERT_EQUAL_UINT16(1000U, array[3]);
  TEST_ASSERT_EQUAL_UINT16(65534U, array[4]);
  TEST_ASSERT_EQUAL_UINT32(66736U, result);
}
