#include "MyLib_ProcessRecord.h"
#include "mock_MyLib.h"
#include "unity.h"

/* ========================================================================
 * SECTION 1 — Mock callbacks
 * ======================================================================== */

/* No mock callbacks required for this test suite. */

/* ========================================================================
 * SECTION 2 — setUp() and tearDown()
 * ======================================================================== */

void setUp(void) {
  g_counter_u32 = 0U;
  g_record.id_u16 = 0U;
  g_record.value_u32 = 0U;
  g_systemReady_b = false;
}

void tearDown(void) {
}

/* ========================================================================
 * SECTION 3 — Test functions
 * ======================================================================== */

/**
 * @brief Test: rec_pc is NULL – function returns immediately with no side effects on g_counter_u32 or invocation of MyLib_ComputeAdjustedValue_u32.
 */
void test_MyLib_ProcessRecord_rec_pc_NULL_returns_immediately_no_side_effects(void) {
  uint32_t initial_counter = g_counter_u32;

  MyLib_ProcessRecord(NULL, 5U);

  TEST_ASSERT_EQUAL_UINT32(initial_counter, g_counter_u32);
}

/**
 * @brief Test: rec_pc valid, multiplier_u8 = 0 – l_acc_u32 is 0, g_counter_u32 unchanged, MyLib_ComputeAdjustedValue_u32 called with l_acc_u32=0.
 */
void test_MyLib_ProcessRecord_multiplier_0_no_accumulation_counter_unchanged(void) {
  MyLib_record_t rec;
  rec.id_u16 = 1U;
  rec.value_u32 = 100U;

  uint32_t initial_counter = g_counter_u32;

  MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(0U, (const uint16_t *)&(uint8_t){0U}, 0U);
  MyLib_ComputeAdjustedValue_u32_IgnoreArg_delta_pc_u16();

  MyLib_ProcessRecord(&rec, 0U);

  TEST_ASSERT_EQUAL_UINT32(initial_counter, g_counter_u32);
}

/**
 * @brief Test: rec_pc valid, multiplier_u8 = 1 – l_acc_u32 equals rec_pc->value_u32, g_counter_u32 incremented by that value, MyLib_ComputeAdjustedValue_u32 called with l_acc_u32.
 */
void test_MyLib_ProcessRecord_multiplier_1_single_accumulation(void) {
  MyLib_record_t rec;
  rec.id_u16 = 2U;
  rec.value_u32 = 50U;

  uint32_t initial_counter = g_counter_u32;
  uint32_t expected_acc = rec.value_u32;

  MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(expected_acc, (const uint16_t *)&(uint8_t){1U}, 0U);
  MyLib_ComputeAdjustedValue_u32_IgnoreArg_delta_pc_u16();

  MyLib_ProcessRecord(&rec, 1U);

  TEST_ASSERT_EQUAL_UINT32(initial_counter + expected_acc, g_counter_u32);
}

/**
 * @brief Test: rec_pc valid, multiplier_u8 = 2 – l_acc_u32 equals 2 * rec_pc->value_u32, g_counter_u32 incremented accordingly, MyLib_ComputeAdjustedValue_u32 called with l_acc_u32.
 */
void test_MyLib_ProcessRecord_multiplier_2_bounded_loop_accumulation(void) {
  MyLib_record_t rec;
  rec.id_u16 = 3U;
  rec.value_u32 = 75U;

  uint32_t initial_counter = g_counter_u32;
  uint32_t expected_acc = 2U * rec.value_u32;

  MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(expected_acc, (const uint16_t *)&(uint8_t){2U}, 0U);
  MyLib_ComputeAdjustedValue_u32_IgnoreArg_delta_pc_u16();

  MyLib_ProcessRecord(&rec, 2U);

  TEST_ASSERT_EQUAL_UINT32(initial_counter + expected_acc, g_counter_u32);
}

/**
 * @brief Test: rec_pc valid, multiplier_u8 = 255 (upper boundary) – l_acc_u32 equals 255 * rec_pc->value_u32, g_counter_u32 incremented accordingly, MyLib_ComputeAdjustedValue_u32 called with l_acc_u32.
 */
void test_MyLib_ProcessRecord_multiplier_255_upper_boundary(void) {
  MyLib_record_t rec;
  rec.id_u16 = 4U;
  rec.value_u32 = 10U;

  uint32_t initial_counter = g_counter_u32;
  uint32_t expected_acc = 255U * rec.value_u32;

  MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(expected_acc, (const uint16_t *)&(uint8_t){255U}, 0U);
  MyLib_ComputeAdjustedValue_u32_IgnoreArg_delta_pc_u16();

  MyLib_ProcessRecord(&rec, 255U);

  TEST_ASSERT_EQUAL_UINT32(initial_counter + expected_acc, g_counter_u32);
}

/**
 * @brief Test: rec_pc valid, multiplier_u8 = 128 (mid-range default case) – l_acc_u32 equals 128 * rec_pc->value_u32, g_counter_u32 incremented accordingly, MyLib_ComputeAdjustedValue_u32 called with l_acc_u32.
 */
void test_MyLib_ProcessRecord_multiplier_128_mid_range_default_case(void) {
  MyLib_record_t rec;
  rec.id_u16 = 5U;
  rec.value_u32 = 20U;

  uint32_t initial_counter = g_counter_u32;
  uint32_t expected_acc = 128U * rec.value_u32;

  MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(expected_acc, (const uint16_t *)&(uint8_t){128U}, 0U);
  MyLib_ComputeAdjustedValue_u32_IgnoreArg_delta_pc_u16();

  MyLib_ProcessRecord(&rec, 128U);

  TEST_ASSERT_EQUAL_UINT32(initial_counter + expected_acc, g_counter_u32);
}

/**
 * @brief Test: rec_pc valid with value_u32 = 0, multiplier_u8 = 10 – l_acc_u32 is 0, g_counter_u32 unchanged, MyLib_ComputeAdjustedValue_u32 called with l_acc_u32=0.
 */
void test_MyLib_ProcessRecord_value_u32_zero_multiplier_10_accumulation_zero(void) {
  MyLib_record_t rec;
  rec.id_u16 = 6U;
  rec.value_u32 = 0U;

  uint32_t initial_counter = g_counter_u32;
  uint32_t expected_acc = 0U;

  MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(expected_acc, (const uint16_t *)&(uint8_t){10U}, 0U);
  MyLib_ComputeAdjustedValue_u32_IgnoreArg_delta_pc_u16();

  MyLib_ProcessRecord(&rec, 10U);

  TEST_ASSERT_EQUAL_UINT32(initial_counter, g_counter_u32);
}

/**
 * @brief Test: rec_pc valid with value_u32 = UINT32_MAX, multiplier_u8 = 1 – l_acc_u32 equals UINT32_MAX, g_counter_u32 incremented by UINT32_MAX, MyLib_ComputeAdjustedValue_u32 called with l_acc_u32.
 */
void test_MyLib_ProcessRecord_value_u32_max_multiplier_1(void) {
  MyLib_record_t rec;
  rec.id_u16 = 7U;
  rec.value_u32 = UINT32_MAX;

  uint32_t initial_counter = g_counter_u32;
  uint32_t expected_acc = UINT32_MAX;

  MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(expected_acc, (const uint16_t *)&(uint8_t){1U}, 0U);
  MyLib_ComputeAdjustedValue_u32_IgnoreArg_delta_pc_u16();

  MyLib_ProcessRecord(&rec, 1U);

  TEST_ASSERT_EQUAL_UINT32(initial_counter + expected_acc, g_counter_u32);
}

/**
 * @brief Test: rec_pc valid with value_u32 = UINT32_MAX, multiplier_u8 = 2 – l_acc_u32 wraps around (2 * UINT32_MAX mod 2^32), g_counter_u32 incremented by wrapped value, MyLib_ComputeAdjustedValue_u32 called with wrapped l_acc_u32.
 */
void test_MyLib_ProcessRecord_value_u32_max_multiplier_2_wraparound(void) {
  MyLib_record_t rec;
  rec.id_u16 = 8U;
  rec.value_u32 = UINT32_MAX;

  uint32_t initial_counter = g_counter_u32;
  uint32_t expected_acc = (uint32_t)(2ULL * UINT32_MAX);

  MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(expected_acc, (const uint16_t *)&(uint8_t){2U}, 0U);
  MyLib_ComputeAdjustedValue_u32_IgnoreArg_delta_pc_u16();

  MyLib_ProcessRecord(&rec, 2U);

  TEST_ASSERT_EQUAL_UINT32(initial_counter + expected_acc, g_counter_u32);
}

/**
 * @brief Test: rec_pc valid with value_u32 causing g_counter_u32 to wrap around from near UINT32_MAX – verify wrap-around behavior is correct and MyLib_ComputeAdjustedValue_u32 is invoked.
 */
void test_MyLib_ProcessRecord_g_counter_u32_wraparound_from_near_max(void) {
  MyLib_record_t rec;
  rec.id_u16 = 9U;
  rec.value_u32 = 100U;

  g_counter_u32 = UINT32_MAX - 50U;
  uint32_t initial_counter = g_counter_u32;
  uint32_t expected_acc = rec.value_u32;

  MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(expected_acc, (const uint16_t *)&(uint8_t){1U}, 0U);
  MyLib_ComputeAdjustedValue_u32_IgnoreArg_delta_pc_u16();

  MyLib_ProcessRecord(&rec, 1U);

  TEST_ASSERT_EQUAL_UINT32(initial_counter + expected_acc, g_counter_u32);
}

/**
 * @brief Test: rec_pc valid, multiplier_u8 = 1, g_counter_u32 initially non-zero – verify g_counter_u32 is incremented correctly and MyLib_ComputeAdjustedValue_u32 is called.
 */
void test_MyLib_ProcessRecord_multiplier_1_g_counter_u32_initially_non_zero(void) {
  MyLib_record_t rec;
  rec.id_u16 = 10U;
  rec.value_u32 = 200U;

  g_counter_u32 = 500U;
  uint32_t initial_counter = g_counter_u32;
  uint32_t expected_acc = rec.value_u32;

  MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(expected_acc, (const uint16_t *)&(uint8_t){1U}, 0U);
  MyLib_ComputeAdjustedValue_u32_IgnoreArg_delta_pc_u16();

  MyLib_ProcessRecord(&rec, 1U);

  TEST_ASSERT_EQUAL_UINT32(initial_counter + expected_acc, g_counter_u32);
}

/**
 * @brief Test: rec_pc valid, multiplier_u8 = 0, g_counter_u32 initially non-zero – verify g_counter_u32 remains unchanged and MyLib_ComputeAdjustedValue_u32 is called with l_acc_u32=0.
 */
void test_MyLib_ProcessRecord_multiplier_0_g_counter_u32_initially_non_zero(void) {
  MyLib_record_t rec;
  rec.id_u16 = 11U;
  rec.value_u32 = 300U;

  g_counter_u32 = 1000U;
  uint32_t initial_counter = g_counter_u32;

  MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(0U, (const uint16_t *)&(uint8_t){0U}, 0U);
  MyLib_ComputeAdjustedValue_u32_IgnoreArg_delta_pc_u16();

  MyLib_ProcessRecord(&rec, 0U);

  TEST_ASSERT_EQUAL_UINT32(initial_counter, g_counter_u32);
}