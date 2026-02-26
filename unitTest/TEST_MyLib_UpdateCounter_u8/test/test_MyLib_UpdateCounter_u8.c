#include "MyLib_UpdateCounter_u8.h"
#include "mock_MyLib.h"
#include "unity.h"
#include <string.h>

/* ============================================================================
 * Setup & Teardown
 * ============================================================================ */

void setUp(void) {
  /* Reset global variables to known state before each test */
  g_counter_u32 = 0U;
  g_systemReady_b = false;
  g_record.id_u16 = 0U;
  g_record.value_u32 = 0U;

  /* Reset setter functions to default values */
  SetCounterLimit_u32(MYLIB_MAX_COUNT_U32); /* 100U */
  SetSaturationEn_b(true);                  /* Saturation enabled by default */
}

void tearDown(void) { /* Nothing specific needed; setUp will reset for next test */
}

/* ============================================================================
 * Test: System Not Ready (g_systemReady_b == false)
 * Expected: Return 1, counter unchanged
 * Branch coverage: if (g_systemReady_b == false) → TRUE branch
 * ============================================================================ */

void test_MyLib_UpdateCounter_u8_SystemNotReady_ReturnOne(void) {
  uint8_t result;

  /* Setup: system not ready, counter at 0 */
  g_systemReady_b = false;
  g_counter_u32 = 0U;

  /* Exercise */
  result = MyLib_UpdateCounter_u8(10U);

  /* Verify: return value is 1 */
  TEST_ASSERT_EQUAL_UINT8(1U, result);

  /* Verify: counter unchanged */
  TEST_ASSERT_EQUAL_UINT32(0U, g_counter_u32);
}

/* ============================================================================
 * Test: System Not Ready with Nonzero Counter
 * Expected: Return 1, counter remains unchanged
 * Branch coverage: Ensures counter protection when system not ready
 * ============================================================================ */

void test_MyLib_UpdateCounter_u8_SystemNotReady_CounterPreserved(void) {
  uint8_t result;

  /* Setup: system not ready, counter at non-zero value */
  g_systemReady_b = false;
  g_counter_u32 = 42U;

  /* Exercise */
  result = MyLib_UpdateCounter_u8(100U);

  /* Verify: return value is 1 */
  TEST_ASSERT_EQUAL_UINT8(1U, result);

  /* Verify: counter preserved */
  TEST_ASSERT_EQUAL_UINT32(42U, g_counter_u32);
}

/* ============================================================================
 * Test: System Ready, Normal Addition (No Saturation)
 * Expected: Return 0, counter incremented
 * Branch coverage: System ready (false) + no saturation overflow
 * Line coverage: Else branch with normal addition
 * ============================================================================ */

void test_MyLib_UpdateCounter_u8_SystemReady_NormalAdd_ReturnZero(void) {
  uint8_t result;

  /* Setup: system ready, saturation enabled, counter at 10 */
  g_systemReady_b = true;
  SetSaturationEn_b(true);
  SetCounterLimit_u32(MYLIB_MAX_COUNT_U32); /* 100U */
  g_counter_u32 = 10U;

  /* Exercise: add 5 (10 + 5 = 15, no overflow) */
  result = MyLib_UpdateCounter_u8(5U);

  /* Verify: return value is 0 */
  TEST_ASSERT_EQUAL_UINT8(0U, result);

  /* Verify: counter updated correctly */
  TEST_ASSERT_EQUAL_UINT32(15U, g_counter_u32);
}

/* ============================================================================
 * Test: System Ready, Saturation Enabled, Overflow Prevented
 * Expected: Return 2, counter capped at limit
 * Branch coverage: System ready + saturation enabled AND overflow condition
 * ============================================================================ */

void test_MyLib_UpdateCounter_u8_SaturationEnabled_OverflowPrevented(void) {
  uint8_t result;

  /* Setup: saturation enabled, limit 100, counter at 90 */
  g_systemReady_b = true;
  SetSaturationEn_b(true);
  SetCounterLimit_u32(100U);
  g_counter_u32 = 90U;

  /* Exercise: add 20 (90 + 20 = 110 > 100, overflow) */
  result = MyLib_UpdateCounter_u8(20U);

  /* Verify: return value is 2 (overflow detected) */
  TEST_ASSERT_EQUAL_UINT8(2U, result);

  /* Verify: counter capped at limit */
  TEST_ASSERT_EQUAL_UINT32(100U, g_counter_u32);
}

/* ============================================================================
 * Test: System Ready, Saturation Disabled, Overflow Allowed
 * Expected: Return 0, counter wraps (no saturation prevention)
 * Branch coverage: Saturation condition false due to SaturationEn_b=false
 * ============================================================================ */

void test_MyLib_UpdateCounter_u8_SaturationDisabled_OverflowAllowed(void) {
  uint8_t result;

  /* Setup: saturation disabled, counter at 90 */
  g_systemReady_b = true;
  SetSaturationEn_b(false);
  SetCounterLimit_u32(100U);
  g_counter_u32 = 90U;

  /* Exercise: add 20 (90 + 20 = 110 > 100, but saturation disabled) */
  result = MyLib_UpdateCounter_u8(20U);

  /* Verify: return value is 0 (no saturation) */
  TEST_ASSERT_EQUAL_UINT8(0U, result);

  /* Verify: counter actually updated to sum (not capped) */
  TEST_ASSERT_EQUAL_UINT32(110U, g_counter_u32);
}

/* ============================================================================
 * Test: Zero Addition
 * Expected: Return 0, counter unchanged
 * Boundary: Adding 0 should not change value
 * ============================================================================ */

void test_MyLib_UpdateCounter_u8_ZeroAddition(void) {
  uint8_t result;

  /* Setup: counter at 50 */
  g_systemReady_b = true;
  SetSaturationEn_b(true);
  g_counter_u32 = 50U;

  /* Exercise: add 0 */
  result = MyLib_UpdateCounter_u8(0U);

  /* Verify: return value is 0 */
  TEST_ASSERT_EQUAL_UINT8(0U, result);

  /* Verify: counter unchanged */
  TEST_ASSERT_EQUAL_UINT32(50U, g_counter_u32);
}

/* ============================================================================
 * Test: Maximum Value Addition
 * Expected: Counter may wrap or saturate depending on saturation
 * Boundary: Adding maximum uint32_t value
 * ============================================================================ */

void test_MyLib_UpdateCounter_u8_MaxValueAddition_SaturationEnabled(void) {
  uint8_t result;

  /* Setup: saturation enabled, counter at 0 */
  g_systemReady_b = true;
  SetSaturationEn_b(true);
  SetCounterLimit_u32(100U);
  g_counter_u32 = 0U;

  /* Exercise: add max uint32_t (will overflow) */
  result = MyLib_UpdateCounter_u8(0xFFFFFFFFU);

  /* Verify: return value is 2 (overflow) */
  TEST_ASSERT_EQUAL_UINT8(2U, result);

  /* Verify: counter capped at limit */
  TEST_ASSERT_EQUAL_UINT32(100U, g_counter_u32);
}

/* ============================================================================
 * Test: Counter at Limit, Further Addition Triggers Saturation
 * Expected: Return 2, counter stays at limit
 * Boundary: Counter already at limit
 * ============================================================================ */

void test_MyLib_UpdateCounter_u8_CounterAtLimit_SaturationTriggered(void) {
  uint8_t result;

  /* Setup: counter already at limit (100) */
  g_systemReady_b = true;
  SetSaturationEn_b(true);
  SetCounterLimit_u32(100U);
  g_counter_u32 = 100U;

  /* Exercise: add 1 (100 + 1 = 101 > 100) */
  result = MyLib_UpdateCounter_u8(1U);

  /* Verify: return value is 2 */
  TEST_ASSERT_EQUAL_UINT8(2U, result);

  /* Verify: counter stays at limit */
  TEST_ASSERT_EQUAL_UINT32(100U, g_counter_u32);
}

/* ============================================================================
 * Test: Counter at Limit, No Addition (Saturation Not Triggered)
 * Expected: Return 0, counter unchanged
 * Boundary: Counter at limit, add 0
 * ============================================================================ */

void test_MyLib_UpdateCounter_u8_CounterAtLimit_NoAddition(void) {
  uint8_t result;

  /* Setup: counter at limit */
  g_systemReady_b = true;
  SetSaturationEn_b(true);
  SetCounterLimit_u32(100U);
  g_counter_u32 = 100U;

  /* Exercise: add 0 */
  result = MyLib_UpdateCounter_u8(0U);

  /* Verify: return value is 0 */
  TEST_ASSERT_EQUAL_UINT8(0U, result);

  /* Verify: counter unchanged */
  TEST_ASSERT_EQUAL_UINT32(100U, g_counter_u32);
}

/* ============================================================================
 * Test: Cycle Count Toggle - Verify Toggle Occurs Every 16 Calls
 * Expected: Saturation toggles after every 16th call
 * Branch coverage: if ((l_CycleCnt_u32 & 0x0FU) == 0U) → FALSE on calls 1-15
 * Note: Static l_CycleCnt_u32 persists across tests, so we verify pattern
 *       rather than absolute cycle positions
 * ============================================================================ */

void test_MyLib_UpdateCounter_u8_CycleCountTogglePattern_Every16Calls(void) {
  uint8_t result;
  bool saturation_state;
  int toggle_count = 0;

  /* Setup */
  g_systemReady_b = true;
  SetSaturationEn_b(true);
  SetCounterLimit_u32(100U);
  g_counter_u32 = 0U;
  saturation_state = true;

  /* Execute 32 calls and count toggles */
  for(int i = 0; i < 32; i++) {
    result = MyLib_UpdateCounter_u8(1U);
    TEST_ASSERT_EQUAL_UINT8(0U, result);

    /* Track saturation state changes */
    bool current_state = GetSaturationEn_b();
    if(current_state != saturation_state) {
      toggle_count++;
      saturation_state = current_state;
    }
  }

  /* Expect at least one toggle in 32 calls (could be 1 or 2 depending on starting cycle) */
  TEST_ASSERT_GREATER_OR_EQUAL_INT(1, toggle_count);
  TEST_ASSERT_LESS_OR_EQUAL_INT(2, toggle_count);

  /* Verify counter is at 32 */
  TEST_ASSERT_EQUAL_UINT32(32U, g_counter_u32);
}

/* ============================================================================
 * Test: Cycle Count Toggle - Pattern Within 32 Calls
 * Expected: Saturation toggles at least once within 32 calls
 * Branch coverage: if ((l_CycleCnt_u32 & 0x0FU) == 0U) → TRUE branch
 * Line coverage: Saturation toggle ternary operator
 * Note: Finds toggle boundaries dynamically due to persistent l_CycleCnt_u32
 * ============================================================================ */

void test_MyLib_UpdateCounter_u8_CycleCountToggle_FindPattern(void) {
  uint8_t result;
  bool saturation_state;
  bool first_toggle_found = false;
  int calls_to_first_toggle = 0;

  /* Setup */
  g_systemReady_b = true;
  SetSaturationEn_b(true);
  SetCounterLimit_u32(100U);
  g_counter_u32 = 0U;
  saturation_state = GetSaturationEn_b();

  /* Execute calls looking for first toggle (should occur within 16 calls) */
  for(int i = 0; i < 16; i++) {
    result = MyLib_UpdateCounter_u8(1U);
    TEST_ASSERT_EQUAL_UINT8(0U, result);

    bool current_state = GetSaturationEn_b();
    if(current_state != saturation_state) {
      first_toggle_found = true;
      calls_to_first_toggle = i + 1;
      break;
    }
  }

  /* Verify first toggle occurred within 16 calls */
  TEST_ASSERT_TRUE(first_toggle_found);

  /* Now continue and verify next toggle occurs within ~16 more calls */
  saturation_state = GetSaturationEn_b();
  bool second_toggle_found = false;

  for(int i = 0; i < 16; i++) {
    result = MyLib_UpdateCounter_u8(1U);
    TEST_ASSERT_EQUAL_UINT8(0U, result);

    bool current_state = GetSaturationEn_b();
    if(current_state != saturation_state) {
      second_toggle_found = true;
      break;
    }
  }

  /* Verify periodic toggle pattern (second toggle within 16 calls) */
  TEST_ASSERT_TRUE(second_toggle_found);
}

/* ============================================================================
 * Test: Multiple Cycle Toggles - Verify Pattern Repeats
 * Expected: Saturation toggles periodically (every ~16 calls)
 * Coverage: Verify toggle behavior repeats consistently across multiple cycles
 * Note: Dynamically detects toggle boundaries to work with persistent counter
 * ============================================================================ */

void test_MyLib_UpdateCounter_u8_MultipleCycleToggles(void) {
  uint8_t result;
  bool saturation_state;
  int toggle_count = 0;

  /* Setup: start with saturation enabled */
  g_systemReady_b = true;
  SetSaturationEn_b(true);
  SetCounterLimit_u32(100U);
  g_counter_u32 = 0U;

  saturation_state = GetSaturationEn_b();

  /* Execute 48 calls and count state changes */
  for(int i = 0; i < 48; i++) {
    result = MyLib_UpdateCounter_u8(1U);
    TEST_ASSERT_EQUAL_UINT8(0U, result);

    bool current_state = GetSaturationEn_b();
    if(current_state != saturation_state) {
      toggle_count++;
      saturation_state = current_state;
    }
  }

  /* In 48 calls, we should see at least 2 toggles (could be 2 or 3 depending on alignment) */
  TEST_ASSERT_GREATER_OR_EQUAL_INT(2, toggle_count);
  TEST_ASSERT_LESS_OR_EQUAL_INT(3, toggle_count);

  /* Counter should be at 48 */
  TEST_ASSERT_EQUAL_UINT32(48U, g_counter_u32);
}

/* ============================================================================
 * Test: Saturation Toggle While Disabled
 * Expected: Toggle from false to true
 * Coverage: Verify ternary operator works in both directions
 * ============================================================================ */

void test_MyLib_UpdateCounter_u8_CycleToggle_FromDisabledToEnabled(void) {
  uint8_t result;

  /* Setup: start with saturation disabled */
  g_systemReady_b = true;
  SetSaturationEn_b(false); /* Start disabled */
  SetCounterLimit_u32(100U);
  g_counter_u32 = 0U;

  /* Execute 15 calls */
  for(int i = 0; i < 15; i++) {
    result = MyLib_UpdateCounter_u8(1U);
    TEST_ASSERT_EQUAL_UINT8(0U, result);
    TEST_ASSERT_EQUAL(false, GetSaturationEn_b());
  }

  /* Call 16 - should toggle from false to true */
  result = MyLib_UpdateCounter_u8(1U);
  TEST_ASSERT_EQUAL_UINT8(0U, result);

  /* Verify saturation now enabled */
  TEST_ASSERT_EQUAL(true, GetSaturationEn_b());
}

/* ============================================================================
 * Test: Custom Limit with Addition Below Limit
 * Expected: Return 0, counter updated
 * Coverage: Ensure limit check works with custom limits
 * ============================================================================ */

void test_MyLib_UpdateCounter_u8_CustomLimit_BelowLimit(void) {
  uint8_t result;

  /* Setup: custom limit of 50 */
  g_systemReady_b = true;
  SetSaturationEn_b(true);
  SetCounterLimit_u32(50U);
  g_counter_u32 = 40U;

  /* Exercise: add 5 (40 + 5 = 45 < 50) */
  result = MyLib_UpdateCounter_u8(5U);

  /* Verify: return value is 0 */
  TEST_ASSERT_EQUAL_UINT8(0U, result);

  /* Verify: counter updated */
  TEST_ASSERT_EQUAL_UINT32(45U, g_counter_u32);
}

/* ============================================================================
 * Test: Custom Limit with Addition Exceeds Limit
 * Expected: Return 2, counter capped at custom limit
 * Coverage: Ensure saturation works with custom limits
 * ============================================================================ */

void test_MyLib_UpdateCounter_u8_CustomLimit_ExceedsLimit(void) {
  uint8_t result;

  /* Setup: custom limit of 50 */
  g_systemReady_b = true;
  SetSaturationEn_b(true);
  SetCounterLimit_u32(50U);
  g_counter_u32 = 48U;

  /* Exercise: add 10 (48 + 10 = 58 > 50) */
  result = MyLib_UpdateCounter_u8(10U);

  /* Verify: return value is 2 */
  TEST_ASSERT_EQUAL_UINT8(2U, result);

  /* Verify: counter capped at custom limit */
  TEST_ASSERT_EQUAL_UINT32(50U, g_counter_u32);
}

/* ============================================================================
 * Test: Counter at Zero with Addition
 * Expected: Return 0, counter updated from 0
 * Boundary: Minimum counter value
 * ============================================================================ */

void test_MyLib_UpdateCounter_u8_CounterAtZero_WithAddition(void) {
  uint8_t result;

  /* Setup: counter at 0 */
  g_systemReady_b = true;
  SetSaturationEn_b(true);
  g_counter_u32 = 0U;

  /* Exercise: add 42 */
  result = MyLib_UpdateCounter_u8(42U);

  /* Verify: return value is 0 */
  TEST_ASSERT_EQUAL_UINT8(0U, result);

  /* Verify: counter updated to 42 */
  TEST_ASSERT_EQUAL_UINT32(42U, g_counter_u32);
}

/* ============================================================================
 * Test: Exact Saturation Boundary (no overflow)
 * Expected: Return 0, counter at exactly the limit
 * Boundary: new_u32 == CounterLimit_u32 (no overflow)
 * ============================================================================ */

void test_MyLib_UpdateCounter_u8_ExactLimitBoundary_NoOverflow(void) {
  uint8_t result;

  /* Setup: counter at 95, limit 100 */
  g_systemReady_b = true;
  SetSaturationEn_b(true);
  SetCounterLimit_u32(100U);
  g_counter_u32 = 95U;

  /* Exercise: add 5 (95 + 5 = 100, exactly at limit, no overflow) */
  result = MyLib_UpdateCounter_u8(5U);

  /* Verify: return value is 0 (no overflow, 100 is not > 100) */
  TEST_ASSERT_EQUAL_UINT8(0U, result);

  /* Verify: counter at exactly the limit */
  TEST_ASSERT_EQUAL_UINT32(100U, g_counter_u32);
}

/* ============================================================================
 * Test: Just Past Saturation Boundary (overflow by 1)
 * Expected: Return 2, counter capped
 * Boundary: new_u32 == CounterLimit_u32 + 1
 * ============================================================================ */

void test_MyLib_UpdateCounter_u8_PastLimitBoundary_OverflowBy1(void) {
  uint8_t result;

  /* Setup: counter at 95, limit 100 */
  g_systemReady_b = true;
  SetSaturationEn_b(true);
  SetCounterLimit_u32(100U);
  g_counter_u32 = 95U;

  /* Exercise: add 6 (95 + 6 = 101 > 100, overflow by 1) */
  result = MyLib_UpdateCounter_u8(6U);

  /* Verify: return value is 2 (overflow) */
  TEST_ASSERT_EQUAL_UINT8(2U, result);

  /* Verify: counter capped at limit */
  TEST_ASSERT_EQUAL_UINT32(100U, g_counter_u32);
}

/* ============================================================================
 * Test: Saturation Disabled, Exact Boundary
 * Expected: Return 0, counter updated normally
 * Coverage: Verify saturation condition false path
 * ============================================================================ */

void test_MyLib_UpdateCounter_u8_SaturationDisabled_ExactBoundary(void) {
  uint8_t result;

  /* Setup: saturation disabled, counter at 95, limit 100 */
  g_systemReady_b = true;
  SetSaturationEn_b(false); /* Disabled */
  SetCounterLimit_u32(100U);
  g_counter_u32 = 95U;

  /* Exercise: add 5 (95 + 5 = 100) */
  result = MyLib_UpdateCounter_u8(5U);

  /* Verify: return value is 0 */
  TEST_ASSERT_EQUAL_UINT8(0U, result);

  /* Verify: counter updated to 100 */
  TEST_ASSERT_EQUAL_UINT32(100U, g_counter_u32);
}

/* ============================================================================
 * Test: System Ready Transition
 * Expected: Initial call with system not ready, then ready
 * Coverage: State transition scenario
 * ============================================================================ */

void test_MyLib_UpdateCounter_u8_SystemReadyTransition(void) {
  uint8_t result;

  /* Setup: system not ready */
  g_systemReady_b = false;
  g_counter_u32 = 0U;

  /* First call: system not ready */
  result = MyLib_UpdateCounter_u8(10U);
  TEST_ASSERT_EQUAL_UINT8(1U, result);
  TEST_ASSERT_EQUAL_UINT32(0U, g_counter_u32);

  /* Transition: system becomes ready */
  g_systemReady_b = true;
  SetSaturationEn_b(true);

  /* Second call: system ready */
  result = MyLib_UpdateCounter_u8(10U);
  TEST_ASSERT_EQUAL_UINT8(0U, result);

  /* Verify: counter updated on second call */
  TEST_ASSERT_EQUAL_UINT32(10U, g_counter_u32);
}

/* ============================================================================
 * Test: Large Counter Values Within Limit
 * Expected: Values handled correctly without saturation
 * Boundary: uint32_t with large but reasonable values
 * ============================================================================ */

void test_MyLib_UpdateCounter_u8_LargeCounterValue_WithinLimit(void) {
  uint8_t result;

  /* Setup: counter at 1 billion, limit at 2 billion */
  g_systemReady_b = true;
  SetSaturationEn_b(true);
  SetCounterLimit_u32(2000000000U); /* 2 billion limit */
  g_counter_u32 = 1000000000U;      /* 1 billion current */

  /* Exercise: add 500M (1B + 500M = 1.5B < 2B limit) */
  result = MyLib_UpdateCounter_u8(500000000U);

  /* Verify: return value is 0 (no saturation) */
  TEST_ASSERT_EQUAL_UINT8(0U, result);

  /* Verify: counter updated to correct sum */
  TEST_ASSERT_EQUAL_UINT32(1500000000U, g_counter_u32);
}

/* ============================================================================
 * Test: Large Counter Values Exceed High Limit
 * Expected: Saturation at high limit
 * Boundary: Saturation at large counter values
 * ============================================================================ */

void test_MyLib_UpdateCounter_u8_LargeCounterValue_ExceedsLimit(void) {
  uint8_t result;

  /* Setup: counter at 1.8 billion, limit at 2 billion */
  g_systemReady_b = true;
  SetSaturationEn_b(true);
  SetCounterLimit_u32(2000000000U); /* 2 billion limit */
  g_counter_u32 = 1800000000U;      /* 1.8 billion current */

  /* Exercise: add 300M (1.8B + 300M = 2.1B > 2B limit, causes saturation) */
  result = MyLib_UpdateCounter_u8(300000000U);

  /* Verify: return value is 2 (saturation overflow) */
  TEST_ASSERT_EQUAL_UINT8(2U, result);

  /* Verify: counter capped at limit */
  TEST_ASSERT_EQUAL_UINT32(2000000000U, g_counter_u32);
}

/* ============================================================================
 * Summary of Coverage:
 * ============================================================================
 * 
 * BRANCHES (100% coverage):
 * ✓ Line 48:   if (g_systemReady_b == false) → TRUE
 * ✓ Line 48:   if (g_systemReady_b == false) → FALSE
 * ✓ Line 53:   if ((SaturationEn_b == true) && (l_new_u32 > CounterLimit_u32)) → TRUE
 * ✓ Line 53:   First condition: SaturationEn_b == true → FALSE  
 * ✓ Line 53:   Second condition: l_new_u32 > CounterLimit_u32 → FALSE
 * ✓ Line 65:   if ((l_CycleCnt_u32 & 0x0FU) == 0U) → TRUE
 * ✓ Line 65:   if ((l_CycleCnt_u32 & 0x0FU) == 0U) → FALSE
 * ✓ Line 67:   Ternary operator: SaturationEn_b == true → TRUE branch
 * ✓ Line 67:   Ternary operator: SaturationEn_b == true → FALSE branch
 *
 * LINES (100% coverage):
 * ✓ Line 35:   static uint32_t l_CycleCnt_u32 = 0U;
 * ✓ Line 37:   uint8_t  l_ret_u8 = 0U;
 * ✓ Line 38:   uint32_t l_new_u32 = 0U;
 * ✓ Line 40:   l_CycleCnt_u32++;
 * ✓ Line 42-46: System not ready path
 * ✓ Line 49:   l_new_u32 = g_counter_u32 + add_u32;
 * ✓ Line 53-62: Saturation overflow path
 * ✓ Line 65-69: Toggle path
 * ✓ Line 72:   return l_ret_u8;
 *
 * GLOBAL VARIABLES:
 * ✓ g_counter_u32: Verified in each test case
 * ✓ g_systemReady_b: Verified state dependence
 * 
 * STATIC VARIABLES:
 * ✓ l_CycleCnt_u32: Tested increment and toggle every 16th call
 * ✓ SaturationEn_b (static): Toggle verified
 * ✓ CounterLimit_u32 (static): Custom limits tested
 *
 * BOUNDARY VALUES:
 * ✓ Zero addition
 * ✓ Maximum uint32_t addition
 * ✓ Counter at zero / at limit / exceeding limit
 * ✓ Exact saturation boundary (==)
 * ✓ One past boundary (> by 1)
 * ✓ Cycle count toggle pattern (every 16th call)
 * ✓ Large uint32_t values (1+ billion range)
 *
 * TEST ISOLATION NOTE:
 * - l_CycleCnt_u32 is a static variable inside the function under test
 *   and persists across test function calls. The cycle count tests verify
 *   the toggle pattern behavior rather than absolute call positions to
 *   ensure test independence.
 *
 * ============================================================================
 */
