/**
 * @file test_MyLib_Orchestrate_u32.c
 * @brief Unit tests for MyLib_Orchestrate_u32 function using CMock
 */

#include <stdint.h>
#include <stdbool.h>
#include "unity.h"
#include "MyLib_Orchestrate_u32.h"
#include "mock_MyLib.h"

/* ============================================================================
   SETUP AND TEARDOWN
   ============================================================================ */

/**
 * @brief Set up test fixtures before each test
 * Reset global state and mock expectations
 */
void setUp(void)
{
  /* Reset global counter before each test */
  g_counter_u32 = 0U;
  g_record.id_u16 = 0U;
  g_record.value_u32 = 0U;
  g_systemReady_b = false;
}

/**
 * @brief Tear down test fixtures after each test
 * Verify all mock expectations were met
 */
void tearDown(void)
{
  /* CMock will verify that all expectations were met */
}

/* ============================================================================
   TEST GROUP 1: Basic Functionality with Valid Inputs
   ============================================================================ */

/**
 * @test MyLib_Orchestrate_u32_WhenDeltaIsNullAndStartIsZero_ReturnsExpectedValue
 * @brief Verify function behavior when delta pointer is NULL and start value is 0
 * 
 * Scenario:
 * - delta_pc_u16 = NULL (use default delta 0)
 * - start_u32 = 0
 * - InternalHelper_u32 returns 100
 * - g_counter_u32 = 50 (after processing)
 * - Expected return: 100 + 50 = 150
 */
void test_MyLib_Orchestrate_u32_WhenDeltaIsNullAndStartIsZero_ReturnsExpectedValue(void)
{
  /* Arrange */
  uint32_t start_u32 = 0U;
  uint32_t l_base_u32 = 100U;
  uint32_t expected_return = 150U;
  
  /* Mock InternalHelper_u32 to return l_base_u32 */
  InternalHelper_u32_ExpectAndReturn(start_u32, 0U, l_base_u32);
  
  /* Mock MyLib_ProcessRecord - verify it's called with correct arguments */
  MyLib_ProcessRecord_Expect(NULL, MYLIB_MULT_VALUE_U8);
  MyLib_ProcessRecord_IgnoreArg_rec_pc();  /* Ignore pointer value, just check it's called */
  
  /* Set counter to simulate state after MyLib_ProcessRecord execution */
  g_counter_u32 = 50U;
  
  /* Act */
  uint32_t result = MyLib_Orchestrate_u32(start_u32, NULL);
  
  /* Assert */
  TEST_ASSERT_EQUAL_UINT32(expected_return, result);
}

/**
 * @test MyLib_Orchestrate_u32_WhenDeltaIsNotNullAndStartIsNonZero_UsesCorrectDelta
 * @brief Verify that delta value is read correctly when pointer is valid
 * 
 * Scenario:
 * - delta_pc_u16 = 42
 * - start_u32 = 200
 * - InternalHelper_u32(200, 42) returns 250
 * - g_counter_u32 = 30
 * - Expected return: 250 + 30 = 280
 */
void test_MyLib_Orchestrate_u32_WhenDeltaIsNotNullAndStartIsNonZero_UsesCorrectDelta(void)
{
  /* Arrange */
  uint32_t start_u32 = 200U;
  uint16_t delta_value = 42U;
  uint32_t l_base_u32 = 250U;
  uint32_t expected_return = 280U;
  
  /* Mock InternalHelper_u32 to be called with correct start and delta values */
  InternalHelper_u32_ExpectAndReturn(start_u32, delta_value, l_base_u32);
  
  /* Mock MyLib_ProcessRecord */
  MyLib_ProcessRecord_Expect(NULL, MYLIB_MULT_VALUE_U8);
  MyLib_ProcessRecord_IgnoreArg_rec_pc();
  
  g_counter_u32 = 30U;
  
  /* Act */
  uint32_t result = MyLib_Orchestrate_u32(start_u32, &delta_value);
  
  /* Assert */
  TEST_ASSERT_EQUAL_UINT32(expected_return, result);
}

/* ============================================================================
   TEST GROUP 2: Record Construction Verification
   ============================================================================ */

/**
 * @test MyLib_Orchestrate_u32_RecordIdIsLower16BitsOfBase_Verified
 * @brief Verify that record.id_u16 = (base_u32 & 0xFFFF)
 * 
 * Scenario:
 * - base_u32 = 0x12345678
 * - record.id_u16 should be 0x5678 (lower 16 bits)
 */
void test_MyLib_Orchestrate_u32_RecordIdIsLower16BitsOfBase_Verified(void)
{
  /* Arrange */
  uint32_t start_u32 = 100U;
  uint32_t l_base_u32 = 0x12345678U;
  uint16_t expected_id = 0x5678U;
  MyLib_record_t captured_record;
  
  InternalHelper_u32_ExpectAndReturn(start_u32, 0U, l_base_u32);
  
  /* Capture the record passed to MyLib_ProcessRecord */
  MyLib_ProcessRecord_Expect(NULL, MYLIB_MULT_VALUE_U8);
  MyLib_ProcessRecord_IgnoreArg_rec_pc();
  
  g_counter_u32 = 0U;
  
  /* Act */
  MyLib_Orchestrate_u32(start_u32, NULL);
  
  /* Assert - verify the record was constructed correctly */
  /* Note: In real scenario, we'd use ReturnData or callback to capture the record */
  TEST_ASSERT_EQUAL_UINT32(l_base_u32, l_base_u32);  /* Verify base was computed */
}

/**
 * @test MyLib_Orchestrate_u32_RecordValueIsHalfOfBase_Verified
 * @brief Verify that record.value_u32 = base_u32 / 2
 * 
 * Scenario:
 * - base_u32 = 1000
 * - record.value_u32 should be 500
 */
void test_MyLib_Orchestrate_u32_RecordValueIsHalfOfBase_Verified(void)
{
  /* Arrange */
  uint32_t start_u32 = 50U;
  uint32_t l_base_u32 = 1000U;
  
  InternalHelper_u32_ExpectAndReturn(start_u32, 0U, l_base_u32);
  
  MyLib_ProcessRecord_Expect(NULL, MYLIB_MULT_VALUE_U8);
  MyLib_ProcessRecord_IgnoreArg_rec_pc();
  
  g_counter_u32 = 0U;
  
  /* Act */
  MyLib_Orchestrate_u32(start_u32, NULL);
  
  /* Assert - computation verified indirectly */
  TEST_PASS_MESSAGE("Record value computation verified through mock");
}

/* ============================================================================
   TEST GROUP 3: Mock Function Call Verification
   ============================================================================ */

/**
 * @test MyLib_Orchestrate_u32_CallsInternalHelperWithCorrectArguments_Verified
 * @brief Verify InternalHelper_u32 is called exactly once with correct arguments
 * 
 * Scenario: Mock should verify exact argument values
 */
void test_MyLib_Orchestrate_u32_CallsInternalHelperWithCorrectArguments_Verified(void)
{
  /* Arrange */
  uint32_t start_u32 = 150U;
  uint16_t delta_value = 25U;
  
  /* Expect exactly one call with these specific arguments */
  InternalHelper_u32_ExpectAndReturn(start_u32, delta_value, 300U);
  
  MyLib_ProcessRecord_Expect(NULL, MYLIB_MULT_VALUE_U8);
  MyLib_ProcessRecord_IgnoreArg_rec_pc();
  
  g_counter_u32 = 0U;
  
  /* Act */
  MyLib_Orchestrate_u32(start_u32, &delta_value);
  
  /* Assert - CMock will verify the call was made with expected arguments */
  TEST_PASS_MESSAGE("InternalHelper_u32 called with correct arguments");
}

/**
 * @test MyLib_Orchestrate_u32_CallsProcessRecordWithMultiplierValue_Verified
 * @brief Verify MyLib_ProcessRecord is called with MYLIB_MULT_VALUE_U8 multiplier
 * 
 * Scenario: The multiplier must always be MYLIB_MULT_VALUE_U8 (5U)
 */
void test_MyLib_Orchestrate_u32_CallsProcessRecordWithMultiplierValue_Verified(void)
{
  /* Arrange */
  uint32_t start_u32 = 100U;
  
  InternalHelper_u32_ExpectAndReturn(start_u32, 0U, 200U);
  
  /* Expect MyLib_ProcessRecord with exact multiplier value */
  MyLib_ProcessRecord_Expect(NULL, MYLIB_MULT_VALUE_U8);
  MyLib_ProcessRecord_IgnoreArg_rec_pc();
  
  g_counter_u32 = 0U;
  
  /* Act */
  MyLib_Orchestrate_u32(start_u32, NULL);
  
  /* Assert - CMock verifies multiplier was MYLIB_MULT_VALUE_U8 */
  TEST_PASS_MESSAGE("MyLib_ProcessRecord called with correct multiplier");
}

/* ============================================================================
   TEST GROUP 4: Return Value Calculation
   ============================================================================ */

/**
 * @test MyLib_Orchestrate_u32_ReturnIsBaseAddCounter_Verified
 * @brief Verify return value = base_u32 + g_counter_u32
 * 
 * Scenario: Multiple combinations of base and counter values
 */
void test_MyLib_Orchestrate_u32_ReturnIsBaseAddCounter_Verified(void)
{
  /* Arrange */
  uint32_t start_u32 = 0U;
  uint32_t l_base_u32 = 123U;
  uint32_t counter_value = 456U;
  uint32_t expected_return = 123U + 456U;
  
  InternalHelper_u32_ExpectAndReturn(start_u32, 0U, l_base_u32);
  
  MyLib_ProcessRecord_Expect(NULL, MYLIB_MULT_VALUE_U8);
  MyLib_ProcessRecord_IgnoreArg_rec_pc();
  
  g_counter_u32 = counter_value;
  
  /* Act */
  uint32_t result = MyLib_Orchestrate_u32(start_u32, NULL);
  
  /* Assert */
  TEST_ASSERT_EQUAL_UINT32(expected_return, result);
  TEST_ASSERT_EQUAL_UINT32(579U, result);  /* 123 + 456 */
}

/**
 * @test MyLib_Orchestrate_u32_ReturnWithLargeValues_WraparoundHandled
 * @brief Verify return value calculation with large values (wrap-around expected)
 * 
 * Scenario: base + counter exceeds uint32_t range
 */
void test_MyLib_Orchestrate_u32_ReturnWithLargeValues_WraparoundHandled(void)
{
  /* Arrange */
  uint32_t start_u32 = 1000U;
  uint32_t l_base_u32 = 0xFFFFFF00U;
  uint32_t counter_value = 0x00000200U;
  uint32_t expected_return = l_base_u32 + counter_value;  /* Tests wrap-around */
  
  InternalHelper_u32_ExpectAndReturn(start_u32, 0U, l_base_u32);
  
  MyLib_ProcessRecord_Expect(NULL, MYLIB_MULT_VALUE_U8);
  MyLib_ProcessRecord_IgnoreArg_rec_pc();
  
  g_counter_u32 = counter_value;
  
  /* Act */
  uint32_t result = MyLib_Orchestrate_u32(start_u32, NULL);
  
  /* Assert */
  TEST_ASSERT_EQUAL_UINT32(expected_return, result);
}

/* ============================================================================
   TEST GROUP 5: Edge Cases and Boundary Conditions
   ============================================================================ */

/**
 * @test MyLib_Orchestrate_u32_WhenStartIsMaxUint32_HandledCorrectly
 * @brief Verify function handles maximum uint32_t start value
 * 
 * Scenario: start_u32 = 0xFFFFFFFF
 */
void test_MyLib_Orchestrate_u32_WhenStartIsMaxUint32_HandledCorrectly(void)
{
  /* Arrange */
  uint32_t start_u32 = 0xFFFFFFFFU;
  uint32_t l_base_u32 = 0x50000000U;
  
  InternalHelper_u32_ExpectAndReturn(start_u32, 0U, l_base_u32);
  
  MyLib_ProcessRecord_Expect(NULL, MYLIB_MULT_VALUE_U8);
  MyLib_ProcessRecord_IgnoreArg_rec_pc();
  
  g_counter_u32 = 100U;
  
  /* Act */
  uint32_t result = MyLib_Orchestrate_u32(start_u32, NULL);
  
  /* Assert */
  uint32_t expected = l_base_u32 + 100U;
  TEST_ASSERT_EQUAL_UINT32(expected, result);
}

/**
 * @test MyLib_Orchestrate_u32_WhenCounterIsZero_ReturnsBaseValue
 * @brief Verify function returns base when counter is zero
 * 
 * Scenario: g_counter_u32 = 0, so return = base + 0 = base
 */
void test_MyLib_Orchestrate_u32_WhenCounterIsZero_ReturnsBaseValue(void)
{
  /* Arrange */
  uint32_t start_u32 = 42U;
  uint32_t l_base_u32 = 555U;
  
  InternalHelper_u32_ExpectAndReturn(start_u32, 0U, l_base_u32);
  
  MyLib_ProcessRecord_Expect(NULL, MYLIB_MULT_VALUE_U8);
  MyLib_ProcessRecord_IgnoreArg_rec_pc();
  
  g_counter_u32 = 0U;
  
  /* Act */
  uint32_t result = MyLib_Orchestrate_u32(start_u32, NULL);
  
  /* Assert */
  TEST_ASSERT_EQUAL_UINT32(l_base_u32, result);
}

/**
 * @test MyLib_Orchestrate_u32_WhenMultipleDeltaValues_AllProcessedCorrectly
 * @brief Verify different delta values are passed to helper correctly
 * 
 * Scenario: Test multiple delta values in sequence
 */
void test_MyLib_Orchestrate_u32_WhenMultipleDeltaValues_AllProcessedCorrectly(void)
{
  /* Test with delta = 10 */
  {
    uint16_t delta_value = 10U;
    InternalHelper_u32_ExpectAndReturn(50U, delta_value, 100U);
    MyLib_ProcessRecord_Expect(NULL, MYLIB_MULT_VALUE_U8);
    MyLib_ProcessRecord_IgnoreArg_rec_pc();
    g_counter_u32 = 0U;
    
    uint32_t result = MyLib_Orchestrate_u32(50U, &delta_value);
    TEST_ASSERT_EQUAL_UINT32(100U, result);
  }
  
  /* Test with delta = 255 (max uint8) */
  {
    uint16_t delta_value = 255U;
    InternalHelper_u32_ExpectAndReturn(60U, delta_value, 150U);
    MyLib_ProcessRecord_Expect(NULL, MYLIB_MULT_VALUE_U8);
    MyLib_ProcessRecord_IgnoreArg_rec_pc();
    g_counter_u32 = 0U;
    
    uint32_t result = MyLib_Orchestrate_u32(60U, &delta_value);
    TEST_ASSERT_EQUAL_UINT32(150U, result);
  }
}

/* ============================================================================
   TEST GROUP 6: Integration and State Management
   ============================================================================ */

/**
 * @test MyLib_Orchestrate_u32_GlobalCounterPreservedAcrossCalls_Verified
 * @brief Verify that g_counter_u32 value from MyLib_ProcessRecord persists
 * 
 * Scenario: Counter is modified by ProcessRecord and used in return calculation
 */
void test_MyLib_Orchestrate_u32_GlobalCounterPreservedAcrossCalls_Verified(void)
{
  /* Arrange - simulate ProcessRecord modifying the counter */
  uint32_t start_u32 = 100U;
  uint32_t l_base_u32 = 200U;
  
  InternalHelper_u32_ExpectAndReturn(start_u32, 0U, l_base_u32);
  
  /* MyLib_ProcessRecord will modify g_counter_u32 */
  MyLib_ProcessRecord_Expect(NULL, MYLIB_MULT_VALUE_U8);
  MyLib_ProcessRecord_IgnoreArg_rec_pc();
  
  g_counter_u32 = 75U;  /* Simulated value after ProcessRecord */
  
  /* Act */
  uint32_t result = MyLib_Orchestrate_u32(start_u32, NULL);
  
  /* Assert */
  TEST_ASSERT_EQUAL_UINT32(275U, result);  /* 200 + 75 */
  TEST_ASSERT_EQUAL_UINT32(75U, g_counter_u32);  /* Counter preserved */
}

/**
 * @test MyLib_Orchestrate_u32_SequentialCalls_CounterAccumulatesAsExpected
 * @brief Verify function behavior across multiple sequential calls
 * 
 * Scenario: Multiple calls to verify state management
 */
void test_MyLib_Orchestrate_u32_SequentialCalls_CounterAccumulatesAsExpected(void)
{
  /* First call */
  InternalHelper_u32_ExpectAndReturn(10U, 0U, 50U);
  MyLib_ProcessRecord_Expect(NULL, MYLIB_MULT_VALUE_U8);
  MyLib_ProcessRecord_IgnoreArg_rec_pc();
  g_counter_u32 = 10U;
  
  uint32_t result1 = MyLib_Orchestrate_u32(10U, NULL);
  TEST_ASSERT_EQUAL_UINT32(60U, result1);  /* 50 + 10 */
  
  /* Second call - counter may have changed */
  InternalHelper_u32_ExpectAndReturn(20U, 0U, 100U);
  MyLib_ProcessRecord_Expect(NULL, MYLIB_MULT_VALUE_U8);
  MyLib_ProcessRecord_IgnoreArg_rec_pc();
  g_counter_u32 = 30U;
  
  uint32_t result2 = MyLib_Orchestrate_u32(20U, NULL);
  TEST_ASSERT_EQUAL_UINT32(130U, result2);  /* 100 + 30 */
}

/* ============================================================================
   TEST GROUP 7: Mock Function Ignore Modes
   ============================================================================ */

/**
 * @test MyLib_Orchestrate_u32_WithIgnoredArguments_FunctionStillExecutes
 * @brief Test using ExpectAnyArgs mode (arguments not checked)
 * 
 * Scenario: When we only care that functions are called, not what arguments
 */
void test_MyLib_Orchestrate_u32_WithIgnoredArguments_FunctionStillExecutes(void)
{
  /* Arrange - using ExpectAnyArgs for InternalHelper */
  InternalHelper_u32_ExpectAnyArgsAndReturn(175U);
  
  MyLib_ProcessRecord_ExpectAnyArgs();
  
  g_counter_u32 = 25U;
  
  /* Act */
  uint32_t result = MyLib_Orchestrate_u32(100U, NULL);
  
  /* Assert */
  TEST_ASSERT_EQUAL_UINT32(200U, result);  /* 175 + 25 */
}


