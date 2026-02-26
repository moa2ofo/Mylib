#include "MyLib_UpdateCounter_u8.h"
#include "mock_MyLib.h"
#include "unity.h"
#include <string.h>




```c
#include "MyLib_UpdateCounter_u8.h"
#include "MyLib.h"

static uint32_t s_counterLimit_u32;
static bool s_saturationEn_b;

uint32_t GetCounterLimit_u32(void)
{
    return s_counterLimit_u32;
}

void SetCounterLimit_u32(uint32_t value)
{
    s_counterLimit_u32 = value;
}

bool GetSaturationEn_b(void)
{
    return s_saturationEn_b;
}

void SetSaturationEn_b(bool enable)
{
    s_saturationEn_b = enable;
}

void setUp(void)
{
    g_counter_u32 = 0U;
    s_counterLimit_u32 = 255U;
    s_saturationEn_b = false;
}

void tearDown(void)
{
}

void test_add_zero_counter_zero_saturation_disabled_limit_255(void)
{
    uint8_t result;
    
    g_counter_u32 = 0U;
    SetCounterLimit_u32(255U);
    SetSaturationEn_b(false);
    
    result = MyLib_UpdateCounter_u8(0U);
    
    TEST_ASSERT_EQUAL_UINT32(0U, g_counter_u32);
    TEST_ASSERT_EQUAL_UINT8(0U, result);
}

void test_add_one_counter_zero_saturation_disabled_limit_255(void)
{
    uint8_t result;
    
    g_counter_u32 = 0U;
    SetCounterLimit_u32(255U);
    SetSaturationEn_b(false);
    
    result = MyLib_UpdateCounter_u8(1U);
    
    TEST_ASSERT_EQUAL_UINT32(1U, g_counter_u32);
    TEST_ASSERT_EQUAL_UINT8(1U, result);
}

void test_add_127_counter_zero_saturation_disabled_limit_255(void)
{
    uint8_t result;
    
    g_counter_u32 = 0U;
    SetCounterLimit_u32(255U);
    SetSaturationEn_b(false);
    
    result = MyLib_UpdateCounter_u8(127U);
    
    TEST_ASSERT_EQUAL_UINT32(127U, g_counter_u32);
    TEST_ASSERT_EQUAL_UINT8(127U, result);
}

void test_add_254_counter_zero_saturation_disabled_limit_255(void)
{
    uint8_t result;
    
    g_counter_u32 = 0U;
    SetCounterLimit_u32(255U);
    SetSaturationEn_b(false);
    
    result = MyLib_UpdateCounter_u8(254U);
    
    TEST_ASSERT_EQUAL_UINT32(254U, g_counter_u32);
    TEST_ASSERT_EQUAL_UINT8(254U, result);
}

void test_add_255_counter_zero_saturation_disabled_limit_255(void)
{
    uint8_t result;
    
    g_counter_u32 = 0U;
    SetCounterLimit_u32(255U);
    SetSaturationEn_b(false);
    
    result = MyLib_UpdateCounter_u8(255U);
    
    TEST_ASSERT_EQUAL_UINT32(255U, g_counter_u32);
    TEST_ASSERT_EQUAL_UINT8(255U, result);
}

void test_add_256_counter_zero_saturation_disabled_limit_255(void)
{
    uint8_t result;
    
    g_counter_u32 = 0U;
    SetCounterLimit_u32(255U);
    SetSaturationEn_b(false);
    
    result = MyLib_UpdateCounter_u8(256U);
    
    TEST_ASSERT_EQUAL_UINT32(0U, g_counter_u32);
    TEST_ASSERT_EQUAL_UINT8(0U, result);
}

void test_add_300_counter_zero_saturation_disabled_limit_255(void)
{
    uint8_t result;
    
    g_counter_u32 = 0U;
    SetCounterLimit_u32(255U);
    SetSaturationEn_b(false);
    
    result = MyLib_UpdateCounter_u8(300U);
    
    TEST_ASSERT_EQUAL_UINT32(44U, g_counter_u32);
    TEST_ASSERT_EQUAL_UINT8(44U, result);
}

void test_add_uint32_max_counter_zero_saturation_disabled_limit_255(void)
{
    uint8_t result;
    uint8_t expected;
    
    g_counter_u32 = 0U;
    SetCounterLimit_u32(255U);
    SetSaturationEn_b(false);
    
    expected = (uint8_t)(UINT32_MAX % 256U);
    
    result = MyLib_UpdateCounter_u8(UINT32_MAX);
    
    TEST_ASSERT_EQUAL_UINT32(expected, g_counter_u32);
    TEST_ASSERT_EQUAL_UINT8(expected, result);
}

void test_add_one_counter_254_saturation_disabled_limit_255(void)
{
    uint8_t result;
    
    g_counter_u32 = 254U;
    SetCounterLimit_u32(255U);
    SetSaturationEn_b(false);
    
    result = MyLib_UpdateCounter_u8(1U);
    
    TEST_ASSERT_EQUAL_UINT32(255U, g_counter_u32);
    TEST_ASSERT_EQUAL_UINT8(255U, result);
}

void test_add_two_counter_254_saturation_disabled_limit_255(void)
{
    uint8_t result;
    
    g_counter_u32 = 254U;
    SetCounterLimit_u32(255U);
    SetSaturationEn_b(false);
    
    result = MyLib_UpdateCounter_u8(2U);
    
    TEST_ASSERT_EQUAL_UINT32(0U, g_counter_u32);
    TEST_ASSERT_EQUAL_UINT8(0U, result);
}

void test_add_ten_counter_250_saturation_disabled_limit_255(void)
{
    uint8_t result;
    
    g_counter_u32 = 250U;
    SetCounterLimit_u32(255U);
    SetSaturationEn_b(false);
    
    result = MyLib_UpdateCounter_u8(10U);
    
    TEST_ASSERT_EQUAL_UINT32(4U, g_counter_u32);
    TEST_ASSERT_EQUAL_UINT8(4U, result);
}

void test_add_one_counter_zero_saturation_enabled_limit_255(void)
{
    uint8_t result;
    
    g_counter_u32 = 0U;
    SetCounterLimit_u32(255U);
    SetSaturationEn_b(true);
    
    result = MyLib_UpdateCounter_u8(1U);
    
    TEST_ASSERT_EQUAL_UINT32(1U, g_counter_u32);
    TEST_ASSERT_EQUAL_UINT8(1U, result);
}

void test_add_127_counter_zero_saturation_enabled_limit_255(void)
{
    uint8_t result;
    
    g_counter_u32 = 0U;
    SetCounterLimit_u32(255U);
    SetSaturationEn_b(true);
    
    result = MyLib_UpdateCounter_u8(127U);
    
    TEST_ASSERT_EQUAL_UINT32(127U, g_counter_u32);
    TEST_ASSERT_EQUAL_UINT8(127U, result);
}

void test_add_255_counter_zero_saturation_enabled_limit_255(void)
{
    uint8_t result;
    
    g_counter_u32 = 0U;
    SetCounterLimit_u32(255U);
    SetSaturationEn_b(true);
    
    result = MyLib_UpdateCounter_u8(255U);
    
    TEST_ASSERT_EQUAL_UINT32(255U, g_counter_u32);
    TEST_ASSERT_EQUAL_UINT8(255U, result);
}

void test_add_256_counter_zero_saturation_enabled_limit_255(void)
{
    uint8_t result;
    
    g_counter_u32 = 0U;
    SetCounterLimit_u32(255U);
    SetSaturationEn_b(true);
    
    result = MyLib_UpdateCounter_u8(256U);
    
    TEST_ASSERT_EQUAL_UINT32(255U, g_counter_u32);
    TEST_ASSERT_EQUAL_UINT8(255U, result);
}

void test_add_300_counter_zero_saturation_enabled_limit_255(void)
{
    uint8_t result;
    
    g_counter_u32 = 0U;
    SetCounterLimit_u32(255U);
    SetSaturationEn_b(true);
    
    result = MyLib_UpdateCounter_u8(300U);
    
    TEST_ASSERT_EQUAL_UINT32(255U, g_counter_u32);
    TEST_ASSERT_EQUAL_UINT8(255U, result);
}

void test_add_uint32_max_counter_zero_saturation_enabled_limit_255(void)
{
    uint8_t result;
    
    g_counter_u32 = 0U;
    SetCounterLimit_u32(255U);
    SetSaturationEn_b(true);
    
    result = MyLib_UpdateCounter_u8(UINT32_MAX);
    
    TEST_ASSERT_EQUAL_UINT32(255U, g_counter_u32);
    TEST_ASSERT_EQUAL_UINT8(255U, result);
}

void test_add_one_counter_254_saturation_enabled_limit_255(void)
{
    uint8_t result;
    
    g_counter_u32 = 254U;
    SetCounterLimit_u32(255U);
    SetSaturationEn_b(true);
    
    result = MyLib_UpdateCounter_u8(1U);
    
    TEST_ASSERT_EQUAL_UINT32(255U, g_counter_u32);
    TEST_ASSERT_EQUAL_UINT8(255U, result);
}

void test_add_two_counter_254_saturation_enabled_limit_255(void)
{
    uint8_t result;
    
    g_counter_u32 = 254U;
    SetCounterLimit_u32(255U);
    SetSaturationEn_b(true);
    
    result = MyLib_UpdateCounter_u8(2U);
    
    TEST_ASSERT_EQUAL_UINT32(255U, g_counter_u32);
    TEST_ASSERT_EQUAL_UINT8(255U, result);
}

void test_add_ten_counter_250_saturation_enabled_limit_255(void)
{
    uint8_t result;
    
    g_counter_u32 = 250U;
    SetCounterLimit_u32(255U);
    SetSaturationEn_b(true);
    
    result = MyLib_UpdateCounter_u8(10U);
    
    TEST_ASSERT_EQUAL_UINT32(255U, g_counter_u32);
    TEST_ASSERT_EQUAL_UINT8(255U, result);
}

void test_add_one_counter_255_saturation_enabled_limit_255(void)
{
    uint8_t result;
    
    g_counter_u32 = 255U;
    SetCounterLimit_u32(255U);
    SetSaturationEn_b(true);
    
    result = MyLib_UpdateCounter_u8(1U);
    
    TEST_ASSERT_EQUAL_UINT32(255U, g_counter_u32);
    TEST_ASSERT_EQUAL_UINT8(255U, result);
}

void test_add_zero_counter_255_saturation_enabled_limit_255(void)
{
    uint8_t result;
    
    g_counter_u32 = 255U;
    SetCounterLimit_u32(255U);
    SetSaturationEn_b(true);
    
    result = MyLib_UpdateCounter_u8(0U);
    
    TEST_ASSERT_EQUAL_UINT32(255U, g_counter_u32);
    TEST_ASSERT_EQUAL_UINT8(255U, result);
}

void test_add_one_counter_zero_saturation_disabled_limit_100(void)
{
    uint8_t result;
    
    g_counter_u32 = 0U;
    SetCounterLimit_u32(100U);
    SetSaturationEn_b(false);
    
    result = MyLib_UpdateCounter_u8(1U);
    
    TEST_ASSERT_EQUAL_UINT32(1U, g_counter_u32);
    TEST_ASSERT_EQUAL_UINT8(1U, result);
}

void test_add_50_counter_zero_saturation_disabled_limit_100(void)
{
    uint8_t result;
    
    g_counter_u32 = 0U;
    SetCounterLimit_u32(100U);
    SetSaturationEn_b(false);
    
    result = MyLib_UpdateCounter_u8(50U);
    
    TEST_ASSERT_EQUAL_UINT32(50U, g_counter_u32);
    TEST_ASSERT_EQUAL_UINT8(50U, result);
}

void test_add_99_counter_zero_saturation_disabled_limit_100(void)
{
    uint8_t result;
    
    g_counter_u32 = 0U;
    SetCounterLimit_u32(100U);
    SetSaturationEn_b(false);
    
    result = MyLib_UpdateCounter_u8(99U);
    
    TEST_ASSERT_EQUAL_UINT32(99U, g_counter_u32);
    TEST_ASSERT_EQUAL_UINT8(99U, result);
}

void test_add_100_counter_zero_saturation_disabled_limit_100(void)
{
    uint8_t result;
    
    g_counter_u32 = 0U;
    SetCounterLimit_u32(100U);
    SetSaturationEn_b(false);
    
    result = MyLib_UpdateCounter_u8(100U);
    
    TEST_ASSERT_EQUAL_UINT32(100U, g_counter_u32);
    TEST_ASSERT_EQUAL_UINT8(100U, result);
}

void test_add_101_counter_zero_saturation_disabled_limit_100(void)
{
    uint8_t result;
    
    g_counter_u32 = 0U;
    SetCounterLimit_u32(100U);
    SetSaturationEn_b(false);
    
    result = MyLib_UpdateCounter_u8(101U);
    
    TEST_ASSERT_EQUAL_UINT32(0U, g_counter_u32);
    TEST_ASSERT_EQUAL_UINT8(0U, result);
}

void test_add_150_counter_zero_saturation_disabled_limit_100(void)
{
    uint8_t result;
    
    g_counter_u32 = 0U;
    SetCounterLimit_u32(100U);
    SetSaturationEn_b(false);
    
    result = MyLib_UpdateCounter_u8(150U);
    
    TEST_ASSERT_EQUAL_UINT32(49U, g_counter_u32);
    TEST_ASSERT_EQUAL_UINT8(49U, result);
}

void test_add_one_counter_99_saturation_disabled_limit_100(void)
{
    uint8_t result;
    
    g_counter_u32 = 99U;
    SetCounterLimit_u32(100U);
    SetSaturationEn_b(false);
    
    result = MyLib_UpdateCounter_u8(1U);
    
    TEST_ASSERT_EQUAL_UINT32(100U, g_counter_u32);
    TEST_ASSERT_EQUAL_UINT8(100U, result);
}

void test_add_two_counter_99_saturation_disabled_limit_100(void)
{
    uint8_t result;
    
    g_counter_u32 = 99U;
    SetCounterLimit_u32(100U);
    SetSaturationEn_b(false);
    
    result = MyLib_UpdateCounter_u8(2U);
    
    TEST_ASSERT_EQUAL_UINT32(0U, g_counter_u32);
    TEST_ASSERT_EQUAL_UINT8(0U, result);
}

void test_add_ten_counter_95_saturation_disabled_limit_100(void)
{
    uint8_t result;
    
    g_counter_u32 = 95U;
    SetCounterLimit_u32(100U);
    SetSaturationEn_b(false);
    
    result = MyLib_UpdateCounter_u8(10U);
    
    TEST_ASSERT_EQUAL_UINT32(4U, g_counter_u32);
    TEST_ASSERT_EQUAL_UINT8(4U, result);
}

void test_add_one_counter_zero_saturation_enabled_limit_100(void)
{
    uint8_t result;
    
    g_counter_u32 = 0U;
    SetCounterLimit_u32(100U);
    SetSaturationEn_b(true);
    
    result = MyLib_UpdateCounter_u8(1U);
    
    TEST_ASSERT_EQUAL_UINT32(1U, g_counter_u32);
    TEST_ASSERT_EQUAL_UINT8(1U, result);
}

void test_add_50_counter_zero_saturation_enabled_limit_100(void)
{
    uint8_t result;
    
    g_counter_u32 = 0U;
    SetCounterLimit_u32(100U);
    SetSaturationEn_b(true);
    
    result = MyLib_UpdateCounter_u8(50U);
    
    TEST_ASSERT_EQUAL_UINT32(50U, g_counter_u32);
    TEST_ASSERT_EQUAL_UINT8(50U, result);
}

void test_add_100_counter_zero_saturation_enabled_limit_100(void)
{
    uint8_t result;
    
    g_counter_u32 = 0U;
    SetCounterLimit_u32(100U);
    SetSaturationEn_b(true);
    
    result = MyLib_UpdateCounter_u8(100U);
    
    TEST_ASSERT_EQUAL_UINT32(100U, g_counter_u32);
    TEST_ASSERT_EQUAL_UINT8(100U, result);
}

void test_add_101_counter_zero_saturation_enabled_limit_100(void)
{
    uint8_t result;
    
    g_counter_u32 = 0U;
    SetCounterLimit_u32(100U);
    SetSaturationEn_b(true);
    
    result = MyLib_UpdateCounter_u8(101U);
    
    TEST_ASSERT_EQUAL_UINT32(100U, g_counter_u32);
    TEST_ASSERT_EQUAL_UINT8(100U, result);
}

void test_add_150_counter_zero_saturation_enabled_limit_100(void)
{
    uint8_t result;
    
    g_counter_u32 = 0U;
    SetCounterLimit_u32(100U);
    SetSaturationEn_b(true);
    
    result = MyLib_UpdateCounter_u8(150U);
    
    TEST_ASSERT_EQUAL_UINT32(100U, g_counter_u32);
    TEST_ASSERT_EQUAL_UINT8(100U, result);
}

void test_add_one_counter_99_saturation_enabled_limit_100(void)
{
    uint8_t result;
    
    g_counter_u32 = 99U;
    SetCounterLimit_u32(100U);
    SetSaturationEn_b(true);
    
    result = MyLib_UpdateCounter_u8(1U);
    
    TEST_ASSERT_EQUAL_UINT32(100U, g_counter_u32);
    TEST_ASSERT_EQUAL_UINT8(100U, result);
}

void test_add_two_counter_99_saturation_enabled_limit_100(void)
{
    uint8_t result;
    
    g_counter_u32 = 99U;
    SetCounterLimit_u32(100U);
    SetSaturationEn_b(true);
    
    result = MyLib_UpdateCounter_u8(2U);
    
    TEST_ASSERT_EQUAL_UINT32(100U, g_counter_u32);
    TEST_ASSERT_EQUAL_UINT8(100U, result);
}

void test_add_ten_counter_95_saturation_enabled_limit_100(void)
{
    uint8_t result;
    
    g_counter_u32 = 95U;
    SetCounterLimit_u32(100U);
    SetSaturationEn_b(true);
    
    result = MyLib_UpdateCounter_u8(10U);
    
    TEST_ASSERT_EQUAL_UINT32(100U, g_counter_u32);
    TEST_ASSERT_EQUAL_UINT8(100U, result);
}

void test_add_one_counter_100_saturation_enabled_limit_100(void)
{
    uint8_t result;
    
    g_counter_u32 = 100U;
    SetCounterLimit_u32(100U);
    SetSaturationEn_b(true);
    
    result = MyLib_UpdateCounter_u8(1U);
    
    TEST_ASSERT_EQUAL_UINT32(100U, g_counter_u32);
    TEST_ASSERT_EQUAL_UINT8(100U, result);
}

void test_add_zero_counter_100_saturation_enabled_limit_100(void)
{
    uint8_t result;
    
    g_counter_u32 = 100U;
    SetCounterLimit_u32(100U);
    SetSaturationEn_b(true);
    
    result = MyLib_UpdateCounter_u8(0U);
    
    TEST_ASSERT_EQUAL_UINT32(100U, g_counter_u32);
    TEST_ASSERT_EQUAL_UINT8(100U, result);
}

void test_add_one_counter_zero_saturation_disabled_limit_0(void)
{
    uint8_t result;
    
    g_counter_u32 = 0U;
    SetCounterLimit_u32(0U);
    SetSaturationEn_b(false);
    
    result = MyLib_UpdateCounter_u8(1U);
    
    TEST_ASSERT_EQUAL_UINT32(0U, g_counter_u32);
    TEST_ASSERT_EQUAL_UINT8(0U, result);
}

void test_add_ten_counter_zero_saturation_disabled_limit_0(void)
{
    uint8_t result;
    
    g_counter_u32 = 0U;
    SetCounterLimit_u32(0U);
    SetSaturationEn_b(false);
    
    result = MyLib_UpdateCounter_u8(10U);
    
    TEST_ASSERT_EQUAL_UINT32(0U, g_counter_u32);
    TEST_ASSERT_EQUAL_UINT8(0U, result);
}

void test_add_one_counter_zero_saturation_enabled_limit_0(void)
{
    uint8_t result;
    
    g_counter_u32 = 0U;
    SetCounterLimit_u32(0U);
    SetSaturationEn_b(true);
    
    result = MyLib_UpdateCounter_u8(1U);
    
    TEST_ASSERT_EQUAL_UINT32(0U, g_counter_u32);
    TEST_ASSERT_EQUAL_UINT8(0U, result);
}

void test_add_ten_counter_zero_saturation_enabled_limit_0(void)
{
    uint8_t result;
    
    g_counter_u32 = 0U;
    SetCounterLimit_u32(0U);
    SetSaturationEn_b(true);
    
    result = MyLib_UpdateCounter_u8(10U);
    
    TEST_ASSERT_EQUAL_UINT32(0U, g_counter_u32);
    TEST_ASSERT_EQUAL_UINT8(0U, result);
}

void test_add_one_counter_zero_saturation_disabled_limit_1(void)
{
    uint8_t result;
    
    g_counter_u32 = 0U;
    SetCounterLimit_u32(1U);
    SetSaturationEn_b(false);
    
    result = MyLib_UpdateCounter_u8(1U);
    
    TEST_ASSERT_EQUAL_UINT32(1U, g_counter_u32);
    TEST_ASSERT_EQUAL_UINT8(1U, result);
}

void test_add_two_counter_zero_saturation_disabled_limit_1(void)
{
    uint8_t result;
    
    g_counter_u32 = 0U;
    SetCounterLimit_u32(1U);
    SetSaturationEn_b(false);
    
    result = MyLib_UpdateCounter_u8(2U);
    
    TEST_ASSERT_EQUAL_UINT32(0U, g_counter_u32);
    TEST_ASSERT_EQUAL_UINT8(0U, result);
}

void test_add_one_counter_zero_saturation_enabled_limit_1(void)
{
    uint8_t result;
    
    g_counter_u32 = 0U;
    SetCounterLimit_u32(1U);
    SetSaturationEn_b(true);
    
    result = MyLib_UpdateCounter_u8(1U);
    
    TEST_ASSERT_EQUAL_UINT32(1U, g_counter_u32);
    TEST_ASSERT_EQUAL_UINT8(1U, result);
}

void test_add_two_counter_zero_saturation_enabled_limit_1(void)
{
    uint8_t result;
    
    g_counter_u32 = 0U;
    SetCounterLimit_u32(1U);
    SetSaturationEn_b(true);
    
    result = MyLib_UpdateCounter_u8(2U);
    
    TEST_ASSERT_EQUAL_UINT32(1U, g_counter_u32);
    TEST_ASSERT_EQUAL_UINT8(1U, result);
}

void test_add_one_counter_zero_saturation_disabled_limit_uint32_max(void)
{
    uint8_t result;
    
    g_counter_u32 = 0U;
    SetCounterLimit_u32(UINT32_MAX);
    SetSaturationEn_b(false);
    
    result = MyLib_UpdateCounter_u8(1U);
    
    TEST_ASSERT_EQUAL_UINT32(1U, g_counter_u32);
    TEST_ASSERT_EQUAL_UINT8(1U, result);
}

void test_add_uint32_max_counter_zero_saturation_disabled_limit_uint32_max(void)
{
    uint8_t result;
    uint8_t expected;
    
    g_counter_u32 = 0U;
    SetCounterLimit_u32(UINT32_MAX);
    SetSaturationEn_b(false);
    
    expected = (uint8_t)(UINT32_MAX % 256U);
    
    result = MyLib_UpdateCounter_u8(UINT32_MAX);
    
    TEST_ASSERT_EQUAL_UINT32(expected, g_counter_u32);
    TEST_ASSERT_EQUAL_UINT8(expected, result);
}

void test_add_one_counter_zero_saturation_enabled_limit_uint32_max(void)
{
    uint8_t result;
    
    g_counter_u32 = 0U;
    SetCounterLimit_u32(UINT32_MAX);
    SetSaturationEn_b(true);
    
    result = MyLib_UpdateCounter_u8(1U);
    
    TEST_ASSERT_EQUAL_UINT32(1U, g_counter_u32);
    TEST_ASSERT_EQUAL_UINT8(1U, result);
}

void test_add_300_counter_zero_saturation_enabled_limit_uint32_max(void)
{
    uint8_t result;
    
    g_counter_u32 = 0U;
    SetCounterLimit_u32(UINT32_MAX);
    SetSaturationEn_b(true);
    
    result = MyLib_UpdateCounter_u8(300U);
    
    TEST_ASSERT_EQUAL_UINT32(255U, g_counter_u32);
    TEST_ASSERT_EQUAL_UINT8(255U, result);
}

void test_multiple_calls_add_ten_counter_zero_saturation_disabled_limit_255(void)
{
    uint8_t result;
    
    g_counter_u32 = 0U;
    SetCounterLimit_u32(255U);
    SetSaturationEn_b(false);
    
    result = MyLib_UpdateCounter_u8(10U);
    TEST_ASSERT_EQUAL_UINT32(10U, g_counter_u32);
    TEST_ASSERT_EQUAL_UINT8(10U, result);
    
    result = MyLib_UpdateCounter_u8(10U);
    TEST_ASSERT_EQUAL_UINT32(20U, g_counter_u32);
    TEST_ASSERT_EQUAL_UINT8(20U, result);
    
    result = MyLib_UpdateCounter_u8(10U);
    TEST_ASSERT_EQUAL_UINT32(30U, g_counter_u32);
    TEST_ASSERT_EQUAL_UINT8(30U, result);
    
    result = MyLib_UpdateCounter_u8(10U);
    TEST_ASSERT_EQUAL_UINT32(40U, g_counter_u32);
    TEST_ASSERT_EQUAL_UINT8(40U, result);
    
    result = MyLib_UpdateCounter_u8(10U);
    TEST_ASSERT_EQUAL_UINT32(50U, g_counter_u32);
    TEST_ASSERT_EQUAL_UINT8(50U, result);
    
    result = MyLib_UpdateCounter_u8(10U);
    TEST_ASSERT_EQUAL_UINT32(60U, g_counter_u32);
    TEST_ASSERT_EQUAL_UINT8(60U, result);
    
    result = MyLib_UpdateCounter_u8(10U);
    TEST_ASSERT_EQUAL_UINT32(70U, g_counter_u32);
    TEST_ASSERT_EQUAL_UINT8(70U, result);
    
    result = MyLib_UpdateCounter_u8(10U);
    TEST_ASSERT_EQUAL_UINT32(80U, g_counter_u32);
    TEST_ASSERT_EQUAL_UINT8(80U, result);
    
    result = MyLib_UpdateCounter_u8(10U);
    TEST_ASSERT_EQUAL_UINT32(90U, g_counter_u32);
    TEST_ASSERT_EQUAL_UINT8(90U, result);
    
    result = MyLib_UpdateCounter_u8(10U);
    TEST_ASSERT_EQUAL_UINT32(100U, g_counter_u32);
    TEST_ASSERT_EQUAL_UINT8(100U, result);
    
    result = MyLib_UpdateCounter_u8(10U);
    TEST_ASSERT_EQUAL_UINT32(110U, g_counter_u32);
    TEST_ASSERT_EQUAL_UINT8(110U, result);
    
    result = MyLib_UpdateCounter_u8(10U);
    TEST_ASSERT_EQUAL_UINT32(120U, g_counter_u32);
    TEST_ASSERT_EQUAL_UINT8(120U, result);
    
    result = MyLib_UpdateCounter_u8(10U);
    TEST_ASSERT_EQUAL_UINT32(130U, g_counter_u32);
    TEST_ASSERT_EQUAL_UINT8(130U, result);
    
    result = MyLib_UpdateCounter_u8(10U);
    TEST_ASSERT_EQUAL_UINT32(140U, g_counter_u32);
    TEST_ASSERT_EQUAL_UINT8(140U, result);
    
    result = MyLib_UpdateCounter_u8(10U);
    TEST_ASSERT_EQUAL_UINT32(150U, g_counter_u32);
    TEST_ASSERT_EQUAL_UINT8(150U, result);
    
    result = MyLib_UpdateCounter_u8(10U);
    TEST_ASSERT_EQUAL_UINT32(160U, g_counter_u32);
    TEST_ASSERT_EQUAL_UINT8(160U, result);
    
    result = MyLib_UpdateCounter_u8(10U);
    TEST_ASSERT_EQUAL_UINT32(170U, g_counter_u32);
    TEST_ASSERT_EQUAL_UINT8(170U, result);
    
    result = MyLib_UpdateCounter_u8(10U);
    TEST_ASSERT_EQUAL_UINT32(180U, g_counter_u32);
    TEST_ASSERT_EQUAL_UINT8(180U, result);
    
    result = MyLib_UpdateCounter_u8(10U);
    TEST_ASSERT_EQUAL_UINT32(190U, g_counter_u32);
    TEST_ASSERT_EQUAL_UINT8(190U, result);
    
    result = MyLib_UpdateCounter_u8(10U);
    TEST_ASSERT_EQUAL_UINT32(200U, g_counter_u32);
    TEST_ASSERT_EQUAL_UINT8(200U, result);
    
    result = MyLib_UpdateCounter_u8(10U);
    TEST_ASSERT_EQUAL_UINT32(210U, g_counter_u32);
    TEST_ASSERT_EQUAL_UINT8(210U, result);
    
    result = MyLib_UpdateCounter_u8(10U);
    TEST_ASSERT_EQUAL_UINT32(220U, g_counter_u32);
    TEST_ASSERT_EQUAL_UINT8(220U, result);
    
    result = MyLib_UpdateCounter_u8(10U);
    TEST_ASSERT_EQUAL_UINT32(230U, g_counter_u32);
    TEST_ASSERT_EQUAL_UINT8(230U, result);
    
    result = MyLib_UpdateCounter_u8(10U);
    TEST_ASSERT_EQUAL_UINT32(240U, g_counter_u32);
    TEST_ASSERT_EQUAL_UINT8(240U, result);
    
    result = MyLib_UpdateCounter_u8(10U);
    TEST_ASSERT_EQUAL_UINT32(250U, g_counter_u32);
    TEST_ASSERT_EQUAL_UINT8(250U, result);
    
    result = MyLib_UpdateCounter_u8(10U);
    TEST_ASSERT_EQUAL_UINT32(4U, g_counter_u32);
    TEST_ASSERT_EQUAL_UINT8(4U, result);
    
    result = MyLib_UpdateCounter_u8(10U);
    TEST_ASSERT_EQUAL_UINT32(14U, g_counter_u32);
    TEST_ASSERT_EQUAL_UINT8(14U, result);
}

void test_multiple_calls_add_ten_counter_zero_saturation_enabled_limit_255(void)
{
    uint8_t result;
    
    g_counter_u32 = 0U;
    SetCounterLimit_u32(255U);
    SetSaturationEn_b(true);
    
    result = MyLib_UpdateCounter_u8(10U);
    TEST_ASSERT_EQUAL_UINT32(10U, g_counter_u32);
    TEST_ASSERT_EQUAL_UINT8(10U, result);
    
    result = MyLib_UpdateCounter_u8(10U);
    TEST_ASSERT_EQUAL_UINT32(20U, g_counter_u32);
    TEST_ASSERT_EQUAL_UINT8(20U, result);
    
    result = MyLib_UpdateCounter_u8(10U);
    TEST_ASSERT_EQUAL_UINT32(30U, g_counter_u32);
    TEST_ASSERT_EQUAL_UINT8(30U, result);
    
    result = MyLib_UpdateCounter_u8(10U);
    TEST_ASSERT_EQUAL_UINT32(40U, g_counter_u32);
    TEST_ASSERT_EQUAL_UINT8(40U, result);
    
    result = MyLib_UpdateCounter_u8(10U);
    TEST_ASSERT_EQUAL_UINT32(50U, g_counter_u32);
    TEST_ASSERT_EQUAL_UINT8(50U, result);
    
    result = MyLib_UpdateCounter_u8(10U);
    TEST_ASSERT_EQUAL_UINT32(60U, g_counter_u32);
    TEST_ASSERT_EQUAL_UINT8(60U, result);
    
    result = MyLib_UpdateCounter_u8(10U);
    TEST_ASSERT_EQUAL_UINT32(70U, g_counter_u32);
    TEST_ASSERT_EQUAL_UINT8(70U, result);
    
    result = MyLib_UpdateCounter_u8(10U);
    TEST_ASSERT_EQUAL_UINT32(80U, g_counter_u32);
    TEST_ASSERT_EQUAL_UINT8(80U, result);
    
    result = MyLib_UpdateCounter_u8(10U);
    TEST_ASSERT_EQUAL_UINT32(90U, g_counter_u32);
    TEST_ASSERT_EQUAL_UINT8(90U, result);
    
    result = MyLib_UpdateCounter_u8(10U);
    TEST_ASSERT_EQUAL_UINT32(100U, g_counter_u32);
    TEST_ASSERT_EQUAL_UINT8(100U, result);
    
    result = MyLib_UpdateCounter_u8(10U);
    TEST_ASSERT_EQUAL_UINT32(110U, g_counter_u32);
    TEST_ASSERT_EQUAL_UINT8(110U, result);
    
    result = MyLib_UpdateCounter_u8(10U);
    TEST_ASSERT_EQUAL_UINT32(120U, g_counter_u32);
    TEST_ASSERT_EQUAL_UINT8(120U, result);
    
    result = MyLib_UpdateCounter_u8(10U);
    TEST_ASSERT_EQUAL_UINT32(130U, g_counter_u32);
    TEST_ASSERT_EQUAL_UINT8(130U, result);
    
    result = MyLib_UpdateCounter_u8(10U);
    TEST_ASSERT_EQUAL_UINT32(140U, g_counter_u32);
    TEST_ASSERT_EQUAL_UINT8(140U, result);
    
    result = MyLib_UpdateCounter_u8(10U);
    TEST_ASSERT_EQUAL_UINT32(150U, g_counter_u32);
    TEST_ASSERT_EQUAL_UINT8(150U, result);
    
    result = MyLib_UpdateCounter_u8(10U);
    TEST_ASSERT_EQUAL_UINT32(160U, g_counter_u32);
    TEST_ASSERT_EQUAL_UINT8(160U, result);
    
    result = MyLib_UpdateCounter_u8(10U);
    TEST_ASSERT_EQUAL_UINT32(170U, g_counter_u32);
    TEST_ASSERT_EQUAL_UINT8(170U, result);
    
    result = MyLib_UpdateCounter_u8(10U);
    TEST_ASSERT_EQUAL_UINT32(180U, g_counter_u32);
    TEST_ASSERT_EQUAL_UINT8(180U, result);
    
    result = MyLib_UpdateCounter_u8(10U);
    TEST_ASSERT_EQUAL_UINT32(190U, g_counter_u32);
    TEST_ASSERT_EQUAL_UINT8(190U, result);
    
    result = MyLib_UpdateCounter_u8(10U);
    TEST_ASSERT_EQUAL_UINT32(200U, g_counter_u32);
    TEST_ASSERT_EQUAL_UINT8(200U, result);
    
    result = MyLib_UpdateCounter_u8(10U);
    TEST_ASSERT_EQUAL_UINT32(210U, g_counter_u32);
    TEST_ASSERT_EQUAL_UINT8(210U, result);
    
    result = MyLib_UpdateCounter_u8(10U);
    TEST_ASSERT_EQUAL_UINT32(220U, g_counter_u32);
    TEST_ASSERT_EQUAL_UINT8(220U, result);
    
    result = MyLib_UpdateCounter_u8(10U);
    TEST_ASSERT_EQUAL_UINT32(230U, g_counter_u32);
    TEST_ASSERT_EQUAL_UINT8(230U, result);
    
    result = MyLib_UpdateCounter_u8(10U);
    TEST_ASSERT_EQUAL_UINT32(240U, g_counter_u32);
    TEST_ASSERT_EQUAL_UINT8(240U, result);
    
    result = MyLib_UpdateCounter_u8(10U);
    TEST_ASSERT_EQUAL_UINT32(250U, g_counter_u32);
    TEST_ASSERT_EQUAL_UINT8(250U, result);
    
    result = MyLib_UpdateCounter_u8(10U);
    TEST_ASSERT_EQUAL_UINT32(255U, g_counter_u32);
    TEST_ASSERT_EQUAL_UINT8(255U, result);
    
    result = MyLib_UpdateCounter_u8(10U);
    TEST_ASSERT_EQUAL_UINT32(255U, g_counter_u32);
    TEST_ASSERT_EQUAL_UINT8(255U, result);
}

void test_change_limit_255_to_100_counter_150_add_ten_saturation_disabled(void)
{
    uint8_t result;
    
    g_counter_u32 = 150U;
    SetCounterLimit_u32(255U);
    SetSaturationEn_b(false);
    
    SetCounterLimit_u32(100U);
    
    result = MyLib_UpdateCounter_u8(10U);
    
    TEST_ASSERT_EQUAL_UINT32(59U, g_counter_u32);
    TEST_ASSERT_EQUAL_UINT8(59U, result);
}

void test_change_limit_255_to_100_counter_150_add_ten_saturation_enabled(void)
{
    uint8_t result;
    
    g_counter_u32 = 150U;
    SetCounterLimit_u32(255U);
    SetSaturationEn_b(true);
    
    SetCounterLimit_u32(100U);
    
    result = MyLib_UpdateCounter_u8(10U);
    
    TEST_ASSERT_EQUAL_UINT32(100U, g_counter_u32);
    TEST_ASSERT_EQUAL_UINT8(100U, result);
}

void test_toggle_saturation_disabled_to_enabled_counter_200_add_100_limit_255(void)
{
    uint8_t result;
    
    g_counter_u32 = 200U;
    SetCounterLimit_u32(255U);
    SetSaturationEn_b(false);
    
    SetSaturationEn_b(true);
    
    result = MyLib_UpdateCounter_u8(100U);
    
    TEST_ASSERT_EQUAL_UINT32(255U, g_counter_u32);
    TEST_ASSERT_EQUAL_UINT8(255U, result);
}

void test_toggle_saturation_enabled_to_disabled_counter_200_add_100_limit_255(void)
{
    uint8_t result;
    
    g_counter_u32 = 200U;
    SetCounterLimit_u32(255U);
    SetSaturationEn_b(true);
    
    SetSaturationEn_b(false);
    
    result = MyLib_UpdateCounter_u8(100U);
    
    TEST_ASSERT_EQUAL_UINT32(44U, g_counter_u32);
    TEST_ASSERT_EQUAL_UINT8(44U, result);
}
```