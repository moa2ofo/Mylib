#include "mock_MyLib.h"
#include "unity.h"
#include <AnalyzeArray_u32.h>

void setUp(void) {
}
void tearDown(void) {
}
void test_values_NULL_returns_zero(void) {
  uint32_t result;

  result = AnalyzeArray_u32(NULL, 5, 10);

  TEST_ASSERT_EQUAL_UINT32(0, result);
}
void test_len_zero_returns_zero(void) {
  uint16_t values[5] = {1, 2, 3, 4, 5};
  uint32_t result;

  result = AnalyzeArray_u32(values, 0, 10);

  TEST_ASSERT_EQUAL_UINT32(0, result);
}
void test_values_NULL_and_len_zero_returns_zero(void) {
  uint32_t result;

  result = AnalyzeArray_u32(NULL, 0, 10);

  TEST_ASSERT_EQUAL_UINT32(0, result);
}
void test_len_1_factor_1_element_10(void) {
  uint16_t values[1] = {10};
  uint32_t result;

  MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(10, NULL, 10);

  result = AnalyzeArray_u32(values, 1, 1);

  TEST_ASSERT_EQUAL_UINT16(10, values[0]);
  TEST_ASSERT_EQUAL_UINT32(10, result);
}
/**
 * @brief Test: len_u32 = 2 (just inside lower boundary), factor_u16 = 2, elements = {5, 10} → elements scaled to {10, 20}, sum returned = 30, MyLib_ComputeAdjustedValue_u32 called with (30, NULL)
 */
void test_len_2_factor_2_elements_5_10(void) {
  uint16_t values[2] = {5, 10};
  uint32_t result;

  MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(30, NULL, 30);

  result = AnalyzeArray_u32(values, 2, 2);

  TEST_ASSERT_EQUAL_UINT16(10, values[0]);
  TEST_ASSERT_EQUAL_UINT16(20, values[1]);
  TEST_ASSERT_EQUAL_UINT32(30, result);
}
void test_len_300_factor_1_all_elements_1(void) {
  uint16_t values[300];
  uint32_t result;
  size_t i;

  for(i = 0; i < 300; i++) {
    values[i] = 1;
  }

  MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(300, NULL, 300);

  result = AnalyzeArray_u32(values, 300, 1);

  for(i = 0; i < 300; i++) {
    TEST_ASSERT_EQUAL_UINT16(1, values[i]);
  }
  TEST_ASSERT_EQUAL_UINT32(300, result);
}
void test_len_599_factor_1_all_elements_1(void) {
  uint16_t values[599];
  uint32_t result;
  size_t i;

  for(i = 0; i < 599; i++) {
    values[i] = 1;
  }

  MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(599, NULL, 599);

  result = AnalyzeArray_u32(values, 599, 1);

  for(i = 0; i < 599; i++) {
    TEST_ASSERT_EQUAL_UINT16(1, values[i]);
  }
  TEST_ASSERT_EQUAL_UINT32(599, result);
}
void test_len_600_factor_1_all_elements_1(void) {
  uint16_t values[600];
  uint32_t result;
  size_t i;

  for(i = 0; i < 600; i++) {
    values[i] = 1;
  }

  MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(600, NULL, 600);

  result = AnalyzeArray_u32(values, 600, 1);

  for(i = 0; i < 600; i++) {
    TEST_ASSERT_EQUAL_UINT16(1, values[i]);
  }
  TEST_ASSERT_EQUAL_UINT32(600, result);
}
/**
 * @brief Test: factor_u16 = 0 (lower boundary), len_u32 = 3, elements = {100, 200, 300} → all elements scaled to 0, sum returned = 0, MyLib_ComputeAdjustedValue_u32 called with (0, NULL)
 */
void test_factor_0_len_3_elements_100_200_300(void) {
  uint16_t values[3] = {100, 200, 300};
  uint32_t result;

  MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(0, NULL, 0);

  result = AnalyzeArray_u32(values, 3, 0);

  TEST_ASSERT_EQUAL_UINT16(0, values[0]);
  TEST_ASSERT_EQUAL_UINT16(0, values[1]);
  TEST_ASSERT_EQUAL_UINT16(0, values[2]);
  TEST_ASSERT_EQUAL_UINT32(0, result);
}
/**
 * @brief Test: factor_u16 = 1 (just inside lower boundary), len_u32 = 3, elements = {10, 20, 30} → elements unchanged {10, 20, 30}, sum returned = 60, MyLib_ComputeAdjustedValue_u32 called with (60, NULL)
 */
void test_factor_1_len_3_elements_10_20_30(void) {
  uint16_t values[3] = {10, 20, 30};
  uint32_t result;

  MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(60, NULL, 60);

  result = AnalyzeArray_u32(values, 3, 1);

  TEST_ASSERT_EQUAL_UINT16(10, values[0]);
  TEST_ASSERT_EQUAL_UINT16(20, values[1]);
  TEST_ASSERT_EQUAL_UINT16(30, values[2]);
  TEST_ASSERT_EQUAL_UINT32(60, result);
}
/**
 * @brief Test: factor_u16 = 32767 (mid-range), len_u32 = 2, elements = {2, 3} → elements scaled to {65534, 98301 mod 65536 = 32765}, sum = 98299, MyLib_ComputeAdjustedValue_u32 called with (98299, NULL)
 */
void test_factor_32767_len_2_elements_2_3(void) {
  uint16_t values[2] = {2, 3};
  uint32_t result;

  MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(98299, NULL, 98299);

  result = AnalyzeArray_u32(values, 2, 32767);

  TEST_ASSERT_EQUAL_UINT16(65534, values[0]);
  TEST_ASSERT_EQUAL_UINT16(32765, values[1]);
  TEST_ASSERT_EQUAL_UINT32(98299, result);
}
/**
 * @brief Test: factor_u16 = 65534 (just inside upper boundary), len_u32 = 2, elements = {1, 1} → elements scaled to {65534, 65534}, sum returned = 131068, MyLib_ComputeAdjustedValue_u32 called with (131068, NULL)
 */
void test_factor_65534_len_2_elements_1_1(void) {
  uint16_t values[2] = {1, 1};
  uint32_t result;

  MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(131068, NULL, 131068);

  result = AnalyzeArray_u32(values, 2, 65534);

  TEST_ASSERT_EQUAL_UINT16(65534, values[0]);
  TEST_ASSERT_EQUAL_UINT16(65534, values[1]);
  TEST_ASSERT_EQUAL_UINT32(131068, result);
}
/**
 * @brief Test: factor_u16 = 65535 (upper boundary), len_u32 = 2, elements = {1, 2} → elements scaled to {65535, 65535*2 mod 65536 = 65534}, sum = 131069, MyLib_ComputeAdjustedValue_u32 called with (131069, NULL)
 */
void test_factor_65535_len_2_elements_1_2(void) {
  uint16_t values[2] = {1, 2};
  uint32_t result;

  MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(131069, NULL, 131069);

  result = AnalyzeArray_u32(values, 2, 65535);

  TEST_ASSERT_EQUAL_UINT16(65535, values[0]);
  TEST_ASSERT_EQUAL_UINT16(65534, values[1]);
  TEST_ASSERT_EQUAL_UINT32(131069, result);
}
void test_uint16_overflow_scaling(void) {
  uint16_t values[1] = {65535};
  uint32_t result;

  MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(65534, NULL, 65534);

  result = AnalyzeArray_u32(values, 1, 2);

  TEST_ASSERT_EQUAL_UINT16(65534, values[0]);
  TEST_ASSERT_EQUAL_UINT32(65534, result);
}
/**
 * @brief Test: uint32_t sum overflow → len_u32 = 2, factor_u16 = 1, elements = {0xFFFFFFFF (65535 repeated to max uint16), 1} such that sum wraps → verify wrap-around behavior in l_sum_u32, MyLib_ComputeAdjustedValue_u32 called with wrapped sum
 */
void test_uint32_sum_overflow(void) {
  uint16_t values[2] = {65535, 65535};
  uint32_t result;
  uint32_t expected_sum;

  expected_sum = (uint32_t)65535 + (uint32_t)65535;

  MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(expected_sum, NULL, expected_sum);

  result = AnalyzeArray_u32(values, 2, 1);

  TEST_ASSERT_EQUAL_UINT16(65535, values[0]);
  TEST_ASSERT_EQUAL_UINT16(65535, values[1]);
  TEST_ASSERT_EQUAL_UINT32(expected_sum, result);
}
/**
 * @brief Test: all array elements are 0 → len_u32 = 5, factor_u16 = 100, elements = {0, 0, 0, 0, 0} → all remain 0, sum returned = 0, MyLib_ComputeAdjustedValue_u32 called with (0, NULL)
 */
void test_all_elements_zero(void) {
  uint16_t values[5] = {0, 0, 0, 0, 0};
  uint32_t result;
  size_t i;

  MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(0, NULL, 0);

  result = AnalyzeArray_u32(values, 5, 100);

  for(i = 0; i < 5; i++) {
    TEST_ASSERT_EQUAL_UINT16(0, values[i]);
  }
  TEST_ASSERT_EQUAL_UINT32(0, result);
}
/**
 * @brief Test: all array elements are maximum uint16_t → len_u32 = 3, factor_u16 = 1, elements = {65535, 65535, 65535} → elements unchanged, sum = 196605, MyLib_ComputeAdjustedValue_u32 called with (196605, NULL)
 */
void test_all_elements_max_uint16(void) {
  uint16_t values[3] = {65535, 65535, 65535};
  uint32_t result;

  MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(196605, NULL, 196605);

  result = AnalyzeArray_u32(values, 3, 1);

  TEST_ASSERT_EQUAL_UINT16(65535, values[0]);
  TEST_ASSERT_EQUAL_UINT16(65535, values[1]);
  TEST_ASSERT_EQUAL_UINT16(65535, values[2]);
  TEST_ASSERT_EQUAL_UINT32(196605, result);
}
/**
 * @brief Test: mixed element values → len_u32 = 4, factor_u16 = 3, elements = {10, 0, 50, 100} → elements scaled to {30, 0, 150, 300}, sum returned = 480, MyLib_ComputeAdjustedValue_u32 called with (480, NULL)
 */
void test_mixed_element_values(void) {
  uint16_t values[4] = {10, 0, 50, 100};
  uint32_t result;

  MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(480, NULL, 480);

  result = AnalyzeArray_u32(values, 4, 3);

  TEST_ASSERT_EQUAL_UINT16(30, values[0]);
  TEST_ASSERT_EQUAL_UINT16(0, values[1]);
  TEST_ASSERT_EQUAL_UINT16(150, values[2]);
  TEST_ASSERT_EQUAL_UINT16(300, values[3]);
  TEST_ASSERT_EQUAL_UINT32(480, result);
}
/**
 * @brief Test: verify in-place modification of array → len_u32 = 3, factor_u16 = 5, elements = {1, 2, 3} → after call, array contains {5, 10, 15}, sum returned = 30, MyLib_ComputeAdjustedValue_u32 called with (30, NULL)
 */
void test_verify_inplace_modification(void) {
  uint16_t values[3] = {1, 2, 3};
  uint32_t result;

  MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(30, NULL, 30);

  result = AnalyzeArray_u32(values, 3, 5);

  TEST_ASSERT_EQUAL_UINT16(5, values[0]);
  TEST_ASSERT_EQUAL_UINT16(10, values[1]);
  TEST_ASSERT_EQUAL_UINT16(15, values[2]);
  TEST_ASSERT_EQUAL_UINT32(30, result);
}
/**
 * @brief Test: MyLib_ComputeAdjustedValue_u32 is called with correct parameters → len_u32 = 2, factor_u16 = 10, elements = {5, 7} → elements scaled to {50, 70}, verify MyLib_ComputeAdjustedValue_u32 invoked exactly once with (120, NULL), sum returned = 120
 */
void test_ComputeAdjustedValue_called_correctly(void) {
  uint16_t values[2] = {5, 7};
  uint32_t result;

  MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(120, NULL, 120);

  result = AnalyzeArray_u32(values, 2, 10);

  TEST_ASSERT_EQUAL_UINT16(50, values[0]);
  TEST_ASSERT_EQUAL_UINT16(70, values[1]);
  TEST_ASSERT_EQUAL_UINT32(120, result);
}
