#include "MyLib.h"
#include "MyLib_UpdateCounter_u8.h"
#include "mock_MyLib.h"
#include "unity.h"
#include <string.h>




void setUp(void)
{
    g_systemReady_b = false;
    g_counter_u32 = 0U;
}
void tearDown(void)
{
}
void test_system_not_ready_returns_1_no_update(void)
{
    uint32_t initial_counter = 42U;
    g_counter_u32 = initial_counter;
    g_systemReady_b = false;

    uint8_t result = MyLib_UpdateCounter_u8(10U);

    TEST_ASSERT_EQUAL_UINT8(1U, result);
    TEST_ASSERT_EQUAL_UINT32(initial_counter, g_counter_u32);
}
void test_ready_sat_off_zero_inc_returns_0_unchanged(void)
{
    uint32_t initial_counter = 50U;
    g_counter_u32 = initial_counter;
    g_systemReady_b = true;
    set_SaturationEn_b(false);
    set_CounterLimit_u32(100U);

    uint8_t result = MyLib_UpdateCounter_u8(0U);

    TEST_ASSERT_EQUAL_UINT8(0U, result);
    TEST_ASSERT_EQUAL_UINT32(initial_counter, g_counter_u32);
}
void test_ready_sat_off_normal_inc_returns_0_updated(void)
{
    g_counter_u32 = 20U;
    g_systemReady_b = true;
    set_SaturationEn_b(false);
    set_CounterLimit_u32(100U);

    uint8_t result = MyLib_UpdateCounter_u8(15U);

    TEST_ASSERT_EQUAL_UINT8(0U, result);
    TEST_ASSERT_EQUAL_UINT32(35U, g_counter_u32);
}
void test_ready_sat_off_wraparound_returns_0_wrapped(void)
{
    g_counter_u32 = UINT32_MAX;
    g_systemReady_b = true;
    set_SaturationEn_b(false);
    set_CounterLimit_u32(100U);

    uint8_t result = MyLib_UpdateCounter_u8(5U);

    TEST_ASSERT_EQUAL_UINT8(0U, result);
    TEST_ASSERT_EQUAL_UINT32(4U, g_counter_u32);
}
void test_ready_sat_on_below_limit_returns_0_updated(void)
{
    g_counter_u32 = 30U;
    g_systemReady_b = true;
    set_SaturationEn_b(true);
    set_CounterLimit_u32(100U);

    uint8_t result = MyLib_UpdateCounter_u8(20U);

    TEST_ASSERT_EQUAL_UINT8(0U, result);
    TEST_ASSERT_EQUAL_UINT32(50U, g_counter_u32);
}
void test_ready_sat_on_equal_limit_returns_0_updated(void)
{
    g_counter_u32 = 80U;
    g_systemReady_b = true;
    set_SaturationEn_b(true);
    set_CounterLimit_u32(100U);

    uint8_t result = MyLib_UpdateCounter_u8(20U);

    TEST_ASSERT_EQUAL_UINT8(0U, result);
    TEST_ASSERT_EQUAL_UINT32(100U, g_counter_u32);
}
void test_ready_sat_on_exceeds_by_one_returns_2_clamped(void)
{
    g_counter_u32 = 90U;
    g_systemReady_b = true;
    set_SaturationEn_b(true);
    set_CounterLimit_u32(100U);

    uint8_t result = MyLib_UpdateCounter_u8(11U);

    TEST_ASSERT_EQUAL_UINT8(2U, result);
    TEST_ASSERT_EQUAL_UINT32(100U, g_counter_u32);
}
void test_ready_sat_on_exceeds_significantly_returns_2_clamped(void)
{
    g_counter_u32 = 50U;
    g_systemReady_b = true;
    set_SaturationEn_b(true);
    set_CounterLimit_u32(100U);

    uint8_t result = MyLib_UpdateCounter_u8(200U);

    TEST_ASSERT_EQUAL_UINT8(2U, result);
    TEST_ASSERT_EQUAL_UINT32(100U, g_counter_u32);
}
void test_ready_sat_on_wraparound_vs_limit(void)
{
    g_counter_u32 = UINT32_MAX - 10U;
    g_systemReady_b = true;
    set_SaturationEn_b(true);
    set_CounterLimit_u32(100U);

    uint8_t result = MyLib_UpdateCounter_u8(20U);

    TEST_ASSERT_EQUAL_UINT8(0U, result);
    TEST_ASSERT_EQUAL_UINT32(9U, g_counter_u32);
}
void test_cycle_counter_toggle_at_16th_call(void)
{
    g_systemReady_b = true;
    set_SaturationEn_b(false);
    set_CounterLimit_u32(1000U);
    g_counter_u32 = 0U;

    for (uint8_t i = 0U; i < 15U; i++)
    {
        MyLib_UpdateCounter_u8(1U);
    }

    TEST_ASSERT_FALSE(get_SaturationEn_b());

    MyLib_UpdateCounter_u8(1U);

    TEST_ASSERT_TRUE(get_SaturationEn_b());
}
void test_cycle_counter_no_toggle_at_15_calls(void)
{
    g_systemReady_b = true;
    set_SaturationEn_b(false);
    set_CounterLimit_u32(1000U);
    g_counter_u32 = 0U;

    for (uint8_t i = 0U; i < 15U; i++)
    {
        MyLib_UpdateCounter_u8(1U);
    }

    TEST_ASSERT_FALSE(get_SaturationEn_b());
}
void test_cycle_counter_toggle_twice_at_32_calls(void)
{
    g_systemReady_b = true;
    set_SaturationEn_b(false);
    set_CounterLimit_u32(1000U);
    g_counter_u32 = 0U;

    for (uint8_t i = 0U; i < 16U; i++)
    {
        MyLib_UpdateCounter_u8(1U);
    }

    TEST_ASSERT_TRUE(get_SaturationEn_b());

    for (uint8_t i = 0U; i < 16U; i++)
    {
        MyLib_UpdateCounter_u8(1U);
    }

    TEST_ASSERT_FALSE(get_SaturationEn_b());
}
void test_not_ready_on_16th_call_no_toggle(void)
{
    g_systemReady_b = true;
    set_SaturationEn_b(false);
    set_CounterLimit_u32(1000U);
    g_counter_u32 = 0U;

    for (uint8_t i = 0U; i < 15U; i++)
    {
        MyLib_UpdateCounter_u8(1U);
    }

    g_systemReady_b = false;
    uint32_t counter_before = g_counter_u32;

    uint8_t result = MyLib_UpdateCounter_u8(1U);

    TEST_ASSERT_EQUAL_UINT8(1U, result);
    TEST_ASSERT_EQUAL_UINT32(counter_before, g_counter_u32);
    TEST_ASSERT_FALSE(get_SaturationEn_b());
}
void test_saturation_on_16th_call_with_toggle(void)
{
    g_systemReady_b = true;
    set_SaturationEn_b(true);
    set_CounterLimit_u32(20U);
    g_counter_u32 = 0U;

    for (uint8_t i = 0U; i < 15U; i++)
    {
        MyLib_UpdateCounter_u8(1U);
    }

    TEST_ASSERT_TRUE(get_SaturationEn_b());

    uint8_t result = MyLib_UpdateCounter_u8(10U);

    TEST_ASSERT_EQUAL_UINT8(2U, result);
    TEST_ASSERT_EQUAL_UINT32(20U, g_counter_u32);
    TEST_ASSERT_FALSE(get_SaturationEn_b());
}
void test_limit_zero_sat_on_positive_inc_returns_2_clamped(void)
{
    g_counter_u32 = 0U;
    g_systemReady_b = true;
    set_SaturationEn_b(true);
    set_CounterLimit_u32(0U);

    uint8_t result = MyLib_UpdateCounter_u8(1U);

    TEST_ASSERT_EQUAL_UINT8(2U, result);
    TEST_ASSERT_EQUAL_UINT32(0U, g_counter_u32);
}
void test_limit_max_sat_on_no_saturation_returns_0(void)
{
    g_counter_u32 = 100U;
    g_systemReady_b = true;
    set_SaturationEn_b(true);
    set_CounterLimit_u32(UINT32_MAX);

    uint8_t result = MyLib_UpdateCounter_u8(50U);

    TEST_ASSERT_EQUAL_UINT8(0U, result);
    TEST_ASSERT_EQUAL_UINT32(150U, g_counter_u32);
}
void test_counter_max_add_1_sat_off_wraps_to_0(void)
{
    g_counter_u32 = UINT32_MAX;
    g_systemReady_b = true;
    set_SaturationEn_b(false);
    set_CounterLimit_u32(100U);

    uint8_t result = MyLib_UpdateCounter_u8(1U);

    TEST_ASSERT_EQUAL_UINT8(0U, result);
    TEST_ASSERT_EQUAL_UINT32(0U, g_counter_u32);
}
void test_counter_max_add_1_sat_on_wrapped_vs_limit(void)
{
    g_counter_u32 = UINT32_MAX;
    g_systemReady_b = true;
    set_SaturationEn_b(true);
    set_CounterLimit_u32(100U);

    uint8_t result = MyLib_UpdateCounter_u8(1U);

    TEST_ASSERT_EQUAL_UINT8(0U, result);
    TEST_ASSERT_EQUAL_UINT32(0U, g_counter_u32);
}
void test_multiple_calls_sat_off_accumulates_correctly(void)
{
    g_counter_u32 = 10U;
    g_systemReady_b = true;
    set_SaturationEn_b(false);
    set_CounterLimit_u32(1000U);

    MyLib_UpdateCounter_u8(5U);
    TEST_ASSERT_EQUAL_UINT32(15U, g_counter_u32);

    MyLib_UpdateCounter_u8(10U);
    TEST_ASSERT_EQUAL_UINT32(25U, g_counter_u32);

    MyLib_UpdateCounter_u8(7U);
    TEST_ASSERT_EQUAL_UINT32(32U, g_counter_u32);
}
void test_transition_not_ready_to_ready(void)
{
    g_counter_u32 = 50U;
    g_systemReady_b = false;
    set_SaturationEn_b(false);
    set_CounterLimit_u32(100U);

    uint8_t result1 = MyLib_UpdateCounter_u8(10U);
    TEST_ASSERT_EQUAL_UINT8(1U, result1);
    TEST_ASSERT_EQUAL_UINT32(50U, g_counter_u32);

    g_systemReady_b = true;

    uint8_t result2 = MyLib_UpdateCounter_u8(10U);
    TEST_ASSERT_EQUAL_UINT8(0U, result2);
    TEST_ASSERT_EQUAL_UINT32(60U, g_counter_u32);
}
