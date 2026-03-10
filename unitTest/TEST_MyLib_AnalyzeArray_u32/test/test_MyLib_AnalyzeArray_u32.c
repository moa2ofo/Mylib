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
void test_NULL_ptr_len0_factor0_returns0(void)
{
    uint32_t result;

    result = MyLib_AnalyzeArray_u32(NULL, 0, 0);

    TEST_ASSERT_EQUAL_UINT32(0, result);
}
void test_NULL_ptr_len1_factor1_returns0(void)
{
    uint32_t result;

    result = MyLib_AnalyzeArray_u32(NULL, 1, 1);

    TEST_ASSERT_EQUAL_UINT32(0, result);
}
void test_valid_ptr_len0_factor1_returns0_unchanged(void)
{
    uint16_t array[1] = {42};
    uint32_t result;

    result = MyLib_AnalyzeArray_u32(array, 0, 1);

    TEST_ASSERT_EQUAL_UINT32(0, result);
    TEST_ASSERT_EQUAL_UINT16(42, array[0]);
}
/**
 * @brief Test: Valid pointer with len_u32 = 1, factor_u16 = 0, array = {10} → array becomes {0}, return 0
 */
void test_len1_factor0_array10_becomes0_return0(void)
{
    uint16_t array[1] = {10};
    uint32_t result;

    MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(0, NULL, 0);
    MyLib_ComputeAdjustedValue_u32_IgnoreArg_delta_pc_u16();

    result = MyLib_AnalyzeArray_u32(array, 1, 0);

    TEST_ASSERT_EQUAL_UINT32(0, result);
    TEST_ASSERT_EQUAL_UINT16(0, array[0]);
}
/**
 * @brief Test: Valid pointer with len_u32 = 1, factor_u16 = 1, array = {0} → array remains {0}, return 0
 */
void test_len1_factor1_array0_remains0_return0(void)
{
    uint16_t array[1] = {0};
    uint32_t result;

    MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(0, NULL, 0);
    MyLib_ComputeAdjustedValue_u32_IgnoreArg_delta_pc_u16();

    result = MyLib_AnalyzeArray_u32(array, 1, 1);

    TEST_ASSERT_EQUAL_UINT32(0, result);
    TEST_ASSERT_EQUAL_UINT16(0, array[0]);
}
/**
 * @brief Test: Valid pointer with len_u32 = 1, factor_u16 = 1, array = {1} → array remains {1}, return 1
 */
void test_len1_factor1_array1_remains1_return1(void)
{
    uint16_t array[1] = {1};
    uint32_t result;

    MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(1, NULL, 0);
    MyLib_ComputeAdjustedValue_u32_IgnoreArg_delta_pc_u16();

    result = MyLib_AnalyzeArray_u32(array, 1, 1);

    TEST_ASSERT_EQUAL_UINT32(1, result);
    TEST_ASSERT_EQUAL_UINT16(1, array[0]);
}
/**
 * @brief Test: Valid pointer with len_u32 = 1, factor_u16 = 1, array = {100} → array remains {100}, return 100
 */
void test_len1_factor1_array100_remains100_return100(void)
{
    uint16_t array[1] = {100};
    uint32_t result;

    MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(100, NULL, 0);
    MyLib_ComputeAdjustedValue_u32_IgnoreArg_delta_pc_u16();

    result = MyLib_AnalyzeArray_u32(array, 1, 1);

    TEST_ASSERT_EQUAL_UINT32(100, result);
    TEST_ASSERT_EQUAL_UINT16(100, array[0]);
}
/**
 * @brief Test: Valid pointer with len_u32 = 1, factor_u16 = 1, array = {599} → array remains {599}, return 599
 */
void test_len1_factor1_array599_remains599_return599(void)
{
    uint16_t array[1] = {599};
    uint32_t result;

    MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(599, NULL, 0);
    MyLib_ComputeAdjustedValue_u32_IgnoreArg_delta_pc_u16();

    result = MyLib_AnalyzeArray_u32(array, 1, 1);

    TEST_ASSERT_EQUAL_UINT32(599, result);
    TEST_ASSERT_EQUAL_UINT16(599, array[0]);
}
/**
 * @brief Test: Valid pointer with len_u32 = 1, factor_u16 = 1, array = {600} → array remains {600}, return 600
 */
void test_len1_factor1_array600_remains600_return600(void)
{
    uint16_t array[1] = {600};
    uint32_t result;

    MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(600, NULL, 0);
    MyLib_ComputeAdjustedValue_u32_IgnoreArg_delta_pc_u16();

    result = MyLib_AnalyzeArray_u32(array, 1, 1);

    TEST_ASSERT_EQUAL_UINT32(600, result);
    TEST_ASSERT_EQUAL_UINT16(600, array[0]);
}
/**
 * @brief Test: Valid pointer with len_u32 = 2, factor_u16 = 1, array = {100, 200} → array remains {100, 200}, return 300
 */
void test_len2_factor1_array100_200_remains_return300(void)
{
    uint16_t array[2] = {100, 200};
    uint32_t result;

    MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(300, NULL, 0);
    MyLib_ComputeAdjustedValue_u32_IgnoreArg_delta_pc_u16();

    result = MyLib_AnalyzeArray_u32(array, 2, 1);

    TEST_ASSERT_EQUAL_UINT32(300, result);
    TEST_ASSERT_EQUAL_UINT16(100, array[0]);
    TEST_ASSERT_EQUAL_UINT16(200, array[1]);
}
/**
 * @brief Test: Valid pointer with len_u32 = 300, factor_u16 = 1, array = all {1} → array remains all {1}, return 300
 */
void test_len300_factor1_arrayAll1_remains_return300(void)
{
    uint16_t array[300];
    uint32_t result;
    size_t i;

    for (i = 0; i < 300; i++)
    {
        array[i] = 1;
    }

    MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(300, NULL, 0);
    MyLib_ComputeAdjustedValue_u32_IgnoreArg_delta_pc_u16();

    result = MyLib_AnalyzeArray_u32(array, 300, 1);

    TEST_ASSERT_EQUAL_UINT32(300, result);
    for (i = 0; i < 300; i++)
    {
        TEST_ASSERT_EQUAL_UINT16(1, array[i]);
    }
}
/**
 * @brief Test: Valid pointer with len_u32 = 599, factor_u16 = 1, array = all {1} → array remains all {1}, return 599
 */
void test_len599_factor1_arrayAll1_remains_return599(void)
{
    uint16_t array[599];
    uint32_t result;
    size_t i;

    for (i = 0; i < 599; i++)
    {
        array[i] = 1;
    }

    MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(599, NULL, 0);
    MyLib_ComputeAdjustedValue_u32_IgnoreArg_delta_pc_u16();

    result = MyLib_AnalyzeArray_u32(array, 599, 1);

    TEST_ASSERT_EQUAL_UINT32(599, result);
    for (i = 0; i < 599; i++)
    {
        TEST_ASSERT_EQUAL_UINT16(1, array[i]);
    }
}
/**
 * @brief Test: Valid pointer with len_u32 = 600, factor_u16 = 1, array = all {1} → array remains all {1}, return 600
 */
void test_len600_factor1_arrayAll1_remains_return600(void)
{
    uint16_t array[600];
    uint32_t result;
    size_t i;

    for (i = 0; i < 600; i++)
    {
        array[i] = 1;
    }

    MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(600, NULL, 0);
    MyLib_ComputeAdjustedValue_u32_IgnoreArg_delta_pc_u16();

    result = MyLib_AnalyzeArray_u32(array, 600, 1);

    TEST_ASSERT_EQUAL_UINT32(600, result);
    for (i = 0; i < 600; i++)
    {
        TEST_ASSERT_EQUAL_UINT16(1, array[i]);
    }
}
/**
 * @brief Test: Valid pointer with len_u32 = 1, factor_u16 = 2, array = {10} → array becomes {20}, return 20
 */
void test_len1_factor2_array10_becomes20_return20(void)
{
    uint16_t array[1] = {10};
    uint32_t result;

    MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(20, NULL, 0);
    MyLib_ComputeAdjustedValue_u32_IgnoreArg_delta_pc_u16();

    result = MyLib_AnalyzeArray_u32(array, 1, 2);

    TEST_ASSERT_EQUAL_UINT32(20, result);
    TEST_ASSERT_EQUAL_UINT16(20, array[0]);
}
/**
 * @brief Test: Valid pointer with len_u32 = 1, factor_u16 = 100, array = {5} → array becomes {500}, return 500
 */
void test_len1_factor100_array5_becomes500_return500(void)
{
    uint16_t array[1] = {5};
    uint32_t result;

    MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(500, NULL, 0);
    MyLib_ComputeAdjustedValue_u32_IgnoreArg_delta_pc_u16();

    result = MyLib_AnalyzeArray_u32(array, 1, 100);

    TEST_ASSERT_EQUAL_UINT32(500, result);
    TEST_ASSERT_EQUAL_UINT16(500, array[0]);
}
/**
 * @brief Test: Valid pointer with len_u32 = 1, factor_u16 = 32767, array = {1} → array becomes {32767}, return 32767
 */
void test_len1_factor32767_array1_becomes32767_return32767(void)
{
    uint16_t array[1] = {1};
    uint32_t result;

    MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(32767, NULL, 0);
    MyLib_ComputeAdjustedValue_u32_IgnoreArg_delta_pc_u16();

    result = MyLib_AnalyzeArray_u32(array, 1, 32767);

    TEST_ASSERT_EQUAL_UINT32(32767, result);
    TEST_ASSERT_EQUAL_UINT16(32767, array[0]);
}
/**
 * @brief Test: Valid pointer with len_u32 = 1, factor_u16 = 65534, array = {1} → array becomes {65534}, return 65534
 */
void test_len1_factor65534_array1_becomes65534_return65534(void)
{
    uint16_t array[1] = {1};
    uint32_t result;

    MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(65534, NULL, 0);
    MyLib_ComputeAdjustedValue_u32_IgnoreArg_delta_pc_u16();

    result = MyLib_AnalyzeArray_u32(array, 1, 65534);

    TEST_ASSERT_EQUAL_UINT32(65534, result);
    TEST_ASSERT_EQUAL_UINT16(65534, array[0]);
}
/**
 * @brief Test: Valid pointer with len_u32 = 1, factor_u16 = 65535, array = {1} → array becomes {65535}, return 65535
 */
void test_len1_factor65535_array1_becomes65535_return65535(void)
{
    uint16_t array[1] = {1};
    uint32_t result;

    MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(65535, NULL, 0);
    MyLib_ComputeAdjustedValue_u32_IgnoreArg_delta_pc_u16();

    result = MyLib_AnalyzeArray_u32(array, 1, 65535);

    TEST_ASSERT_EQUAL_UINT32(65535, result);
    TEST_ASSERT_EQUAL_UINT16(65535, array[0]);
}
/**
 * @brief Test: Valid pointer with len_u32 = 1, factor_u16 = 2, array = {65535} → array wraps to {65534}, return 65534
 */
void test_len1_factor2_array65535_wraps65534_return65534(void)
{
    uint16_t array[1] = {65535};
    uint32_t result;

    MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(65534, NULL, 0);
    MyLib_ComputeAdjustedValue_u32_IgnoreArg_delta_pc_u16();

    result = MyLib_AnalyzeArray_u32(array, 1, 2);

    TEST_ASSERT_EQUAL_UINT32(65534, result);
    TEST_ASSERT_EQUAL_UINT16(65534, array[0]);
}
/**
 * @brief Test: Valid pointer with len_u32 = 2, factor_u16 = 2, array = {32767, 32768} → array becomes {65534, 0}, sum wraps to 65534
 */
void test_len2_factor2_array32767_32768_becomes65534_0_sum65534(void)
{
    uint16_t array[2] = {32767, 32768};
    uint32_t result;

    MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(65534, NULL, 0);
    MyLib_ComputeAdjustedValue_u32_IgnoreArg_delta_pc_u16();

    result = MyLib_AnalyzeArray_u32(array, 2, 2);

    TEST_ASSERT_EQUAL_UINT32(65534, result);
    TEST_ASSERT_EQUAL_UINT16(65534, array[0]);
    TEST_ASSERT_EQUAL_UINT16(0, array[1]);
}
/**
 * @brief Test: Valid pointer with len_u32 = 3, factor_u16 = 3, array = {10, 20, 30} → array becomes {30, 60, 90}, return 180
 */
void test_len3_factor3_array10_20_30_becomes30_60_90_return180(void)
{
    uint16_t array[3] = {10, 20, 30};
    uint32_t result;

    MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(180, NULL, 0);
    MyLib_ComputeAdjustedValue_u32_IgnoreArg_delta_pc_u16();

    result = MyLib_AnalyzeArray_u32(array, 3, 3);

    TEST_ASSERT_EQUAL_UINT32(180, result);
    TEST_ASSERT_EQUAL_UINT16(30, array[0]);
    TEST_ASSERT_EQUAL_UINT16(60, array[1]);
    TEST_ASSERT_EQUAL_UINT16(90, array[2]);
}
/**
 * @brief Test: Valid pointer with len_u32 = 600, factor_u16 = 10, array = all {50} → array becomes all {500}, sum wraps as per uint32_t overflow
 */
void test_len600_factor10_arrayAll50_becomesAll500_sumWraps(void)
{
    uint16_t array[600];
    uint32_t result;
    uint32_t expected_sum;
    size_t i;

    for (i = 0; i < 600; i++)
    {
        array[i] = 50;
    }

    expected_sum = (uint32_t)(600 * 500);

    MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(expected_sum, NULL, 0);
    MyLib_ComputeAdjustedValue_u32_IgnoreArg_delta_pc_u16();

    result = MyLib_AnalyzeArray_u32(array, 600, 10);

    TEST_ASSERT_EQUAL_UINT32(expected_sum, result);
    for (i = 0; i < 600; i++)
    {
        TEST_ASSERT_EQUAL_UINT16(500, array[i]);
    }
}
/**
 * @brief Test: Valid pointer with len_u32 = 1, factor_u16 = 65535, array = {65535} → array wraps to {1}, return 1
 */
void test_len1_factor65535_array65535_wraps1_return1(void)
{
    uint16_t array[1] = {65535};
    uint32_t result;

    MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(1, NULL, 0);
    MyLib_ComputeAdjustedValue_u32_IgnoreArg_delta_pc_u16();

    result = MyLib_AnalyzeArray_u32(array, 1, 65535);

    TEST_ASSERT_EQUAL_UINT32(1, result);
    TEST_ASSERT_EQUAL_UINT16(1, array[0]);
}
/**
 * @brief Test: Valid pointer with len_u32 = 2, factor_u16 = 1, array = {65535, 1} → array remains {65535, 1}, sum wraps to 0
 */
void test_len2_factor1_array65535_1_remains_sumWraps0(void)
{
    uint16_t array[2] = {65535, 1};
    uint32_t result;

    MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(0, NULL, 0);
    MyLib_ComputeAdjustedValue_u32_IgnoreArg_delta_pc_u16();

    result = MyLib_AnalyzeArray_u32(array, 2, 1);

    TEST_ASSERT_EQUAL_UINT32(0, result);
    TEST_ASSERT_EQUAL_UINT16(65535, array[0]);
    TEST_ASSERT_EQUAL_UINT16(1, array[1]);
}
