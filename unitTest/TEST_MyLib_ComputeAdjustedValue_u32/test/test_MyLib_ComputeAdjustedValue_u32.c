#include "MyLib_ComputeAdjustedValue_u32.h"
#include "mock_MyLib.h"
#include "unity.h"

SECTION 1 — Mock callbacks

    static uint32_t
    InternalHelper_u32_Callback(uint32_t x_u32, uint16_t y_u16, int call_count) {
  (void)call_count;
  return x_u32 + y_u16;
}

SECTION 2 — setUp() and tearDown()

                            void setUp(void) {
  g_counter_u32 = 0U;
  g_record.id_u16 = 0U;
  g_record.value_u32 = 0U;
  g_systemReady_b = false;
}

void tearDown(void) {
}

SECTION 3 — Test functions

    /**
 * @brief Test: base_u32 at lower boundary (0) with NULL delta pointer; expect return value computed as InternalHelper_u32(0 * 1, MYLIB_MULT_VALUE_U8).
 */
    void
    test_MyLib_ComputeAdjustedValue_u32_base_0_delta_NULL(void) {
  uint32_t result_u32;
  uint32_t expected_intermediate_u32 = 0U * 1U;
  uint32_t expected_result_u32 = expected_intermediate_u32 + MYLIB_MULT_VALUE_U8;

  InternalHelper_u32_Stub(InternalHelper_u32_Callback);

  result_u32 = MyLib_ComputeAdjustedValue_u32(0U, NULL);

  TEST_ASSERT_EQUAL_UINT32(expected_result_u32, result_u32);
}

/**
 * @brief Test: base_u32 at lower boundary (0) with valid delta pointer pointing to value 1; expect return value computed as InternalHelper_u32(0 * 1, MYLIB_MULT_VALUE_U8).
 */
void test_MyLib_ComputeAdjustedValue_u32_base_0_delta_1(void) {
  uint32_t result_u32;
  uint16_t delta_u16 = 1U;
  uint32_t expected_intermediate_u32 = 0U * 1U;
  uint32_t expected_result_u32 = expected_intermediate_u32 + MYLIB_MULT_VALUE_U8;

  InternalHelper_u32_Stub(InternalHelper_u32_Callback);

  result_u32 = MyLib_ComputeAdjustedValue_u32(0U, &delta_u16);

  TEST_ASSERT_EQUAL_UINT32(expected_result_u32, result_u32);
}

/**
 * @brief Test: base_u32 just inside lower boundary (1) with NULL delta pointer; expect return value computed as InternalHelper_u32(1 * 1, MYLIB_MULT_VALUE_U8).
 */
void test_MyLib_ComputeAdjustedValue_u32_base_1_delta_NULL(void) {
  uint32_t result_u32;
  uint32_t expected_intermediate_u32 = 1U * 1U;
  uint32_t expected_result_u32 = expected_intermediate_u32 + MYLIB_MULT_VALUE_U8;

  InternalHelper_u32_Stub(InternalHelper_u32_Callback);

  result_u32 = MyLib_ComputeAdjustedValue_u32(1U, NULL);

  TEST_ASSERT_EQUAL_UINT32(expected_result_u32, result_u32);
}

/**
 * @brief Test: base_u32 just inside lower boundary (1) with valid delta pointer pointing to value 1; expect return value computed as InternalHelper_u32(1 * 1, MYLIB_MULT_VALUE_U8).
 */
void test_MyLib_ComputeAdjustedValue_u32_base_1_delta_1(void) {
  uint32_t result_u32;
  uint16_t delta_u16 = 1U;
  uint32_t expected_intermediate_u32 = 1U * 1U;
  uint32_t expected_result_u32 = expected_intermediate_u32 + MYLIB_MULT_VALUE_U8;

  InternalHelper_u32_Stub(InternalHelper_u32_Callback);

  result_u32 = MyLib_ComputeAdjustedValue_u32(1U, &delta_u16);

  TEST_ASSERT_EQUAL_UINT32(expected_result_u32, result_u32);
}

/**
 * @brief Test: base_u32 at mid-range (300) with NULL delta pointer; expect return value computed as InternalHelper_u32(300 * 1, MYLIB_MULT_VALUE_U8).
 */
void test_MyLib_ComputeAdjustedValue_u32_base_300_delta_NULL(void) {
  uint32_t result_u32;
  uint32_t expected_intermediate_u32 = 300U * 1U;
  uint32_t expected_result_u32 = expected_intermediate_u32 + MYLIB_MULT_VALUE_U8;

  InternalHelper_u32_Stub(InternalHelper_u32_Callback);

  result_u32 = MyLib_ComputeAdjustedValue_u32(300U, NULL);

  TEST_ASSERT_EQUAL_UINT32(expected_result_u32, result_u32);
}

/**
 * @brief Test: base_u32 at mid-range (300) with valid delta pointer pointing to mid-range delta value (32768); expect return value computed as InternalHelper_u32(300 * 32768, MYLIB_MULT_VALUE_U8).
 */
void test_MyLib_ComputeAdjustedValue_u32_base_300_delta_32768(void) {
  uint32_t result_u32;
  uint16_t delta_u16 = 32768U;
  uint32_t expected_intermediate_u32 = 300U * 32768U;
  uint32_t expected_result_u32 = expected_intermediate_u32 + MYLIB_MULT_VALUE_U8;

  InternalHelper_u32_Stub(InternalHelper_u32_Callback);

  result_u32 = MyLib_ComputeAdjustedValue_u32(300U, &delta_u16);

  TEST_ASSERT_EQUAL_UINT32(expected_result_u32, result_u32);
}

/**
 * @brief Test: base_u32 just inside upper boundary (599) with NULL delta pointer; expect return value computed as InternalHelper_u32(599 * 1, MYLIB_MULT_VALUE_U8).
 */
void test_MyLib_ComputeAdjustedValue_u32_base_599_delta_NULL(void) {
  uint32_t result_u32;
  uint32_t expected_intermediate_u32 = 599U * 1U;
  uint32_t expected_result_u32 = expected_intermediate_u32 + MYLIB_MULT_VALUE_U8;

  InternalHelper_u32_Stub(InternalHelper_u32_Callback);

  result_u32 = MyLib_ComputeAdjustedValue_u32(599U, NULL);

  TEST_ASSERT_EQUAL_UINT32(expected_result_u32, result_u32);
}

/**
 * @brief Test: base_u32 just inside upper boundary (599) with valid delta pointer pointing to value 1; expect return value computed as InternalHelper_u32(599 * 1, MYLIB_MULT_VALUE_U8).
 */
void test_MyLib_ComputeAdjustedValue_u32_base_599_delta_1(void) {
  uint32_t result_u32;
  uint16_t delta_u16 = 1U;
  uint32_t expected_intermediate_u32 = 599U * 1U;
  uint32_t expected_result_u32 = expected_intermediate_u32 + MYLIB_MULT_VALUE_U8;

  InternalHelper_u32_Stub(InternalHelper_u32_Callback);

  result_u32 = MyLib_ComputeAdjustedValue_u32(599U, &delta_u16);

  TEST_ASSERT_EQUAL_UINT32(expected_result_u32, result_u32);
}

/**
 * @brief Test: base_u32 at upper boundary (600) with NULL delta pointer; expect return value computed as InternalHelper_u32(600 * 1, MYLIB_MULT_VALUE_U8).
 */
void test_MyLib_ComputeAdjustedValue_u32_base_600_delta_NULL(void) {
  uint32_t result_u32;
  uint32_t expected_intermediate_u32 = 600U * 1U;
  uint32_t expected_result_u32 = expected_intermediate_u32 + MYLIB_MULT_VALUE_U8;

  InternalHelper_u32_Stub(InternalHelper_u32_Callback);

  result_u32 = MyLib_ComputeAdjustedValue_u32(600U, NULL);

  TEST_ASSERT_EQUAL_UINT32(expected_result_u32, result_u32);
}

/**
 * @brief Test: base_u32 at upper boundary (600) with valid delta pointer pointing to value 1; expect return value computed as InternalHelper_u32(600 * 1, MYLIB_MULT_VALUE_U8).
 */
void test_MyLib_ComputeAdjustedValue_u32_base_600_delta_1(void) {
  uint32_t result_u32;
  uint16_t delta_u16 = 1U;
  uint32_t expected_intermediate_u32 = 600U * 1U;
  uint32_t expected_result_u32 = expected_intermediate_u32 + MYLIB_MULT_VALUE_U8;

  InternalHelper_u32_Stub(InternalHelper_u32_Callback);

  result_u32 = MyLib_ComputeAdjustedValue_u32(600U, &delta_u16);

  TEST_ASSERT_EQUAL_UINT32(expected_result_u32, result_u32);
}

/**
 * @brief Test: base_u32 at lower boundary (0) with valid delta pointer pointing to lower boundary delta (0); expect return value computed as InternalHelper_u32(0 * 0, MYLIB_MULT_VALUE_U8).
 */
void test_MyLib_ComputeAdjustedValue_u32_base_0_delta_0(void) {
  uint32_t result_u32;
  uint16_t delta_u16 = 0U;
  uint32_t expected_intermediate_u32 = 0U * 0U;
  uint32_t expected_result_u32 = expected_intermediate_u32 + MYLIB_MULT_VALUE_U8;

  InternalHelper_u32_Stub(InternalHelper_u32_Callback);

  result_u32 = MyLib_ComputeAdjustedValue_u32(0U, &delta_u16);

  TEST_ASSERT_EQUAL_UINT32(expected_result_u32, result_u32);
}

/**
 * @brief Test: base_u32 at mid-range (300) with valid delta pointer pointing to lower boundary delta (0); expect return value computed as InternalHelper_u32(300 * 0, MYLIB_MULT_VALUE_U8).
 */
void test_MyLib_ComputeAdjustedValue_u32_base_300_delta_0(void) {
  uint32_t result_u32;
  uint16_t delta_u16 = 0U;
  uint32_t expected_intermediate_u32 = 300U * 0U;
  uint32_t expected_result_u32 = expected_intermediate_u32 + MYLIB_MULT_VALUE_U8;

  InternalHelper_u32_Stub(InternalHelper_u32_Callback);

  result_u32 = MyLib_ComputeAdjustedValue_u32(300U, &delta_u16);

  TEST_ASSERT_EQUAL_UINT32(expected_result_u32, result_u32);
}

/**
 * @brief Test: base_u32 at upper boundary (600) with valid delta pointer pointing to lower boundary delta (0); expect return value computed as InternalHelper_u32(600 * 0, MYLIB_MULT_VALUE_U8).
 */
void test_MyLib_ComputeAdjustedValue_u32_base_600_delta_0(void) {
  uint32_t result_u32;
  uint16_t delta_u16 = 0U;
  uint32_t expected_intermediate_u32 = 600U * 0U;
  uint32_t expected_result_u32 = expected_intermediate_u32 + MYLIB_MULT_VALUE_U8;

  InternalHelper_u32_Stub(InternalHelper_u32_Callback);

  result_u32 = MyLib_ComputeAdjustedValue_u32(600U, &delta_u16);

  TEST_ASSERT_EQUAL_UINT32(expected_result_u32, result_u32);
}

/**
 * @brief Test: base_u32 at lower boundary (0) with valid delta pointer pointing to just inside lower boundary delta (1); expect return value computed as InternalHelper_u32(0 * 1, MYLIB_MULT_VALUE_U8).
 */
void test_MyLib_ComputeAdjustedValue_u32_base_0_delta_1_just_inside_lower(void) {
  uint32_t result_u32;
  uint16_t delta_u16 = 1U;
  uint32_t expected_intermediate_u32 = 0U * 1U;
  uint32_t expected_result_u32 = expected_intermediate_u32 + MYLIB_MULT_VALUE_U8;

  InternalHelper_u32_Stub(InternalHelper_u32_Callback);

  result_u32 = MyLib_ComputeAdjustedValue_u32(0U, &delta_u16);

  TEST_ASSERT_EQUAL_UINT32(expected_result_u32, result_u32);
}

/**
 * @brief Test: base_u32 at mid-range (300) with valid delta pointer pointing to just inside lower boundary delta (1); expect return value computed as InternalHelper_u32(300 * 1, MYLIB_MULT_VALUE_U8).
 */
void test_MyLib_ComputeAdjustedValue_u32_base_300_delta_1_just_inside_lower(void) {
  uint32_t result_u32;
  uint16_t delta_u16 = 1U;
  uint32_t expected_intermediate_u32 = 300U * 1U;
  uint32_t expected_result_u32 = expected_intermediate_u32 + MYLIB_MULT_VALUE_U8;

  InternalHelper_u32_Stub(InternalHelper_u32_Callback);

  result_u32 = MyLib_ComputeAdjustedValue_u32(300U, &delta_u16);

  TEST_ASSERT_EQUAL_UINT32(expected_result_u32, result_u32);
}

/**
 * @brief Test: base_u32 at upper boundary (600) with valid delta pointer pointing to just inside lower boundary delta (1); expect return value computed as InternalHelper_u32(600 * 1, MYLIB_MULT_VALUE_U8).
 */
void test_MyLib_ComputeAdjustedValue_u32_base_600_delta_1_just_inside_lower(void) {
  uint32_t result_u32;
  uint16_t delta_u16 = 1U;
  uint32_t expected_intermediate_u32 = 600U * 1U;
  uint32_t expected_result_u32 = expected_intermediate_u32 + MYLIB_MULT_VALUE_U8;

  InternalHelper_u32_Stub(InternalHelper_u32_Callback);

  result_u32 = MyLib_ComputeAdjustedValue_u32(600U, &delta_u16);

  TEST_ASSERT_EQUAL_UINT32(expected_result_u32, result_u32);
}

/**
 * @brief Test: base_u32 at lower boundary (0) with valid delta pointer pointing to just inside upper boundary delta (65534); expect return value computed as InternalHelper_u32(0 * 65534, MYLIB_MULT_VALUE_U8).
 */
void test_MyLib_ComputeAdjustedValue_u32_base_0_delta_65534(void) {
  uint32_t result_u32;
  uint16_t delta_u16 = 65534U;
  uint32_t expected_intermediate_u32 = 0U * 65534U;
  uint32_t expected_result_u32 = expected_intermediate_u32 + MYLIB_MULT_VALUE_U8;

  InternalHelper_u32_Stub(InternalHelper_u32_Callback);

  result_u32 = MyLib_ComputeAdjustedValue_u32(0U, &delta_u16);

  TEST_ASSERT_EQUAL_UINT32(expected_result_u32, result_u32);
}

/**
 * @brief Test: base_u32 at mid-range (300) with valid delta pointer pointing to just inside upper boundary delta (65534); expect return value computed as InternalHelper_u32(300 * 65534, MYLIB_MULT_VALUE_U8).
 */
void test_MyLib_ComputeAdjustedValue_u32_base_300_delta_65534(void) {
  uint32_t result_u32;
  uint16_t delta_u16 = 65534U;
  uint32_t expected_intermediate_u32 = 300U * 65534U;
  uint32_t expected_result_u32 = expected_intermediate_u32 + MYLIB_MULT_VALUE_U8;

  InternalHelper_u32_Stub(InternalHelper_u32_Callback);

  result_u32 = MyLib_ComputeAdjustedValue_u32(300U, &delta_u16);

  TEST_ASSERT_EQUAL_UINT32(expected_result_u32, result_u32);
}

/**
 * @brief Test: base_u32 at upper boundary (600) with valid delta pointer pointing to just inside upper boundary delta (65534); expect return value computed as InternalHelper_u32(600 * 65534, MYLIB_MULT_VALUE_U8).
 */
void test_MyLib_ComputeAdjustedValue_u32_base_600_delta_65534(void) {
  uint32_t result_u32;
  uint16_t delta_u16 = 65534U;
  uint32_t expected_intermediate_u32 = 600U * 65534U;
  uint32_t expected_result_u32 = expected_intermediate_u32 + MYLIB_MULT_VALUE_U8;

  InternalHelper_u32_Stub(InternalHelper_u32_Callback);

  result_u32 = MyLib_ComputeAdjustedValue_u32(600U, &delta_u16);

  TEST_ASSERT_EQUAL_UINT32(expected_result_u32, result_u32);
}

/**
 * @brief Test: base_u32 at lower boundary (0) with valid delta pointer pointing to upper boundary delta (65535); expect return value computed as InternalHelper_u32(0 * 65535, MYLIB_MULT_VALUE_U8).
 */
void test_MyLib_ComputeAdjustedValue_u32_base_0_delta_65535(void) {
  uint32_t result_u32;
  uint16_t delta_u16 = 65535U;
  uint32_t expected_intermediate_u32 = 0U * 65535U;
  uint32_t expected_result_u32 = expected_intermediate_u32 + MYLIB_MULT_VALUE_U8;

  InternalHelper_u32_Stub(InternalHelper_u32_Callback);

  result_u32 = MyLib_ComputeAdjustedValue_u32(0U, &delta_u16);

  TEST_ASSERT_EQUAL_UINT32(expected_result_u32, result_u32);
}

/**
 * @brief Test: base_u32 at mid-range (300) with valid delta pointer pointing to upper boundary delta (65535); expect return value computed as InternalHelper_u32(300 * 65535, MYLIB_MULT_VALUE_U8).
 */
void test_MyLib_ComputeAdjustedValue_u32_base_300_delta_65535(void) {
  uint32_t result_u32;
  uint16_t delta_u16 = 65535U;
  uint32_t expected_intermediate_u32 = 300U * 65535U;
  uint32_t expected_result_u32 = expected_intermediate_u32 + MYLIB_MULT_VALUE_U8;

  InternalHelper_u32_Stub(InternalHelper_u32_Callback);

  result_u32 = MyLib_ComputeAdjustedValue_u32(300U, &delta_u16);

  TEST_ASSERT_EQUAL_UINT32(expected_result_u32, result_u32);
}

/**
 * @brief Test: base_u32 at upper boundary (600) with valid delta pointer pointing to upper boundary delta (65535); expect return value computed as InternalHelper_u32(600 * 65535, MYLIB_MULT_VALUE_U8).
 */
void test_MyLib_ComputeAdjustedValue_u32_base_600_delta_65535(void) {
  uint32_t result_u32;
  uint16_t delta_u16 = 65535U;
  uint32_t expected_intermediate_u32 = 600U * 65535U;
  uint32_t expected_result_u32 = expected_intermediate_u32 + MYLIB_MULT_VALUE_U8;

  InternalHelper_u32_Stub(InternalHelper_u32_Callback);

  result_u32 = MyLib_ComputeAdjustedValue_u32(600U, &delta_u16);

  TEST_ASSERT_EQUAL_UINT32(expected_result_u32, result_u32);
}