#include "MyLib_AnalyzeArray_u32.h"
#include "mock_MyLib.h"
#include "unity.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>




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
void test_NullPointer_ZeroLen_ZeroFactor_Returns0(void)
{
    uint32_t result;

    result = MyLib_AnalyzeArray_u32(NULL, 0U, 0U);

    TEST_ASSERT_EQUAL_UINT32(0U, result);
}
void test_NullPointer_NonZeroLen_Returns0(void)
{
    uint32_t result;

    result = MyLib_AnalyzeArray_u32(NULL, 1U, 1U);

    TEST_ASSERT_EQUAL_UINT32(0U, result);
}
void test_ValidPointer_ZeroLen_Returns0_ArrayUnchanged(void)
{
    uint16_t array[1] = {42U};
    uint32_t result;

    result = MyLib_AnalyzeArray_u32(array, 0U, 1U);

    TEST_ASSERT_EQUAL_UINT32(0U, result);
    TEST_ASSERT_EQUAL_UINT16(42U, array[0]);
}
/**
 * @brief Test: Valid pointer with len_u32 = 1, factor_u16 = 0, array = {10} → array becomes {0}, return 0
 */
void test_OneElement_ZeroFactor_ArrayBecomesZero(void)
{
    uint16_t array[1] = {10U};
    uint32_t result;

    MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(0U, NULL, 0U);

    result = MyLib_AnalyzeArray_u32(array, 1U, 0U);

    TEST_ASSERT_EQUAL_UINT32(0U, result);
    TEST_ASSERT_EQUAL_UINT16(0U, array[0]);
}
/**
 * @brief Test: Valid pointer with len_u32 = 1, factor_u16 = 1, array = {0} → array remains {0}, return 0
 */
void test_OneElement_FactorOne_ArrayZero_RemainsZero(void)
{
    uint16_t array[1] = {0U};
    uint32_t result;

    MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(0U, NULL, 0U);

    result = MyLib_AnalyzeArray_u32(array, 1U, 1U);

    TEST_ASSERT_EQUAL_UINT32(0U, result);
    TEST_ASSERT_EQUAL_UINT16(0U, array[0]);
}
/**
 * @brief Test: Valid pointer with len_u32 = 1, factor_u16 = 1, array = {1} → array remains {1}, return 1
 */
void test_OneElement_FactorOne_ArrayOne_RemainsOne(void)
{
    uint16_t array[1] = {1U};
    uint32_t result;

    MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(1U, NULL, 0U);

    result = MyLib_AnalyzeArray_u32(array, 1U, 1U);

    TEST_ASSERT_EQUAL_UINT32(1U, result);
    TEST_ASSERT_EQUAL_UINT16(1U, array[0]);
}
/**
 * @brief Test: Valid pointer with len_u32 = 1, factor_u16 = 1, array = {100} → array remains {100}, return 100
 */
void test_OneElement_FactorOne_Array100_Remains100(void)
{
    uint16_t array[1] = {100U};
    uint32_t result;

    MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(100U, NULL, 0U);

    result = MyLib_AnalyzeArray_u32(array, 1U, 1U);

    TEST_ASSERT_EQUAL_UINT32(100U, result);
    TEST_ASSERT_EQUAL_UINT16(100U, array[0]);
}
/**
 * @brief Test: Valid pointer with len_u32 = 1, factor_u16 = 1, array = {599} → array remains {599}, return 599
 */
void test_OneElement_FactorOne_Array599_Remains599(void)
{
    uint16_t array[1] = {599U};
    uint32_t result;

    MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(599U, NULL, 0U);

    result = MyLib_AnalyzeArray_u32(array, 1U, 1U);

    TEST_ASSERT_EQUAL_UINT32(599U, result);
    TEST_ASSERT_EQUAL_UINT16(599U, array[0]);
}
/**
 * @brief Test: Valid pointer with len_u32 = 1, factor_u16 = 1, array = {600} → array remains {600}, return 600
 */
void test_OneElement_FactorOne_Array600_Remains600(void)
{
    uint16_t array[1] = {600U};
    uint32_t result;

    MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(600U, NULL, 0U);

    result = MyLib_AnalyzeArray_u32(array, 1U, 1U);

    TEST_ASSERT_EQUAL_UINT32(600U, result);
    TEST_ASSERT_EQUAL_UINT16(600U, array[0]);
}
/**
 * @brief Test: Valid pointer with len_u32 = 2, factor_u16 = 1, array = {100, 200} → array remains {100, 200}, return 300
 */
void test_TwoElements_FactorOne_ArrayUnchanged_Return300(void)
{
    uint16_t array[2] = {100U, 200U};
    uint32_t result;

    MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(300U, NULL, 0U);

    result = MyLib_AnalyzeArray_u32(array, 2U, 1U);

    TEST_ASSERT_EQUAL_UINT32(300U, result);
    TEST_ASSERT_EQUAL_UINT16(100U, array[0]);
    TEST_ASSERT_EQUAL_UINT16(200U, array[1]);
}
void test_300Elements_FactorOne_AllOnes_Return300(void)
{
    uint16_t array[300];
    uint32_t result;
    size_t i;

    for (i = 0U; i < 300U; i++)
    {
        array[i] = 1U;
    }

    MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(300U, NULL, 0U);

    result = MyLib_AnalyzeArray_u32(array, 300U, 1U);

    TEST_ASSERT_EQUAL_UINT32(300U, result);
    for (i = 0U; i < 300U; i++)
    {
        TEST_ASSERT_EQUAL_UINT16(1U, array[i]);
    }
}
void test_599Elements_FactorOne_AllOnes_Return599(void)
{
    uint16_t array[599];
    uint32_t result;
    size_t i;

    for (i = 0U; i < 599U; i++)
    {
        array[i] = 1U;
    }

    MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(599U, NULL, 0U);

    result = MyLib_AnalyzeArray_u32(array, 599U, 1U);

    TEST_ASSERT_EQUAL_UINT32(599U, result);
    for (i = 0U; i < 599U; i++)
    {
        TEST_ASSERT_EQUAL_UINT16(1U, array[i]);
    }
}
void test_600Elements_FactorOne_AllOnes_Return600(void)
{
    uint16_t array[600];
    uint32_t result;
    size_t i;

    for (i = 0U; i < 600U; i++)
    {
        array[i] = 1U;
    }

    MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(600U, NULL, 0U);

    result = MyLib_AnalyzeArray_u32(array, 600U, 1U);

    TEST_ASSERT_EQUAL_UINT32(600U, result);
    for (i = 0U; i < 600U; i++)
    {
        TEST_ASSERT_EQUAL_UINT16(1U, array[i]);
    }
}
/**
 * @brief Test: Valid pointer with len_u32 = 1, factor_u16 = 2, array = {10} → array becomes {20}, return 20
 */
void test_OneElement_FactorTwo_Array10_Becomes20(void)
{
    uint16_t array[1] = {10U};
    uint32_t result;

    MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(20U, NULL, 0U);

    result = MyLib_AnalyzeArray_u32(array, 1U, 2U);

    TEST_ASSERT_EQUAL_UINT32(20U, result);
    TEST_ASSERT_EQUAL_UINT16(20U, array[0]);
}
/**
 * @brief Test: Valid pointer with len_u32 = 1, factor_u16 = 100, array = {5} → array becomes {500}, return 500
 */
void test_OneElement_Factor100_Array5_Becomes500(void)
{
    uint16_t array[1] = {5U};
    uint32_t result;

    MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(500U, NULL, 0U);

    result = MyLib_AnalyzeArray_u32(array, 1U, 100U);

    TEST_ASSERT_EQUAL_UINT32(500U, result);
    TEST_ASSERT_EQUAL_UINT16(500U, array[0]);
}
/**
 * @brief Test: Valid pointer with len_u32 = 1, factor_u16 = 65534, array = {1} → array becomes {65534}, return 65534
 */
void test_OneElement_Factor65534_Array1_Becomes65534(void)
{
    uint16_t array[1] = {1U};
    uint32_t result;

    MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(65534U, NULL, 0U);

    result = MyLib_AnalyzeArray_u32(array, 1U, 65534U);

    TEST_ASSERT_EQUAL_UINT32(65534U, result);
    TEST_ASSERT_EQUAL_UINT16(65534U, array[0]);
}
/**
 * @brief Test: Valid pointer with len_u32 = 1, factor_u16 = 65535, array = {1} → array becomes {65535}, return 65535
 */
void test_OneElement_Factor65535_Array1_Becomes65535(void)
{
    uint16_t array[1] = {1U};
    uint32_t result;

    MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(65535U, NULL, 0U);

    result = MyLib_AnalyzeArray_u32(array, 1U, 65535U);

    TEST_ASSERT_EQUAL_UINT32(65535U, result);
    TEST_ASSERT_EQUAL_UINT16(65535U, array[0]);
}
/**
 * @brief Test: Valid pointer with len_u32 = 1, factor_u16 = 2, array = {65535} → array wraps to {65534}, return 65534
 */
void test_OneElement_FactorTwo_Array65535_WrapsTo65534(void)
{
    uint16_t array[1] = {65535U};
    uint32_t result;

    MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(65534U, NULL, 0U);

    result = MyLib_AnalyzeArray_u32(array, 1U, 2U);

    TEST_ASSERT_EQUAL_UINT32(65534U, result);
    TEST_ASSERT_EQUAL_UINT16(65534U, array[0]);
}
/**
 * @brief Test: Valid pointer with len_u32 = 2, factor_u16 = 2, array = {32767, 32768} → array becomes {65534, 0}, sum wraps to 65534
 */
void test_TwoElements_FactorTwo_ArrayWraps_SumWraps(void)
{
    uint16_t array[2] = {32767U, 32768U};
    uint32_t result;

    MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(65534U, NULL, 0U);

    result = MyLib_AnalyzeArray_u32(array, 2U, 2U);

    TEST_ASSERT_EQUAL_UINT32(65534U, result);
    TEST_ASSERT_EQUAL_UINT16(65534U, array[0]);
    TEST_ASSERT_EQUAL_UINT16(0U, array[1]);
}
/**
 * @brief Test: Valid pointer with len_u32 = 3, factor_u16 = 3, array = {10, 20, 30} → array becomes {30, 60, 90}, return 180
 */
void test_ThreeElements_FactorThree_ArrayScaled_Return180(void)
{
    uint16_t array[3] = {10U, 20U, 30U};
    uint32_t result;

    MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(180U, NULL, 0U);

    result = MyLib_AnalyzeArray_u32(array, 3U, 3U);

    TEST_ASSERT_EQUAL_UINT32(180U, result);
    TEST_ASSERT_EQUAL_UINT16(30U, array[0]);
    TEST_ASSERT_EQUAL_UINT16(60U, array[1]);
    TEST_ASSERT_EQUAL_UINT16(90U, array[2]);
}
/**
 * @brief Test: Valid pointer with len_u32 = 5, factor_u16 = 10, array = {1, 2, 3, 4, 5} → array becomes {10, 20, 30, 40, 50}, return 150
 */
void test_FiveElements_Factor10_ArrayScaled_Return150(void)
{
    uint16_t array[5] = {1U, 2U, 3U, 4U, 5U};
    uint32_t result;

    MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(150U, NULL, 0U);

    result = MyLib_AnalyzeArray_u32(array, 5U, 10U);

    TEST_ASSERT_EQUAL_UINT32(150U, result);
    TEST_ASSERT_EQUAL_UINT16(10U, array[0]);
    TEST_ASSERT_EQUAL_UINT16(20U, array[1]);
    TEST_ASSERT_EQUAL_UINT16(30U, array[2]);
    TEST_ASSERT_EQUAL_UINT16(40U, array[3]);
    TEST_ASSERT_EQUAL_UINT16(50U, array[4]);
}
void test_600Elements_Factor65535_AllOnes_SumWraps(void)
{
    uint16_t array[600];
    uint32_t result;
    size_t i;
    uint32_t expected_sum;

    for (i = 0U; i < 600U; i++)
    {
        array[i] = 1U;
    }

    expected_sum = (uint32_t)((uint64_t)600U * 65535U);

    MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(expected_sum, NULL, 0U);

    result = MyLib_AnalyzeArray_u32(array, 600U, 65535U);

    TEST_ASSERT_EQUAL_UINT32(expected_sum, result);
    for (i = 0U; i < 600U; i++)
    {
        TEST_ASSERT_EQUAL_UINT16(65535U, array[i]);
    }
}
