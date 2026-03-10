#include "MyLib.h"
#include "MyLib_UpdateCounter_u8.h"
#include "mock_MyLib.h"
#include "unity.h"
#include <string.h>




void setUp(void)
{
}
void tearDown(void)
{
}
void test_system_not_ready_returns_1_no_update(void)
{
    uint8_t result;
    uint32_t initial_counter = 42U;

    g_systemReady_b = false;
    g_counter_u32 = initial_counter;

    result = MyLib_UpdateCounter_u8(10U);

    TEST_ASSERT_EQUAL_UINT8(1U, result);
    TEST_ASSERT_EQUAL_UINT32(initial_counter, g_counter_u32);
}
void test_ready_sat_off_zero_inc_returns_0_unchanged(void)
{
    uint8_t result;
    uint32_t initial_counter = 50U;

    g_systemReady_b = true;
    g_counter_u32 = initial_counter;
    set_SaturationEn_b(false);
    set_CounterLimit_u32(100U);

    result = MyLib_UpdateCounter_u8(0U);

    TEST_ASSERT_EQUAL_UINT8(0U, result);
    TEST_ASSERT_EQUAL_UINT32(initial_counter, g_counter_u32);
}
void test_ready_sat_off_normal_inc_returns_0_updated(void)
{
    uint8_t result;

    g_systemReady_b = true;
    g_counter_u32 = 30U;
    set_SaturationEn_b(false);
    set_CounterLimit_u32(100U);

    result = MyLib_UpdateCounter_u8(15U);

    TEST_ASSERT_EQUAL_UINT8(0U, result);
    TEST_ASSERT_EQUAL_UINT32(45U, g_counter_u32);
}
void test_ready_sat_off_wraparound_returns_0_wrapped(void)
{
    uint8_t result;

    g_systemReady_b = true;
    g_counter_u32 = UINT32_MAX - 5U;
    set_SaturationEn_b(false);
    set_CounterLimit_u32(100U);

    result = MyLib_UpdateCounter_u8(10U);

    TEST_ASSERT_EQUAL_UINT8(0U, result);
    TEST_ASSERT_EQUAL_UINT32(4U, g_counter_u32);
}
void test_ready_sat_on_below_limit_returns_0_updated(void)
{
    uint8_t result;

    g_systemReady_b = true;
    g_counter_u32 = 20U;
    set_SaturationEn_b(true);
    set_CounterLimit_u32(100U);

    result = MyLib_UpdateCounter_u8(30U);

    TEST_ASSERT_EQUAL_UINT8(0U, result);
    TEST_ASSERT_EQUAL_UINT32(50U, g_counter_u32);
}
void test_ready_sat_on_exact_limit_returns_0_at_limit(void)
{
    uint8_t result;

    g_systemReady_b = true;
    g_counter_u32 = 80U;
    set_SaturationEn_b(true);
    set_CounterLimit_u32(100U);

    result = MyLib_UpdateCounter_u8(20U);

    TEST_ASSERT_EQUAL_UINT8(0U, result);
    TEST_ASSERT_EQUAL_UINT32(100U, g_counter_u32);
}
void test_ready_sat_on_exceed_by_one_returns_2_clamped(void)
{
    uint8_t result;

    g_systemReady_b = true;
    g_counter_u32 = 80U;
    set_SaturationEn_b(true);
    set_CounterLimit_u32(100U);

    result = MyLib_UpdateCounter_u8(21U);

    TEST_ASSERT_EQUAL_UINT8(2U, result);
    TEST_ASSERT_EQUAL_UINT32(100U, g_counter_u32);
}
void test_ready_sat_on_far_exceed_returns_2_clamped(void)
{
    uint8_t result;

    g_systemReady_b = true;
    g_counter_u32 = 50U;
    set_SaturationEn_b(true);
    set_CounterLimit_u32(100U);

    result = MyLib_UpdateCounter_u8(1000U);

    TEST_ASSERT_EQUAL_UINT8(2U, result);
    TEST_ASSERT_EQUAL_UINT32(100U, g_counter_u32);
}
void test_ready_sat_on_wraparound_vs_limit(void)
{
    uint8_t result;

    g_systemReady_b = true;
    g_counter_u32 = UINT32_MAX - 10U;
    set_SaturationEn_b(true);
    set_CounterLimit_u32(100U);

    result = MyLib_UpdateCounter_u8(20U);

    TEST_ASSERT_EQUAL_UINT8(0U, result);
    TEST_ASSERT_EQUAL_UINT32(9U, g_counter_u32);
}
void test_cycle_counter_toggles_after_16_calls(void)
{
    uint8_t i;
    bool initial_sat;

    g_systemReady_b = true;
    g_counter_u32 = 0U;
    set_SaturationEn_b(false);
    set_CounterLimit_u32(1000U);
    initial_sat = get_SaturationEn_b();

    for (i = 0U; i < 15U; i++)
    {
        MyLib_UpdateCounter_u8(1U);
        TEST_ASSERT_EQUAL(initial_sat, get_SaturationEn_b());
    }

    MyLib_UpdateCounter_u8(1U);
    TEST_ASSERT_EQUAL(!initial_sat, get_SaturationEn_b());
}
void test_cycle_counter_no_toggle_non_multiple_16(void)
{
    uint8_t i;
    bool initial_sat;

    g_systemReady_b = true;
    g_counter_u32 = 0U;
    set_SaturationEn_b(true);
    set_CounterLimit_u32(1000U);
    initial_sat = get_SaturationEn_b();

    for (i = 0U; i < 10U; i++)
    {
        MyLib_UpdateCounter_u8(1U);
    }

    TEST_ASSERT_EQUAL(initial_sat, get_SaturationEn_b());
}
void test_cycle_counter_increments_independent_of_ready(void)
{
    bool initial_sat;

    g_systemReady_b = true;
    g_counter_u32 = 0U;
    set_SaturationEn_b(false);
    set_CounterLimit_u32(1000U);
    initial_sat = get_SaturationEn_b();

    MyLib_UpdateCounter_u8(1U);
    MyLib_UpdateCounter_u8(1U);

    g_systemReady_b = false;
    MyLib_UpdateCounter_u8(1U);
    MyLib_UpdateCounter_u8(1U);

    g_systemReady_b = true;
    MyLib_UpdateCounter_u8(1U);
    MyLib_UpdateCounter_u8(1U);
    MyLib_UpdateCounter_u8(1U);
    MyLib_UpdateCounter_u8(1U);
    MyLib_UpdateCounter_u8(1U);
    MyLib_UpdateCounter_u8(1U);
    MyLib_UpdateCounter_u8(1U);
    MyLib_UpdateCounter_u8(1U);
    MyLib_UpdateCounter_u8(1U);
    MyLib_UpdateCounter_u8(1U);
    MyLib_UpdateCounter_u8(1U);
    MyLib_UpdateCounter_u8(1U);

    TEST_ASSERT_EQUAL(!initial_sat, get_SaturationEn_b());
}
void test_saturation_limit_zero_clamps_correctly(void)
{
    uint8_t result;

    g_systemReady_b = true;
    g_counter_u32 = 0U;
    set_SaturationEn_b(true);
    set_CounterLimit_u32(0U);

    result = MyLib_UpdateCounter_u8(1U);

    TEST_ASSERT_EQUAL_UINT8(2U, result);
    TEST_ASSERT_EQUAL_UINT32(0U, g_counter_u32);
}
void test_saturation_limit_max_no_clamp(void)
{
    uint8_t result;

    g_systemReady_b = true;
    g_counter_u32 = UINT32_MAX - 10U;
    set_SaturationEn_b(true);
    set_CounterLimit_u32(UINT32_MAX);

    result = MyLib_UpdateCounter_u8(5U);

    TEST_ASSERT_EQUAL_UINT8(0U, result);
    TEST_ASSERT_EQUAL_UINT32(UINT32_MAX - 5U, g_counter_u32);
}
void test_counter_max_add_one_sat_on_wraparound(void)
{
    uint8_t result;

    g_systemReady_b = true;
    g_counter_u32 = UINT32_MAX;
    set_SaturationEn_b(true);
    set_CounterLimit_u32(100U);

    result = MyLib_UpdateCounter_u8(1U);

    TEST_ASSERT_EQUAL_UINT8(0U, result);
    TEST_ASSERT_EQUAL_UINT32(0U, g_counter_u32);
}
