#include "MyLib_AnalyzeArray_u32.h"
#include "mock_MyLib.h"
#include "unity.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>

void setUp(void) {
}
void tearDown(void) {
}
void test_NULL_ptr_len0_factor0_returns_0(void) {
  uint32_t result;

  result = MyLib_AnalyzeArray_u32(NULL, 0, 0);

  TEST_ASSERT_EQUAL_UINT32(0, result);
}
void test_NULL_ptr_len1_factor1_returns_0(void) {
  uint32_t result;

  result = MyLib_AnalyzeArray_u32(NULL, 1, 1);

  TEST_ASSERT_EQUAL_UINT32(0, result);
}
void test_valid_ptr_len0_factor1_returns_0(void) {
  uint16_t array[1] = {10};
  uint32_t result;

  result = MyLib_AnalyzeArray_u32(array, 0, 1);

  TEST_ASSERT_EQUAL_UINT32(0, result);
  TEST_ASSERT_EQUAL_UINT16(10, array[0]);
}
/**
 * @brief Test: Valid pointer with len_u32 = 1, factor_u16 = 0, array = {10} → array becomes {0}, return 0
 */
void test_len1_factor0_array10_becomes_0_returns_0(void) {
  uint16_t array[1] = {10};
  uint32_t result;

  MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(0, NULL, 0);

  result = MyLib_AnalyzeArray_u32(array, 1, 0);

  TEST_ASSERT_EQUAL_UINT32(0, result);
  TEST_ASSERT_EQUAL_UINT16(0, array[0]);
}
/**
 * @brief Test: Valid pointer with len_u32 = 1, factor_u16 = 1, array = {0} → array remains {0}, return 0
 */
void test_len1_factor1_array0_remains_0_returns_0(void) {
  uint16_t array[1] = {0};
  uint32_t result;

  MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(0, NULL, 0);

  result = MyLib_AnalyzeArray_u32(array, 1, 1);

  TEST_ASSERT_EQUAL_UINT32(0, result);
  TEST_ASSERT_EQUAL_UINT16(0, array[0]);
}
/**
 * @brief Test: Valid pointer with len_u32 = 1, factor_u16 = 1, array = {1} → array remains {1}, return 1
 */
void test_len1_factor1_array1_remains_1_returns_1(void) {
  uint16_t array[1] = {1};
  uint32_t result;

  MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(1, NULL, 0);

  result = MyLib_AnalyzeArray_u32(array, 1, 1);

  TEST_ASSERT_EQUAL_UINT32(1, result);
  TEST_ASSERT_EQUAL_UINT16(1, array[0]);
}
/**
 * @brief Test: Valid pointer with len_u32 = 1, factor_u16 = 1, array = {100} → array remains {100}, return 100
 */
void test_len1_factor1_array100_remains_100_returns_100(void) {
  uint16_t array[1] = {100};
  uint32_t result;

  MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(100, NULL, 0);

  result = MyLib_AnalyzeArray_u32(array, 1, 1);

  TEST_ASSERT_EQUAL_UINT32(100, result);
  TEST_ASSERT_EQUAL_UINT16(100, array[0]);
}
/**
 * @brief Test: Valid pointer with len_u32 = 1, factor_u16 = 1, array = {599} → array remains {599}, return 599
 */
void test_len1_factor1_array599_remains_599_returns_599(void) {
  uint16_t array[1] = {599};
  uint32_t result;

  MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(599, NULL, 0);

  result = MyLib_AnalyzeArray_u32(array, 1, 1);

  TEST_ASSERT_EQUAL_UINT32(599, result);
  TEST_ASSERT_EQUAL_UINT16(599, array[0]);
}
/**
 * @brief Test: Valid pointer with len_u32 = 1, factor_u16 = 1, array = {600} → array remains {600}, return 600
 */
void test_len1_factor1_array600_remains_600_returns_600(void) {
  uint16_t array[1] = {600};
  uint32_t result;

  MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(600, NULL, 0);

  result = MyLib_AnalyzeArray_u32(array, 1, 1);

  TEST_ASSERT_EQUAL_UINT32(600, result);
  TEST_ASSERT_EQUAL_UINT16(600, array[0]);
}
/**
 * @brief Test: Valid pointer with len_u32 = 2, factor_u16 = 1, array = {100, 200} → array remains {100, 200}, return 300
 */
void test_len2_factor1_array100_200_remains_returns_300(void) {
  uint16_t array[2] = {100, 200};
  uint32_t result;

  MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(300, NULL, 0);

  result = MyLib_AnalyzeArray_u32(array, 2, 1);

  TEST_ASSERT_EQUAL_UINT32(300, result);
  TEST_ASSERT_EQUAL_UINT16(100, array[0]);
  TEST_ASSERT_EQUAL_UINT16(200, array[1]);
}
void test_len300_factor1_array_all1s_unchanged_returns_300(void) {
  uint16_t array[300];
  uint32_t result;
  size_t i;

  for(i = 0; i < 300; i++) {
    array[i] = 1;
  }

  MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(300, NULL, 0);

  result = MyLib_AnalyzeArray_u32(array, 300, 1);

  TEST_ASSERT_EQUAL_UINT32(300, result);
  for(i = 0; i < 300; i++) {
    TEST_ASSERT_EQUAL_UINT16(1, array[i]);
  }
}
void test_len599_factor1_array_all1s_unchanged_returns_599(void) {
  uint16_t array[599];
  uint32_t result;
  size_t i;

  for(i = 0; i < 599; i++) {
    array[i] = 1;
  }

  MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(599, NULL, 0);

  result = MyLib_AnalyzeArray_u32(array, 599, 1);

  TEST_ASSERT_EQUAL_UINT32(599, result);
  for(i = 0; i < 599; i++) {
    TEST_ASSERT_EQUAL_UINT16(1, array[i]);
  }
}
void test_len600_factor1_array_all1s_unchanged_returns_600(void) {
  uint16_t array[600];
  uint32_t result;
  size_t i;

  for(i = 0; i < 600; i++) {
    array[i] = 1;
  }

  MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(600, NULL, 0);

  result = MyLib_AnalyzeArray_u32(array, 600, 1);

  TEST_ASSERT_EQUAL_UINT32(600, result);
  for(i = 0; i < 600; i++) {
    TEST_ASSERT_EQUAL_UINT16(1, array[i]);
  }
}
/**
 * @brief Test: Valid pointer with len_u32 = 1, factor_u16 = 2, array = {10} → array becomes {20}, return 20
 */
void test_len1_factor2_array10_becomes_20_returns_20(void) {
  uint16_t array[1] = {10};
  uint32_t result;

  MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(20, NULL, 0);

  result = MyLib_AnalyzeArray_u32(array, 1, 2);

  TEST_ASSERT_EQUAL_UINT32(20, result);
  TEST_ASSERT_EQUAL_UINT16(20, array[0]);
}
/**
 * @brief Test: Valid pointer with len_u32 = 1, factor_u16 = 100, array = {5} → array becomes {500}, return 500
 */
void test_len1_factor100_array5_becomes_500_returns_500(void) {
  uint16_t array[1] = {5};
  uint32_t result;

  MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(500, NULL, 0);

  result = MyLib_AnalyzeArray_u32(array, 1, 100);

  TEST_ASSERT_EQUAL_UINT32(500, result);
  TEST_ASSERT_EQUAL_UINT16(500, array[0]);
}
/**
 * @brief Test: Valid pointer with len_u32 = 1, factor_u16 = 65534, array = {1} → array becomes {65534}, return 65534
 */
void test_len1_factor65534_array1_becomes_65534_returns_65534(void) {
  uint16_t array[1] = {1};
  uint32_t result;

  MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(65534, NULL, 0);

  result = MyLib_AnalyzeArray_u32(array, 1, 65534);

  TEST_ASSERT_EQUAL_UINT32(65534, result);
  TEST_ASSERT_EQUAL_UINT16(65534, array[0]);
}
/**
 * @brief Test: Valid pointer with len_u32 = 1, factor_u16 = 65535, array = {1} → array becomes {65535}, return 65535
 */
void test_len1_factor65535_array1_becomes_65535_returns_65535(void) {
  uint16_t array[1] = {1};
  uint32_t result;

  MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(65535, NULL, 0);

  result = MyLib_AnalyzeArray_u32(array, 1, 65535);

  TEST_ASSERT_EQUAL_UINT32(65535, result);
  TEST_ASSERT_EQUAL_UINT16(65535, array[0]);
}
/**
 * @brief Test: Valid pointer with len_u32 = 2, factor_u16 = 2, array = {10, 20} → array becomes {20, 40}, return 60
 */
void test_len2_factor2_array10_20_becomes_20_40_returns_60(void) {
  uint16_t array[2] = {10, 20};
  uint32_t result;

  MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(60, NULL, 0);

  result = MyLib_AnalyzeArray_u32(array, 2, 2);

  TEST_ASSERT_EQUAL_UINT32(60, result);
  TEST_ASSERT_EQUAL_UINT16(20, array[0]);
  TEST_ASSERT_EQUAL_UINT16(40, array[1]);
}
/**
 * @brief Test: Valid pointer with len_u32 = 3, factor_u16 = 3, array = {1, 2, 3} → array becomes {3, 6, 9}, return 18
 */
void test_len3_factor3_array1_2_3_becomes_3_6_9_returns_18(void) {
  uint16_t array[3] = {1, 2, 3};
  uint32_t result;

  MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(18, NULL, 0);

  result = MyLib_AnalyzeArray_u32(array, 3, 3);

  TEST_ASSERT_EQUAL_UINT32(18, result);
  TEST_ASSERT_EQUAL_UINT16(3, array[0]);
  TEST_ASSERT_EQUAL_UINT16(6, array[1]);
  TEST_ASSERT_EQUAL_UINT16(9, array[2]);
}
/**
 * @brief Test: Valid pointer with len_u32 = 1, factor_u16 = 2, array = {65535} → array becomes {65534} (wrap-around), return 65534
 */
void test_len1_factor2_array65535_wraps_to_65534_returns_65534(void) {
  uint16_t array[1] = {65535};
  uint32_t result;

  MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(65534, NULL, 0);

  result = MyLib_AnalyzeArray_u32(array, 1, 2);

  TEST_ASSERT_EQUAL_UINT32(65534, result);
  TEST_ASSERT_EQUAL_UINT16(65534, array[0]);
}
/**
 * @brief Test: Valid pointer with len_u32 = 2, factor_u16 = 65535, array = {2, 3} → array becomes {65534, 65533} (wrap-around), sum wraps to 65531
 */
void test_len2_factor65535_array2_3_wraps_sum_to_65531(void) {
  uint16_t array[2] = {2, 3};
  uint32_t result;

  MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(65531, NULL, 0);

  result = MyLib_AnalyzeArray_u32(array, 2, 65535);

  TEST_ASSERT_EQUAL_UINT32(65531, result);
  TEST_ASSERT_EQUAL_UINT16(65534, array[0]);
  TEST_ASSERT_EQUAL_UINT16(65533, array[1]);
}
void test_len10_factor10_array_all6553s_sum_wraps_around(void) {
  uint16_t array[10];
  uint32_t result;
  uint32_t expected_sum;
  size_t i;

  for(i = 0; i < 10; i++) {
    array[i] = 6553;
  }

  expected_sum = 0;
  for(i = 0; i < 10; i++) {
    expected_sum += (uint32_t)((uint16_t)(6553 * 10));
  }

  MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(expected_sum, NULL, 0);

  result = MyLib_AnalyzeArray_u32(array, 10, 10);

  TEST_ASSERT_EQUAL_UINT32(expected_sum, result);
  for(i = 0; i < 10; i++) {
    TEST_ASSERT_EQUAL_UINT16((uint16_t)(6553 * 10), array[i]);
  }
}
