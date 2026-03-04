#include "MyLib.h"
#include "MyLib_UpdateCounter_u8.h"
#include "mock_MyLib.h"
#include "unity.h"
#include <string.h>

/******************************************************************************
 * SECTION 1 — Mock callbacks
 ******************************************************************************/

/* No mock callbacks required for this unit test file */

/******************************************************************************
 * SECTION 2 — setUp() and tearDown()
 ******************************************************************************/

void setUp(void) {
  /* Initialize all global variables to their default state */
  g_counter_u32 = 0U;
  g_systemReady_b = false;

  /* Initialize static variables via setters to default state */
  set_CounterLimit_u32(0U);
  set_SaturationEn_b(false);
}

void tearDown(void) {
  /* No cleanup required */
}

/******************************************************************************
 * SECTION 3 — Test functions
 ******************************************************************************/

/**
 * @brief Test: System not ready – verify return code 1 and no counter update
 */
void test_MyLib_UpdateCounter_u8_system_not_ready_returns_1_no_update(void) {
  uint8_t result_u8;
  uint32_t initial_counter_u32 = 42U;

  g_systemReady_b = false;
  g_counter_u32 = initial_counter_u32;

  result_u8 = MyLib_UpdateCounter_u8(10U);

  TEST_ASSERT_EQUAL_UINT8(1U, result_u8);
  TEST_ASSERT_EQUAL_UINT32(initial_counter_u32, g_counter_u32);
}

/**
 * @brief Test: System ready, saturation disabled, zero increment – verify return code 0 and counter unchanged
 */
void test_MyLib_UpdateCounter_u8_ready_saturation_disabled_zero_increment_returns_0_unchanged(void) {
  uint8_t result_u8;
  uint32_t initial_counter_u32 = 50U;

  g_systemReady_b = true;
  g_counter_u32 = initial_counter_u32;
  set_SaturationEn_b(false);
  set_CounterLimit_u32(100U);

  result_u8 = MyLib_UpdateCounter_u8(0U);

  TEST_ASSERT_EQUAL_UINT8(0U, result_u8);
  TEST_ASSERT_EQUAL_UINT32(initial_counter_u32, g_counter_u32);
}

/**
 * @brief Test: System ready, saturation disabled, small increment within limit – verify return code 0 and counter updated correctly
 */
void test_MyLib_UpdateCounter_u8_ready_saturation_disabled_small_increment_returns_0_updated(void) {
  uint8_t result_u8;

  g_systemReady_b = true;
  g_counter_u32 = 10U;
  set_SaturationEn_b(false);
  set_CounterLimit_u32(100U);

  result_u8 = MyLib_UpdateCounter_u8(25U);

  TEST_ASSERT_EQUAL_UINT8(0U, result_u8);
  TEST_ASSERT_EQUAL_UINT32(35U, g_counter_u32);
}

/**
 * @brief Test: System ready, saturation disabled, increment causing uint32_t wrap-around – verify return code 0 and counter wraps correctly
 */
void test_MyLib_UpdateCounter_u8_ready_saturation_disabled_wraparound_returns_0_wrapped(void) {
  uint8_t result_u8;

  g_systemReady_b = true;
  g_counter_u32 = 0xFFFFFFF0U;
  set_SaturationEn_b(false);
  set_CounterLimit_u32(100U);

  result_u8 = MyLib_UpdateCounter_u8(0x20U);

  TEST_ASSERT_EQUAL_UINT8(0U, result_u8);
  TEST_ASSERT_EQUAL_UINT32(0x10U, g_counter_u32);
}

/**
 * @brief Test: System ready, saturation enabled, increment resulting in new value equal to limit – verify return code 0 and counter updated to limit
 */
void test_MyLib_UpdateCounter_u8_ready_saturation_enabled_new_equals_limit_returns_0_at_limit(void) {
  uint8_t result_u8;

  g_systemReady_b = true;
  g_counter_u32 = 90U;
  set_SaturationEn_b(true);
  set_CounterLimit_u32(100U);

  result_u8 = MyLib_UpdateCounter_u8(10U);

  TEST_ASSERT_EQUAL_UINT8(0U, result_u8);
  TEST_ASSERT_EQUAL_UINT32(100U, g_counter_u32);
}

/**
 * @brief Test: System ready, saturation enabled, increment resulting in new value one above limit – verify return code 2 and counter clamped to limit
 */
void test_MyLib_UpdateCounter_u8_ready_saturation_enabled_new_one_above_limit_returns_2_clamped(void) {
  uint8_t result_u8;

  g_systemReady_b = true;
  g_counter_u32 = 90U;
  set_SaturationEn_b(true);
  set_CounterLimit_u32(100U);

  result_u8 = MyLib_UpdateCounter_u8(11U);

  TEST_ASSERT_EQUAL_UINT8(2U, result_u8);
  TEST_ASSERT_EQUAL_UINT32(100U, g_counter_u32);
}

/**
 * @brief Test: System ready, saturation enabled, increment resulting in new value far above limit – verify return code 2 and counter clamped to limit
 */
void test_MyLib_UpdateCounter_u8_ready_saturation_enabled_new_far_above_limit_returns_2_clamped(void) {
  uint8_t result_u8;

  g_systemReady_b = true;
  g_counter_u32 = 50U;
  set_SaturationEn_b(true);
  set_CounterLimit_u32(100U);

  result_u8 = MyLib_UpdateCounter_u8(1000U);

  TEST_ASSERT_EQUAL_UINT8(2U, result_u8);
  TEST_ASSERT_EQUAL_UINT32(100U, g_counter_u32);
}

/**
 * @brief Test: System ready, saturation enabled, increment causing wrap-around that appears less than limit – verify return code 0 and counter updated to wrapped value
 */
void test_MyLib_UpdateCounter_u8_ready_saturation_enabled_wraparound_below_limit_returns_0_wrapped(void) {
  uint8_t result_u8;

  g_systemReady_b = true;
  g_counter_u32 = 0xFFFFFFF0U;
  set_SaturationEn_b(true);
  set_CounterLimit_u32(100U);

  result_u8 = MyLib_UpdateCounter_u8(0x20U);

  TEST_ASSERT_EQUAL_UINT8(0U, result_u8);
  TEST_ASSERT_EQUAL_UINT32(0x10U, g_counter_u32);
}

/**
 * @brief Test: Cycle counter toggle – verify SaturationEn_b toggles after exactly 16 calls
 */
void test_MyLib_UpdateCounter_u8_cycle_counter_toggle_after_16_calls(void) {
  uint8_t i;
  bool initial_saturation_b;
  bool final_saturation_b;

  g_systemReady_b = true;
  g_counter_u32 = 0U;
  set_SaturationEn_b(false);
  set_CounterLimit_u32(1000U);

  initial_saturation_b = get_SaturationEn_b();

  for(i = 0U; i < 16U; i++) {
    MyLib_UpdateCounter_u8(1U);
  }

  final_saturation_b = get_SaturationEn_b();

  TEST_ASSERT_NOT_EQUAL(initial_saturation_b, final_saturation_b);
}

/**
 * @brief Test: Cycle counter toggle boundary – verify SaturationEn_b does not toggle on call 15 but does toggle on call 16
 */
void test_MyLib_UpdateCounter_u8_cycle_counter_toggle_boundary_call_15_and_16(void) {
  uint8_t i;
  bool initial_saturation_b;
  bool after_15_saturation_b;
  bool after_16_saturation_b;

  g_systemReady_b = true;
  g_counter_u32 = 0U;
  set_SaturationEn_b(false);
  set_CounterLimit_u32(1000U);

  initial_saturation_b = get_SaturationEn_b();

  for(i = 0U; i < 15U; i++) {
    MyLib_UpdateCounter_u8(1U);
  }

  after_15_saturation_b = get_SaturationEn_b();
  TEST_ASSERT_EQUAL(initial_saturation_b, after_15_saturation_b);

  MyLib_UpdateCounter_u8(1U);

  after_16_saturation_b = get_SaturationEn_b();
  TEST_ASSERT_NOT_EQUAL(initial_saturation_b, after_16_saturation_b);
}

/**
 * @brief Test: Multiple sequential updates with saturation disabled – verify counter accumulates correctly over multiple calls
 */
void test_MyLib_UpdateCounter_u8_multiple_updates_saturation_disabled_accumulates(void) {
  uint8_t result_u8;

  g_systemReady_b = true;
  g_counter_u32 = 0U;
  set_SaturationEn_b(false);
  set_CounterLimit_u32(1000U);

  result_u8 = MyLib_UpdateCounter_u8(10U);
  TEST_ASSERT_EQUAL_UINT8(0U, result_u8);
  TEST_ASSERT_EQUAL_UINT32(10U, g_counter_u32);

  result_u8 = MyLib_UpdateCounter_u8(20U);
  TEST_ASSERT_EQUAL_UINT8(0U, result_u8);
  TEST_ASSERT_EQUAL_UINT32(30U, g_counter_u32);

  result_u8 = MyLib_UpdateCounter_u8(15U);
  TEST_ASSERT_EQUAL_UINT8(0U, result_u8);
  TEST_ASSERT_EQUAL_UINT32(45U, g_counter_u32);
}

/**
 * @brief Test: Multiple sequential updates with saturation enabled hitting limit – verify counter saturates and remains clamped across subsequent calls
 */
void test_MyLib_UpdateCounter_u8_multiple_updates_saturation_enabled_hits_limit_remains_clamped(void) {
  uint8_t result_u8;

  g_systemReady_b = true;
  g_counter_u32 = 90U;
  set_SaturationEn_b(true);
  set_CounterLimit_u32(100U);

  result_u8 = MyLib_UpdateCounter_u8(5U);
  TEST_ASSERT_EQUAL_UINT8(0U, result_u8);
  TEST_ASSERT_EQUAL_UINT32(95U, g_counter_u32);

  result_u8 = MyLib_UpdateCounter_u8(10U);
  TEST_ASSERT_EQUAL_UINT8(2U, result_u8);
  TEST_ASSERT_EQUAL_UINT32(100U, g_counter_u32);

  result_u8 = MyLib_UpdateCounter_u8(50U);
  TEST_ASSERT_EQUAL_UINT8(2U, result_u8);
  TEST_ASSERT_EQUAL_UINT32(100U, g_counter_u32);
}

/**
 * @brief Test: System becomes not ready after initial ready state – verify return code 1 and counter not updated
 */
void test_MyLib_UpdateCounter_u8_system_becomes_not_ready_returns_1_no_update(void) {
  uint8_t result_u8;

  g_systemReady_b = true;
  g_counter_u32 = 50U;
  set_SaturationEn_b(false);
  set_CounterLimit_u32(100U);

  result_u8 = MyLib_UpdateCounter_u8(10U);
  TEST_ASSERT_EQUAL_UINT8(0U, result_u8);
  TEST_ASSERT_EQUAL_UINT32(60U, g_counter_u32);

  g_systemReady_b = false;

  result_u8 = MyLib_UpdateCounter_u8(10U);
  TEST_ASSERT_EQUAL_UINT8(1U, result_u8);
  TEST_ASSERT_EQUAL_UINT32(60U, g_counter_u32);
}

/**
 * @brief Test: Saturation enabled, counter at limit, zero increment – verify return code 0 and counter remains at limit
 */
void test_MyLib_UpdateCounter_u8_saturation_enabled_at_limit_zero_increment_returns_0_at_limit(void) {
  uint8_t result_u8;

  g_systemReady_b = true;
  g_counter_u32 = 100U;
  set_SaturationEn_b(true);
  set_CounterLimit_u32(100U);

  result_u8 = MyLib_UpdateCounter_u8(0U);

  TEST_ASSERT_EQUAL_UINT8(0U, result_u8);
  TEST_ASSERT_EQUAL_UINT32(100U, g_counter_u32);
}

/**
 * @brief Test: Saturation enabled, counter at limit, non-zero increment – verify return code 2 and counter remains clamped at limit
 */
void test_MyLib_UpdateCounter_u8_saturation_enabled_at_limit_nonzero_increment_returns_2_clamped(void) {
  uint8_t result_u8;

  g_systemReady_b = true;
  g_counter_u32 = 100U;
  set_SaturationEn_b(true);
  set_CounterLimit_u32(100U);

  result_u8 = MyLib_UpdateCounter_u8(1U);

  TEST_ASSERT_EQUAL_UINT8(2U, result_u8);
  TEST_ASSERT_EQUAL_UINT32(100U, g_counter_u32);
}

/**
 * @brief Test: Counter at maximum uint32_t value, saturation disabled, increment by 1 – verify return code 0 and counter wraps to 0
 */
void test_MyLib_UpdateCounter_u8_counter_at_max_saturation_disabled_increment_1_returns_0_wraps_to_0(void) {
  uint8_t result_u8;

  g_systemReady_b = true;
  g_counter_u32 = 0xFFFFFFFFU;
  set_SaturationEn_b(false);
  set_CounterLimit_u32(100U);

  result_u8 = MyLib_UpdateCounter_u8(1U);

  TEST_ASSERT_EQUAL_UINT8(0U, result_u8);
  TEST_ASSERT_EQUAL_UINT32(0U, g_counter_u32);
}

/**
 * @brief Test: Counter at maximum uint32_t value, saturation enabled with limit at max, increment by 1 – verify return code 2 and counter clamped at limit
 */
void test_MyLib_UpdateCounter_u8_counter_at_max_saturation_enabled_limit_at_max_increment_1_returns_2_clamped(void) {
  uint8_t result_u8;

  g_systemReady_b = true;
  g_counter_u32 = 0xFFFFFFFFU;
  set_SaturationEn_b(true);
  set_CounterLimit_u32(0xFFFFFFFFU);

  result_u8 = MyLib_UpdateCounter_u8(1U);

  TEST_ASSERT_EQUAL_UINT8(2U, result_u8);
  TEST_ASSERT_EQUAL_UINT32(0xFFFFFFFFU, g_counter_u32);
}

/**
 * @brief Test: Limit set to 0, saturation enabled, any positive increment – verify return code 2 and counter clamped to 0
 */
void test_MyLib_UpdateCounter_u8_limit_zero_saturation_enabled_positive_increment_returns_2_clamped_to_0(void) {
  uint8_t result_u8;

  g_systemReady_b = true;
  g_counter_u32 = 0U;
  set_SaturationEn_b(true);
  set_CounterLimit_u32(0U);

  result_u8 = MyLib_UpdateCounter_u8(10U);

  TEST_ASSERT_EQUAL_UINT8(2U, result_u8);
  TEST_ASSERT_EQUAL_UINT32(0U, g_counter_u32);
}

/**
 * @brief Test: Limit set to maximum uint32_t, saturation enabled, increment causing wrap – verify saturation logic correctly compares wrapped value against limit
 */
void test_MyLib_UpdateCounter_u8_limit_max_saturation_enabled_increment_causing_wrap_correct_comparison(void) {
  uint8_t result_u8;

  g_systemReady_b = true;
  g_counter_u32 = 0xFFFFFFF0U;
  set_SaturationEn_b(true);
  set_CounterLimit_u32(0xFFFFFFFFU);

  result_u8 = MyLib_UpdateCounter_u8(0x20U);

  TEST_ASSERT_EQUAL_UINT8(0U, result_u8);
  TEST_ASSERT_EQUAL_UINT32(0x10U, g_counter_u32);
}

/**
 * @brief Test: Cycle counter persistence – verify l_CycleCnt_u32 increments across all calls regardless of return path
 */
void test_MyLib_UpdateCounter_u8_cycle_counter_persistence_increments_all_paths(void) {
  uint8_t i;
  bool initial_saturation_b;
  bool final_saturation_b;

  g_systemReady_b = false;
  g_counter_u32 = 0U;
  set_SaturationEn_b(false);
  set_CounterLimit_u32(100U);

  initial_saturation_b = get_SaturationEn_b();

  for(i = 0U; i < 8U; i++) {
    MyLib_UpdateCounter_u8(1U);
  }

  g_systemReady_b = true;

  for(i = 0U; i < 8U; i++) {
    MyLib_UpdateCounter_u8(1U);
  }

  final_saturation_b = get_SaturationEn_b();

  TEST_ASSERT_NOT_EQUAL(initial_saturation_b, final_saturation_b);
}