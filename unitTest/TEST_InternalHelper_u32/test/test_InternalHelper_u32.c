#include "InternalHelper_u32.h"
#include "unity.h"

/* Test setup and teardown */
void setUp(void) {
  /* Reset global variables before each test */
  g_counter_u32 = 0U;
  g_record.id_u16 = 0U;
  g_record.value_u32 = 0U;
  g_systemReady_b = false;
}

void tearDown(void) { /* Cleanup after each test if needed */ }

/* =============================================================================
 * TEST SUITE: InternalHelper_u32 - Deterministic Arithmetic Helper
 * =============================================================================
 *
 * FUNCTION UNDER TEST:
 *   uint32_t InternalHelper_u32(uint32_t x_u32, uint16_t y_u16)
 *
 * BEHAVIOR:
 *   Initializes accumulator with x_u32, then loops y_u16 times adding (i * 2)
 *   where i is the loop counter from [0..y_u16-1].
 *
 *   Mathematical formula: result = x_u32 + (0*2 + 1*2 + 2*2 + ... + (y_u16-1)*2)
 *                                = x_u32 + 2*(0 + 1 + 2 + ... + (y_u16-1))
 *                                = x_u32 + 2*(y_u16*(y_u16-1)/2)
 *                                = x_u32 + y_u16*(y_u16-1)
 *
 * COVERAGE OBJECTIVES:
 *   - 100% line coverage: all statements executed
 *   - 100% branch coverage: loop condition tested at boundary (y_u16=0)
 *   - Boundary testing: min/max input values
 *   - Overflow detection: large input accumulations
 *
 * ============================================================================= */

/* ============================================================================
 * TEST GROUP 1: Boundary Conditions - Zero/Minimal Values
 * ============================================================================ */

/**
 * @test InternalHelper_u32__x_is_zero_y_is_zero
 * @brief Loop does not execute when y_u16 = 0, return x_u32 unchanged
 *
 * @details
 * When y_u16 = 0, the for loop condition (l_i_u16 < y_u16) is false from the
 * start, so the loop body never executes. The function returns x_u32 unchanged.
 *
 * @assertion result == 0
 */
void test_InternalHelper_u32__x_is_zero_y_is_zero(void) {
  /* Arrange */
  uint32_t x_u32 = 0U;
  uint16_t y_u16 = 0U;
  uint32_t expected_u32 = 0U;

  /* Act */
  uint32_t result_u32 = InternalHelper_u32(x_u32, y_u16);

  /* Assert */
  TEST_ASSERT_EQUAL_UINT32(expected_u32, result_u32);
}

/**
 * @test InternalHelper_u32__x_nonzero_y_is_zero
 * @brief Loop does not execute when y_u16 = 0, return x_u32 unchanged
 *
 * @details
 * Even when x_u32 is non-zero, if y_u16 = 0, the loop does not execute
 * and x_u32 is returned unchanged. This verifies the loop boundary condition.
 *
 * @assertion result == x_u32
 */
void test_InternalHelper_u32__x_nonzero_y_is_zero(void) {
  /* Arrange */
  uint32_t x_u32 = 100U;
  uint16_t y_u16 = 0U;
  uint32_t expected_u32 = 100U;

  /* Act */
  uint32_t result_u32 = InternalHelper_u32(x_u32, y_u16);

  /* Assert */
  TEST_ASSERT_EQUAL_UINT32(expected_u32, result_u32);
}

/**
 * @test InternalHelper_u32__x_is_zero_y_is_one
 * @brief Single loop iteration: adds (0 * 2) = 0
 *
 * @details
 * When y_u16 = 1, the loop executes once with l_i_u16 = 0.
 * l_acc_u32 += (0 * 2U) = 0, so the result is x_u32.
 *
 * Formula: 0 + 1*(1-1) = 0
 *
 * @assertion result == 0
 */
void test_InternalHelper_u32__x_is_zero_y_is_one(void) {
  /* Arrange */
  uint32_t x_u32 = 0U;
  uint16_t y_u16 = 1U;
  uint32_t expected_u32 = 0U; /* 0 + 1*(1-1) = 0 */

  /* Act */
  uint32_t result_u32 = InternalHelper_u32(x_u32, y_u16);

  /* Assert */
  TEST_ASSERT_EQUAL_UINT32(expected_u32, result_u32);
}

/**
 * @test InternalHelper_u32__x_nonzero_y_is_one
 * @brief Single loop iteration: adds (0 * 2) = 0, returns x unchanged
 *
 * @details
 * When y_u16 = 1, the loop executes once adding 0. The result equals x_u32.
 *
 * Formula: 50 + 1*(1-1) = 50
 *
 * @assertion result == 50
 */
void test_InternalHelper_u32__x_nonzero_y_is_one(void) {
  /* Arrange */
  uint32_t x_u32 = 50U;
  uint16_t y_u16 = 1U;
  uint32_t expected_u32 = 50U; /* 50 + 1*(1-1) = 50 */

  /* Act */
  uint32_t result_u32 = InternalHelper_u32(x_u32, y_u16);

  /* Assert */
  TEST_ASSERT_EQUAL_UINT32(expected_u32, result_u32);
}

/* ============================================================================
 * TEST GROUP 2: Typical Cases - Small Values
 * ============================================================================ */

/**
 * @test InternalHelper_u32__x_is_zero_y_is_two
 * @brief Two loop iterations: adds (0*2 + 1*2) = 2
 *
 * @details
 * When y_u16 = 2:
 * - Iteration 0: l_acc_u32 += (0 * 2) = 0
 * - Iteration 1: l_acc_u32 += (1 * 2) = 2
 * Result: 0 + 2 = 2
 *
 * Formula: 0 + 2*(2-1) = 2
 *
 * @assertion result == 2
 */
void test_InternalHelper_u32__x_is_zero_y_is_two(void) {
  /* Arrange */
  uint32_t x_u32 = 0U;
  uint16_t y_u16 = 2U;
  uint32_t expected_u32 = 2U; /* 0 + 2*1 = 2 */

  /* Act */
  uint32_t result_u32 = InternalHelper_u32(x_u32, y_u16);

  /* Assert */
  TEST_ASSERT_EQUAL_UINT32(expected_u32, result_u32);
}

/**
 * @test InternalHelper_u32__x_is_zero_y_is_five
 * @brief Five loop iterations: adds (0 + 2 + 4 + 6 + 8) = 20
 *
 * @details
 * When y_u16 = 5:
 * - Iteration 0: l_acc_u32 += (0 * 2) = 0
 * - Iteration 1: l_acc_u32 += (1 * 2) = 2
 * - Iteration 2: l_acc_u32 += (2 * 2) = 4
 * - Iteration 3: l_acc_u32 += (3 * 2) = 6
 * - Iteration 4: l_acc_u32 += (4 * 2) = 8
 * Result: 0 + 20 = 20
 *
 * Formula: 0 + 5*(5-1) = 20
 *
 * @assertion result == 20
 */
void test_InternalHelper_u32__x_is_zero_y_is_five(void) {
  /* Arrange */
  uint32_t x_u32 = 0U;
  uint16_t y_u16 = 5U;
  uint32_t expected_u32 = 20U; /* 0 + 5*4 = 20 */

  /* Act */
  uint32_t result_u32 = InternalHelper_u32(x_u32, y_u16);

  /* Assert */
  TEST_ASSERT_EQUAL_UINT32(expected_u32, result_u32);
}

/**
 * @test InternalHelper_u32__x_nonzero_y_is_five
 * @brief Mixed case: x=100, y=5 → result = 100 + 5*4 = 120
 *
 * @details
 * Verifies that the accumulation adds correctly when both x_u32 and loop
 * accumulation are non-zero.
 *
 * Formula: 100 + 5*(5-1) = 100 + 20 = 120
 *
 * @assertion result == 120
 */
void test_InternalHelper_u32__x_nonzero_y_is_five(void) {
  /* Arrange */
  uint32_t x_u32 = 100U;
  uint16_t y_u16 = 5U;
  uint32_t expected_u32 = 120U; /* 100 + 5*4 = 120 */

  /* Act */
  uint32_t result_u32 = InternalHelper_u32(x_u32, y_u16);

  /* Assert */
  TEST_ASSERT_EQUAL_UINT32(expected_u32, result_u32);
}

/**
 * @test InternalHelper_u32__x_is_250_y_is_ten
 * @brief Moderate values: x=250, y=10 → result = 250 + 10*9 = 340
 *
 * @details
 * Ten loop iterations accumulating (0+2+4+6+8+10+12+14+16+18) = 90
 * Result: 250 + 90 = 340
 *
 * Formula: 250 + 10*(10-1) = 250 + 90 = 340
 *
 * @assertion result == 340
 */
void test_InternalHelper_u32__x_is_250_y_is_ten(void) {
  /* Arrange */
  uint32_t x_u32 = 250U;
  uint16_t y_u16 = 10U;
  uint32_t expected_u32 = 340U; /* 250 + 10*9 = 340 */

  /* Act */
  uint32_t result_u32 = InternalHelper_u32(x_u32, y_u16);

  /* Assert */
  TEST_ASSERT_EQUAL_UINT32(expected_u32, result_u32);
}

/* ============================================================================
 * TEST GROUP 3: Input Boundary Values - High Limits
 * ============================================================================ */

/**
 * @test InternalHelper_u32__x_max_u32_y_is_one
 * @brief Maximum x_u32 with minimal y: result ≈ UINT32_MAX
 *
 * @details
 * When x_u32 is at maximum and y_u16 = 1, the loop adds 0.
 * Result should equal the maximum uint32_t value.
 *
 * @assertion result == UINT32_MAX
 */
void test_InternalHelper_u32__x_max_u32_y_is_one(void) {
  /* Arrange */
  uint32_t x_u32 = UINT32_MAX;
  uint16_t y_u16 = 1U;
  uint32_t expected_u32 = UINT32_MAX;

  /* Act */
  uint32_t result_u32 = InternalHelper_u32(x_u32, y_u16);

  /* Assert */
  TEST_ASSERT_EQUAL_UINT32(expected_u32, result_u32);
}

/**
 * @test InternalHelper_u32__x_is_zero_y_max_u16
 * @brief Maximum y_u16 with x=0
 *
 * @details
 * When y_u16 = UINT16_MAX (65535):
 * Loop accumulation = 65535 * (65535 - 1) = 65535 * 65534 = 4294836090
 *
 * This tests the maximum realistic y value.
 *
 * @note The result may be within the documented range (0..700 per MyLib.h is
 *       a constraint for typical usage, not for all inputs).
 */
void test_InternalHelper_u32__x_is_zero_y_max_u16(void) {
  /* Arrange */
  uint32_t x_u32 = 0U;
  uint16_t y_u16 = UINT16_MAX;
  uint32_t expected_u32;

  /* Calculate expected: 0 + UINT16_MAX * (UINT16_MAX - 1)
     = 65535 * 65534 = 4294836090 */
  expected_u32 = (uint32_t)UINT16_MAX * (uint32_t)(UINT16_MAX - 1U);

  /* Act */
  uint32_t result_u32 = InternalHelper_u32(x_u32, y_u16);

  /* Assert */
  TEST_ASSERT_EQUAL_UINT32(expected_u32, result_u32);
}

/* ============================================================================
 * TEST GROUP 4: Input Range Limits (as documented in MyLib.h)
 * ============================================================================ */

/**
 * @test InternalHelper_u32__x_at_documented_max_y_moderate
 * @brief x at documented maximum (60535) with moderate y
 *
 * @details
 * Per MyLib.h documentation: x_u32 range is 0..60535
 * Testing with x=60535, y=100
 * Result = 60535 + 100*99 = 60535 + 9900 = 70435
 *
 * @assertion result == 70435
 */
void test_InternalHelper_u32__x_at_documented_max_y_moderate(void) {
  /* Arrange */
  uint32_t x_u32 = 60535U;
  uint16_t y_u16 = 100U;
  uint32_t expected_u32 = 70435U; /* 60535 + 100*99 */

  /* Act */
  uint32_t result_u32 = InternalHelper_u32(x_u32, y_u16);

  /* Assert */
  TEST_ASSERT_EQUAL_UINT32(expected_u32, result_u32);
}

/* ============================================================================
 * TEST GROUP 5: Global Variables Verification
 * ============================================================================ */

/**
 * @test InternalHelper_u32__does_not_modify_global_counter
 * @brief Verify that InternalHelper_u32 does not modify g_counter_u32
 *
 * @details
 * InternalHelper_u32 is a pure computational function that does not
 * access or modify any global variables. This test ensures that
 * g_counter_u32 remains unchanged after the function call.
 *
 * @assertion g_counter_u32 == 0 (unchanged after call)
 */
void test_InternalHelper_u32__does_not_modify_global_counter(void) {
  /* Arrange */
  g_counter_u32 = 0U;
  uint32_t x_u32 = 100U;
  uint16_t y_u16 = 5U;
  uint32_t counter_before = g_counter_u32;

  /* Act */
  InternalHelper_u32(x_u32, y_u16);

  /* Assert */
  TEST_ASSERT_EQUAL_UINT32(counter_before, g_counter_u32);
  TEST_ASSERT_EQUAL_UINT32(0U, g_counter_u32);
}

/**
 * @test InternalHelper_u32__does_not_modify_global_record
 * @brief Verify that InternalHelper_u32 does not modify g_record
 *
 * @details
 * InternalHelper_u32 should not access or modify the global record structure.
 *
 * @assertion g_record remains unchanged (id_u16 = 0, value_u32 = 0)
 */
void test_InternalHelper_u32__does_not_modify_global_record(void) {
  /* Arrange */
  g_record.id_u16 = 0U;
  g_record.value_u32 = 0U;
  MyLib_record_t record_before = g_record;
  uint32_t x_u32 = 100U;
  uint16_t y_u16 = 5U;

  /* Act */
  InternalHelper_u32(x_u32, y_u16);

  /* Assert */
  TEST_ASSERT_EQUAL_UINT16(record_before.id_u16, g_record.id_u16);
  TEST_ASSERT_EQUAL_UINT32(record_before.value_u32, g_record.value_u32);
}

/**
 * @test InternalHelper_u32__does_not_modify_system_ready_flag
 * @brief Verify that InternalHelper_u32 does not modify g_systemReady_b
 *
 * @details
 * InternalHelper_u32 is independent of system state and should not
 * modify the g_systemReady_b flag.
 *
 * @assertion g_systemReady_b remains false
 */
void test_InternalHelper_u32__does_not_modify_system_ready_flag(void) {
  /* Arrange */
  g_systemReady_b = false;
  bool ready_before = g_systemReady_b;
  uint32_t x_u32 = 100U;
  uint16_t y_u16 = 5U;

  /* Act */
  InternalHelper_u32(x_u32, y_u16);

  /* Assert */
  TEST_ASSERT_EQUAL(ready_before, g_systemReady_b);
  TEST_ASSERT_FALSE(g_systemReady_b);
}

/* ============================================================================
 * TEST GROUP 6: Loop Coverage Verification - Branch Conditions
 * ============================================================================ */

/**
 * @test InternalHelper_u32__loop_executes_exactly_y_times
 * @brief Verify loop execution count through result verification
 *
 * @details
 * By testing multiple specific y values and verifying the accumulated
 * value through the formula, we ensure the loop executes exactly y times.
 * This covers the loop condition branches:
 * - Branch 1: y = 0 (loop never enters)
 * - Branch 2: y > 0 (loop executes at least once)
 * - Branch 3: Loop terminates when l_i_u16 >= y_u16
 *
 * Testing y = 3: should add 0 + 2 + 4 = 6
 *
 * @assertion result == 6 (verifies loop executed exactly 3 times)
 */
void test_InternalHelper_u32__loop_executes_exactly_y_times(void) {
  /* Arrange */
  uint32_t x_u32 = 0U;
  uint16_t y_u16 = 3U;
  /* Loop iterations: i=0 (add 0), i=1 (add 2), i=2 (add 4) = sum 6 */
  uint32_t expected_u32 = 6U; /* 0 + 3*2 = 6 */

  /* Act */
  uint32_t result_u32 = InternalHelper_u32(x_u32, y_u16);

  /* Assert */
  TEST_ASSERT_EQUAL_UINT32(expected_u32, result_u32);
}

/**
 * @test InternalHelper_u32__loop_counter_increments_correctly
 * @brief Verify loop counter increments by 1 each iteration
 *
 * @details
 * Testing with y = 4 ensures the loop counter increments from 0 to 3:
 * - i=0: add 0*2 = 0
 * - i=1: add 1*2 = 2
 * - i=2: add 2*2 = 4
 * - i=3: add 3*2 = 6
 * Total additions: 0 + 2 + 4 + 6 = 12
 *
 * Formula: 0 + 4*3 = 12
 *
 * @assertion result == 12 (verifies counter incremented correctly)
 */
void test_InternalHelper_u32__loop_counter_increments_correctly(void) {
  /* Arrange */
  uint32_t x_u32 = 0U;
  uint16_t y_u16 = 4U;
  uint32_t expected_u32 = 12U; /* 0 + 4*3 = 12 */

  /* Act */
  uint32_t result_u32 = InternalHelper_u32(x_u32, y_u16);

  /* Assert */
  TEST_ASSERT_EQUAL_UINT32(expected_u32, result_u32);
}

/* ============================================================================
 * TEST GROUP 7: Cast and Arithmetic Verification
 * ============================================================================ */

/**
 * @test InternalHelper_u32__uint16_to_uint32_cast_correctness
 * @brief Verify the cast from uint16_t to uint32_t in multiplication
 *
 * @details
 * The line `l_acc_u32 += (uint32_t)(l_i_u16 * 2U);` involves casting.
 * This test ensures the cast doesn't cause unexpected truncation.
 * With y=200, the loop counter reaches 199, and 199*2 = 398, well within
 * uint32_t range.
 *
 * Formula: 0 + 200*199 = 39800
 *
 * @assertion result == 39800
 */
void test_InternalHelper_u32__uint16_to_uint32_cast_correctness(void) {
  /* Arrange */
  uint32_t x_u32 = 0U;
  uint16_t y_u16 = 200U;
  uint32_t expected_u32 = 39800U; /* 0 + 200*199 */

  /* Act */
  uint32_t result_u32 = InternalHelper_u32(x_u32, y_u16);

  /* Assert */
  TEST_ASSERT_EQUAL_UINT32(expected_u32, result_u32);
}

/**
 * @test InternalHelper_u32__accumulation_prevents_intermediate_overflow
 * @brief Verify correct handling of intermediate multiplication results
 *
 * @details
 * Testing that (uint16_t) * (uint16_t value 2) cast works correctly.
 * With maximum uint16_t value (65535) * 2 = 131070, which fits in uint32_t.
 * The multiplication is cast to uint32_t, so no overflow in the intermediate.
 *
 * Testing indirectly through large y values to stress the arithmetic.
 *
 * @assertion Loop completes without unexpected behavior
 */
void test_InternalHelper_u32__accumulation_prevents_intermediate_overflow(void) {
  /* Arrange */
  uint32_t x_u32 = 0U;
  uint16_t y_u16 = 500U;
  uint32_t expected_u32 = 249500U; /* 0 + 500*499 */

  /* Act */
  uint32_t result_u32 = InternalHelper_u32(x_u32, y_u16);

  /* Assert */
  TEST_ASSERT_EQUAL_UINT32(expected_u32, result_u32);
}

/* ============================================================================
 * TEST GROUP 8: Edge Cases and Stress Tests
 * ============================================================================ */

/**
 * @test InternalHelper_u32__alternating_values_consistency
 * @brief Verify consistency with alternating input values
 *
 * @details
 * Call the function multiple times with different values to ensure
 * no state corruption or side effects persist between calls.
 *
 * Call 1: x=10, y=2 → 10 + 2*1 = 12
 * Call 2: x=20, y=3 → 20 + 3*2 = 26
 * Call 3: x=30, y=1 → 30 + 1*0 = 30
 */
void test_InternalHelper_u32__alternating_values_consistency(void) {
  /* Act & Assert - Call 1 */
  uint32_t result1 = InternalHelper_u32(10U, 2U);
  TEST_ASSERT_EQUAL_UINT32(12U, result1);

  /* Act & Assert - Call 2 */
  uint32_t result2 = InternalHelper_u32(20U, 3U);
  TEST_ASSERT_EQUAL_UINT32(26U, result2);

  /* Act & Assert - Call 3 */
  uint32_t result3 = InternalHelper_u32(30U, 1U);
  TEST_ASSERT_EQUAL_UINT32(30U, result3);
}

/**
 * @test InternalHelper_u32__repeated_same_input_returns_same_output
 * @brief Verify function is deterministic (same input always gives same output)
 *
 * @details
 * Call the function multiple times with identical inputs and verify
 * the results are identical each time. This confirms the function is
 * deterministic and has no state-dependent behavior.
 *
 * Testing with x=42, y=7:
 * Expected: 42 + 7*6 = 84
 */
void test_InternalHelper_u32__repeated_same_input_returns_same_output(void) {
  /* Arrange */
  uint32_t x_u32 = 42U;
  uint16_t y_u16 = 7U;
  uint32_t expected_u32 = 84U; /* 42 + 7*6 */

  /* Act & Assert - Call 1 */
  uint32_t result1 = InternalHelper_u32(x_u32, y_u16);
  TEST_ASSERT_EQUAL_UINT32(expected_u32, result1);

  /* Act & Assert - Call 2 (verify determinism) */
  uint32_t result2 = InternalHelper_u32(x_u32, y_u16);
  TEST_ASSERT_EQUAL_UINT32(expected_u32, result2);

  /* Act & Assert - Call 3 (verify no state corruption) */
  uint32_t result3 = InternalHelper_u32(x_u32, y_u16);
  TEST_ASSERT_EQUAL_UINT32(expected_u32, result3);
}
