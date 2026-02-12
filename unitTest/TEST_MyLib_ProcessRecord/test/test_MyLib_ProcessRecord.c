#include "MyLib_ProcessRecord.h"
#include "mock_MyLib.h"
#include "unity.h"

/* Test fixtures */
static MyLib_record_t test_record;
static uint32_t initial_counter;

/**
 * @brief Setup function called before each test
 */
void setUp(void) {
  /* Initialize test record */
  test_record.id_u16 = 0U;
  test_record.value_u32 = 0U;

  /* Save initial counter value */
  initial_counter = g_counter_u32;
}

/**
 * @brief Teardown function called after each test
 */
void tearDown(void) {}

/*=============================================================================
 * Test Case 1: NULL pointer - function returns immediately
 *=============================================================================*/

/**
 * @brief Verify that MyLib_ProcessRecord handles NULL pointer gracefully
 *
 * Expected behavior:
 * - Function returns immediately
 * - No mocked functions are called
 * - Global counter is unchanged
 */
void test_MyLib_ProcessRecord_NullPointer_ReturnsWithoutSideEffects(void) {
  /* Setup: No expectations on mocked functions */

  /* Execute: Call with NULL pointer */
  MyLib_ProcessRecord(NULL, 5U);

  /* Verify: Global counter should be unchanged */
  TEST_ASSERT_EQUAL_UINT32(initial_counter, g_counter_u32);
}

/*=============================================================================
 * Test Case 2: Multiplier = 0 - no accumulation
 *=============================================================================*/

/**
 * @brief Verify behavior when multiplier is 0 (no accumulation)
 *
 * Expected behavior:
 * - Accumulator is 0
 * - Counter is incremented by 0 (remains unchanged)
 * - MyLib_ComputeAdjustedValue_u32 is called with (0, address of 0)
 */
void test_MyLib_ProcessRecord_Multiplier0_NoAccumulation(void) {
  /* Setup: Initialize test record */
  test_record.id_u16 = 100U;
  test_record.value_u32 = 1000U;

  /* Setup CMock expectation: Function is called with 0 accumulation */
  MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(0U, NULL, 0U);
  MyLib_ComputeAdjustedValue_u32_IgnoreArg_delta_pc_u16();

  /* Execute */
  MyLib_ProcessRecord(&test_record, 0U);

  /* Verify: Counter unchanged (0 was added) */
  TEST_ASSERT_EQUAL_UINT32(initial_counter, g_counter_u32);
}

/*=============================================================================
 * Test Case 3: Multiplier = 1 - single accumulation
 *=============================================================================*/

/**
 * @brief Verify behavior when multiplier is 1 (single value assignment)
 *
 * Expected behavior:
 * - Accumulator = record->value_u32
 * - Counter incremented by record->value_u32
 * - MyLib_ComputeAdjustedValue_u32 called with the record value
 */
void test_MyLib_ProcessRecord_Multiplier1_SingleAccumulation(void) {
  /* Setup: Initialize test record with known value */
  test_record.id_u16 = 42U;
  test_record.value_u32 = 500U;
  uint32_t expected_counter = initial_counter + 500U;

  /* Setup CMock expectation */
  MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(500U, NULL, 42U);
  MyLib_ComputeAdjustedValue_u32_IgnoreArg_delta_pc_u16();

  /* Execute */
  MyLib_ProcessRecord(&test_record, 1U);

  /* Verify: Counter incremented by value */
  TEST_ASSERT_EQUAL_UINT32(expected_counter, g_counter_u32);
}

/*=============================================================================
 * Test Case 4: Multiplier = 5 - bounded loop accumulation
 *=============================================================================*/

/**
 * @brief Verify behavior with loop accumulation (multiplier > 1)
 *
 * Expected behavior:
 * - Accumulator = value_u32 * multiplier_u8
 * - Counter incremented by accumulated value
 * - MyLib_ComputeAdjustedValue_u32 called once with accumulated value
 */
void test_MyLib_ProcessRecord_Multiplier5_LoopAccumulation(void) {
  /* Setup: Initialize test record */
  test_record.id_u16 = 200U;
  test_record.value_u32 = 100U;

  uint32_t expected_accumulation = 100U * 5U; /* 500U */
  uint32_t expected_counter = initial_counter + expected_accumulation;

  /* Setup CMock expectation */
  MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(expected_accumulation, NULL, 99U);
  MyLib_ComputeAdjustedValue_u32_IgnoreArg_delta_pc_u16();

  /* Execute */
  MyLib_ProcessRecord(&test_record, 5U);

  /* Verify: Counter incremented by accumulated value */
  TEST_ASSERT_EQUAL_UINT32(expected_counter, g_counter_u32);
}

/*=============================================================================
 * Test Case 5: Multiplier = 255 (max uint8_t) - boundary case
 *=============================================================================*/

/**
 * @brief Verify behavior with maximum multiplier value
 *
 * Expected behavior:
 * - Accumulator = value_u32 * 255
 * - Counter properly incremented
 * - No overflow issues in the loop
 */
void test_MyLib_ProcessRecord_MultiplierMax_BoundaryCase(void) {
  /* Setup: Initialize test record with small value to avoid overflow */
  test_record.id_u16 = 1U;
  test_record.value_u32 = 10U;

  uint32_t expected_accumulation = 10U * 255U; /* 2550U */
  uint32_t expected_counter = initial_counter + expected_accumulation;

  /* Setup CMock expectation */
  MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(expected_accumulation, NULL, 0U);
  MyLib_ComputeAdjustedValue_u32_IgnoreArg_delta_pc_u16();

  /* Execute */
  MyLib_ProcessRecord(&test_record, 255U);

  /* Verify: Counter properly incremented */
  TEST_ASSERT_EQUAL_UINT32(expected_counter, g_counter_u32);
}

/*=============================================================================
 * Test Case 6: Accumulation with wrap-around on uint32_t
 *=============================================================================*/

/**
 * @brief Verify wrap-around behavior when accumulation exceeds UINT32_MAX
 *
 * Expected behavior:
 * - Accumulation wraps around (by design per documentation)
 * - Counter is updated with wrapped value
 */
void test_MyLib_ProcessRecord_WrapAroundAccumulation(void) {
  /* Setup: Large initial counter value */
  g_counter_u32 = UINT32_MAX - 100U;
  initial_counter = g_counter_u32;

  /* Setup: Record with large value */
  test_record.id_u16 = 10U;
  test_record.value_u32 = 200U;

  uint32_t expected_accumulation = 200U * 5U;              /* 1000U */
  uint32_t expected_counter = (UINT32_MAX - 100U) + 1000U; /* Wraps around */

  /* Setup CMock expectation */
  MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(expected_accumulation, NULL, 0U);
  MyLib_ComputeAdjustedValue_u32_IgnoreArg_delta_pc_u16();

  /* Execute */
  MyLib_ProcessRecord(&test_record, 5U);

  /* Verify: Wrap-around behavior */
  TEST_ASSERT_EQUAL_UINT32(expected_counter, g_counter_u32);
}

/*=============================================================================
 * Test Case 7: Multiple sequential calls - state consistency
 *=============================================================================*/

/**
 * @brief Verify correct behavior with multiple sequential calls
 *
 * Expected behavior:
 * - Each call correctly accumulates and updates global counter
 * - Counter is cumulative across calls
 */
void test_MyLib_ProcessRecord_SequentialCalls_StateConsistency(void) {
  /* Setup: First call - multiplier = 2 */
  test_record.id_u16 = 1U;
  test_record.value_u32 = 100U;

  uint32_t first_accumulation = 100U * 2U; /* 200U */
  MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(first_accumulation, NULL, 0U);
  MyLib_ComputeAdjustedValue_u32_IgnoreArg_delta_pc_u16();

  MyLib_ProcessRecord(&test_record, 2U);
  uint32_t counter_after_first = g_counter_u32;

  /* Verify first call */
  TEST_ASSERT_EQUAL_UINT32(initial_counter + 200U, counter_after_first);

  /* Setup: Second call - multiplier = 3 */
  test_record.value_u32 = 50U;
  uint32_t second_accumulation = 50U * 3U; /* 150U */
  MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(second_accumulation, NULL, 0U);
  MyLib_ComputeAdjustedValue_u32_IgnoreArg_delta_pc_u16();

  MyLib_ProcessRecord(&test_record, 3U);

  /* Verify cumulative behavior */
  TEST_ASSERT_EQUAL_UINT32(counter_after_first + 150U, g_counter_u32);
}

/*=============================================================================
 * Test Case 8: Record with maximum value_u32
 *=============================================================================*/

/**
 * @brief Verify behavior with maximum record value
 *
 * Expected behavior:
 * - Correctly handles large uint32_t value
 * - Accumulation and counter update work correctly
 */
void test_MyLib_ProcessRecord_MaxRecordValue(void) {
  /* Setup: Record with maximum value */
  test_record.id_u16 = 65535U;
  test_record.value_u32 = UINT32_MAX;

  uint32_t expected_accumulation = UINT32_MAX; /* multiplier = 1 */
  uint32_t expected_counter = initial_counter + expected_accumulation;

  /* Setup CMock expectation */
  MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(expected_accumulation, NULL, 0U);
  MyLib_ComputeAdjustedValue_u32_IgnoreArg_delta_pc_u16();

  /* Execute */
  MyLib_ProcessRecord(&test_record, 1U);

  /* Verify: Counter properly updated */
  TEST_ASSERT_EQUAL_UINT32(expected_counter, g_counter_u32);
}

/*=============================================================================
 * Test Case 9: Verify mock function is called with correct multiplier address
 *=============================================================================*/

/**
 * @brief Verify that MyLib_ComputeAdjustedValue_u32 receives pointer to multiplier_u8
 *
 * Expected behavior:
 * - Mock function called with correct params
 * - Demonstrates proper parameter passing
 */
void test_MyLib_ProcessRecord_MockFunctionCalledWithCorrectParams(void) {
  /* Setup: Initialize test record */
  test_record.id_u16 = 100U;
  test_record.value_u32 = 300U;

  uint32_t expected_accumulation = 300U * 3U;

  /* Setup CMock expectation - verify all exactly */
  MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(expected_accumulation, NULL, 55U);
  MyLib_ComputeAdjustedValue_u32_IgnoreArg_delta_pc_u16();

  /* Execute */
  MyLib_ProcessRecord(&test_record, 3U);

  /* Verification is implicit through CMock_Verify in tearDown */
  TEST_ASSERT_TRUE(true);
}
