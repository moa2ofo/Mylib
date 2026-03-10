#include "MyLib_AnalyzeArray_u32.h"
#include "mock_MyLib.h"
#include "unity.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>




```c
/* SECTION 1 — setUp() and tearDown() */

void setUp(void)
{
    g_counter_u32 = 0U;
    g_record.id_u16 = 0U;
    g_record.value_u32 = 0U;
    g_systemReady_b = false;
}

void tearDown(void)
{
}

/* SECTION 2 — Test functions */

/**
 * @brief Test: NULL pointer with len_u32 = 0 and factor_u16 = 0 → return 0, no processing
 */
void test_NullPtr_ZeroLen_ZeroFactor(void)
{
    uint32_t result;

    result = MyLib_AnalyzeArray_u32(NULL, 0U, 0U);

    TEST_ASSERT_EQUAL_UINT32(0U, result);
}

/**
 * @brief Test: NULL pointer with len_u32 = 1 and factor_u16 = 1 → return 0, no processing
 */
void test_NullPtr_NonZeroLen_NonZeroFactor(void)
{
    uint32_t result;

    result = MyLib_AnalyzeArray_u32(NULL, 1U, 1U);

    TEST_ASSERT_EQUAL_UINT32(0U, result);
}

/**
 * @brief Test: Valid pointer with len_u32 = 0 and factor_u16 = 1 → return 0, array unchanged
 */
void test_ValidPtr_ZeroLen(void)
{
    uint16_t array[1] = {100U};
    uint32_t result;

    result = MyLib_AnalyzeArray_u32(array, 0U, 1U);

    TEST_ASSERT_EQUAL_UINT32(0U, result);
    TEST_ASSERT_EQUAL_UINT16(100U, array[0]);
}

/**
 * @brief Test: Valid pointer with len_u32 = 1, factor_u16 = 0, initial value = 100 → array[0] = 0, return 0
 */
void test_OneElem_ZeroFactor(void)
{
    uint16_t array[1] = {100U};
    uint32_t result;

    MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(0U, NULL, 0U);
    MyLib_ComputeAdjustedValue_u32_IgnoreArg_delta_pc_u16();

    result = MyLib_AnalyzeArray_u32(array, 1U, 0U);

    TEST_ASSERT_EQUAL_UINT32(0U, result);
    TEST_ASSERT_EQUAL_UINT16(0U, array[0]);
}

/**
 * @brief Test: Valid pointer with len_u32 = 1, factor_u16 = 1, initial value = 50 → array[0] = 50, return 50
 */
void test_OneElem_FactorOne_Value50(void)
{
    uint16_t array[1] = {50U};
    uint32_t result;

    MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(50U, NULL, 0U);
    MyLib_ComputeAdjustedValue_u32_IgnoreArg_delta_pc_u16();

    result = MyLib_AnalyzeArray_u32(array, 1U, 1U);

    TEST_ASSERT_EQUAL_UINT32(50U, result);
    TEST_ASSERT_EQUAL_UINT16(50U, array[0]);
}

/**
 * @brief Test: Valid pointer with len_u32 = 1, factor_u16 = 2, initial value = 100 → array[0] = 200, return 200
 */
void test_OneElem_FactorTwo_Value100(void)
{
    uint16_t array[1] = {100U};
    uint32_t result;

    MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(200U, NULL, 0U);
    MyLib_ComputeAdjustedValue_u32_IgnoreArg_delta_pc_u16();

    result = MyLib_AnalyzeArray_u32(array, 1U, 2U);

    TEST_ASSERT_EQUAL_UINT32(200U, result);
    TEST_ASSERT_EQUAL_UINT16(200U, array[0]);
}

/**
 * @brief Test: Valid pointer with len_u32 = 1, factor_u16 = 65535, initial value = 1 → array[0] = 65535, return 65535
 */
void test_OneElem_MaxFactor_Value1(void)
{
    uint16_t array[1] = {1U};
    uint32_t result;

    MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(65535U, NULL, 0U);
    MyLib_ComputeAdjustedValue_u32_IgnoreArg_delta_pc_u16();

    result = MyLib_AnalyzeArray_u32(array, 1U, 65535U);

    TEST_ASSERT_EQUAL_UINT32(65535U, result);
    TEST_ASSERT_EQUAL_UINT16(65535U, array[0]);
}

/**
 * @brief Test: Valid pointer with len_u32 = 2, factor_u16 = 1, initial values = {10, 20} → array = {10, 20}, return 30
 */
void test_TwoElems_FactorOne(void)
{
    uint16_t array[2] = {10U, 20U};
    uint32_t result;

    MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(30U, NULL, 0U);
    MyLib_ComputeAdjustedValue_u32_IgnoreArg_delta_pc_u16();

    result = MyLib_AnalyzeArray_u32(array, 2U, 1U);

    TEST_ASSERT_EQUAL_UINT32(30U, result);
    TEST_ASSERT_EQUAL_UINT16(10U, array[0]);
    TEST_ASSERT_EQUAL_UINT16(20U, array[1]);
}

/**
 * @brief Test: Valid pointer with len_u32 = 2, factor_u16 = 3, initial values = {5, 10} → array = {15, 30}, return 45
 */
void test_TwoElems_FactorThree(void)
{
    uint16_t array[2] = {5U, 10U};
    uint32_t result;

    MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(45U, NULL, 0U);
    MyLib_ComputeAdjustedValue_u32_IgnoreArg_delta_pc_u16();

    result = MyLib_AnalyzeArray_u32(array, 2U, 3U);

    TEST_ASSERT_EQUAL_UINT32(45U, result);
    TEST_ASSERT_EQUAL_UINT16(15U, array[0]);
    TEST_ASSERT_EQUAL_UINT16(30U, array[1]);
}

/**
 * @brief Test: Valid pointer with len_u32 = 300, factor_u16 = 1, all elements = 1 → all elements remain 1, return 300
 */
void test_300Elems_FactorOne_AllOnes(void)
{
    uint16_t array[300];
    uint32_t result;
    size_t i;

    for (i = 0U; i < 300U; i++)
    {
        array[i] = 1U;
    }

    MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(300U, NULL, 0U);
    MyLib_ComputeAdjustedValue_u32_IgnoreArg_delta_pc_u16();

    result = MyLib_AnalyzeArray_u32(array, 300U, 1U);

    TEST_ASSERT_EQUAL_UINT32(300U, result);
    for (i = 0U; i < 300U; i++)
    {
        TEST_ASSERT_EQUAL_UINT16(1U, array[i]);
    }
}

/**
 * @brief Test: Valid pointer with len_u32 = 599, factor_u16 = 1, all elements = 1 → all elements remain 1, return 599
 */
void test_599Elems_FactorOne_AllOnes(void)
{
    uint16_t array[599];
    uint32_t result;
    size_t i;

    for (i = 0U; i < 599U; i++)
    {
        array[i] = 1U;
    }

    MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(599U, NULL, 0U);
    MyLib_ComputeAdjustedValue_u32_IgnoreArg_delta_pc_u16();

    result = MyLib_AnalyzeArray_u32(array, 599U, 1U);

    TEST_ASSERT_EQUAL_UINT32(599U, result);
    for (i = 0U; i < 599U; i++)
    {
        TEST_ASSERT_EQUAL_UINT16(1U, array[i]);
    }
}

/**
 * @brief Test: Valid pointer with len_u32 = 600, factor_u16 = 1, all elements = 1 → all elements remain 1, return 600
 */
void test_600Elems_FactorOne_AllOnes(void)
{
    uint16_t array[600];
    uint32_t result;
    size_t i;

    for (i = 0U; i < 600U; i++)
    {
        array[i] = 1U;
    }

    MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(600U, NULL, 0U);
    MyLib_ComputeAdjustedValue_u32_IgnoreArg_delta_pc_u16();

    result = MyLib_AnalyzeArray_u32(array, 600U, 1U);

    TEST_ASSERT_EQUAL_UINT32(600U, result);
    for (i = 0U; i < 600U; i++)
    {
        TEST_ASSERT_EQUAL_UINT16(1U, array[i]);
    }
}

/**
 * @brief Test: Valid pointer with len_u32 = 3, factor_u16 = 2, initial values = {100, 200, 300} → array = {200, 400, 600}, return 1200
 */
void test_ThreeElems_FactorTwo(void)
{
    uint16_t array[3] = {100U, 200U, 300U};
    uint32_t result;

    MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(1200U, NULL, 0U);
    MyLib_ComputeAdjustedValue_u32_IgnoreArg_delta_pc_u16();

    result = MyLib_AnalyzeArray_u32(array, 3U, 2U);

    TEST_ASSERT_EQUAL_UINT32(1200U, result);
    TEST_ASSERT_EQUAL_UINT16(200U, array[0]);
    TEST_ASSERT_EQUAL_UINT16(400U, array[1]);
    TEST_ASSERT_EQUAL_UINT16(600U, array[2]);
}

/**
 * @brief Test: Valid pointer with len_u32 = 2, factor_u16 = 65535, initial values = {1, 1} → array = {65535, 65535}, return 131070
 */
void test_TwoElems_MaxFactor(void)
{
    uint16_t array[2] = {1U, 1U};
    uint32_t result;

    MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(131070U, NULL, 0U);
    MyLib_ComputeAdjustedValue_u32_IgnoreArg_delta_pc_u16();

    result = MyLib_AnalyzeArray_u32(array, 2U, 65535U);

    TEST_ASSERT_EQUAL_UINT32(131070U, result);
    TEST_ASSERT_EQUAL_UINT16(65535U, array[0]);
    TEST_ASSERT_EQUAL_UINT16(65535U, array[1]);
}

/**
 * @brief Test: Valid pointer with len_u32 = 1, factor_u16 = 2, initial value = 40000 → array[0] = 14464 (wrap-around), return 14464
 */
void test_OneElem_WrapAround(void)
{
    uint16_t array[1] = {40000U};
    uint32_t result;
    uint16_t expected_value;

    expected_value = (uint16_t)(40000U * 2U);

    MyLib_ComputeAdjustedValue_u32_ExpectAndReturn((uint32_t)expected_value, NULL, 0U);
    MyLib_ComputeAdjustedValue_u32_IgnoreArg_delta_pc_u16();

    result = MyLib_AnalyzeArray_u32(array, 1U, 2U);

    TEST_ASSERT_EQUAL_UINT32((uint32_t)expected_value, result);
    TEST_ASSERT_EQUAL_UINT16(expected_value, array[0]);
}

/**
 * @brief Test: Valid pointer with len_u32 = 3, factor_u16 = 10, initial values = {10000, 10000, 10000} → verify sum wrap-around behavior, return (100000 + 100000 + 100000) mod 2^32
 */
void test_ThreeElems_SumWrapAround(void)
{
    uint16_t array[3] = {10000U, 10000U, 10000U};
    uint32_t result;
    uint16_t scaled_value;
    uint32_t expected_sum;

    scaled_value = (uint16_t)(10000U * 10U);
    expected_sum = (uint32_t)scaled_value + (uint32_t)scaled_value + (uint32_t)scaled_value;

    MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(expected_sum, NULL, 0U);
    MyLib_ComputeAdjustedValue_u32_IgnoreArg_delta_pc_u16();

    result = MyLib_AnalyzeArray_u32(array, 3U, 10U);

    TEST_ASSERT_EQUAL_UINT32(expected_sum, result);
    TEST_ASSERT_EQUAL_UINT16(scaled_value, array[0]);
    TEST_ASSERT_EQUAL_UINT16(scaled_value, array[1]);
    TEST_ASSERT_EQUAL_UINT16(scaled_value, array[2]);
}

/**
 * @brief Test: Valid pointer with len_u32 = 2, factor_u16 = 1, initial values = {65535, 65535} → array unchanged, return 131070
 */
void test_TwoElems_MaxValues_FactorOne(void)
{
    uint16_t array[2] = {65535U, 65535U};
    uint32_t result;

    MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(131070U, NULL, 0U);
    MyLib_ComputeAdjustedValue_u32_IgnoreArg_delta_pc_u16();

    result = MyLib_AnalyzeArray_u32(array, 2U, 1U);

    TEST_ASSERT_EQUAL_UINT32(131070U, result);
    TEST_ASSERT_EQUAL_UINT16(65535U, array[0]);
    TEST_ASSERT_EQUAL_UINT16(65535U, array[1]);
}

/**
 * @brief Test: Valid pointer with len_u32 = 5, factor_u16 = 100, initial values = {100, 200, 300, 400, 500} → verify scaled array and sum = 150000
 */
void test_FiveElems_Factor100(void)
{
    uint16_t array[5] = {100U, 200U, 300U, 400U, 500U};
    uint32_t result;

    MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(150000U, NULL, 0U);
    MyLib_ComputeAdjustedValue_u32_IgnoreArg_delta_pc_u16();

    result = MyLib_AnalyzeArray_u32(array, 5U, 100U);

    TEST_ASSERT_EQUAL_UINT32(150000U, result);
    TEST_ASSERT_EQUAL_UINT16(10000U, array[0]);
    TEST_ASSERT_EQUAL_UINT16(20000U, array[1]);
    TEST_ASSERT_EQUAL_UINT16(30000U, array[2]);
    TEST_ASSERT_EQUAL_UINT16(40000U, array[3]);
    TEST_ASSERT_EQUAL_UINT16(50000U, array[4]);
}
```