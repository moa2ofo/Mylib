#include "mock_MyLib.h"
#include "unity.h"
#include <UpdateCounter_u8.h>




void setUp(void)
{
}
void tearDown(void)
{
}
void test_system_not_ready_returns_1_no_counter_change(void)
{
    uint8_t result;
    uint32_t initial_counter = 42U;

    g_systemReady_b = false;
    g_counter_u32 = initial_counter;

    result = UpdateCounter_u8(10U);

    TEST_ASSERT_EQUAL_UINT8(1U, result);
    TEST_ASSERT_EQUAL_UINT32(initial_counter, g_counter_u32);
}
void test_ready_add_zero_sat_disabled_returns_0(void)
{
    uint8_t result;
    uint32_t initial_counter = 100U;

    g_systemReady_b = true;
    g_counter_u32 = initial_counter;
    set_SaturationEn_b(false);

    result = UpdateCounter_u8(0U);

    TEST_ASSERT_EQUAL_UINT8(0U, result);
    TEST_ASSERT_EQUAL_UINT32(initial_counter, g_counter_u32);
}
void test_ready_add_one_sat_disabled_returns_0(void)
{
    uint8_t result;
    uint32_t initial_counter = 50U;

    g_systemReady_b = true;
    g_counter_u32 = initial_counter;
    set_SaturationEn_b(false);

    result = UpdateCounter_u8(1U);

    TEST_ASSERT_EQUAL_UINT8(0U, result);
    TEST_ASSERT_EQUAL_UINT32(initial_counter + 1U, g_counter_u32);
}
void test_ready_add_midrange_sat_disabled_returns_0(void)
{
    uint8_t result;
    uint32_t initial_counter = 0x10000000U;
    uint32_t add_value = 0x80000000U;

    g_systemReady_b = true;
    g_counter_u32 = initial_counter;
    set_SaturationEn_b(false);

    result = UpdateCounter_u8(add_value);

    TEST_ASSERT_EQUAL_UINT8(0U, result);
    TEST_ASSERT_EQUAL_UINT32(initial_counter + add_value, g_counter_u32);
}
void test_ready_add_max_minus_one_sat_disabled_returns_0(void)
{
    uint8_t result;
    uint32_t initial_counter = 10U;
    uint32_t add_value = 0xFFFFFFFEU;

    g_systemReady_b = true;
    g_counter_u32 = initial_counter;
    set_SaturationEn_b(false);

    result = UpdateCounter_u8(add_value);

    TEST_ASSERT_EQUAL_UINT8(0U, result);
    TEST_ASSERT_EQUAL_UINT32(initial_counter + add_value, g_counter_u32);
}
void test_ready_add_max_sat_disabled_returns_0(void)
{
    uint8_t result;
    uint32_t initial_counter = 5U;
    uint32_t add_value = 0xFFFFFFFFU;

    g_systemReady_b = true;
    g_counter_u32 = initial_counter;
    set_SaturationEn_b(false);

    result = UpdateCounter_u8(add_value);

    TEST_ASSERT_EQUAL_UINT8(0U, result);
    TEST_ASSERT_EQUAL_UINT32(initial_counter + add_value, g_counter_u32);
}
void test_ready_sat_enabled_below_limit_returns_0(void)
{
    uint8_t result;
    uint32_t initial_counter = 50U;
    uint32_t add_value = 30U;
    uint32_t limit = 100U;

    g_systemReady_b = true;
    g_counter_u32 = initial_counter;
    set_SaturationEn_b(true);
    set_CounterLimit_u32(limit);

    result = UpdateCounter_u8(add_value);

    TEST_ASSERT_EQUAL_UINT8(0U, result);
    TEST_ASSERT_EQUAL_UINT32(initial_counter + add_value, g_counter_u32);
}
void test_ready_sat_enabled_equals_limit_returns_0(void)
{
    uint8_t result;
    uint32_t initial_counter = 50U;
    uint32_t add_value = 50U;
    uint32_t limit = 100U;

    g_systemReady_b = true;
    g_counter_u32 = initial_counter;
    set_SaturationEn_b(true);
    set_CounterLimit_u32(limit);

    result = UpdateCounter_u8(add_value);

    TEST_ASSERT_EQUAL_UINT8(0U, result);
    TEST_ASSERT_EQUAL_UINT32(limit, g_counter_u32);
}
void test_ready_sat_enabled_exceeds_limit_by_one_returns_2(void)
{
    uint8_t result;
    uint32_t initial_counter = 50U;
    uint32_t add_value = 51U;
    uint32_t limit = 100U;

    g_systemReady_b = true;
    g_counter_u32 = initial_counter;
    set_SaturationEn_b(true);
    set_CounterLimit_u32(limit);

    result = UpdateCounter_u8(add_value);

    TEST_ASSERT_EQUAL_UINT8(2U, result);
    TEST_ASSERT_EQUAL_UINT32(limit, g_counter_u32);
}
void test_ready_sat_enabled_exceeds_limit_large_returns_2(void)
{
    uint8_t result;
    uint32_t initial_counter = 50U;
    uint32_t add_value = 1000U;
    uint32_t limit = 100U;

    g_systemReady_b = true;
    g_counter_u32 = initial_counter;
    set_SaturationEn_b(true);
    set_CounterLimit_u32(limit);

    result = UpdateCounter_u8(add_value);

    TEST_ASSERT_EQUAL_UINT8(2U, result);
    TEST_ASSERT_EQUAL_UINT32(limit, g_counter_u32);
}
void test_ready_sat_enabled_wrap_exceeds_limit_returns_2(void)
{
    uint8_t result;
    uint32_t initial_counter = 0xFFFFFFFFU;
    uint32_t add_value = 100U;
    uint32_t limit = 50U;

    g_systemReady_b = true;
    g_counter_u32 = initial_counter;
    set_SaturationEn_b(true);
    set_CounterLimit_u32(limit);

    result = UpdateCounter_u8(add_value);

    TEST_ASSERT_EQUAL_UINT8(2U, result);
    TEST_ASSERT_EQUAL_UINT32(limit, g_counter_u32);
}
void test_ready_sat_enabled_wrap_below_limit_returns_0(void)
{
    uint8_t result;
    uint32_t initial_counter = 0xFFFFFFFFU;
    uint32_t add_value = 10U;
    uint32_t limit = 100U;

    g_systemReady_b = true;
    g_counter_u32 = initial_counter;
    set_SaturationEn_b(true);
    set_CounterLimit_u32(limit);

    result = UpdateCounter_u8(add_value);

    TEST_ASSERT_EQUAL_UINT8(0U, result);
    TEST_ASSERT_EQUAL_UINT32(9U, g_counter_u32);
}
void test_cycle_16_toggles_saturation_false_to_true(void)
{
    uint8_t result;
    int i;

    g_systemReady_b = true;
    g_counter_u32 = 0U;
    set_SaturationEn_b(false);
    set_CounterLimit_u32(1000U);

    for (i = 0; i < 15; i++)
    {
        result = UpdateCounter_u8(1U);
    }

    TEST_ASSERT_EQUAL(false, get_SaturationEn_b());

    result = UpdateCounter_u8(1U);

    TEST_ASSERT_EQUAL(true, get_SaturationEn_b());
}
void test_cycle_32_toggles_saturation_true_to_false(void)
{
    uint8_t result;
    int i;

    g_systemReady_b = true;
    g_counter_u32 = 0U;
    set_SaturationEn_b(false);
    set_CounterLimit_u32(1000U);

    for (i = 0; i < 16; i++)
    {
        result = UpdateCounter_u8(1U);
    }

    TEST_ASSERT_EQUAL(true, get_SaturationEn_b());

    for (i = 0; i < 16; i++)
    {
        result = UpdateCounter_u8(1U);
    }

    TEST_ASSERT_EQUAL(false, get_SaturationEn_b());
}
void test_cycle_not_multiple_16_no_toggle(void)
{
    uint8_t result;
    int i;

    g_systemReady_b = true;
    g_counter_u32 = 0U;
    set_SaturationEn_b(false);
    set_CounterLimit_u32(1000U);

    for (i = 0; i < 10; i++)
    {
        result = UpdateCounter_u8(1U);
    }

    TEST_ASSERT_EQUAL(false, get_SaturationEn_b());
}
void test_limit_zero_sat_enabled_positive_add_returns_2(void)
{
    uint8_t result;

    g_systemReady_b = true;
    g_counter_u32 = 0U;
    set_SaturationEn_b(true);
    set_CounterLimit_u32(0U);

    result = UpdateCounter_u8(5U);

    TEST_ASSERT_EQUAL_UINT8(2U, result);
    TEST_ASSERT_EQUAL_UINT32(0U, g_counter_u32);
}
void test_limit_max_sat_enabled_no_overflow_returns_0(void)
{
    uint8_t result;
    uint32_t initial_counter = 100U;
    uint32_t add_value = 50U;

    g_systemReady_b = true;
    g_counter_u32 = initial_counter;
    set_SaturationEn_b(true);
    set_CounterLimit_u32(0xFFFFFFFFU);

    result = UpdateCounter_u8(add_value);

    TEST_ASSERT_EQUAL_UINT8(0U, result);
    TEST_ASSERT_EQUAL_UINT32(initial_counter + add_value, g_counter_u32);
}
void test_counter_zero_add_zero_sat_disabled_returns_0(void)
{
    uint8_t result;

    g_systemReady_b = true;
    g_counter_u32 = 0U;
    set_SaturationEn_b(false);

    result = UpdateCounter_u8(0U);

    TEST_ASSERT_EQUAL_UINT8(0U, result);
    TEST_ASSERT_EQUAL_UINT32(0U, g_counter_u32);
}
void test_counter_max_add_zero_sat_disabled_returns_0(void)
{
    uint8_t result;

    g_systemReady_b = true;
    g_counter_u32 = 0xFFFFFFFFU;
    set_SaturationEn_b(false);

    result = UpdateCounter_u8(0U);

    TEST_ASSERT_EQUAL_UINT8(0U, result);
    TEST_ASSERT_EQUAL_UINT32(0xFFFFFFFFU, g_counter_u32);
}
void test_multiple_calls_sat_disabled_all_return_0(void)
{
    uint8_t result;
    int i;

    g_systemReady_b = true;
    g_counter_u32 = 0U;
    set_SaturationEn_b(false);

    for (i = 0; i < 10; i++)
    {
        result = UpdateCounter_u8(1U);
        TEST_ASSERT_EQUAL_UINT8(0U, result);
        TEST_ASSERT_EQUAL_UINT32(i + 1, g_counter_u32);
    }
}
void test_multiple_calls_cross_cycle_16_toggle_and_saturation(void)
{
    uint8_t result;
    int i;

    g_systemReady_b = true;
    g_counter_u32 = 0U;
    set_SaturationEn_b(false);
    set_CounterLimit_u32(20U);

    for (i = 0; i < 15; i++)
    {
        result = UpdateCounter_u8(1U);
        TEST_ASSERT_EQUAL_UINT8(0U, result);
    }

    TEST_ASSERT_EQUAL(false, get_SaturationEn_b());

    result = UpdateCounter_u8(1U);
    TEST_ASSERT_EQUAL_UINT8(0U, result);
    TEST_ASSERT_EQUAL(true, get_SaturationEn_b());

    result = UpdateCounter_u8(10U);
    TEST_ASSERT_EQUAL_UINT8(2U, result);
    TEST_ASSERT_EQUAL_UINT32(20U, g_counter_u32);
}
void test_system_ready_after_rejection(void)
{
    uint8_t result;

    g_systemReady_b = false;
    g_counter_u32 = 10U;

    result = UpdateCounter_u8(5U);
    TEST_ASSERT_EQUAL_UINT8(1U, result);
    TEST_ASSERT_EQUAL_UINT32(10U, g_counter_u32);

    g_systemReady_b = true;
    set_SaturationEn_b(false);

    result = UpdateCounter_u8(5U);
    TEST_ASSERT_EQUAL_UINT8(0U, result);
    TEST_ASSERT_EQUAL_UINT32(15U, g_counter_u32);
}
void test_sat_enabled_wrap_equals_limit_returns_0(void)
{
    uint8_t result;
    uint32_t initial_counter = 0xFFFFFFFFU;
    uint32_t add_value = 101U;
    uint32_t limit = 100U;

    g_systemReady_b = true;
    g_counter_u32 = initial_counter;
    set_SaturationEn_b(true);
    set_CounterLimit_u32(limit);

    result = UpdateCounter_u8(add_value);

    TEST_ASSERT_EQUAL_UINT8(0U, result);
    TEST_ASSERT_EQUAL_UINT32(limit, g_counter_u32);
}
void test_sat_disabled_wrap_to_small_value_returns_0(void)
{
    uint8_t result;
    uint32_t initial_counter = 0xFFFFFFFFU;
    uint32_t add_value = 5U;

    g_systemReady_b = true;
    g_counter_u32 = initial_counter;
    set_SaturationEn_b(false);

    result = UpdateCounter_u8(add_value);

    TEST_ASSERT_EQUAL_UINT8(0U, result);
    TEST_ASSERT_EQUAL_UINT32(4U, g_counter_u32);
}
