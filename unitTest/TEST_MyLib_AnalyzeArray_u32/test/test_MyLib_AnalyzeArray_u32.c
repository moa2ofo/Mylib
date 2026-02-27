#include "MyLib_AnalyzeArray_u32.h"
#include "mock_MyLib.h"
#include "unity.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>

/* ========================================================================== */
/* CALLBACKS                                                                  */
/* ========================================================================== */

/* No callbacks required for this test suite */

/* ========================================================================== */
/* SETUP AND TEARDOWN                                                         */
/* ========================================================================== */

void setUp(void) {
  /* Initialize test environment before each test */
}

void tearDown(void) {
  /* Clean up after each test */
}

/* ========================================================================== */
/* TEST FUNCTIONS                                                             */
/* ========================================================================== */

void test_NullPtr_Len0_Factor0(void) {
  uint32_t result;

  result = MyLib_AnalyzeArray_u32(NULL, 0, 0);

  TEST_ASSERT_EQUAL_UINT32(0, result);
}

void test_NullPtr_Len1_Factor1(void) {
  uint32_t result;

  result = MyLib_AnalyzeArray_u32(NULL, 1, 1);

  TEST_ASSERT_EQUAL_UINT32(0, result);
}

void test_NullPtr_Len600_Factor100(void) {
  uint32_t result;

  result = MyLib_AnalyzeArray_u32(NULL, 600, 100);

  TEST_ASSERT_EQUAL_UINT32(0, result);
}

void test_ValidPtr_Len0_Factor1(void) {
  uint16_t array[1] = {42};
  uint32_t result;

  result = MyLib_AnalyzeArray_u32(array, 0, 1);

  TEST_ASSERT_EQUAL_UINT32(0, result);
  TEST_ASSERT_EQUAL_UINT16(42, array[0]);
}

void test_ValidPtr_Len0_Factor65535(void) {
  uint16_t array[1] = {100};
  uint32_t result;

  result = MyLib_AnalyzeArray_u32(array, 0, 65535);

  TEST_ASSERT_EQUAL_UINT32(0, result);
  TEST_ASSERT_EQUAL_UINT16(100, array[0]);
}

void test_ValidArray_Len1_Factor0(void) {
  uint16_t array[1] = {123};
  uint32_t result;

  MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(0, NULL, 0);

  result = MyLib_AnalyzeArray_u32(array, 1, 0);

  TEST_ASSERT_EQUAL_UINT32(0, result);
  TEST_ASSERT_EQUAL_UINT16(0, array[0]);
}

void test_ValidArray_Len1_Factor1(void) {
  uint16_t array[1] = {50};
  uint32_t result;

  MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(50, NULL, 0);

  result = MyLib_AnalyzeArray_u32(array, 1, 1);

  TEST_ASSERT_EQUAL_UINT32(50, result);
  TEST_ASSERT_EQUAL_UINT16(50, array[0]);
}

void test_ValidArray_Len1_Factor65535(void) {
  uint16_t array[1] = {2};
  uint32_t result;
  uint32_t expected_scaled = (uint16_t)(2 * 65535);

  MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(expected_scaled, NULL, 0);

  result = MyLib_AnalyzeArray_u32(array, 1, 65535);

  TEST_ASSERT_EQUAL_UINT32(expected_scaled, result);
  TEST_ASSERT_EQUAL_UINT16(expected_scaled, array[0]);
}

void test_ValidArray_Len1_Elem65535_Factor2_Wraparound(void) {
  uint16_t array[1] = {65535};
  uint32_t result;
  uint16_t expected_elem = (uint16_t)(65535 * 2);

  MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(expected_elem, NULL, 0);

  result = MyLib_AnalyzeArray_u32(array, 1, 2);

  TEST_ASSERT_EQUAL_UINT32(expected_elem, result);
  TEST_ASSERT_EQUAL_UINT16(expected_elem, array[0]);
}

void test_ValidArray_Len2_Factor1(void) {
  uint16_t array[2] = {10, 20};
  uint32_t result;

  MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(30, NULL, 0);

  result = MyLib_AnalyzeArray_u32(array, 2, 1);

  TEST_ASSERT_EQUAL_UINT32(30, result);
  TEST_ASSERT_EQUAL_UINT16(10, array[0]);
  TEST_ASSERT_EQUAL_UINT16(20, array[1]);
}

void test_ValidArray_Len2_Factor10(void) {
  uint16_t array[2] = {5, 15};
  uint32_t result;

  MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(200, NULL, 0);

  result = MyLib_AnalyzeArray_u32(array, 2, 10);

  TEST_ASSERT_EQUAL_UINT32(200, result);
  TEST_ASSERT_EQUAL_UINT16(50, array[0]);
  TEST_ASSERT_EQUAL_UINT16(150, array[1]);
}

void test_ValidArray_Len2_ElemOverflow(void) {
  uint16_t array[2] = {40000, 50000};
  uint32_t result;
  uint16_t expected_elem0 = (uint16_t)(40000 * 2);
  uint16_t expected_elem1 = (uint16_t)(50000 * 2);
  uint32_t expected_sum = (uint32_t)expected_elem0 + (uint32_t)expected_elem1;

  MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(expected_sum, NULL, 0);

  result = MyLib_AnalyzeArray_u32(array, 2, 2);

  TEST_ASSERT_EQUAL_UINT32(expected_sum, result);
  TEST_ASSERT_EQUAL_UINT16(expected_elem0, array[0]);
  TEST_ASSERT_EQUAL_UINT16(expected_elem1, array[1]);
}

void test_ValidArray_Len2_SumOverflow(void) {
  uint16_t array[2] = {65535, 65535};
  uint32_t result;
  uint16_t expected_elem = (uint16_t)(65535 * 65535);
  uint32_t expected_sum = (uint32_t)expected_elem + (uint32_t)expected_elem;

  MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(expected_sum, NULL, 0);

  result = MyLib_AnalyzeArray_u32(array, 2, 65535);

  TEST_ASSERT_EQUAL_UINT32(expected_sum, result);
  TEST_ASSERT_EQUAL_UINT16(expected_elem, array[0]);
  TEST_ASSERT_EQUAL_UINT16(expected_elem, array[1]);
}

void test_ValidArray_Len300_Factor1(void) {
  uint16_t array[300];
  uint32_t result;
  uint32_t expected_sum = 0;
  size_t i;

  for(i = 0; i < 300; i++) {
    array[i] = (uint16_t)(i + 1);
    expected_sum += (i + 1);
  }

  MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(expected_sum, NULL, 0);

  result = MyLib_AnalyzeArray_u32(array, 300, 1);

  TEST_ASSERT_EQUAL_UINT32(expected_sum, result);
  for(i = 0; i < 300; i++) {
    TEST_ASSERT_EQUAL_UINT16((uint16_t)(i + 1), array[i]);
  }
}

void test_ValidArray_Len300_Factor100(void) {
  uint16_t array[300];
  uint32_t result;
  uint32_t expected_sum = 0;
  size_t i;

  for(i = 0; i < 300; i++) {
    array[i] = (uint16_t)(i + 1);
  }

  for(i = 0; i < 300; i++) {
    uint16_t scaled = (uint16_t)((i + 1) * 100);
    expected_sum += scaled;
  }

  MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(expected_sum, NULL, 0);

  result = MyLib_AnalyzeArray_u32(array, 300, 100);

  TEST_ASSERT_EQUAL_UINT32(expected_sum, result);
  for(i = 0; i < 300; i++) {
    TEST_ASSERT_EQUAL_UINT16((uint16_t)((i + 1) * 100), array[i]);
  }
}

void test_ValidArray_Len600_Factor1(void) {
  uint16_t array[600];
  uint32_t result;
  uint32_t expected_sum = 0;
  size_t i;

  for(i = 0; i < 600; i++) {
    array[i] = (uint16_t)(i % 100);
    expected_sum += (i % 100);
  }

  MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(expected_sum, NULL, 0);

  result = MyLib_AnalyzeArray_u32(array, 600, 1);

  TEST_ASSERT_EQUAL_UINT32(expected_sum, result);
  for(i = 0; i < 600; i++) {
    TEST_ASSERT_EQUAL_UINT16((uint16_t)(i % 100), array[i]);
  }
}

void test_ValidArray_Len600_Factor10(void) {
  uint16_t array[600];
  uint32_t result;
  uint32_t expected_sum = 0;
  size_t i;

  for(i = 0; i < 600; i++) {
    array[i] = (uint16_t)(i % 100);
  }

  for(i = 0; i < 600; i++) {
    uint16_t scaled = (uint16_t)((i % 100) * 10);
    expected_sum += scaled;
  }

  MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(expected_sum, NULL, 0);

  result = MyLib_AnalyzeArray_u32(array, 600, 10);

  TEST_ASSERT_EQUAL_UINT32(expected_sum, result);
  for(i = 0; i < 600; i++) {
    TEST_ASSERT_EQUAL_UINT16((uint16_t)((i % 100) * 10), array[i]);
  }
}

void test_ValidArray_Len599_Factor2(void) {
  uint16_t array[599];
  uint32_t result;
  uint32_t expected_sum = 0;
  size_t i;

  for(i = 0; i < 599; i++) {
    array[i] = (uint16_t)(i % 50);
  }

  for(i = 0; i < 599; i++) {
    uint16_t scaled = (uint16_t)((i % 50) * 2);
    expected_sum += scaled;
  }

  MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(expected_sum, NULL, 0);

  result = MyLib_AnalyzeArray_u32(array, 599, 2);

  TEST_ASSERT_EQUAL_UINT32(expected_sum, result);
  for(i = 0; i < 599; i++) {
    TEST_ASSERT_EQUAL_UINT16((uint16_t)((i % 50) * 2), array[i]);
  }
}

void test_ValidArray_Len1_LowerBoundary_Factor1(void) {
  uint16_t array[1] = {77};
  uint32_t result;

  MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(77, NULL, 0);

  result = MyLib_AnalyzeArray_u32(array, 1, 1);

  TEST_ASSERT_EQUAL_UINT32(77, result);
  TEST_ASSERT_EQUAL_UINT16(77, array[0]);
}

void test_ValidArray_AllZeros_Len10_Factor100(void) {
  uint16_t array[10] = {0};
  uint32_t result;
  size_t i;

  MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(0, NULL, 0);

  result = MyLib_AnalyzeArray_u32(array, 10, 100);

  TEST_ASSERT_EQUAL_UINT32(0, result);
  for(i = 0; i < 10; i++) {
    TEST_ASSERT_EQUAL_UINT16(0, array[i]);
  }
}

void test_ValidArray_AllMax_Len3_Factor1(void) {
  uint16_t array[3] = {65535, 65535, 65535};
  uint32_t result;
  uint32_t expected_sum = 3 * 65535;

  MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(expected_sum, NULL, 0);

  result = MyLib_AnalyzeArray_u32(array, 3, 1);

  TEST_ASSERT_EQUAL_UINT32(expected_sum, result);
  TEST_ASSERT_EQUAL_UINT16(65535, array[0]);
  TEST_ASSERT_EQUAL_UINT16(65535, array[1]);
  TEST_ASSERT_EQUAL_UINT16(65535, array[2]);
}

void test_ValidArray_MixedValues_Len5_Factor3(void) {
  uint16_t array[5] = {10, 20, 30, 40, 50};
  uint32_t result;
  uint32_t expected_sum = 30 + 60 + 90 + 120 + 150;

  MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(expected_sum, NULL, 0);

  result = MyLib_AnalyzeArray_u32(array, 5, 3);

  TEST_ASSERT_EQUAL_UINT32(expected_sum, result);
  TEST_ASSERT_EQUAL_UINT16(30, array[0]);
  TEST_ASSERT_EQUAL_UINT16(60, array[1]);
  TEST_ASSERT_EQUAL_UINT16(90, array[2]);
  TEST_ASSERT_EQUAL_UINT16(120, array[3]);
  TEST_ASSERT_EQUAL_UINT16(150, array[4]);
}

void test_ValidArray_Len10_Factor0_AllZero(void) {
  uint16_t array[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  uint32_t result;
  size_t i;

  MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(0, NULL, 0);

  result = MyLib_AnalyzeArray_u32(array, 10, 0);

  TEST_ASSERT_EQUAL_UINT32(0, result);
  for(i = 0; i < 10; i++) {
    TEST_ASSERT_EQUAL_UINT16(0, array[i]);
  }
}

void test_ValidArray_SumOverflowDuringAccumulation(void) {
  uint16_t array[100];
  uint32_t result;
  uint32_t expected_sum = 0;
  size_t i;

  for(i = 0; i < 100; i++) {
    array[i] = 65535;
  }

  for(i = 0; i < 100; i++) {
    uint16_t scaled = (uint16_t)(65535 * 100);
    expected_sum += scaled;
  }

  MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(expected_sum, NULL, 0);

  result = MyLib_AnalyzeArray_u32(array, 100, 100);

  TEST_ASSERT_EQUAL_UINT32(expected_sum, result);
}

void test_ComputeAdjustedValueCalled_ValidArray(void) {
  uint16_t array[3] = {100, 200, 300};
  uint32_t result;
  uint32_t expected_sum = 200 + 400 + 600;

  MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(expected_sum, NULL, 0);

  result = MyLib_AnalyzeArray_u32(array, 3, 2);

  TEST_ASSERT_EQUAL_UINT32(expected_sum, result);
}