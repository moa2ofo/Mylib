#include "MyLib_AnalyzeArray_u32.h"
#include "mock_MyLib.h"
#include "unity.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>

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
 * @brief Test: NULL pointer with len_u32 = 0 and factor_u16 = 0 → return 0, no processing
 */
void test_NullPointer_ZeroLen_ZeroFactor(void) {
  uint32_t result;

  result = MyLib_AnalyzeArray_u32(NULL, 0U, 0U);

  TEST_ASSERT_EQUAL_UINT32(0U, result);
}

/**
 * @brief Test: NULL pointer with len_u32 = 1 and factor_u16 = 1 → return 0, no processing
 */
void test_NullPointer_NonZeroLen_NonZeroFactor(void) {
  uint32_t result;

  result = MyLib_AnalyzeArray_u32(NULL, 1U, 1U);

  TEST_ASSERT_EQUAL_UINT32(0U, result);
}

/**
 * @brief Test: Valid pointer with len_u32 = 0 and factor_u16 = 1 → return 0, array unchanged
 */
void test_ValidPointer_ZeroLen(void) {
  uint16_t array[1] = {100U};
  uint32_t result;

  result = MyLib_AnalyzeArray_u32(array, 0U, 1U);

  TEST_ASSERT_EQUAL_UINT32(0U, result);
  TEST_ASSERT_EQUAL_UINT16(100U, array[0]);
}

/**
 * @brief Test: Valid pointer with len_u32 = 1, factor_u16 = 0, initial value = 100 → array[0] = 0, return 0
 */
void test_SingleElement_ZeroFactor(void) {
  uint16_t array[1] = {100U};
  uint32_t result;

  MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(0U, NULL, 0U);

  result = MyLib_AnalyzeArray_u32(array, 1U, 0U);

  TEST_ASSERT_EQUAL_UINT32(0U, result);
  TEST_ASSERT_EQUAL_UINT16(0U, array[0]);
}

/**
 * @brief Test: Valid pointer with len_u32 = 1, factor_u16 = 1, initial value = 50 → array[0] = 50, return 50
 */
void test_SingleElement_FactorOne_Value50(void) {
  uint16_t array[1] = {50U};
  uint32_t result;

  MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(50U, NULL, 0U);

  result = MyLib_AnalyzeArray_u32(array, 1U, 1U);

  TEST_ASSERT_EQUAL_UINT32(50U, result);
  TEST_ASSERT_EQUAL_UINT16(50U, array[0]);
}

/**
 * @brief Test: Valid pointer with len_u32 = 1, factor_u16 = 2, initial value = 100 → array[0] = 200, return 200
 */
void test_SingleElement_FactorTwo_Value100(void) {
  uint16_t array[1] = {100U};
  uint32_t result;

  MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(200U, NULL, 0U);

  result = MyLib_AnalyzeArray_u32(array, 1U, 2U);

  TEST_ASSERT_EQUAL_UINT32(200U, result);
  TEST_ASSERT_EQUAL_UINT16(200U, array[0]);
}

/**
 * @brief Test: Valid pointer with len_u32 = 1, factor_u16 = 65535, initial value = 1 → array[0] = 65535, return 65535
 */
void test_SingleElement_MaxFactor_Value1(void) {
  uint16_t array[1] = {1U};
  uint32_t result;

  MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(65535U, NULL, 0U);

  result = MyLib_AnalyzeArray_u32(array, 1U, 65535U);

  TEST_ASSERT_EQUAL_UINT32(65535U, result);
  TEST_ASSERT_EQUAL_UINT16(65535U, array[0]);
}

/**
 * @brief Test: Valid pointer with len_u32 = 2, factor_u16 = 1, initial values = {10, 20} → array = {10, 20}, return 30
 */
void test_TwoElements_FactorOne(void) {
  uint16_t array[2] = {10U, 20U};
  uint32_t result;

  MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(30U, NULL, 0U);

  result = MyLib_AnalyzeArray_u32(array, 2U, 1U);

  TEST_ASSERT_EQUAL_UINT32(30U, result);
  TEST_ASSERT_EQUAL_UINT16(10U, array[0]);
  TEST_ASSERT_EQUAL_UINT16(20U, array[1]);
}

/**
 * @brief Test: Valid pointer with len_u32 = 2, factor_u16 = 3, initial values = {5, 10} → array = {15, 30}, return 45
 */
void test_TwoElements_FactorThree(void) {
  uint16_t array[2] = {5U, 10U};
  uint32_t result;

  MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(45U, NULL, 0U);

  result = MyLib_AnalyzeArray_u32(array, 2U, 3U);

  TEST_ASSERT_EQUAL_UINT32(45U, result);
  TEST_ASSERT_EQUAL_UINT16(15U, array[0]);
  TEST_ASSERT_EQUAL_UINT16(30U, array[1]);
}

/**
 * @brief Test: Valid pointer with len_u32 = 599, factor_u16 = 1, all elements = 1 → all elements remain 1, return 599
 */
void test_599Elements_FactorOne_AllOnes(void) {
  uint16_t array[599];
  uint32_t result;
  size_t i;

  for(i = 0U; i < 599U; i++) {
    array[i] = 1U;
  }

  MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(599U, NULL, 0U);

  result = MyLib_AnalyzeArray_u32(array, 599U, 1U);

  TEST_ASSERT_EQUAL_UINT32(599U, result);
  for(i = 0U; i < 599U; i++) {
    TEST_ASSERT_EQUAL_UINT16(1U, array[i]);
  }
}

/**
 * @brief Test: Valid pointer with len_u32 = 600 (upper boundary), factor_u16 = 1, all elements = 1 → all elements remain 1, return 600
 */
void test_600Elements_FactorOne_AllOnes(void) {
  uint16_t array[600];
  uint32_t result;
  size_t i;

  for(i = 0U; i < 600U; i++) {
    array[i] = 1U;
  }

  MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(600U, NULL, 0U);

  result = MyLib_AnalyzeArray_u32(array, 600U, 1U);

  TEST_ASSERT_EQUAL_UINT32(600U, result);
  for(i = 0U; i < 600U; i++) {
    TEST_ASSERT_EQUAL_UINT16(1U, array[i]);
  }
}

/**
 * @brief Test: Valid pointer with len_u32 = 3, factor_u16 = 2, initial values = {100, 200, 300} → array = {200, 400, 600}, return 1200
 */
void test_ThreeElements_FactorTwo(void) {
  uint16_t array[3] = {100U, 200U, 300U};
  uint32_t result;

  MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(1200U, NULL, 0U);

  result = MyLib_AnalyzeArray_u32(array, 3U, 2U);

  TEST_ASSERT_EQUAL_UINT32(1200U, result);
  TEST_ASSERT_EQUAL_UINT16(200U, array[0]);
  TEST_ASSERT_EQUAL_UINT16(400U, array[1]);
  TEST_ASSERT_EQUAL_UINT16(600U, array[2]);
}

/**
 * @brief Test: Valid pointer with len_u32 = 2, factor_u16 = 65535, initial values = {1, 1} → array = {65535, 65535}, return 131070
 */
void test_TwoElements_MaxFactor_AllOnes(void) {
  uint16_t array[2] = {1U, 1U};
  uint32_t result;

  MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(131070U, NULL, 0U);

  result = MyLib_AnalyzeArray_u32(array, 2U, 65535U);

  TEST_ASSERT_EQUAL_UINT32(131070U, result);
  TEST_ASSERT_EQUAL_UINT16(65535U, array[0]);
  TEST_ASSERT_EQUAL_UINT16(65535U, array[1]);
}

/**
 * @brief Test: Valid pointer with len_u32 = 3, factor_u16 = 10000, initial values = {5, 6, 7} → verify wrap-around behavior on uint16_t multiplication and uint32_t sum
 */
void test_ThreeElements_LargeFactor_WrapAround(void) {
  uint16_t array[3] = {5U, 6U, 7U};
  uint32_t result;
  uint16_t expected_0 = (uint16_t)(5U * 10000U);
  uint16_t expected_1 = (uint16_t)(6U * 10000U);
  uint16_t expected_2 = (uint16_t)(7U * 10000U);
  uint32_t expected_sum = (uint32_t)expected_0 + (uint32_t)expected_1 + (uint32_t)expected_2;

  MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(expected_sum, NULL, 0U);

  result = MyLib_AnalyzeArray_u32(array, 3U, 10000U);

  TEST_ASSERT_EQUAL_UINT32(expected_sum, result);
  TEST_ASSERT_EQUAL_UINT16(expected_0, array[0]);
  TEST_ASSERT_EQUAL_UINT16(expected_1, array[1]);
  TEST_ASSERT_EQUAL_UINT16(expected_2, array[2]);
}

/**
 * @brief Test: Valid pointer with len_u32 = 10, factor_u16 = 100, initial values = {100, 200, 300, 400, 500, 600, 700, 800, 900, 1000} → verify correct in-place scaling and sum computation
 */
void test_TenElements_Factor100(void) {
  uint16_t array[10] = {100U, 200U, 300U, 400U, 500U, 600U, 700U, 800U, 900U, 1000U};
  uint32_t result;
  uint16_t expected[10];
  uint32_t expected_sum = 0U;
  size_t i;

  for(i = 0U; i < 10U; i++) {
    expected[i] = (uint16_t)(array[i] * 100U);
    expected_sum += (uint32_t)expected[i];
  }

  MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(expected_sum, NULL, 0U);

  result = MyLib_AnalyzeArray_u32(array, 10U, 100U);

  TEST_ASSERT_EQUAL_UINT32(expected_sum, result);
  for(i = 0U; i < 10U; i++) {
    TEST_ASSERT_EQUAL_UINT16(expected[i], array[i]);
  }
}

/**
 * @brief Test: Valid pointer with len_u32 = 1, factor_u16 = 65535, initial value = 65535 → verify uint16_t overflow wraps to 1 (65535*65535 mod 65536), return 1
 */
void test_SingleElement_MaxFactor_MaxValue_Overflow(void) {
  uint16_t array[1] = {65535U};
  uint32_t result;
  uint16_t expected = (uint16_t)(65535U * 65535U);

  MyLib_ComputeAdjustedValue_u32_ExpectAndReturn((uint32_t)expected, NULL, 0U);

  result = MyLib_AnalyzeArray_u32(array, 1U, 65535U);

  TEST_ASSERT_EQUAL_UINT32((uint32_t)expected, result);
  TEST_ASSERT_EQUAL_UINT16(expected, array[0]);
}

/**
 * @brief Test: Valid pointer with len_u32 = 5, factor_u16 = 1, initial values = {0, 1, 32767, 32768, 65535} → array unchanged, return 131071
 */
void test_FiveElements_FactorOne_BoundaryValues(void) {
  uint16_t array[5] = {0U, 1U, 32767U, 32768U, 65535U};
  uint32_t result;

  MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(131071U, NULL, 0U);

  result = MyLib_AnalyzeArray_u32(array, 5U, 1U);

  TEST_ASSERT_EQUAL_UINT32(131071U, result);
  TEST_ASSERT_EQUAL_UINT16(0U, array[0]);
  TEST_ASSERT_EQUAL_UINT16(1U, array[1]);
  TEST_ASSERT_EQUAL_UINT16(32767U, array[2]);
  TEST_ASSERT_EQUAL_UINT16(32768U, array[3]);
  TEST_ASSERT_EQUAL_UINT16(65535U, array[4]);
}

/**
 * @brief Test: Valid pointer with len_u32 = 4, factor_u16 = 2, initial values = {0, 1, 32767, 32768} → array = {0, 2, 65534, 0 (wrap)}, return 65536
 */
void test_FourElements_FactorTwo_BoundaryWrap(void) {
  uint16_t array[4] = {0U, 1U, 32767U, 32768U};
  uint32_t result;
  uint16_t expected_0 = (uint16_t)(0U * 2U);
  uint16_t expected_1 = (uint16_t)(1U * 2U);
  uint16_t expected_2 = (uint16_t)(32767U * 2U);
  uint16_t expected_3 = (uint16_t)(32768U * 2U);
  uint32_t expected_sum = (uint32_t)expected_0 + (uint32_t)expected_1 + (uint32_t)expected_2 + (uint32_t)expected_3;

  MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(expected_sum, NULL, 0U);

  result = MyLib_AnalyzeArray_u32(array, 4U, 2U);

  TEST_ASSERT_EQUAL_UINT32(expected_sum, result);
  TEST_ASSERT_EQUAL_UINT16(expected_0, array[0]);
  TEST_ASSERT_EQUAL_UINT16(expected_1, array[1]);
  TEST_ASSERT_EQUAL_UINT16(expected_2, array[2]);
  TEST_ASSERT_EQUAL_UINT16(expected_3, array[3]);
}