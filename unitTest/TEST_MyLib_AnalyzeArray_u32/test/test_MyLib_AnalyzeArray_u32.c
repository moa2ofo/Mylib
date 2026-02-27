#include "MyLib_AnalyzeArray_u32.h"
#include "mock_MyLib.h"
#include "unity.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>

static uint16_t test_array[100];

void setUp(void) {
  for(size_t i = 0; i < 100; i++) {
    test_array[i] = 0;
  }
}

void tearDown(void) {
}

void test_null_ptr_valid_len_factor(void) {
  uint32_t result = MyLib_AnalyzeArray_u32(NULL, 10, 5);
  TEST_ASSERT_EQUAL_UINT32(0, result);
}

void test_zero_len_valid_ptr_factor(void) {
  test_array[0] = 100;
  uint32_t result = MyLib_AnalyzeArray_u32(test_array, 0, 5);
  TEST_ASSERT_EQUAL_UINT32(0, result);
}

void test_single_elem_factor_one(void) {
  test_array[0] = 42;
  uint32_t result = MyLib_AnalyzeArray_u32(test_array, 1, 1);
  TEST_ASSERT_EQUAL_UINT32(42, result);
}

void test_single_elem_factor_zero(void) {
  test_array[0] = 42;
  uint32_t result = MyLib_AnalyzeArray_u32(test_array, 1, 0);
  TEST_ASSERT_EQUAL_UINT32(0, result);
}

void test_single_elem_factor_max(void) {
  test_array[0] = 1;
  uint32_t result = MyLib_AnalyzeArray_u32(test_array, 1, UINT16_MAX);
  TEST_ASSERT_EQUAL_UINT32(UINT16_MAX, result);
}

void test_two_elem_factor_one(void) {
  test_array[0] = 10;
  test_array[1] = 20;
  uint32_t result = MyLib_AnalyzeArray_u32(test_array, 2, 1);
  TEST_ASSERT_EQUAL_UINT32(30, result);
}

void test_mid_range_len_factor_one(void) {
  for(size_t i = 0; i < 100; i++) {
    test_array[i] = 1;
  }
  uint32_t result = MyLib_AnalyzeArray_u32(test_array, 100, 1);
  TEST_ASSERT_EQUAL_UINT32(100, result);
}

void test_max_len_factor_one(void) {
  test_array[0] = 1;
  uint32_t result = MyLib_AnalyzeArray_u32(test_array, SIZE_MAX, 1);
  TEST_ASSERT_EQUAL_UINT32(1, result);
}

void test_all_zero_elem_factor_one(void) {
  for(size_t i = 0; i < 10; i++) {
    test_array[i] = 0;
  }
  uint32_t result = MyLib_AnalyzeArray_u32(test_array, 10, 1);
  TEST_ASSERT_EQUAL_UINT32(0, result);
}

void test_all_max_elem_factor_one(void) {
  for(size_t i = 0; i < 10; i++) {
    test_array[i] = UINT16_MAX;
  }
  uint32_t result = MyLib_AnalyzeArray_u32(test_array, 10, 1);
  TEST_ASSERT_EQUAL_UINT32(UINT32_MAX, result);
}

void test_mixed_values_factor_one(void) {
  test_array[0] = 0;
  test_array[1] = 32768;
  test_array[2] = UINT16_MAX;
  uint32_t result = MyLib_AnalyzeArray_u32(test_array, 3, 1);
  TEST_ASSERT_EQUAL_UINT32(98303, result);
}

void test_lower_boundary_elem_factor_one(void) {
  test_array[0] = 0;
  test_array[1] = 1;
  uint32_t result = MyLib_AnalyzeArray_u32(test_array, 2, 1);
  TEST_ASSERT_EQUAL_UINT32(1, result);
}

void test_upper_boundary_elem_factor_one(void) {
  test_array[0] = UINT16_MAX - 1;
  test_array[1] = UINT16_MAX;
  uint32_t result = MyLib_AnalyzeArray_u32(test_array, 2, 1);
  TEST_ASSERT_EQUAL_UINT32(131069, result);
}

void test_ten_elem_factor_zero(void) {
  for(size_t i = 0; i < 10; i++) {
    test_array[i] = 100;
  }
  uint32_t result = MyLib_AnalyzeArray_u32(test_array, 10, 0);
  TEST_ASSERT_EQUAL_UINT32(0, result);
}

void test_ten_elem_factor_one(void) {
  for(size_t i = 0; i < 10; i++) {
    test_array[i] = 10;
  }
  uint32_t result = MyLib_AnalyzeArray_u32(test_array, 10, 1);
  TEST_ASSERT_EQUAL_UINT32(100, result);
}

void test_ten_elem_factor_two(void) {
  for(size_t i = 0; i < 10; i++) {
    test_array[i] = 10;
  }
  uint32_t result = MyLib_AnalyzeArray_u32(test_array, 10, 2);
  TEST_ASSERT_EQUAL_UINT32(200, result);
}

void test_ten_elem_factor_max(void) {
  for(size_t i = 0; i < 10; i++) {
    test_array[i] = 1;
  }
  uint32_t result = MyLib_AnalyzeArray_u32(test_array, 10, UINT16_MAX);
  TEST_ASSERT_EQUAL_UINT32(655350, result);
}

void test_ten_elem_factor_near_max(void) {
  for(size_t i = 0; i < 10; i++) {
    test_array[i] = 1;
  }
  uint32_t result = MyLib_AnalyzeArray_u32(test_array, 10, UINT16_MAX - 1);
  TEST_ASSERT_EQUAL_UINT32(655340, result);
}

void test_overflow_handling(void) {
  for(size_t i = 0; i < 10; i++) {
    test_array[i] = UINT16_MAX;
  }
  uint32_t result = MyLib_AnalyzeArray_u32(test_array, 10, UINT16_MAX);
  TEST_ASSERT_EQUAL_UINT32(UINT32_MAX, result);
}

void test_minimal_valid_computation(void) {
  test_array[0] = 1;
  uint32_t result = MyLib_AnalyzeArray_u32(test_array, 1, 1);
  TEST_ASSERT_EQUAL_UINT32(1, result);
}

void test_max_multiplication_boundary(void) {
  test_array[0] = UINT16_MAX;
  uint32_t result = MyLib_AnalyzeArray_u32(test_array, 1, UINT16_MAX);
  TEST_ASSERT_EQUAL_UINT32(UINT32_MAX, result);
}

void test_null_ptr_zero_len_factor_one(void) {
  uint32_t result = MyLib_AnalyzeArray_u32(NULL, 0, 1);
  TEST_ASSERT_EQUAL_UINT32(0, result);
}

void test_null_ptr_zero_len_zero_factor(void) {
  uint32_t result = MyLib_AnalyzeArray_u32(NULL, 0, 0);
  TEST_ASSERT_EQUAL_UINT32(0, result);
}