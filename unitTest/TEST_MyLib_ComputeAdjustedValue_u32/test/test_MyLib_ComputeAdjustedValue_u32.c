#include "MyLib_ComputeAdjustedValue_u32.h"
#include "mock_MyLib.h"
#include "unity.h"




void setUp(void)
{
}
void tearDown(void)
{
}
void test_base_0_delta_NULL(void)
{
    uint32_t l_result_u32;
    uint32_t l_expected_u32 = 42U;

    InternalHelper_u32_ExpectAndReturn(0U, (uint16_t)MYLIB_MULT_VALUE_U8, l_expected_u32);

    l_result_u32 = MyLib_ComputeAdjustedValue_u32(0U, NULL);

    TEST_ASSERT_EQUAL_UINT32(l_expected_u32, l_result_u32);
}
void test_base_0_delta_1(void)
{
    uint32_t l_result_u32;
    uint32_t l_expected_u32 = 42U;
    uint16_t l_delta_u16 = 1U;

    InternalHelper_u32_ExpectAndReturn(0U, (uint16_t)MYLIB_MULT_VALUE_U8, l_expected_u32);

    l_result_u32 = MyLib_ComputeAdjustedValue_u32(0U, &l_delta_u16);

    TEST_ASSERT_EQUAL_UINT32(l_expected_u32, l_result_u32);
}
void test_base_1_delta_NULL(void)
{
    uint32_t l_result_u32;
    uint32_t l_expected_u32 = 100U;

    InternalHelper_u32_ExpectAndReturn(1U, (uint16_t)MYLIB_MULT_VALUE_U8, l_expected_u32);

    l_result_u32 = MyLib_ComputeAdjustedValue_u32(1U, NULL);

    TEST_ASSERT_EQUAL_UINT32(l_expected_u32, l_result_u32);
}
void test_base_1_delta_1(void)
{
    uint32_t l_result_u32;
    uint32_t l_expected_u32 = 100U;
    uint16_t l_delta_u16 = 1U;

    InternalHelper_u32_ExpectAndReturn(1U, (uint16_t)MYLIB_MULT_VALUE_U8, l_expected_u32);

    l_result_u32 = MyLib_ComputeAdjustedValue_u32(1U, &l_delta_u16);

    TEST_ASSERT_EQUAL_UINT32(l_expected_u32, l_result_u32);
}
void test_base_300_delta_NULL(void)
{
    uint32_t l_result_u32;
    uint32_t l_expected_u32 = 250U;

    InternalHelper_u32_ExpectAndReturn(300U, (uint16_t)MYLIB_MULT_VALUE_U8, l_expected_u32);

    l_result_u32 = MyLib_ComputeAdjustedValue_u32(300U, NULL);

    TEST_ASSERT_EQUAL_UINT32(l_expected_u32, l_result_u32);
}
void test_base_300_delta_32768(void)
{
    uint32_t l_result_u32;
    uint32_t l_expected_u32 = 350U;
    uint16_t l_delta_u16 = 32768U;
    uint32_t l_intermediate_u32 = 300U * 32768U;

    InternalHelper_u32_ExpectAndReturn(l_intermediate_u32, (uint16_t)MYLIB_MULT_VALUE_U8, l_expected_u32);

    l_result_u32 = MyLib_ComputeAdjustedValue_u32(300U, &l_delta_u16);

    TEST_ASSERT_EQUAL_UINT32(l_expected_u32, l_result_u32);
}
void test_base_599_delta_NULL(void)
{
    uint32_t l_result_u32;
    uint32_t l_expected_u32 = 450U;

    InternalHelper_u32_ExpectAndReturn(599U, (uint16_t)MYLIB_MULT_VALUE_U8, l_expected_u32);

    l_result_u32 = MyLib_ComputeAdjustedValue_u32(599U, NULL);

    TEST_ASSERT_EQUAL_UINT32(l_expected_u32, l_result_u32);
}
void test_base_599_delta_1(void)
{
    uint32_t l_result_u32;
    uint32_t l_expected_u32 = 450U;
    uint16_t l_delta_u16 = 1U;

    InternalHelper_u32_ExpectAndReturn(599U, (uint16_t)MYLIB_MULT_VALUE_U8, l_expected_u32);

    l_result_u32 = MyLib_ComputeAdjustedValue_u32(599U, &l_delta_u16);

    TEST_ASSERT_EQUAL_UINT32(l_expected_u32, l_result_u32);
}
void test_base_600_delta_NULL(void)
{
    uint32_t l_result_u32;
    uint32_t l_expected_u32 = 500U;

    InternalHelper_u32_ExpectAndReturn(600U, (uint16_t)MYLIB_MULT_VALUE_U8, l_expected_u32);

    l_result_u32 = MyLib_ComputeAdjustedValue_u32(600U, NULL);

    TEST_ASSERT_EQUAL_UINT32(l_expected_u32, l_result_u32);
}
void test_base_600_delta_1(void)
{
    uint32_t l_result_u32;
    uint32_t l_expected_u32 = 500U;
    uint16_t l_delta_u16 = 1U;

    InternalHelper_u32_ExpectAndReturn(600U, (uint16_t)MYLIB_MULT_VALUE_U8, l_expected_u32);

    l_result_u32 = MyLib_ComputeAdjustedValue_u32(600U, &l_delta_u16);

    TEST_ASSERT_EQUAL_UINT32(l_expected_u32, l_result_u32);
}
void test_base_0_delta_0(void)
{
    uint32_t l_result_u32;
    uint32_t l_expected_u32 = 0U;
    uint16_t l_delta_u16 = 0U;

    InternalHelper_u32_ExpectAndReturn(0U, (uint16_t)MYLIB_MULT_VALUE_U8, l_expected_u32);

    l_result_u32 = MyLib_ComputeAdjustedValue_u32(0U, &l_delta_u16);

    TEST_ASSERT_EQUAL_UINT32(l_expected_u32, l_result_u32);
}
void test_base_0_delta_1_duplicate(void)
{
    uint32_t l_result_u32;
    uint32_t l_expected_u32 = 42U;
    uint16_t l_delta_u16 = 1U;

    InternalHelper_u32_ExpectAndReturn(0U, (uint16_t)MYLIB_MULT_VALUE_U8, l_expected_u32);

    l_result_u32 = MyLib_ComputeAdjustedValue_u32(0U, &l_delta_u16);

    TEST_ASSERT_EQUAL_UINT32(l_expected_u32, l_result_u32);
}
void test_base_0_delta_65534(void)
{
    uint32_t l_result_u32;
    uint32_t l_expected_u32 = 0U;
    uint16_t l_delta_u16 = 65534U;

    InternalHelper_u32_ExpectAndReturn(0U, (uint16_t)MYLIB_MULT_VALUE_U8, l_expected_u32);

    l_result_u32 = MyLib_ComputeAdjustedValue_u32(0U, &l_delta_u16);

    TEST_ASSERT_EQUAL_UINT32(l_expected_u32, l_result_u32);
}
void test_base_0_delta_65535(void)
{
    uint32_t l_result_u32;
    uint32_t l_expected_u32 = 0U;
    uint16_t l_delta_u16 = 65535U;

    InternalHelper_u32_ExpectAndReturn(0U, (uint16_t)MYLIB_MULT_VALUE_U8, l_expected_u32);

    l_result_u32 = MyLib_ComputeAdjustedValue_u32(0U, &l_delta_u16);

    TEST_ASSERT_EQUAL_UINT32(l_expected_u32, l_result_u32);
}
void test_base_300_delta_0(void)
{
    uint32_t l_result_u32;
    uint32_t l_expected_u32 = 0U;
    uint16_t l_delta_u16 = 0U;

    InternalHelper_u32_ExpectAndReturn(0U, (uint16_t)MYLIB_MULT_VALUE_U8, l_expected_u32);

    l_result_u32 = MyLib_ComputeAdjustedValue_u32(300U, &l_delta_u16);

    TEST_ASSERT_EQUAL_UINT32(l_expected_u32, l_result_u32);
}
void test_base_300_delta_1(void)
{
    uint32_t l_result_u32;
    uint32_t l_expected_u32 = 250U;
    uint16_t l_delta_u16 = 1U;

    InternalHelper_u32_ExpectAndReturn(300U, (uint16_t)MYLIB_MULT_VALUE_U8, l_expected_u32);

    l_result_u32 = MyLib_ComputeAdjustedValue_u32(300U, &l_delta_u16);

    TEST_ASSERT_EQUAL_UINT32(l_expected_u32, l_result_u32);
}
void test_base_300_delta_65534(void)
{
    uint32_t l_result_u32;
    uint32_t l_expected_u32 = 400U;
    uint16_t l_delta_u16 = 65534U;
    uint32_t l_intermediate_u32 = 300U * 65534U;

    InternalHelper_u32_ExpectAndReturn(l_intermediate_u32, (uint16_t)MYLIB_MULT_VALUE_U8, l_expected_u32);

    l_result_u32 = MyLib_ComputeAdjustedValue_u32(300U, &l_delta_u16);

    TEST_ASSERT_EQUAL_UINT32(l_expected_u32, l_result_u32);
}
void test_base_300_delta_65535(void)
{
    uint32_t l_result_u32;
    uint32_t l_expected_u32 = 410U;
    uint16_t l_delta_u16 = 65535U;
    uint32_t l_intermediate_u32 = 300U * 65535U;

    InternalHelper_u32_ExpectAndReturn(l_intermediate_u32, (uint16_t)MYLIB_MULT_VALUE_U8, l_expected_u32);

    l_result_u32 = MyLib_ComputeAdjustedValue_u32(300U, &l_delta_u16);

    TEST_ASSERT_EQUAL_UINT32(l_expected_u32, l_result_u32);
}
void test_base_600_delta_0(void)
{
    uint32_t l_result_u32;
    uint32_t l_expected_u32 = 0U;
    uint16_t l_delta_u16 = 0U;

    InternalHelper_u32_ExpectAndReturn(0U, (uint16_t)MYLIB_MULT_VALUE_U8, l_expected_u32);

    l_result_u32 = MyLib_ComputeAdjustedValue_u32(600U, &l_delta_u16);

    TEST_ASSERT_EQUAL_UINT32(l_expected_u32, l_result_u32);
}
void test_base_600_delta_1_duplicate(void)
{
    uint32_t l_result_u32;
    uint32_t l_expected_u32 = 500U;
    uint16_t l_delta_u16 = 1U;

    InternalHelper_u32_ExpectAndReturn(600U, (uint16_t)MYLIB_MULT_VALUE_U8, l_expected_u32);

    l_result_u32 = MyLib_ComputeAdjustedValue_u32(600U, &l_delta_u16);

    TEST_ASSERT_EQUAL_UINT32(l_expected_u32, l_result_u32);
}
void test_base_600_delta_65534(void)
{
    uint32_t l_result_u32;
    uint32_t l_expected_u32 = 490U;
    uint16_t l_delta_u16 = 65534U;
    uint32_t l_intermediate_u32 = 600U * 65534U;

    InternalHelper_u32_ExpectAndReturn(l_intermediate_u32, (uint16_t)MYLIB_MULT_VALUE_U8, l_expected_u32);

    l_result_u32 = MyLib_ComputeAdjustedValue_u32(600U, &l_delta_u16);

    TEST_ASSERT_EQUAL_UINT32(l_expected_u32, l_result_u32);
}
void test_base_600_delta_65535(void)
{
    uint32_t l_result_u32;
    uint32_t l_expected_u32 = 495U;
    uint16_t l_delta_u16 = 65535U;
    uint32_t l_intermediate_u32 = 600U * 65535U;

    InternalHelper_u32_ExpectAndReturn(l_intermediate_u32, (uint16_t)MYLIB_MULT_VALUE_U8, l_expected_u32);

    l_result_u32 = MyLib_ComputeAdjustedValue_u32(600U, &l_delta_u16);

    TEST_ASSERT_EQUAL_UINT32(l_expected_u32, l_result_u32);
}
