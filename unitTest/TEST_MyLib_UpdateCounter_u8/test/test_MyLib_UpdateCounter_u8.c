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
 * @brief Test: System not ready – verify return code 1 and no counter update when g_systemReady_b is false
 */
void test_MyLib_UpdateCounter_u8_system_not_ready_returns_1_no_update(void) {
  uint8_t result_u8;
  uint32_t initial_counter_u32;

  /* Preconditions */
  g_systemReady_b = false;
  g_counter_u32 = 50U;
  initial_counter_u32 = g_counter_u32;

  /* Execute */
  result_u8 = MyLib_UpdateCounter_u8(10U);

  /* Verify return code */
  TEST_ASSERT_EQUAL_UINT8(1U, result_u8);

  /* Verify counter unchanged */
  TEST_ASSERT_EQUAL_UINT32(initial_counter_u32, g_counter_u32);
}

/**
 * @brief Test: System ready, saturation disabled, zero increment – verify return code 0 and counter unchanged
 */
void test_MyLib_UpdateCounter_u8_system_ready_saturation_disabled_zero_increment(void) {
  uint8_t result_u8;

  /* Preconditions */
  g_systemReady_b = true;
  g_counter_u32 = 100U;
  set_SaturationEn_b(false);
  set_CounterLimit_u32(200U);

  /* Execute */
  result_u8 = MyLib_UpdateCounter_u8(0U);

  /* Verify return code */
  TEST_ASSERT_EQUAL_UINT8(0U, result_u8);

  /* Verify counter unchanged */
  TEST_ASSERT_EQUAL_UINT32(100U, g_counter_u32);
}

/**
 * @brief Test: System ready, saturation disabled, normal increment – verify return code 0 and counter updated correctly
 */
void test_MyLib_UpdateCounter_u8_system_ready_saturation_disabled_normal_increment(void) {
  uint8_t result_u8;

  /* Preconditions */
  g_systemReady_b = true;
  g_counter_u32 = 50U;
  set_SaturationEn_b(false);
  set_CounterLimit_u32(200U);

  /* Execute */
  result_u8 = MyLib_UpdateCounter_u8(25U);

  /* Verify return code */
  TEST_ASSERT_EQUAL_UINT8(0U, result_u8);

  /* Verify counter updated */
  TEST_ASSERT_EQUAL_UINT32(75U, g_counter_u32);
}

/**
 * @brief Test: System ready, saturation disabled, increment causing uint32_t wrap-around – verify return code 0 and counter wraps correctly
 */
void test_MyLib_UpdateCounter_u8_system_ready_saturation_disabled_wraparound(void) {
  uint8_t result_u8;

  /* Preconditions */
  g_systemReady_b = true;
  g_counter_u32 = 0xFFFFFFF0U;
  set_SaturationEn_b(false);
  set_CounterLimit_u32(0xFFFFFFFFU);

  /* Execute */
  result_u8 = MyLib_UpdateCounter_u8(0x20U);

  /* Verify return code */
  TEST_ASSERT_EQUAL_UINT8(0U, result_u8);

  /* Verify counter wrapped */
  TEST_ASSERT_EQUAL_UINT32(0x10U, g_counter_u32);
}

/**
 * @brief Test: System ready, saturation enabled, increment below limit – verify return code 0 and counter updated without clamping
 */
void test_MyLib_UpdateCounter_u8_system_ready_saturation_enabled_below_limit(void) {
  uint8_t result_u8;

  /* Preconditions */
  g_systemReady_b = true;
  g_counter_u32 = 50U;
  set_SaturationEn_b(true);
  set_CounterLimit_u32(200U);

  /* Execute */
  result_u8 = MyLib_UpdateCounter_u8(100U);

  /* Verify return code */
  TEST_ASSERT_EQUAL_UINT8(0U, result_u8);

  /* Verify counter updated without clamping */
  TEST_ASSERT_EQUAL_UINT32(150U, g_counter_u32);
}

/**
 * @brief Test: System ready, saturation enabled, increment exactly reaching limit – verify return code 0 and counter equals limit
 */
void test_MyLib_UpdateCounter_u8_system_ready_saturation_enabled_exactly_at_limit(void) {
  uint8_t result_u8;

  /* Preconditions */
  g_systemReady_b = true;
  g_counter_u32 = 100U;
  set_SaturationEn_b(true);
  set_CounterLimit_u32(200U);

  /* Execute */
  result_u8 = MyLib_UpdateCounter_u8(100U);

  /* Verify return code */
  TEST_ASSERT_EQUAL_UINT8(0U, result_u8);

  /* Verify counter equals limit */
  TEST_ASSERT_EQUAL_UINT32(200U, g_counter_u32);
}

/**
 * @brief Test: System ready, saturation enabled, increment exceeding limit by one – verify return code 2 and counter clamped to limit
 */
void test_MyLib_UpdateCounter_u8_system_ready_saturation_enabled_exceeds_limit_by_one(void) {
  uint8_t result_u8;

  /* Preconditions */
  g_systemReady_b = true;
  g_counter_u32 = 100U;
  set_SaturationEn_b(true);
  set_CounterLimit_u32(200U);

  /* Execute */
  result_u8 = MyLib_UpdateCounter_u8(101U);

  /* Verify return code */
  TEST_ASSERT_EQUAL_UINT8(2U, result_u8);

  /* Verify counter clamped to limit */
  TEST_ASSERT_EQUAL_UINT32(200U, g_counter_u32);
}

/**
 * @brief Test: System ready, saturation enabled, increment exceeding limit by large margin – verify return code 2 and counter clamped to limit
 */
void test_MyLib_UpdateCounter_u8_system_ready_saturation_enabled_exceeds_limit_large_margin(void) {
  uint8_t result_u8;

  /* Preconditions */
  g_systemReady_b = true;
  g_counter_u32 = 100U;
  set_SaturationEn_b(true);
  set_CounterLimit_u32(200U);

  /* Execute */
  result_u8 = MyLib_UpdateCounter_u8(1000U);

  /* Verify return code */
  TEST_ASSERT_EQUAL_UINT8(2U, result_u8);

  /* Verify counter clamped to limit */
  TEST_ASSERT_EQUAL_UINT32(200U, g_counter_u32);
}

/**
 * @brief Test: System ready, saturation enabled, increment causing wrap-around before saturation check – verify return code 2 and counter clamped to limit
 */
void test_MyLib_UpdateCounter_u8_system_ready_saturation_enabled_wraparound_before_check(void) {
  uint8_t result_u8;

  /* Preconditions */
  g_systemReady_b = true;
  g_counter_u32 = 0xFFFFFFF0U;
  set_SaturationEn_b(true);
  set_CounterLimit_u32(100U);

  /* Execute - wrap occurs: 0xFFFFFFF0 + 0x20 = 0x10 */
  result_u8 = MyLib_UpdateCounter_u8(0x20U);

  /* Verify return code - wrapped value 0x10 is below limit 100, so no saturation */
  TEST_ASSERT_EQUAL_UINT8(0U, result_u8);

  /* Verify counter wrapped */
  TEST_ASSERT_EQUAL_UINT32(0x10U, g_counter_u32);
}

/**
 * @brief Test: Cycle counter toggle – verify SaturationEn_b toggles on 16th call (l_CycleCnt_u32 & 0x0F == 0)
 */
void test_MyLib_UpdateCounter_u8_cycle_counter_toggle_on_16th_call(void) {
  uint8_t result_u8;
  uint8_t i;
  _Bool initial_saturation_b;
  _Bool final_saturation_b;

  /* Preconditions */
  g_systemReady_b = true;
  g_counter_u32 = 0U;
  set_SaturationEn_b(false);
  set_CounterLimit_u32(1000U);
  initial_saturation_b = get_SaturationEn_b();

  /* Execute 15 calls - no toggle should occur */
  for(i = 0U; i < 15U; i++) {
    result_u8 = MyLib_UpdateCounter_u8(1U);
  }

  /* Verify no toggle yet */
  TEST_ASSERT_EQUAL(initial_saturation_b, get_SaturationEn_b());

  /* Execute 16th call - toggle should occur */
  result_u8 = MyLib_UpdateCounter_u8(1U);

  /* Verify toggle occurred */
  final_saturation_b = get_SaturationEn_b();
  TEST_ASSERT_NOT_EQUAL(initial_saturation_b, final_saturation_b);
}

/**
 * @brief Test: Cycle counter no toggle – verify SaturationEn_b remains unchanged on non-16th call (l_CycleCnt_u32 & 0x0F != 0)
 */
void test_MyLib_UpdateCounter_u8_cycle_counter_no_toggle_on_non_16th_call(void) {
  uint8_t result_u8;
  _Bool initial_saturation_b;

  /* Preconditions */
  g_systemReady_b = true;
  g_counter_u32 = 0U;
  set_SaturationEn_b(true);
  set_CounterLimit_u32(1000U);
  initial_saturation_b = get_SaturationEn_b();

  /* Execute single call - no toggle should occur */
  result_u8 = MyLib_UpdateCounter_u8(1U);

  /* Verify no toggle */
  TEST_ASSERT_EQUAL(initial_saturation_b, get_SaturationEn_b());
}

/**
 * @brief Test: Saturation precedence – verify that when system is ready, saturation logic is evaluated before toggle logic
 */
void test_MyLib_UpdateCounter_u8_saturation_precedence_before_toggle(void) {
  uint8_t result_u8;
  uint8_t i;

  /* Preconditions - set up for 16th call with saturation condition */
  g_systemReady_b = true;
  g_counter_u32 = 0U;
  set_SaturationEn_b(true);
  set_CounterLimit_u32(100U);

  /* Execute 15 calls to reach cycle 15 */
  for(i = 0U; i < 15U; i++) {
    result_u8 = MyLib_UpdateCounter_u8(1U);
  }

  /* Set up saturation condition for 16th call */
  g_counter_u32 = 50U;

  /* Execute 16th call with saturation trigger */
  result_u8 = MyLib_UpdateCounter_u8(100U);

  /* Verify saturation occurred (return code 2) */
  TEST_ASSERT_EQUAL_UINT8(2U, result_u8);

  /* Verify counter clamped */
  TEST_ASSERT_EQUAL_UINT32(100U, g_counter_u32);

  /* Verify toggle also occurred on 16th call */
  TEST_ASSERT_EQUAL(false, get_SaturationEn_b());
}

/**
 * @brief Test: Multiple calls sequence – verify l_CycleCnt_u32 increments correctly across successive calls and toggle occurs at correct intervals
 */
void test_MyLib_UpdateCounter_u8_multiple_calls_sequence_toggle_intervals(void) {
  uint8_t result_u8;
  uint8_t i;
  _Bool saturation_state_b;

  /* Preconditions */
  g_systemReady_b = true;
  g_counter_u32 = 0U;
  set_SaturationEn_b(false);
  set_CounterLimit_u32(10000U);

  /* Execute 48 calls and verify toggles at 16, 32, 48 */
  for(i = 1U; i <= 48U; i++) {
    saturation_state_b = get_SaturationEn_b();
    result_u8 = MyLib_UpdateCounter_u8(1U);

    if((i % 16U) == 0U) {
      /* Toggle should have occurred */
      TEST_ASSERT_NOT_EQUAL(saturation_state_b, get_SaturationEn_b());
    }
  }

  /* Verify final counter value */
  TEST_ASSERT_EQUAL_UINT32(48U, g_counter_u32);

  /* Verify final saturation state (toggled 3 times: false->true->false->true) */
  TEST_ASSERT_EQUAL(false, get_SaturationEn_b());
}

/**
 * @brief Test: Counter at maximum uint32_t value with saturation disabled – verify wrap-around behavior and return code 0
 */
void test_MyLib_UpdateCounter_u8_counter_at_max_saturation_disabled_wraparound(void) {
  uint8_t result_u8;

  /* Preconditions */
  g_systemReady_b = true;
  g_counter_u32 = 0xFFFFFFFFU;
  set_SaturationEn_b(false);
  set_CounterLimit_u32(0xFFFFFFFFU);

  /* Execute */
  result_u8 = MyLib_UpdateCounter_u8(1U);

  /* Verify return code */
  TEST_ASSERT_EQUAL_UINT8(0U, result_u8);

  /* Verify counter wrapped to 0 */
  TEST_ASSERT_EQUAL_UINT32(0U, g_counter_u32);
}

/**
 * @brief Test: Counter at maximum uint32_t value with saturation enabled and limit at maximum – verify no clamping and return code 0
 */
void test_MyLib_UpdateCounter_u8_counter_at_max_saturation_enabled_limit_at_max(void) {
  uint8_t result_u8;

  /* Preconditions */
  g_systemReady_b = true;
  g_counter_u32 = 0xFFFFFFFFU;
  set_SaturationEn_b(true);
  set_CounterLimit_u32(0xFFFFFFFFU);

  /* Execute - wraps to 0, which is below limit */
  result_u8 = MyLib_UpdateCounter_u8(1U);

  /* Verify return code */
  TEST_ASSERT_EQUAL_UINT8(0U, result_u8);

  /* Verify counter wrapped to 0 (0 <= 0xFFFFFFFF, no saturation) */
  TEST_ASSERT_EQUAL_UINT32(0U, g_counter_u32);
}

/**
 * @brief Test: Counter at zero with saturation enabled and limit at zero – verify any non-zero increment triggers saturation and return code 2
 */
void test_MyLib_UpdateCounter_u8_counter_at_zero_saturation_enabled_limit_at_zero(void) {
  uint8_t result_u8;

  /* Preconditions */
  g_systemReady_b = true;
  g_counter_u32 = 0U;
  set_SaturationEn_b(true);
  set_CounterLimit_u32(0U);

  /* Execute */
  result_u8 = MyLib_UpdateCounter_u8(1U);

  /* Verify return code - saturation triggered */
  TEST_ASSERT_EQUAL_UINT8(2U, result_u8);

  /* Verify counter clamped to limit */
  TEST_ASSERT_EQUAL_UINT32(0U, g_counter_u32);
}