#include "MyLib_AnalyzeArray_u32.h"
#include "mock_MyLib.h"
#include "unity.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>




void setUp(void)
{
}
void tearDown(void)
{
}
void test_NULL_pointer_len_0_factor_0_returns_0(void)
{
    uint32_t result;

    result = MyLib_AnalyzeArray_u32(NULL, 0U, 0U);

    TEST_ASSERT_EQUAL_UINT32(0U, result);
}
void test_NULL_pointer_len_1_factor_1_returns_0(void)
{
    uint32_t result;

    result = MyLib_AnalyzeArray_u32(NULL, 1U, 1U);

    TEST_ASSERT_EQUAL_UINT32(0U, result);
}
void test_valid_pointer_len_0_factor_1_returns_0(void)
{
    uint16_t array[1] = {100U};
    uint32_t result;

    result = MyLib_AnalyzeArray_u32(array, 0U, 1U);

    TEST_ASSERT_EQUAL_UINT32(0U, result);
    TEST_ASSERT_EQUAL_UINT16(100U, array[0]);
}
void test_len_1_factor_0_value_100_becomes_0_returns_0(void)
{
    uint16_t array[1] = {100U};
    uint32_t result;

    MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(0U, NULL, 0U);
    MyLib_ComputeAdjustedValue_u32_IgnoreArg_delta_pc_u16();

    result = MyLib_AnalyzeArray_u32(array, 1U, 0U);

    TEST_ASSERT_EQUAL_UINT16(0U, array[0]);
    TEST_ASSERT_EQUAL_UINT32(0U, result);
}
void test_len_1_factor_1_value_50_remains_50_returns_50(void)
{
    uint16_t array[1] = {50U};
    uint32_t result;

    MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(50U, NULL, 0U);
    MyLib_ComputeAdjustedValue_u32_IgnoreArg_delta_pc_u16();

    result = MyLib_AnalyzeArray_u32(array, 1U, 1U);

    TEST_ASSERT_EQUAL_UINT16(50U, array[0]);
    TEST_ASSERT_EQUAL_UINT32(50U, result);
}
void test_len_1_factor_2_value_100_becomes_200_returns_200(void)
{
    uint16_t array[1] = {100U};
    uint32_t result;

    MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(200U, NULL, 0U);
    MyLib_ComputeAdjustedValue_u32_IgnoreArg_delta_pc_u16();

    result = MyLib_AnalyzeArray_u32(array, 1U, 2U);

    TEST_ASSERT_EQUAL_UINT16(200U, array[0]);
    TEST_ASSERT_EQUAL_UINT32(200U, result);
}
void test_len_1_factor_65535_value_1_becomes_65535_returns_65535(void)
{
    uint16_t array[1] = {1U};
    uint32_t result;

    MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(65535U, NULL, 0U);
    MyLib_ComputeAdjustedValue_u32_IgnoreArg_delta_pc_u16();

    result = MyLib_AnalyzeArray_u32(array, 1U, 65535U);

    TEST_ASSERT_EQUAL_UINT16(65535U, array[0]);
    TEST_ASSERT_EQUAL_UINT32(65535U, result);
}
/**
 * @brief Test: valid pointer with len_u32=2, factor_u16=1, initial values={10, 20} → array becomes {10, 20}, return 30
 */
void test_len_2_factor_1_values_10_20_becomes_10_20_returns_30(void)
{
    uint16_t array[2] = {10U, 20U};
    uint32_t result;

    MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(30U, NULL, 0U);
    MyLib_ComputeAdjustedValue_u32_IgnoreArg_delta_pc_u16();

    result = MyLib_AnalyzeArray_u32(array, 2U, 1U);

    TEST_ASSERT_EQUAL_UINT16(10U, array[0]);
    TEST_ASSERT_EQUAL_UINT16(20U, array[1]);
    TEST_ASSERT_EQUAL_UINT32(30U, result);
}
/**
 * @brief Test: valid pointer with len_u32=2, factor_u16=3, initial values={5, 10} → array becomes {15, 30}, return 45
 */
void test_len_2_factor_3_values_5_10_becomes_15_30_returns_45(void)
{
    uint16_t array[2] = {5U, 10U};
    uint32_t result;

    MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(45U, NULL, 0U);
    MyLib_ComputeAdjustedValue_u32_IgnoreArg_delta_pc_u16();

    result = MyLib_AnalyzeArray_u32(array, 2U, 3U);

    TEST_ASSERT_EQUAL_UINT16(15U, array[0]);
    TEST_ASSERT_EQUAL_UINT16(30U, array[1]);
    TEST_ASSERT_EQUAL_UINT32(45U, result);
}
void test_len_300_factor_1_all_1_unchanged_returns_300(void)
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

    for (i = 0U; i < 300U; i++)
    {
        TEST_ASSERT_EQUAL_UINT16(1U, array[i]);
    }
    TEST_ASSERT_EQUAL_UINT32(300U, result);
}
void test_len_599_factor_1_all_1_unchanged_returns_599(void)
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

    for (i = 0U; i < 599U; i++)
    {
        TEST_ASSERT_EQUAL_UINT16(1U, array[i]);
    }
    TEST_ASSERT_EQUAL_UINT32(599U, result);
}
void test_len_600_factor_1_all_1_unchanged_returns_600(void)
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

    for (i = 0U; i < 600U; i++)
    {
        TEST_ASSERT_EQUAL_UINT16(1U, array[i]);
    }
    TEST_ASSERT_EQUAL_UINT32(600U, result);
}
void test_len_1_factor_2_value_40000_wraps_to_14464_returns_14464(void)
{
    uint16_t array[1] = {40000U};
    uint32_t result;

    MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(14464U, NULL, 0U);
    MyLib_ComputeAdjustedValue_u32_IgnoreArg_delta_pc_u16();

    result = MyLib_AnalyzeArray_u32(array, 1U, 2U);

    TEST_ASSERT_EQUAL_UINT16(14464U, array[0]);
    TEST_ASSERT_EQUAL_UINT32(14464U, result);
}
/**
 * @brief Test: valid pointer with len_u32=3, factor_u16=10, initial values={100, 200, 300} → array becomes {1000, 2000, 3000}, return 6000
 */
void test_len_3_factor_10_values_100_200_300_becomes_1000_2000_3000_returns_6000(void)
{
    uint16_t array[3] = {100U, 200U, 300U};
    uint32_t result;

    MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(6000U, NULL, 0U);
    MyLib_ComputeAdjustedValue_u32_IgnoreArg_delta_pc_u16();

    result = MyLib_AnalyzeArray_u32(array, 3U, 10U);

    TEST_ASSERT_EQUAL_UINT16(1000U, array[0]);
    TEST_ASSERT_EQUAL_UINT16(2000U, array[1]);
    TEST_ASSERT_EQUAL_UINT16(3000U, array[2]);
    TEST_ASSERT_EQUAL_UINT32(6000U, result);
}
/**
 * @brief Test: valid pointer with len_u32=2, factor_u16=65535, initial values={1, 1} → array becomes {65535, 65535}, sum wraps to 65534, return 65534
 */
void test_len_2_factor_65535_values_1_1_becomes_65535_65535_sum_wraps_to_65534(void)
{
    uint16_t array[2] = {1U, 1U};
    uint32_t result;

    MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(131070U, NULL, 0U);
    MyLib_ComputeAdjustedValue_u32_IgnoreArg_delta_pc_u16();

    result = MyLib_AnalyzeArray_u32(array, 2U, 65535U);

    TEST_ASSERT_EQUAL_UINT16(65535U, array[0]);
    TEST_ASSERT_EQUAL_UINT16(65535U, array[1]);
    TEST_ASSERT_EQUAL_UINT32(131070U, result);
}
void test_len_1_factor_1_value_65535_remains_65535_returns_65535(void)
{
    uint16_t array[1] = {65535U};
    uint32_t result;

    MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(65535U, NULL, 0U);
    MyLib_ComputeAdjustedValue_u32_IgnoreArg_delta_pc_u16();

    result = MyLib_AnalyzeArray_u32(array, 1U, 1U);

    TEST_ASSERT_EQUAL_UINT16(65535U, array[0]);
    TEST_ASSERT_EQUAL_UINT32(65535U, result);
}
void test_len_1_factor_32768_value_2_wraps_to_0_returns_0(void)
{
    uint16_t array[1] = {2U};
    uint32_t result;

    MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(0U, NULL, 0U);
    MyLib_ComputeAdjustedValue_u32_IgnoreArg_delta_pc_u16();

    result = MyLib_AnalyzeArray_u32(array, 1U, 32768U);

    TEST_ASSERT_EQUAL_UINT16(0U, array[0]);
    TEST_ASSERT_EQUAL_UINT32(0U, result);
}
