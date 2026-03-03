#include "MyLib_ComputeAdjustedValue_u32.h"
#include "mock_MyLib.h"
#include "unity.h"

/* SECTION 1 — Mock callbacks */

/* SECTION 2 — setUp() and tearDown() */

void setUp(void) {
  g_counter_u32 = 0U;
  g_record.id_u16 = 0U;
  g_record.value_u32 = 0U;
  g_systemReady_b = false;
}

void tearDown(void) {
}

/* SECTION 3 — Test functions */

/**
 * @brief Test: base_u32 at lower boundary (0) with NULL delta pointer; expect return value computed as InternalHelper_u32(0 * 1, MYLIB_MULT_VALUE_U8).
 */
void test_MyLib_ComputeAdjustedValue_u32_base_0_delta_NULL(void) {
  uint32_t l_val_u32;
  uint32_t l_expected_u32;

  l_val_u32 = 0U * 1U;
  l_expected_u32 = 42U;

  InternalHelper_u32_ExpectAndReturn(l_val_u32, (uint16_t)MYLIB_MULT_VALUE_U8, l_expected_u32);

  TEST_ASSERT_EQUAL_UINT32(l_expected_u32, MyLib_ComputeAdjustedValue_u32(0U, NULL));
}

/**
 * @brief Test: base_u32 at lower boundary (0) with valid delta pointer pointing to value 1; expect return value computed as InternalHelper_u32(0 * 1, MYLIB_MULT_VALUE_U8).
 */
void test_MyLib_ComputeAdjustedValue_u32_base_0_delta_1(void) {
  uint32_t l_val_u32;
  uint32_t l_expected_u32;
  uint16_t l_delta_u16 = 1U;

  l_val_u32 = 0U * 1U;
  l_expected_u32 = 42U;

  InternalHelper_u32_ExpectAndReturn(l_val_u32, (uint16_t)MYLIB_MULT_VALUE_U8, l_expected_u32);

  TEST_ASSERT_EQUAL_UINT32(l_expected_u32, MyLib_ComputeAdjustedValue_u32(0U, &l_delta_u16));
}

/**
 * @brief Test: base_u32 just inside lower boundary (1) with NULL delta pointer; expect return value computed as InternalHelper_u32(1 * 1, MYLIB_MULT_VALUE_U8).
 */
void test_MyLib_ComputeAdjustedValue_u32_base_1_delta_NULL(void) {
  uint32_t l_val_u32;
  uint32_t l_expected_u32;

  l_val_u32 = 1U * 1U;
  l_expected_u32 = 43U;

  InternalHelper_u32_ExpectAndReturn(l_val_u32, (uint16_t)MYLIB_MULT_VALUE_U8, l_expected_u32);

  TEST_ASSERT_EQUAL_UINT32(l_expected_u32, MyLib_ComputeAdjustedValue_u32(1U, NULL));
}

/**
 * @brief Test: base_u32 just inside lower boundary (1) with valid delta pointer pointing to value 1; expect return value computed as InternalHelper_u32(1 * 1, MYLIB_MULT_VALUE_U8).
 */
void test_MyLib_ComputeAdjustedValue_u32_base_1_delta_1(void) {
  uint32_t l_val_u32;
  uint32_t l_expected_u32;
  uint16_t l_delta_u16 = 1U;

  l_val_u32 = 1U * 1U;
  l_expected_u32 = 43U;

  InternalHelper_u32_ExpectAndReturn(l_val_u32, (uint16_t)MYLIB_MULT_VALUE_U8, l_expected_u32);

  TEST_ASSERT_EQUAL_UINT32(l_expected_u32, MyLib_ComputeAdjustedValue_u32(1U, &l_delta_u16));
}

/**
 * @brief Test: base_u32 at mid-range (300) with NULL delta pointer; expect return value computed as InternalHelper_u32(300 * 1, MYLIB_MULT_VALUE_U8).
 */
void test_MyLib_ComputeAdjustedValue_u32_base_300_delta_NULL(void) {
  uint32_t l_val_u32;
  uint32_t l_expected_u32;

  l_val_u32 = 300U * 1U;
  l_expected_u32 = 1500U;

  InternalHelper_u32_ExpectAndReturn(l_val_u32, (uint16_t)MYLIB_MULT_VALUE_U8, l_expected_u32);

  TEST_ASSERT_EQUAL_UINT32(l_expected_u32, MyLib_ComputeAdjustedValue_u32(300U, NULL));
}

/**
 * @brief Test: base_u32 at mid-range (300) with valid delta pointer pointing to mid-range delta value (32768); expect return value computed as InternalHelper_u32(300 * 32768, MYLIB_MULT_VALUE_U8).
 */
void test_MyLib_ComputeAdjustedValue_u32_base_300_delta_32768(void) {
  uint32_t l_val_u32;
  uint32_t l_expected_u32;
  uint16_t l_delta_u16 = 32768U;

  l_val_u32 = 300U * 32768U;
  l_expected_u32 = 49152000U;

  InternalHelper_u32_ExpectAndReturn(l_val_u32, (uint16_t)MYLIB_MULT_VALUE_U8, l_expected_u32);

  TEST_ASSERT_EQUAL_UINT32(l_expected_u32, MyLib_ComputeAdjustedValue_u32(300U, &l_delta_u16));
}

/**
 * @brief Test: base_u32 just inside upper boundary (599) with NULL delta pointer; expect return value computed as InternalHelper_u32(599 * 1, MYLIB_MULT_VALUE_U8).
 */
void test_MyLib_ComputeAdjustedValue_u32_base_599_delta_NULL(void) {
  uint32_t l_val_u32;
  uint32_t l_expected_u32;

  l_val_u32 = 599U * 1U;
  l_expected_u32 = 2995U;

  InternalHelper_u32_ExpectAndReturn(l_val_u32, (uint16_t)MYLIB_MULT_VALUE_U8, l_expected_u32);

  TEST_ASSERT_EQUAL_UINT32(l_expected_u32, MyLib_ComputeAdjustedValue_u32(599U, NULL));
}

/**
 * @brief Test: base_u32 just inside upper boundary (599) with valid delta pointer pointing to value 1; expect return value computed as InternalHelper_u32(599 * 1, MYLIB_MULT_VALUE_U8).
 */
void test_MyLib_ComputeAdjustedValue_u32_base_599_delta_1(void) {
  uint32_t l_val_u32;
  uint32_t l_expected_u32;
  uint16_t l_delta_u16 = 1U;

  l_val_u32 = 599U * 1U;
  l_expected_u32 = 2995U;

  InternalHelper_u32_ExpectAndReturn(l_val_u32, (uint16_t)MYLIB_MULT_VALUE_U8, l_expected_u32);

  TEST_ASSERT_EQUAL_UINT32(l_expected_u32, MyLib_ComputeAdjustedValue_u32(599U, &l_delta_u16));
}

/**
 * @brief Test: base_u32 at upper boundary (600) with NULL delta pointer; expect return value computed as InternalHelper_u32(600 * 1, MYLIB_MULT_VALUE_U8).
 */
void test_MyLib_ComputeAdjustedValue_u32_base_600_delta_NULL(void) {
  uint32_t l_val_u32;
  uint32_t l_expected_u32;

  l_val_u32 = 600U * 1U;
  l_expected_u32 = 3000U;

  InternalHelper_u32_ExpectAndReturn(l_val_u32, (uint16_t)MYLIB_MULT_VALUE_U8, l_expected_u32);

  TEST_ASSERT_EQUAL_UINT32(l_expected_u32, MyLib_ComputeAdjustedValue_u32(600U, NULL));
}

/**
 * @brief Test: base_u32 at upper boundary (600) with valid delta pointer pointing to value 1; expect return value computed as InternalHelper_u32(600 * 1, MYLIB_MULT_VALUE_U8).
 */
void test_MyLib_ComputeAdjustedValue_u32_base_600_delta_1(void) {
  uint32_t l_val_u32;
  uint32_t l_expected_u32;
  uint16_t l_delta_u16 = 1U;

  l_val_u32 = 600U * 1U;
  l_expected_u32 = 3000U;

  InternalHelper_u32_ExpectAndReturn(l_val_u32, (uint16_t)MYLIB_MULT_VALUE_U8, l_expected_u32);

  TEST_ASSERT_EQUAL_UINT32(l_expected_u32, MyLib_ComputeAdjustedValue_u32(600U, &l_delta_u16));
}

/**
 * @brief Test: base_u32 at lower boundary (0) with valid delta pointer pointing to lower boundary delta (0); expect return value computed as InternalHelper_u32(0 * 0, MYLIB_MULT_VALUE_U8).
 */
void test_MyLib_ComputeAdjustedValue_u32_base_0_delta_0(void) {
  uint32_t l_val_u32;
  uint32_t l_expected_u32;
  uint16_t l_delta_u16 = 0U;

  l_val_u32 = 0U * 0U;
  l_expected_u32 = 0U;

  InternalHelper_u32_ExpectAndReturn(l_val_u32, (uint16_t)MYLIB_MULT_VALUE_U8, l_expected_u32);

  TEST_ASSERT_EQUAL_UINT32(l_expected_u32, MyLib_ComputeAdjustedValue_u32(0U, &l_delta_u16));
}

/**
 * @brief Test: base_u32 at lower boundary (0) with valid delta pointer pointing to just inside lower boundary delta (1); expect return value computed as InternalHelper_u32(0 * 1, MYLIB_MULT_VALUE_U8) — already covered by earlier test, omitted as duplicate.
 */
void test_MyLib_ComputeAdjustedValue_u32_base_0_delta_1_duplicate(void) {
  uint32_t l_val_u32;
  uint32_t l_expected_u32;
  uint16_t l_delta_u16 = 1U;

  l_val_u32 = 0U * 1U;
  l_expected_u32 = 42U;

  InternalHelper_u32_ExpectAndReturn(l_val_u32, (uint16_t)MYLIB_MULT_VALUE_U8, l_expected_u32);

  TEST_ASSERT_EQUAL_UINT32(l_expected_u32, MyLib_ComputeAdjustedValue_u32(0U, &l_delta_u16));
}

/**
 * @brief Test: base_u32 at lower boundary (0) with valid delta pointer pointing to just inside upper boundary delta (65534); expect return value computed as InternalHelper_u32(0 * 65534, MYLIB_MULT_VALUE_U8).
 */
void test_MyLib_ComputeAdjustedValue_u32_base_0_delta_65534(void) {
  uint32_t l_val_u32;
  uint32_t l_expected_u32;
  uint16_t l_delta_u16 = 65534U;

  l_val_u32 = 0U * 65534U;
  l_expected_u32 = 0U;

  InternalHelper_u32_ExpectAndReturn(l_val_u32, (uint16_t)MYLIB_MULT_VALUE_U8, l_expected_u32);

  TEST_ASSERT_EQUAL_UINT32(l_expected_u32, MyLib_ComputeAdjustedValue_u32(0U, &l_delta_u16));
}

/**
 * @brief Test: base_u32 at lower boundary (0) with valid delta pointer pointing to upper boundary delta (65535); expect return value computed as InternalHelper_u32(0 * 65535, MYLIB_MULT_VALUE_U8).
 */
void test_MyLib_ComputeAdjustedValue_u32_base_0_delta_65535(void) {
  uint32_t l_val_u32;
  uint32_t l_expected_u32;
  uint16_t l_delta_u16 = 65535U;

  l_val_u32 = 0U * 65535U;
  l_expected_u32 = 0U;

  InternalHelper_u32_ExpectAndReturn(l_val_u32, (uint16_t)MYLIB_MULT_VALUE_U8, l_expected_u32);

  TEST_ASSERT_EQUAL_UINT32(l_expected_u32, MyLib_ComputeAdjustedValue_u32(0U, &l_delta_u16));
}

/**
 * @brief Test: base_u32 at mid-range (300) with valid delta pointer pointing to lower boundary delta (0); expect return value computed as InternalHelper_u32(300 * 0, MYLIB_MULT_VALUE_U8).
 */
void test_MyLib_ComputeAdjustedValue_u32_base_300_delta_0(void) {
  uint32_t l_val_u32;
  uint32_t l_expected_u32;
  uint16_t l_delta_u16 = 0U;

  l_val_u32 = 300U * 0U;
  l_expected_u32 = 0U;

  InternalHelper_u32_ExpectAndReturn(l_val_u32, (uint16_t)MYLIB_MULT_VALUE_U8, l_expected_u32);

  TEST_ASSERT_EQUAL_UINT32(l_expected_u32, MyLib_ComputeAdjustedValue_u32(300U, &l_delta_u16));
}

/**
 * @brief Test: base_u32 at mid-range (300) with valid delta pointer pointing to just inside lower boundary delta (1); expect return value computed as InternalHelper_u32(300 * 1, MYLIB_MULT_VALUE_U8).
 */
void test_MyLib_ComputeAdjustedValue_u32_base_300_delta_1(void) {
  uint32_t l_val_u32;
  uint32_t l_expected_u32;
  uint16_t l_delta_u16 = 1U;

  l_val_u32 = 300U * 1U;
  l_expected_u32 = 1500U;

  InternalHelper_u32_ExpectAndReturn(l_val_u32, (uint16_t)MYLIB_MULT_VALUE_U8, l_expected_u32);

  TEST_ASSERT_EQUAL_UINT32(l_expected_u32, MyLib_ComputeAdjustedValue_u32(300U, &l_delta_u16));
}

/**
 * @brief Test: base_u32 at mid-range (300) with valid delta pointer pointing to just inside upper boundary delta (65534); expect return value computed as InternalHelper_u32(300 * 65534, MYLIB_MULT_VALUE_U8).
 */
void test_MyLib_ComputeAdjustedValue_u32_base_300_delta_65534(void) {
  uint32_t l_val_u32;
  uint32_t l_expected_u32;
  uint16_t l_delta_u16 = 65534U;

  l_val_u32 = 300U * 65534U;
  l_expected_u32 = 98301000U;

  InternalHelper_u32_ExpectAndReturn(l_val_u32, (uint16_t)MYLIB_MULT_VALUE_U8, l_expected_u32);

  TEST_ASSERT_EQUAL_UINT32(l_expected_u32, MyLib_ComputeAdjustedValue_u32(300U, &l_delta_u16));
}

/**
 * @brief Test: base_u32 at mid-range (300) with valid delta pointer pointing to upper boundary delta (65535); expect return value computed as InternalHelper_u32(300 * 65535, MYLIB_MULT_VALUE_U8).
 */
void test_MyLib_ComputeAdjustedValue_u32_base_300_delta_65535(void) {
  uint32_t l_val_u32;
  uint32_t l_expected_u32;
  uint16_t l_delta_u16 = 65535U;

  l_val_u32 = 300U * 65535U;
  l_expected_u32 = 98301500U;

  InternalHelper_u32_ExpectAndReturn(l_val_u32, (uint16_t)MYLIB_MULT_VALUE_U8, l_expected_u32);

  TEST_ASSERT_EQUAL_UINT32(l_expected_u32, MyLib_ComputeAdjustedValue_u32(300U, &l_delta_u16));
}

/**
 * @brief Test: base_u32 at upper boundary (600) with valid delta pointer pointing to lower boundary delta (0); expect return value computed as InternalHelper_u32(600 * 0, MYLIB_MULT_VALUE_U8).
 */
void test_MyLib_ComputeAdjustedValue_u32_base_600_delta_0(void) {
  uint32_t l_val_u32;
  uint32_t l_expected_u32;
  uint16_t l_delta_u16 = 0U;

  l_val_u32 = 600U * 0U;
  l_expected_u32 = 0U;

  InternalHelper_u32_ExpectAndReturn(l_val_u32, (uint16_t)MYLIB_MULT_VALUE_U8, l_expected_u32);

  TEST_ASSERT_EQUAL_UINT32(l_expected_u32, MyLib_ComputeAdjustedValue_u32(600U, &l_delta_u16));
}

/**
 * @brief Test: base_u32 at upper boundary (600) with valid delta pointer pointing to just inside lower boundary delta (1); expect return value computed as InternalHelper_u32(600 * 1, MYLIB_MULT_VALUE_U8) — already covered by earlier test, omitted as duplicate.
 */
void test_MyLib_ComputeAdjustedValue_u32_base_600_delta_1_duplicate(void) {
  uint32_t l_val_u32;
  uint32_t l_expected_u32;
  uint16_t l_delta_u16 = 1U;

  l_val_u32 = 600U * 1U;
  l_expected_u32 = 3000U;

  InternalHelper_u32_ExpectAndReturn(l_val_u32, (uint16_t)MYLIB_MULT_VALUE_U8, l_expected_u32);

  TEST_ASSERT_EQUAL_UINT32(l_expected_u32, MyLib_ComputeAdjustedValue_u32(600U, &l_delta_u16));
}

/**
 * @brief Test: base_u32 at upper boundary (600) with valid delta pointer pointing to just inside upper boundary delta (65534); expect return value computed as InternalHelper_u32(600 * 65534, MYLIB_MULT_VALUE_U8).
 */
void test_MyLib_ComputeAdjustedValue_u32_base_600_delta_65534(void) {
  uint32_t l_val_u32;
  uint32_t l_expected_u32;
  uint16_t l_delta_u16 = 65534U;

  l_val_u32 = 600U * 65534U;
  l_expected_u32 = 196602000U;

  InternalHelper_u32_ExpectAndReturn(l_val_u32, (uint16_t)MYLIB_MULT_VALUE_U8, l_expected_u32);

  TEST_ASSERT_EQUAL_UINT32(l_expected_u32, MyLib_ComputeAdjustedValue_u32(600U, &l_delta_u16));
}

/**
 * @brief Test: base_u32 at upper boundary (600) with valid delta pointer pointing to upper boundary delta (65535); expect return value computed as InternalHelper_u32(600 * 65535, MYLIB_MULT_VALUE_U8).
 */
void test_MyLib_ComputeAdjustedValue_u32_base_600_delta_65535(void) {
  uint32_t l_val_u32;
  uint32_t l_expected_u32;
  uint16_t l_delta_u16 = 65535U;

  l_val_u32 = 600U * 65535U;
  l_expected_u32 = 196603000U;

  InternalHelper_u32_ExpectAndReturn(l_val_u32, (uint16_t)MYLIB_MULT_VALUE_U8, l_expected_u32);

  TEST_ASSERT_EQUAL_UINT32(l_expected_u32, MyLib_ComputeAdjustedValue_u32(600U, &l_delta_u16));
}