#include "MyLib_ComputeAdjustedValue_u32.h"
#include "mock_MyLib.h"
#include "unity.h"

/* ============================================================================
 * TEST SETUP AND TEARDOWN
 * ============================================================================
 */

void setUp(void) { /* Reset mock state before each test */
}

void tearDown(void) { /* Verify all expectations were met */
}

/* ============================================================================
 * TEST CASES: MyLib_ComputeAdjustedValue_u32
 * ============================================================================
 */

/**
 * @test
 * Nominal case: delta pointer is NULL, so default delta = 1 is used.
 * 
 * Given:
 *   - base_u32 = 100
 *   - delta_pc_u16 = NULL
 * 
 * When:
 *   - MyLib_ComputeAdjustedValue_u32(100, NULL) is called
 * 
 * Then:
 *   - InternalHelper_u32 should be called with (100 * 1, 5) = (100, 5)
 *   - Return the mocked result from InternalHelper_u32
 */
void test_ComputeAdjustedValue_u32_NullDeltaPointer_UsesDefaultDelta(void) {
  uint32_t base_u32 = 100U;
  uint32_t expected_helper_input = 100U;    /* base * 1 */
  uint16_t expected_helper_multiplier = 5U; /* MYLIB_MULT_VALUE_U8 */
  uint32_t mocked_helper_result = 200U;

  /* Expect InternalHelper_u32 to be called with specific arguments */
  InternalHelper_u32_ExpectAndReturn(expected_helper_input, expected_helper_multiplier, mocked_helper_result);

  /* Call function under test */
  uint32_t result = MyLib_ComputeAdjustedValue_u32(base_u32, NULL);

  /* Verify return value matches mocked helper result */
  TEST_ASSERT_EQUAL_UINT32(mocked_helper_result, result);
}

/**
 * @test
 * Normal case: delta pointer points to a valid value.
 * 
 * Given:
 *   - base_u32 = 50
 *   - delta_pc_u16 points to 3
 * 
 * When:
 *   - MyLib_ComputeAdjustedValue_u32(50, &delta) is called
 * 
 * Then:
 *   - InternalHelper_u32 should be called with (50 * 3, 5) = (150, 5)
 *   - Return the mocked result
 */
void test_ComputeAdjustedValue_u32_WithValidDelta_ComputesCorrectly(void) {
  uint32_t base_u32 = 50U;
  uint16_t delta = 3U;
  uint32_t expected_helper_input = 150U; /* base * delta = 50 * 3 */
  uint16_t expected_helper_multiplier = 5U;
  uint32_t mocked_helper_result = 180U;

  InternalHelper_u32_ExpectAndReturn(expected_helper_input, expected_helper_multiplier, mocked_helper_result);

  uint32_t result = MyLib_ComputeAdjustedValue_u32(base_u32, &delta);

  TEST_ASSERT_EQUAL_UINT32(mocked_helper_result, result);
}

/**
 * @test
 * Edge case: delta = 1 (same as default).
 * 
 * Given:
 *   - base_u32 = 200
 *   - delta_pc_u16 points to 1
 * 
 * When:
 *   - MyLib_ComputeAdjustedValue_u32(200, &delta) is called
 * 
 * Then:
 *   - InternalHelper_u32 should be called with (200 * 1, 5) = (200, 5)
 */
void test_ComputeAdjustedValue_u32_WithDeltaOne_PassesThroughBase(void) {
  uint32_t base_u32 = 200U;
  uint16_t delta = 1U;
  uint32_t expected_helper_input = 200U;
  uint16_t expected_helper_multiplier = 5U;
  uint32_t mocked_helper_result = 250U;

  InternalHelper_u32_ExpectAndReturn(expected_helper_input, expected_helper_multiplier, mocked_helper_result);

  uint32_t result = MyLib_ComputeAdjustedValue_u32(base_u32, &delta);

  TEST_ASSERT_EQUAL_UINT32(mocked_helper_result, result);
}

/**
 * @test
 * Edge case: base = 0.
 * 
 * Given:
 *   - base_u32 = 0
 *   - delta_pc_u16 points to 10
 * 
 * When:
 *   - MyLib_ComputeAdjustedValue_u32(0, &delta) is called
 * 
 * Then:
 *   - InternalHelper_u32 should be called with (0 * 10, 5) = (0, 5)
 *   - Result should be whatever InternalHelper returns
 */
void test_ComputeAdjustedValue_u32_WithZeroBase_ReturnsHelperResult(void) {
  uint32_t base_u32 = 0U;
  uint16_t delta = 10U;
  uint32_t expected_helper_input = 0U; /* 0 * 10 */
  uint16_t expected_helper_multiplier = 5U;
  uint32_t mocked_helper_result = 0U;

  InternalHelper_u32_ExpectAndReturn(expected_helper_input, expected_helper_multiplier, mocked_helper_result);

  uint32_t result = MyLib_ComputeAdjustedValue_u32(base_u32, &delta);

  TEST_ASSERT_EQUAL_UINT32(mocked_helper_result, result);
}

/**
 * @test
 * Large values: base and delta both large.
 * 
 * Given:
 *   - base_u32 = 600
 *   - delta_pc_u16 points to 100
 * 
 * When:
 *   - MyLib_ComputeAdjustedValue_u32(600, &delta) is called
 * 
 * Then:
 *   - InternalHelper_u32 should be called with (600 * 100, 5) = (60000, 5)
 *   - Return helper result
 */
void test_ComputeAdjustedValue_u32_WithLargeValues_HandlesMultiplication(void) {
  uint32_t base_u32 = 600U;
  uint16_t delta = 100U;
  uint32_t expected_helper_input = 60000U; /* 600 * 100 */
  uint16_t expected_helper_multiplier = 5U;
  uint32_t mocked_helper_result = 60050U;

  InternalHelper_u32_ExpectAndReturn(expected_helper_input, expected_helper_multiplier, mocked_helper_result);

  uint32_t result = MyLib_ComputeAdjustedValue_u32(base_u32, &delta);

  TEST_ASSERT_EQUAL_UINT32(mocked_helper_result, result);
}

/**
 * @test
 * Maximum delta value (uint16_t max).
 * 
 * Given:
 *   - base_u32 = 100
 *   - delta_pc_u16 points to 65535 (UINT16_MAX)
 * 
 * When:
 *   - MyLib_ComputeAdjustedValue_u32(100, &delta) is called
 * 
 * Then:
 *   - InternalHelper_u32 should be called with (100 * 65535, 5) = (6553500, 5)
 *   - Verify multiplication does not overflow in the test
 */
void test_ComputeAdjustedValue_u32_WithMaxDelta_HandlesLargeMultiplication(void) {
  uint32_t base_u32 = 100U;
  uint16_t delta = 65535U;                                  /* UINT16_MAX */
  uint32_t expected_helper_input = (uint32_t)100U * 65535U; /* 6553500 */
  uint16_t expected_helper_multiplier = 5U;
  uint32_t mocked_helper_result = 500U; /* Arbitrary return value */

  InternalHelper_u32_ExpectAndReturn(expected_helper_input, expected_helper_multiplier, mocked_helper_result);

  uint32_t result = MyLib_ComputeAdjustedValue_u32(base_u32, &delta);

  TEST_ASSERT_EQUAL_UINT32(mocked_helper_result, result);
}

/**
 * @test
 * Verify InternalHelper is always called with MYLIB_MULT_VALUE_U8 (5) as second parameter.
 * 
 * Given:
 *   - Various base and delta values
 * 
 * When:
 *   - MyLib_ComputeAdjustedValue_u32 is called
 * 
 * Then:
 *   - The second argument to InternalHelper_u32 must always be 5
 */
void test_ComputeAdjustedValue_u32_HelperMultiplierAlwaysFive(void) {
  uint32_t base_u32 = 75U;
  uint16_t delta = 8U;
  uint32_t expected_helper_input = 600U;    /* 75 * 8 */
  uint16_t expected_helper_multiplier = 5U; /* MYLIB_MULT_VALUE_U8 */
  uint32_t mocked_helper_result = 320U;

  InternalHelper_u32_ExpectAndReturn(expected_helper_input, expected_helper_multiplier, mocked_helper_result);

  uint32_t result = MyLib_ComputeAdjustedValue_u32(base_u32, &delta);

  TEST_ASSERT_EQUAL_UINT32(mocked_helper_result, result);
}

/**
 * @test
 * Return value passthrough: Verify the function returns exactly what InternalHelper returns.
 * 
 * Given:
 *   - base_u32 = 50
 *   - delta = 2
 * 
 * When:
 *   - InternalHelper_u32 is mocked to return a specific value
 * 
 * Then:
 *   - MyLib_ComputeAdjustedValue_u32 should return that exact value, not modify it
 */
void test_ComputeAdjustedValue_u32_ReturnValuePassthroughFromHelper(void) {
  uint32_t base_u32 = 50U;
  uint16_t delta = 2U;
  uint32_t expected_helper_input = 100U; /* 50 * 2 */
  uint16_t expected_helper_multiplier = 5U;
  uint32_t expected_return_value = 12345U; /* Arbitrary large value */

  InternalHelper_u32_ExpectAndReturn(expected_helper_input, expected_helper_multiplier, expected_return_value);

  uint32_t result = MyLib_ComputeAdjustedValue_u32(base_u32, &delta);

  TEST_ASSERT_EQUAL_UINT32(expected_return_value, result);
}

/**
 * @test
 * Multiple sequential calls with different parameters.
 * 
 * Given:
 *   - First call: base = 10, delta = NULL
 *   - Second call: base = 20, delta pointing to 2
 * 
 * When:
 *   - Both calls are made in sequence
 * 
 * Then:
 *   - Each should invoke InternalHelper_u32 with correct parameters
 *   - Each should return the corresponding mocked result
 */
void test_ComputeAdjustedValue_u32_SequentialCallsWithDifferentParameters(void) {
  /* First call: base = 10, delta = NULL (uses default 1) */
  uint32_t result1 = 0U;
  InternalHelper_u32_ExpectAndReturn(10U, 5U, 100U);
  result1 = MyLib_ComputeAdjustedValue_u32(10U, NULL);
  TEST_ASSERT_EQUAL_UINT32(100U, result1);

  /* Second call: base = 20, delta = 3 */
  uint32_t delta2 = 3U;
  InternalHelper_u32_ExpectAndReturn(60U, 5U, 150U);
  uint32_t result2 = MyLib_ComputeAdjustedValue_u32(20U, &delta2);
  TEST_ASSERT_EQUAL_UINT32(150U, result2);
}

/**
 * @test
 * Boundary case: delta = 0 (unusual but valid per function spec).
 * 
 * Given:
 *   - base_u32 = 100
 *   - delta_pc_u16 points to 0
 * 
 * When:
 *   - MyLib_ComputeAdjustedValue_u32(100, &delta) is called
 * 
 * Then:
 *   - InternalHelper_u32 should be called with (100 * 0, 5) = (0, 5)
 */
void test_ComputeAdjustedValue_u32_WithZeroDelta_ResultsInZeroProduct(void) {
  uint32_t base_u32 = 100U;
  uint16_t delta = 0U;
  uint32_t expected_helper_input = 0U; /* 100 * 0 */
  uint16_t expected_helper_multiplier = 5U;
  uint32_t mocked_helper_result = 5U; /* Helper's own computation */

  InternalHelper_u32_ExpectAndReturn(expected_helper_input, expected_helper_multiplier, mocked_helper_result);

  uint32_t result = MyLib_ComputeAdjustedValue_u32(base_u32, &delta);

  TEST_ASSERT_EQUAL_UINT32(mocked_helper_result, result);
}
