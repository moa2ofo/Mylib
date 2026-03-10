#include "unity.h"
#include <UpdateCounter_u8.h>
#include "mock_MyLib.h"




void setUp(void)
{
    g_counter_u32 = 0U;
    g_systemReady_b = true;
}
void tearDown(void)
{
}
void test_system_not_ready_returns_1_no_counter_change(void)
{
    g_systemReady_b = false;
    g_counter_u32 = 42U;

    uint8_t result = UpdateCounter_u8(10U);

    TEST_ASSERT_EQUAL_UINT8(1U, result);
    TEST_ASSERT_EQUAL_UINT32(42U, g_counter_u32);
}
void test_add_zero_saturation_disabled_no_change(void)
{
    g_counter_u32 = 100U;
    set_SaturationEn_b(false);

    uint8_t result = UpdateCounter_u8(0U);

    TEST_ASSERT_EQUAL_UINT8(0U, result);
    TEST_ASSERT_EQUAL_UINT32(100U, g_counter_u32);
}
void test_add_one_saturation_disabled_increments(void)
{
    g_counter_u32 = 50U;
    set_SaturationEn_b(false);

    uint8_t result = UpdateCounter_u8(1U);

    TEST_ASSERT_EQUAL_UINT8(0U, result);
    TEST_ASSERT_EQUAL_UINT32(51U, g_counter_u32);
}
void test_add_midrange_saturation_disabled_increments(void)
{
    g_counter_u32 = 100U;
    set_SaturationEn_b(false);

    uint8_t result = UpdateCounter_u8(0x7FFFFFFFU);

    TEST_ASSERT_EQUAL_UINT8(0U, result);
    TEST_ASSERT_EQUAL_UINT32(100U + 0x7FFFFFFFU, g_counter_u32);
}
void test_add_max_saturation_disabled_wraps(void)
{
    g_counter_u32 = 10U;
    set_SaturationEn_b(false);

    uint8_t result = UpdateCounter_u8(0xFFFFFFFFU);

    TEST_ASSERT_EQUAL_UINT8(0U, result);
    TEST_ASSERT_EQUAL_UINT32(9U, g_counter_u32);
}
void test_saturation_enabled_new_equals_limit_no_clamp(void)
{
    g_counter_u32 = 100U;
    set_CounterLimit_u32(150U);
    set_SaturationEn_b(true);

    uint8_t result = UpdateCounter_u8(50U);

    TEST_ASSERT_EQUAL_UINT8(0U, result);
    TEST_ASSERT_EQUAL_UINT32(150U, g_counter_u32);
}
void test_saturation_enabled_new_exceeds_limit_by_one(void)
{
    g_counter_u32 = 100U;
    set_CounterLimit_u32(150U);
    set_SaturationEn_b(true);

    uint8_t result = UpdateCounter_u8(51U);

    TEST_ASSERT_EQUAL_UINT8(2U, result);
    TEST_ASSERT_EQUAL_UINT32(150U, g_counter_u32);
}
void test_saturation_enabled_new_significantly_exceeds_limit(void)
{
    g_counter_u32 = 100U;
    set_CounterLimit_u32(200U);
    set_SaturationEn_b(true);

    uint8_t result = UpdateCounter_u8(1000U);

    TEST_ASSERT_EQUAL_UINT8(2U, result);
    TEST_ASSERT_EQUAL_UINT32(200U, g_counter_u32);
}
void test_saturation_enabled_new_below_limit_no_clamp(void)
{
    g_counter_u32 = 100U;
    set_CounterLimit_u32(500U);
    set_SaturationEn_b(true);

    uint8_t result = UpdateCounter_u8(50U);

    TEST_ASSERT_EQUAL_UINT8(0U, result);
    TEST_ASSERT_EQUAL_UINT32(150U, g_counter_u32);
}
void test_cycle_counter_toggle_at_16th_call(void)
{
    set_SaturationEn_b(false);
    set_CounterLimit_u32(0xFFFFFFFFU);

    for (uint8_t i = 0; i < 15U; i++)
    {
        UpdateCounter_u8(0U);
        TEST_ASSERT_FALSE(get_SaturationEn_b());
    }

    UpdateCounter_u8(0U);
    TEST_ASSERT_TRUE(get_SaturationEn_b());
}
void test_cycle_counter_toggle_false_to_true(void)
{
    set_SaturationEn_b(false);
    set_CounterLimit_u32(0xFFFFFFFFU);

    for (uint8_t i = 0; i < 16U; i++)
    {
        UpdateCounter_u8(0U);
    }

    TEST_ASSERT_TRUE(get_SaturationEn_b());
}
void test_cycle_counter_toggle_true_to_false(void)
{
    set_SaturationEn_b(true);
    set_CounterLimit_u32(0xFFFFFFFFU);

    for (uint8_t i = 0; i < 16U; i++)
    {
        UpdateCounter_u8(0U);
    }

    TEST_ASSERT_FALSE(get_SaturationEn_b());
}
void test_multiple_toggle_cycles_32_calls(void)
{
    set_SaturationEn_b(false);
    set_CounterLimit_u32(0xFFFFFFFFU);

    for (uint8_t i = 0; i < 32U; i++)
    {
        UpdateCounter_u8(0U);
    }

    TEST_ASSERT_FALSE(get_SaturationEn_b());
}
void test_saturation_disabled_max_counter_wraps_to_zero(void)
{
    g_counter_u32 = 0xFFFFFFFFU;
    set_SaturationEn_b(false);

    uint8_t result = UpdateCounter_u8(1U);

    TEST_ASSERT_EQUAL_UINT8(0U, result);
    TEST_ASSERT_EQUAL_UINT32(0U, g_counter_u32);
}
void test_saturation_enabled_wrap_below_limit_no_clamp(void)
{
    g_counter_u32 = 0xFFFFFFFFU;
    set_CounterLimit_u32(100U);
    set_SaturationEn_b(true);

    uint8_t result = UpdateCounter_u8(50U);

    TEST_ASSERT_EQUAL_UINT8(0U, result);
    TEST_ASSERT_EQUAL_UINT32(49U, g_counter_u32);
}
void test_saturation_enabled_wrap_exceeds_limit_clamped(void)
{
    g_counter_u32 = 0xFFFFFFFFU;
    set_CounterLimit_u32(50U);
    set_SaturationEn_b(true);

    uint8_t result = UpdateCounter_u8(100U);

    TEST_ASSERT_EQUAL_UINT8(2U, result);
    TEST_ASSERT_EQUAL_UINT32(50U, g_counter_u32);
}
void test_saturation_enabled_limit_zero_clamps_to_zero(void)
{
    g_counter_u32 = 0U;
    set_CounterLimit_u32(0U);
    set_SaturationEn_b(true);

    uint8_t result = UpdateCounter_u8(10U);

    TEST_ASSERT_EQUAL_UINT8(2U, result);
    TEST_ASSERT_EQUAL_UINT32(0U, g_counter_u32);
}
void test_saturation_enabled_limit_max_no_clamp(void)
{
    g_counter_u32 = 100U;
    set_CounterLimit_u32(0xFFFFFFFFU);
    set_SaturationEn_b(true);

    uint8_t result = UpdateCounter_u8(50U);

    TEST_ASSERT_EQUAL_UINT8(0U, result);
    TEST_ASSERT_EQUAL_UINT32(150U, g_counter_u32);
}
void test_system_ready_transition_across_calls(void)
{
    g_counter_u32 = 50U;
    g_systemReady_b = false;

    uint8_t result1 = UpdateCounter_u8(10U);
    TEST_ASSERT_EQUAL_UINT8(1U, result1);
    TEST_ASSERT_EQUAL_UINT32(50U, g_counter_u32);

    g_systemReady_b = true;
    set_SaturationEn_b(false);

    uint8_t result2 = UpdateCounter_u8(10U);
    TEST_ASSERT_EQUAL_UINT8(0U, result2);
    TEST_ASSERT_EQUAL_UINT32(60U, g_counter_u32);
}
void test_saturation_precedence_return_2_over_0(void)
{
    g_counter_u32 = 100U;
    set_CounterLimit_u32(120U);
    set_SaturationEn_b(true);

    uint8_t result = UpdateCounter_u8(30U);

    TEST_ASSERT_EQUAL_UINT8(2U, result);
    TEST_ASSERT_EQUAL_UINT32(120U, g_counter_u32);
}
