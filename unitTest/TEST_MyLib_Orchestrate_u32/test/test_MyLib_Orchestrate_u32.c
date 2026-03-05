#include "MyLib_Orchestrate_u32.h"
#include "mock_MyLib.h"
#include "unity.h"
#include <stdbool.h>
#include <stdint.h>

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
 * @brief Test: start_u32 at lower boundary (0) with NULL delta_pc_u16, verify return value equals InternalHelper_u32(0,0) + g_counter_u32 and ProcessRecord called with correct derived record.
 */
void test_start_at_lower_boundary_0_with_NULL_delta(void) {
  uint32_t start_u32 = 0U;
  const uint16_t *delta_pc_u16 = NULL;
  uint32_t l_base_u32 = 50U;
  uint32_t expected_return;
  uint32_t actual_return;
  MyLib_record_t expected_record;

  g_counter_u32 = 10U;

  InternalHelper_u32_ExpectAndReturn(start_u32, 0U, l_base_u32);

  expected_record.id_u16 = (uint16_t)(l_base_u32 & 0xFFFFU);
  expected_record.value_u32 = l_base_u32 / 2U;

  MyLib_ProcessRecord_Expect(&expected_record, MYLIB_MULT_VALUE_U8);
  MyLib_ProcessRecord_IgnoreArg_rec_pc();

  expected_return = l_base_u32 + g_counter_u32;

  actual_return = MyLib_Orchestrate_u32(start_u32, delta_pc_u16);

  TEST_ASSERT_EQUAL_UINT32(expected_return, actual_return);
}

/**
 * @brief Test: start_u32 at lower boundary (0) with valid delta_pc_u16 pointing to 0, verify return value equals InternalHelper_u32(0,0) + g_counter_u32 and ProcessRecord called with correct derived record.
 */
void test_start_at_lower_boundary_0_with_delta_pointing_to_0(void) {
  uint32_t start_u32 = 0U;
  uint16_t delta_value = 0U;
  const uint16_t *delta_pc_u16 = &delta_value;
  uint32_t l_base_u32 = 50U;
  uint32_t expected_return;
  uint32_t actual_return;
  MyLib_record_t expected_record;

  g_counter_u32 = 10U;

  InternalHelper_u32_ExpectAndReturn(start_u32, delta_value, l_base_u32);

  expected_record.id_u16 = (uint16_t)(l_base_u32 & 0xFFFFU);
  expected_record.value_u32 = l_base_u32 / 2U;

  MyLib_ProcessRecord_Expect(&expected_record, MYLIB_MULT_VALUE_U8);
  MyLib_ProcessRecord_IgnoreArg_rec_pc();

  expected_return = l_base_u32 + g_counter_u32;

  actual_return = MyLib_Orchestrate_u32(start_u32, delta_pc_u16);

  TEST_ASSERT_EQUAL_UINT32(expected_return, actual_return);
}

/**
 * @brief Test: start_u32 at lower boundary (0) with valid delta_pc_u16 pointing to mid-range value (100), verify return value equals InternalHelper_u32(0,100) + g_counter_u32 and ProcessRecord called with correct derived record.
 */
void test_start_at_lower_boundary_0_with_delta_pointing_to_100(void) {
  uint32_t start_u32 = 0U;
  uint16_t delta_value = 100U;
  const uint16_t *delta_pc_u16 = &delta_value;
  uint32_t l_base_u32 = 150U;
  uint32_t expected_return;
  uint32_t actual_return;
  MyLib_record_t expected_record;

  g_counter_u32 = 20U;

  InternalHelper_u32_ExpectAndReturn(start_u32, delta_value, l_base_u32);

  expected_record.id_u16 = (uint16_t)(l_base_u32 & 0xFFFFU);
  expected_record.value_u32 = l_base_u32 / 2U;

  MyLib_ProcessRecord_Expect(&expected_record, MYLIB_MULT_VALUE_U8);
  MyLib_ProcessRecord_IgnoreArg_rec_pc();

  expected_return = l_base_u32 + g_counter_u32;

  actual_return = MyLib_Orchestrate_u32(start_u32, delta_pc_u16);

  TEST_ASSERT_EQUAL_UINT32(expected_return, actual_return);
}

/**
 * @brief Test: start_u32 at lower boundary (0) with valid delta_pc_u16 pointing to maximum representable uint16_t (65535), verify return value equals InternalHelper_u32(0,65535) + g_counter_u32 and ProcessRecord called with correct derived record.
 */
void test_start_at_lower_boundary_0_with_delta_pointing_to_65535(void) {
  uint32_t start_u32 = 0U;
  uint16_t delta_value = 65535U;
  const uint16_t *delta_pc_u16 = &delta_value;
  uint32_t l_base_u32 = 70000U;
  uint32_t expected_return;
  uint32_t actual_return;
  MyLib_record_t expected_record;

  g_counter_u32 = 30U;

  InternalHelper_u32_ExpectAndReturn(start_u32, delta_value, l_base_u32);

  expected_record.id_u16 = (uint16_t)(l_base_u32 & 0xFFFFU);
  expected_record.value_u32 = l_base_u32 / 2U;

  MyLib_ProcessRecord_Expect(&expected_record, MYLIB_MULT_VALUE_U8);
  MyLib_ProcessRecord_IgnoreArg_rec_pc();

  expected_return = l_base_u32 + g_counter_u32;

  actual_return = MyLib_Orchestrate_u32(start_u32, delta_pc_u16);

  TEST_ASSERT_EQUAL_UINT32(expected_return, actual_return);
}

/**
 * @brief Test: start_u32 just inside lower boundary (1) with NULL delta_pc_u16, verify return value equals InternalHelper_u32(1,0) + g_counter_u32 and ProcessRecord called with correct derived record.
 */
void test_start_just_inside_lower_boundary_1_with_NULL_delta(void) {
  uint32_t start_u32 = 1U;
  const uint16_t *delta_pc_u16 = NULL;
  uint32_t l_base_u32 = 60U;
  uint32_t expected_return;
  uint32_t actual_return;
  MyLib_record_t expected_record;

  g_counter_u32 = 15U;

  InternalHelper_u32_ExpectAndReturn(start_u32, 0U, l_base_u32);

  expected_record.id_u16 = (uint16_t)(l_base_u32 & 0xFFFFU);
  expected_record.value_u32 = l_base_u32 / 2U;

  MyLib_ProcessRecord_Expect(&expected_record, MYLIB_MULT_VALUE_U8);
  MyLib_ProcessRecord_IgnoreArg_rec_pc();

  expected_return = l_base_u32 + g_counter_u32;

  actual_return = MyLib_Orchestrate_u32(start_u32, delta_pc_u16);

  TEST_ASSERT_EQUAL_UINT32(expected_return, actual_return);
}

/**
 * @brief Test: start_u32 just inside lower boundary (1) with valid delta_pc_u16 pointing to mid-range value (100), verify return value equals InternalHelper_u32(1,100) + g_counter_u32 and ProcessRecord called with correct derived record.
 */
void test_start_just_inside_lower_boundary_1_with_delta_pointing_to_100(void) {
  uint32_t start_u32 = 1U;
  uint16_t delta_value = 100U;
  const uint16_t *delta_pc_u16 = &delta_value;
  uint32_t l_base_u32 = 160U;
  uint32_t expected_return;
  uint32_t actual_return;
  MyLib_record_t expected_record;

  g_counter_u32 = 25U;

  InternalHelper_u32_ExpectAndReturn(start_u32, delta_value, l_base_u32);

  expected_record.id_u16 = (uint16_t)(l_base_u32 & 0xFFFFU);
  expected_record.value_u32 = l_base_u32 / 2U;

  MyLib_ProcessRecord_Expect(&expected_record, MYLIB_MULT_VALUE_U8);
  MyLib_ProcessRecord_IgnoreArg_rec_pc();

  expected_return = l_base_u32 + g_counter_u32;

  actual_return = MyLib_Orchestrate_u32(start_u32, delta_pc_u16);

  TEST_ASSERT_EQUAL_UINT32(expected_return, actual_return);
}

/**
 * @brief Test: start_u32 at mid-range (100) with NULL delta_pc_u16, verify return value equals InternalHelper_u32(100,0) + g_counter_u32 and ProcessRecord called with correct derived record.
 */
void test_start_at_mid_range_100_with_NULL_delta(void) {
  uint32_t start_u32 = 100U;
  const uint16_t *delta_pc_u16 = NULL;
  uint32_t l_base_u32 = 200U;
  uint32_t expected_return;
  uint32_t actual_return;
  MyLib_record_t expected_record;

  g_counter_u32 = 50U;

  InternalHelper_u32_ExpectAndReturn(start_u32, 0U, l_base_u32);

  expected_record.id_u16 = (uint16_t)(l_base_u32 & 0xFFFFU);
  expected_record.value_u32 = l_base_u32 / 2U;

  MyLib_ProcessRecord_Expect(&expected_record, MYLIB_MULT_VALUE_U8);
  MyLib_ProcessRecord_IgnoreArg_rec_pc();

  expected_return = l_base_u32 + g_counter_u32;

  actual_return = MyLib_Orchestrate_u32(start_u32, delta_pc_u16);

  TEST_ASSERT_EQUAL_UINT32(expected_return, actual_return);
}

/**
 * @brief Test: start_u32 at mid-range (100) with valid delta_pc_u16 pointing to mid-range value (100), verify return value equals InternalHelper_u32(100,100) + g_counter_u32 and ProcessRecord called with correct derived record.
 */
void test_start_at_mid_range_100_with_delta_pointing_to_100(void) {
  uint32_t start_u32 = 100U;
  uint16_t delta_value = 100U;
  const uint16_t *delta_pc_u16 = &delta_value;
  uint32_t l_base_u32 = 300U;
  uint32_t expected_return;
  uint32_t actual_return;
  MyLib_record_t expected_record;

  g_counter_u32 = 75U;

  InternalHelper_u32_ExpectAndReturn(start_u32, delta_value, l_base_u32);

  expected_record.id_u16 = (uint16_t)(l_base_u32 & 0xFFFFU);
  expected_record.value_u32 = l_base_u32 / 2U;

  MyLib_ProcessRecord_Expect(&expected_record, MYLIB_MULT_VALUE_U8);
  MyLib_ProcessRecord_IgnoreArg_rec_pc();

  expected_return = l_base_u32 + g_counter_u32;

  actual_return = MyLib_Orchestrate_u32(start_u32, delta_pc_u16);

  TEST_ASSERT_EQUAL_UINT32(expected_return, actual_return);
}

/**
 * @brief Test: start_u32 just inside upper boundary (199) with NULL delta_pc_u16, verify return value equals InternalHelper_u32(199,0) + g_counter_u32 and ProcessRecord called with correct derived record.
 */
void test_start_just_inside_upper_boundary_199_with_NULL_delta(void) {
  uint32_t start_u32 = 199U;
  const uint16_t *delta_pc_u16 = NULL;
  uint32_t l_base_u32 = 350U;
  uint32_t expected_return;
  uint32_t actual_return;
  MyLib_record_t expected_record;

  g_counter_u32 = 40U;

  InternalHelper_u32_ExpectAndReturn(start_u32, 0U, l_base_u32);

  expected_record.id_u16 = (uint16_t)(l_base_u32 & 0xFFFFU);
  expected_record.value_u32 = l_base_u32 / 2U;

  MyLib_ProcessRecord_Expect(&expected_record, MYLIB_MULT_VALUE_U8);
  MyLib_ProcessRecord_IgnoreArg_rec_pc();

  expected_return = l_base_u32 + g_counter_u32;

  actual_return = MyLib_Orchestrate_u32(start_u32, delta_pc_u16);

  TEST_ASSERT_EQUAL_UINT32(expected_return, actual_return);
}

/**
 * @brief Test: start_u32 just inside upper boundary (199) with valid delta_pc_u16 pointing to mid-range value (100), verify return value equals InternalHelper_u32(199,100) + g_counter_u32 and ProcessRecord called with correct derived record.
 */
void test_start_just_inside_upper_boundary_199_with_delta_pointing_to_100(void) {
  uint32_t start_u32 = 199U;
  uint16_t delta_value = 100U;
  const uint16_t *delta_pc_u16 = &delta_value;
  uint32_t l_base_u32 = 450U;
  uint32_t expected_return;
  uint32_t actual_return;
  MyLib_record_t expected_record;

  g_counter_u32 = 60U;

  InternalHelper_u32_ExpectAndReturn(start_u32, delta_value, l_base_u32);

  expected_record.id_u16 = (uint16_t)(l_base_u32 & 0xFFFFU);
  expected_record.value_u32 = l_base_u32 / 2U;

  MyLib_ProcessRecord_Expect(&expected_record, MYLIB_MULT_VALUE_U8);
  MyLib_ProcessRecord_IgnoreArg_rec_pc();

  expected_return = l_base_u32 + g_counter_u32;

  actual_return = MyLib_Orchestrate_u32(start_u32, delta_pc_u16);

  TEST_ASSERT_EQUAL_UINT32(expected_return, actual_return);
}

/**
 * @brief Test: start_u32 at upper boundary (200) with NULL delta_pc_u16, verify return value equals InternalHelper_u32(200,0) + g_counter_u32 and ProcessRecord called with correct derived record.
 */
void test_start_at_upper_boundary_200_with_NULL_delta(void) {
  uint32_t start_u32 = 200U;
  const uint16_t *delta_pc_u16 = NULL;
  uint32_t l_base_u32 = 400U;
  uint32_t expected_return;
  uint32_t actual_return;
  MyLib_record_t expected_record;

  g_counter_u32 = 0U;

  InternalHelper_u32_ExpectAndReturn(start_u32, 0U, l_base_u32);

  expected_record.id_u16 = (uint16_t)(l_base_u32 & 0xFFFFU);
  expected_record.value_u32 = l_base_u32 / 2U;

  MyLib_ProcessRecord_Expect(&expected_record, MYLIB_MULT_VALUE_U8);
  MyLib_ProcessRecord_IgnoreArg_rec_pc();

  expected_return = l_base_u32 + g_counter_u32;

  actual_return = MyLib_Orchestrate_u32(start_u32, delta_pc_u16);

  TEST_ASSERT_EQUAL_UINT32(expected_return, actual_return);
}

/**
 * @brief Test: start_u32 at upper boundary (200) with valid delta_pc_u16 pointing to mid-range value (100), verify return value equals InternalHelper_u32(200,100) + g_counter_u32 and ProcessRecord called with correct derived record.
 */
void test_start_at_upper_boundary_200_with_delta_pointing_to_100(void) {
  uint32_t start_u32 = 200U;
  uint16_t delta_value = 100U;
  const uint16_t *delta_pc_u16 = &delta_value;
  uint32_t l_base_u32 = 500U;
  uint32_t expected_return;
  uint32_t actual_return;
  MyLib_record_t expected_record;

  g_counter_u32 = 80U;

  InternalHelper_u32_ExpectAndReturn(start_u32, delta_value, l_base_u32);

  expected_record.id_u16 = (uint16_t)(l_base_u32 & 0xFFFFU);
  expected_record.value_u32 = l_base_u32 / 2U;

  MyLib_ProcessRecord_Expect(&expected_record, MYLIB_MULT_VALUE_U8);
  MyLib_ProcessRecord_IgnoreArg_rec_pc();

  expected_return = l_base_u32 + g_counter_u32;

  actual_return = MyLib_Orchestrate_u32(start_u32, delta_pc_u16);

  TEST_ASSERT_EQUAL_UINT32(expected_return, actual_return);
}

/**
 * @brief Test: start_u32 at upper boundary (200) with valid delta_pc_u16 pointing to maximum representable uint16_t (65535), verify return value equals InternalHelper_u32(200,65535) + g_counter_u32 and ProcessRecord called with correct derived record.
 */
void test_start_at_upper_boundary_200_with_delta_pointing_to_65535(void) {
  uint32_t start_u32 = 200U;
  uint16_t delta_value = 65535U;
  const uint16_t *delta_pc_u16 = &delta_value;
  uint32_t l_base_u32 = 80000U;
  uint32_t expected_return;
  uint32_t actual_return;
  MyLib_record_t expected_record;

  g_counter_u32 = 100U;

  InternalHelper_u32_ExpectAndReturn(start_u32, delta_value, l_base_u32);

  expected_record.id_u16 = (uint16_t)(l_base_u32 & 0xFFFFU);
  expected_record.value_u32 = l_base_u32 / 2U;

  MyLib_ProcessRecord_Expect(&expected_record, MYLIB_MULT_VALUE_U8);
  MyLib_ProcessRecord_IgnoreArg_rec_pc();

  expected_return = l_base_u32 + g_counter_u32;

  actual_return = MyLib_Orchestrate_u32(start_u32, delta_pc_u16);

  TEST_ASSERT_EQUAL_UINT32(expected_return, actual_return);
}

/**
 * @brief Test: start_u32 just outside upper boundary (201) with NULL delta_pc_u16, verify behavior (return value equals InternalHelper_u32(201,0) + g_counter_u32 and ProcessRecord called with correct derived record).
 */
void test_start_just_outside_upper_boundary_201_with_NULL_delta(void) {
  uint32_t start_u32 = 201U;
  const uint16_t *delta_pc_u16 = NULL;
  uint32_t l_base_u32 = 410U;
  uint32_t expected_return;
  uint32_t actual_return;
  MyLib_record_t expected_record;

  g_counter_u32 = 90U;

  InternalHelper_u32_ExpectAndReturn(start_u32, 0U, l_base_u32);

  expected_record.id_u16 = (uint16_t)(l_base_u32 & 0xFFFFU);
  expected_record.value_u32 = l_base_u32 / 2U;

  MyLib_ProcessRecord_Expect(&expected_record, MYLIB_MULT_VALUE_U8);
  MyLib_ProcessRecord_IgnoreArg_rec_pc();

  expected_return = l_base_u32 + g_counter_u32;

  actual_return = MyLib_Orchestrate_u32(start_u32, delta_pc_u16);

  TEST_ASSERT_EQUAL_UINT32(expected_return, actual_return);
}

/**
 * @brief Test: start_u32 just outside upper boundary (201) with valid delta_pc_u16 pointing to mid-range value (100), verify behavior (return value equals InternalHelper_u32(201,100) + g_counter_u32 and ProcessRecord called with correct derived record).
 */
void test_start_just_outside_upper_boundary_201_with_delta_pointing_to_100(void) {
  uint32_t start_u32 = 201U;
  uint16_t delta_value = 100U;
  const uint16_t *delta_pc_u16 = &delta_value;
  uint32_t l_base_u32 = 510U;
  uint32_t expected_return;
  uint32_t actual_return;
  MyLib_record_t expected_record;

  g_counter_u32 = 95U;

  InternalHelper_u32_ExpectAndReturn(start_u32, delta_value, l_base_u32);

  expected_record.id_u16 = (uint16_t)(l_base_u32 & 0xFFFFU);
  expected_record.value_u32 = l_base_u32 / 2U;

  MyLib_ProcessRecord_Expect(&expected_record, MYLIB_MULT_VALUE_U8);
  MyLib_ProcessRecord_IgnoreArg_rec_pc();

  expected_return = l_base_u32 + g_counter_u32;

  actual_return = MyLib_Orchestrate_u32(start_u32, delta_pc_u16);

  TEST_ASSERT_EQUAL_UINT32(expected_return, actual_return);
}

/**
 * @brief Test: g_counter_u32 at lower boundary (0), start_u32 at mid-range (100) with NULL delta_pc_u16, verify return value equals InternalHelper_u32(100,0) + 0.
 */
void test_g_counter_at_lower_boundary_0_start_100_NULL_delta(void) {
  uint32_t start_u32 = 100U;
  const uint16_t *delta_pc_u16 = NULL;
  uint32_t l_base_u32 = 200U;
  uint32_t expected_return;
  uint32_t actual_return;
  MyLib_record_t expected_record;

  g_counter_u32 = 0U;

  InternalHelper_u32_ExpectAndReturn(start_u32, 0U, l_base_u32);

  expected_record.id_u16 = (uint16_t)(l_base_u32 & 0xFFFFU);
  expected_record.value_u32 = l_base_u32 / 2U;

  MyLib_ProcessRecord_Expect(&expected_record, MYLIB_MULT_VALUE_U8);
  MyLib_ProcessRecord_IgnoreArg_rec_pc();

  expected_return = l_base_u32 + 0U;

  actual_return = MyLib_Orchestrate_u32(start_u32, delta_pc_u16);

  TEST_ASSERT_EQUAL_UINT32(expected_return, actual_return);
}

/**
 * @brief Test: g_counter_u32 at mid-range (250), start_u32 at mid-range (100) with NULL delta_pc_u16, verify return value equals InternalHelper_u32(100,0) + 250.
 */
void test_g_counter_at_mid_range_250_start_100_NULL_delta(void) {
  uint32_t start_u32 = 100U;
  const uint16_t *delta_pc_u16 = NULL;
  uint32_t l_base_u32 = 200U;
  uint32_t expected_return;
  uint32_t actual_return;
  MyLib_record_t expected_record;

  g_counter_u32 = 250U;

  InternalHelper_u32_ExpectAndReturn(start_u32, 0U, l_base_u32);

  expected_record.id_u16 = (uint16_t)(l_base_u32 & 0xFFFFU);
  expected_record.value_u32 = l_base_u32 / 2U;

  MyLib_ProcessRecord_Expect(&expected_record, MYLIB_MULT_VALUE_U8);
  MyLib_ProcessRecord_IgnoreArg_rec_pc();

  expected_return = l_base_u32 + 250U;

  actual_return = MyLib_Orchestrate_u32(start_u32, delta_pc_u16);

  TEST_ASSERT_EQUAL_UINT32(expected_return, actual_return);
}

/**
 * @brief Test: g_counter_u32 at upper boundary (500), start_u32 at mid-range (100) with NULL delta_pc_u16, verify return value equals InternalHelper_u32(100,0) + 500.
 */
void test_g_counter_at_upper_boundary_500_start_100_NULL_delta(void) {
  uint32_t start_u32 = 100U;
  const uint16_t *delta_pc_u16 = NULL;
  uint32_t l_base_u32 = 200U;
  uint32_t expected_return;
  uint32_t actual_return;
  MyLib_record_t expected_record;

  g_counter_u32 = 500U;

  InternalHelper_u32_ExpectAndReturn(start_u32, 0U, l_base_u32);

  expected_record.id_u16 = (uint16_t)(l_base_u32 & 0xFFFFU);
  expected_record.value_u32 = l_base_u32 / 2U;

  MyLib_ProcessRecord_Expect(&expected_record, MYLIB_MULT_VALUE_U8);
  MyLib_ProcessRecord_IgnoreArg_rec_pc();

  expected_return = l_base_u32 + 500U;

  actual_return = MyLib_Orchestrate_u32(start_u32, delta_pc_u16);

  TEST_ASSERT_EQUAL_UINT32(expected_return, actual_return);
}

/**
 * @brief Test: Verify MyLib_ProcessRecord is called with l_r.id_u16 = (l_base_u32 & 0xFFFF) and l_r.value_u32 = l_base_u32 / 2 when l_base_u32 is even (start_u32=100, delta NULL).
 */
void test_ProcessRecord_called_with_correct_record_even_base(void) {
  uint32_t start_u32 = 100U;
  const uint16_t *delta_pc_u16 = NULL;
  uint32_t l_base_u32 = 200U;
  uint32_t actual_return;
  MyLib_record_t expected_record;

  g_counter_u32 = 50U;

  InternalHelper_u32_ExpectAndReturn(start_u32, 0U, l_base_u32);

  expected_record.id_u16 = (uint16_t)(l_base_u32 & 0xFFFFU);
  expected_record.value_u32 = l_base_u32 / 2U;

  MyLib_ProcessRecord_Expect(&expected_record, MYLIB_MULT_VALUE_U8);
  MyLib_ProcessRecord_IgnoreArg_rec_pc();

  actual_return = MyLib_Orchestrate_u32(start_u32, delta_pc_u16);

  TEST_ASSERT_EQUAL_UINT32(l_base_u32 + g_counter_u32, actual_return);
}

/**
 * @brief Test: Verify MyLib_ProcessRecord is called with l_r.id_u16 = (l_base_u32 & 0xFFFF) and l_r.value_u32 = l_base_u32 / 2 when l_base_u32 is odd (start_u32=101, delta NULL), ensuring integer division behavior.
 */
void test_ProcessRecord_called_with_correct_record_odd_base(void) {
  uint32_t start_u32 = 101U;
  const uint16_t *delta_pc_u16 = NULL;
  uint32_t l_base_u32 = 201U;
  uint32_t actual_return;
  MyLib_record_t expected_record;

  g_counter_u32 = 50U;

  InternalHelper_u32_ExpectAndReturn(start_u32, 0U, l_base_u32);

  expected_record.id_u16 = (uint16_t)(l_base_u32 & 0xFFFFU);
  expected_record.value_u32 = l_base_u32 / 2U;

  MyLib_ProcessRecord_Expect(&expected_record, MYLIB_MULT_VALUE_U8);
  MyLib_ProcessRecord_IgnoreArg_rec_pc();

  actual_return = MyLib_Orchestrate_u32(start_u32, delta_pc_u16);

  TEST_ASSERT_EQUAL_UINT32(l_base_u32 + g_counter_u32, actual_return);
}

/**
 * @brief Test: Verify MyLib_ProcessRecord is called with second parameter MYLIB_MULT_VALUE_U8 (start_u32=100, delta NULL).
 */
void test_ProcessRecord_called_with_MYLIB_MULT_VALUE_U8(void) {
  uint32_t start_u32 = 100U;
  const uint16_t *delta_pc_u16 = NULL;
  uint32_t l_base_u32 = 200U;
  uint32_t actual_return;

  g_counter_u32 = 50U;

  InternalHelper_u32_ExpectAndReturn(start_u32, 0U, l_base_u32);

  MyLib_ProcessRecord_ExpectAnyArgsAndReturn();

  actual_return = MyLib_Orchestrate_u32(start_u32, delta_pc_u16);

  TEST_ASSERT_EQUAL_UINT32(l_base_u32 + g_counter_u32, actual_return);
}

/**
 * @brief Test: Verify correct record derivation when l_base_u32 exceeds 16-bit range (start_u32=200, delta pointing to 65535), ensuring id_u16 wraps correctly via bitwise AND and value_u32 computed correctly.
 */
void test_record_derivation_when_base_exceeds_16bit_range(void) {
  uint32_t start_u32 = 200U;
  uint16_t delta_value = 65535U;
  const uint16_t *delta_pc_u16 = &delta_value;
  uint32_t l_base_u32 = 80000U;
  uint32_t actual_return;
  MyLib_record_t expected_record;

  g_counter_u32 = 100U;

  InternalHelper_u32_ExpectAndReturn(start_u32, delta_value, l_base_u32);

  expected_record.id_u16 = (uint16_t)(l_base_u32 & 0xFFFFU);
  expected_record.value_u32 = l_base_u32 / 2U;

  MyLib_ProcessRecord_Expect(&expected_record, MYLIB_MULT_VALUE_U8);
  MyLib_ProcessRecord_IgnoreArg_rec_pc();

  actual_return = MyLib_Orchestrate_u32(start_u32, delta_pc_u16);

  TEST_ASSERT_EQUAL_UINT32(l_base_u32 + g_counter_u32, actual_return);
}

/**
 * @brief Test: Verify return value at lower boundary of expected range (0) when InternalHelper_u32 returns 0 and g_counter_u32 is 0.
 */
void test_return_value_at_lower_boundary_0(void) {
  uint32_t start_u32 = 0U;
  const uint16_t *delta_pc_u16 = NULL;
  uint32_t l_base_u32 = 0U;
  uint32_t expected_return;
  uint32_t actual_return;
  MyLib_record_t expected_record;

  g_counter_u32 = 0U;

  InternalHelper_u32_ExpectAndReturn(start_u32, 0U, l_base_u32);

  expected_record.id_u16 = (uint16_t)(l_base_u32 & 0xFFFFU);
  expected_record.value_u32 = l_base_u32 / 2U;

  MyLib_ProcessRecord_Expect(&expected_record, MYLIB_MULT_VALUE_U8);
  MyLib_ProcessRecord_IgnoreArg_rec_pc();

  expected_return = 0U;

  actual_return = MyLib_Orchestrate_u32(start_u32, delta_pc_u16);

  TEST_ASSERT_EQUAL_UINT32(expected_return, actual_return);
}

/**
 * @brief Test: Verify return value at upper boundary of expected range (400) when InternalHelper_u32 and g_counter_u32 sum to 400.
 */
void test_return_value_at_upper_boundary_400(void) {
  uint32_t start_u32 = 100U;
  const uint16_t *delta_pc_u16 = NULL;
  uint32_t l_base_u32 = 300U;
  uint32_t expected_return;
  uint32_t actual_return;
  MyLib_record_t expected_record;

  g_counter_u32 = 100U;

  InternalHelper_u32_ExpectAndReturn(start_u32, 0U, l_base_u32);

  expected_record.id_u16 = (uint16_t)(l_base_u32 & 0xFFFFU);
  expected_record.value_u32 = l_base_u32 / 2U;

  MyLib_ProcessRecord_Expect(&expected_record, MYLIB_MULT_VALUE_U8);
  MyLib_ProcessRecord_IgnoreArg_rec_pc();

  expected_return = 400U;

  actual_return = MyLib_Orchestrate_u32(start_u32, delta_pc_u16);

  TEST_ASSERT_EQUAL_UINT32(expected_return, actual_return);
}