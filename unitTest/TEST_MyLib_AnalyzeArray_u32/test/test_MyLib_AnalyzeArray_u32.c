#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>
#include "unity.h"
#include "MyLib_AnalyzeArray_u32.h"
#include "mock_MyLib.h"

/* ========================================================================
 *
 * Test Suite: MyLib_AnalyzeArray_u32
 * 
 * Purpose:
 *   Achieve 100% line coverage and 100% branch coverage of the function:
 *   uint32_t MyLib_AnalyzeArray_u32(uint16_t *values_pu16, size_t len_u32, uint16_t factor_u16)
 *
 * Coverage Requirements:
 *   - Branch 1: NULL pointer input
 *   - Branch 2: Zero length input
 *   - Branch 3: Valid array processing (normal path)
 *   - Boundary cases: factor = 0, factor = 1, large factors
 *   - Global variable state verification
 *
 * ======================================================================== */



/* ========================================================================
 * SETUP AND TEARDOWN
 * ======================================================================== */

void setUp(void) {
    /* Reset global variables before each test */
    g_counter_u32 = 0U;
    g_record.id_u16 = 0U;
    g_record.value_u32 = 0U;
    g_systemReady_b = false;
    
    /* Clear mock expectations */
    mock_MyLib_Init();
}

void tearDown(void) {
    /* Verify all mock expectations were met */
    mock_MyLib_Verify();
}

/* ========================================================================
 * TEST CASE: BRANCH 1 - NULL POINTER INPUT
 * ======================================================================== */

void test_AnalyzeArray_u32_NULL_pointer_returns_zero(void) {
    /* Test: When values_pu16 is NULL, function should return 0
     * Expected branches: NULL check (true), no processing loop
     * Expected side effects: None (MyLib_ComputeAdjustedValue_u32 should NOT be called)
     */
    uint32_t result;
    
    /* Expect that the mock function is NOT called when pointer is NULL */
    /* (no expectation set means the function should not be called) */
    
    result = MyLib_AnalyzeArray_u32(NULL, 10U, 2U);
    
    TEST_ASSERT_EQUAL_UINT32(0U, result);
    TEST_ASSERT_EQUAL_UINT32(0U, g_counter_u32);
    TEST_ASSERT_EQUAL_UINT16(0U, g_record.id_u16);
    TEST_ASSERT_EQUAL_UINT32(0U, g_record.value_u32);
    TEST_ASSERT_EQUAL(false, g_systemReady_b);
}

/* ========================================================================
 * TEST CASE: BRANCH 2 - ZERO LENGTH INPUT
 * ======================================================================== */

void test_AnalyzeArray_u32_zero_length_returns_zero(void) {
    /* Test: When len_u32 is 0, function should return 0
     * Expected branches: NULL check (false), length check (true), no processing loop
     * Expected side effects: None (MyLib_ComputeAdjustedValue_u32 should NOT be called)
     */
    uint16_t array[5] = {1U, 2U, 3U, 4U, 5U};
    uint32_t result;
    uint16_t expected_array[5] = {1U, 2U, 3U, 4U, 5U};
    
    /* Expect that the mock function is NOT called when length is 0 */
    
    result = MyLib_AnalyzeArray_u32(array, 0U, 5U);
    
    TEST_ASSERT_EQUAL_UINT32(0U, result);
    /* Verify array was not modified */
    TEST_ASSERT_EQUAL_UINT16_ARRAY(expected_array, array, 5U);
    TEST_ASSERT_EQUAL_UINT32(0U, g_counter_u32);
    TEST_ASSERT_EQUAL(false, g_systemReady_b);
}

/* ========================================================================
 * TEST CASE: BRANCH 3 - SINGLE ELEMENT WITH FACTOR 1 (BOUNDARY)
 * ======================================================================== */

void test_AnalyzeArray_u32_single_element_factor_1(void) {
    /* Test: Single element with factor 1 (identity)
     * Expected: Element unchanged, sum = element value
     * Expected side effects: MyLib_ComputeAdjustedValue_u32 called with sum and NULL
     */
    uint16_t array[1] = {42U};
    uint32_t result;
    
    /* Mock the internal function call */
    MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(42U, NULL, 0U);
    
    result = MyLib_AnalyzeArray_u32(array, 1U, 1U);
    
    TEST_ASSERT_EQUAL_UINT32(42U, result);
    TEST_ASSERT_EQUAL_UINT16(42U, array[0]);
}

/* ========================================================================
 * TEST CASE: SINGLE ELEMENT WITH FACTOR 0 (BOUNDARY)
 * ======================================================================== */

void test_AnalyzeArray_u32_single_element_factor_zero(void) {
    /* Test: Single element with factor 0
     * Expected: Element becomes 0, sum = 0
     * Expected side effects: MyLib_ComputeAdjustedValue_u32 called with 0 and NULL
     */
    uint16_t array[1] = {100U};
    uint32_t result;
    
    MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(0U, NULL, 0U);
    
    result = MyLib_AnalyzeArray_u32(array, 1U, 0U);
    
    TEST_ASSERT_EQUAL_UINT32(0U, result);
    TEST_ASSERT_EQUAL_UINT16(0U, array[0]);
}

/* ========================================================================
 * TEST CASE: SINGLE ELEMENT WITH LARGE FACTOR
 * ======================================================================== */

void test_AnalyzeArray_u32_single_element_factor_max(void) {
    /* Test: Single element with maximum factor (65535)
     * Expected: Element scaled, potential overflow handled by uint16_t
     */
    uint16_t array[1] = {1U};
    uint32_t result;
    
    /* 1 * 65535 = 65535 */
    MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(65535U, NULL, 0U);
    
    result = MyLib_AnalyzeArray_u32(array, 1U, 65535U);
    
    TEST_ASSERT_EQUAL_UINT32(65535U, result);
    TEST_ASSERT_EQUAL_UINT16(65535U, array[0]);
}

/* ========================================================================
 * TEST CASE: MULTIPLE ELEMENTS WITH FACTOR 2
 * ======================================================================== */

void test_AnalyzeArray_u32_multiple_elements_factor_2(void) {
    /* Test: Multiple elements, each multiplied by 2
     * Input array: [10, 20, 30]
     * Expected array: [20, 40, 60]
     * Expected sum: 120
     */
    uint16_t array[3] = {10U, 20U, 30U};
    uint16_t expected_array[3] = {20U, 40U, 60U};
    uint32_t result;
    
    MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(120U, NULL, 0U);
    
    result = MyLib_AnalyzeArray_u32(array, 3U, 2U);
    
    TEST_ASSERT_EQUAL_UINT32(120U, result);
    TEST_ASSERT_EQUAL_UINT16_ARRAY(expected_array, array, 3U);
}

/* ========================================================================
 * TEST CASE: MULTIPLE ELEMENTS WITH FACTOR 0
 * ======================================================================== */

void test_AnalyzeArray_u32_multiple_elements_factor_zero(void) {
    /* Test: All elements zeroed out by factor 0
     * Input array: [5, 10, 15, 20]
     * Expected array: [0, 0, 0, 0]
     * Expected sum: 0
     */
    uint16_t array[4] = {5U, 10U, 15U, 20U};
    uint16_t expected_array[4] = {0U, 0U, 0U, 0U};
    uint32_t result;
    
    MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(0U, NULL, 0U);
    
    result = MyLib_AnalyzeArray_u32(array, 4U, 0U);
    
    TEST_ASSERT_EQUAL_UINT32(0U, result);
    TEST_ASSERT_EQUAL_UINT16_ARRAY(expected_array, array, 4U);
}

/* ========================================================================
 * TEST CASE: IN-PLACE MODIFICATION VERIFICATION
 * ======================================================================== */

void test_AnalyzeArray_u32_in_place_modification(void) {
    /* Test: Verify that array is modified in-place, not copied
     * Track pointer values to ensure original array is modified
     */
    uint16_t original_array[5] = {1U, 2U, 3U, 4U, 5U};
    uint16_t *array_ptr = original_array;
    uint32_t result;
    
    MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(45U, NULL, 0U);
    
    result = MyLib_AnalyzeArray_u32(array_ptr, 5U, 3U);
    
    /* Verify original array was modified */
    TEST_ASSERT_EQUAL_UINT16(3U, original_array[0]);
    TEST_ASSERT_EQUAL_UINT16(6U, original_array[1]);
    TEST_ASSERT_EQUAL_UINT16(9U, original_array[2]);
    TEST_ASSERT_EQUAL_UINT16(12U, original_array[3]);
    TEST_ASSERT_EQUAL_UINT16(15U, original_array[4]);
    TEST_ASSERT_EQUAL_UINT32(45U, result);
}

/* ========================================================================
 * TEST CASE: SUM ACCUMULATION WITH VARIOUS SIZES
 * ======================================================================== */

void test_AnalyzeArray_u32_sum_accumulation_10_elements(void) {
    /* Test: Larger array with factor 1 (identity)
     * Verify correct summation over multiple iterations
     */
    uint16_t array[10] = {1U, 2U, 3U, 4U, 5U, 6U, 7U, 8U, 9U, 10U};
    uint16_t expected[10] = {1U, 2U, 3U, 4U, 5U, 6U, 7U, 8U, 9U, 10U};
    uint32_t expected_sum = 55U;  /* 1+2+3+4+5+6+7+8+9+10 */
    uint32_t result;
    
    MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(expected_sum, NULL, 0U);
    
    result = MyLib_AnalyzeArray_u32(array, 10U, 1U);
    
    TEST_ASSERT_EQUAL_UINT32(expected_sum, result);
    TEST_ASSERT_EQUAL_UINT16_ARRAY(expected, array, 10U);
}

/* ========================================================================
 * TEST CASE: LARGE ARRAY SCALING
 * ======================================================================== */

void test_AnalyzeArray_u32_large_array_factor_5(void) {
    /* Test: Larger array with more significant factor
     * Input: {1, 2, 3, 4, 5} * 5 = {5, 10, 15, 20, 25}
     * Sum: 75
     */
    uint16_t array[5] = {1U, 2U, 3U, 4U, 5U};
    uint16_t expected[5] = {5U, 10U, 15U, 20U, 25U};
    uint32_t expected_sum = 75U;
    uint32_t result;
    
    MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(expected_sum, NULL, 0U);
    
    result = MyLib_AnalyzeArray_u32(array, 5U, 5U);
    
    TEST_ASSERT_EQUAL_UINT32(expected_sum, result);
    TEST_ASSERT_EQUAL_UINT16_ARRAY(expected, array, 5U);
}

/* ========================================================================
 * TEST CASE: VERIFY MOCK FUNCTION IS CALLED WITH CORRECT PARAMETERS
 * ======================================================================== */

void test_AnalyzeArray_u32_mock_function_called_correct_params(void) {
    /* Test: Verify MyLib_ComputeAdjustedValue_u32 is invoked with:
     *   - First parameter: calculated sum
     *   - Second parameter: NULL pointer
     */
    uint16_t array[3] = {5U, 5U, 5U};
    uint32_t result;
    uint32_t expected_sum = 30U;  /* (5*2) + (5*2) + (5*2) */
    
    /* Strict expectation: exact parameters and return value */
    MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(expected_sum, NULL, 100U);
    
    result = MyLib_AnalyzeArray_u32(array, 3U, 2U);
    
    TEST_ASSERT_EQUAL_UINT32(expected_sum, result);
}

/* ========================================================================
 * TEST CASE: MOCK FUNCTION WITH RETURN VALUE IGNORED
 * ======================================================================== */

void test_AnalyzeArray_u32_mock_return_value_unused(void) {
    /* Test: Function ignores return value from MyLib_ComputeAdjustedValue_u32
     * Verify that the function still returns the correct local sum value
     */
    uint16_t array[2] = {10U, 20U};
    uint32_t result;
    
    /* Mock returns 999, but function should still return 60 (10*2 + 20*2) */
    MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(60U, NULL, 999U);
    
    result = MyLib_AnalyzeArray_u32(array, 2U, 2U);
    
    TEST_ASSERT_EQUAL_UINT32(60U, result);  /* Local sum, not mock return */
}

/* ========================================================================
 * TEST CASE: ZERO ARRAY VALUES
 * ======================================================================== */

void test_AnalyzeArray_u32_all_zeros_with_factor(void) {
    /* Test: Array of zeros multiplied by any factor remains zeros
     * Edge case: Ensure sum calculation works correctly with all zeros
     */
    uint16_t array[5] = {0U, 0U, 0U, 0U, 0U};
    uint16_t expected[5] = {0U, 0U, 0U, 0U, 0U};
    uint32_t result;
    
    MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(0U, NULL, 0U);
    
    result = MyLib_AnalyzeArray_u32(array, 5U, 100U);
    
    TEST_ASSERT_EQUAL_UINT32(0U, result);
    TEST_ASSERT_EQUAL_UINT16_ARRAY(expected, array, 5U);
}

