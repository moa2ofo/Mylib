#include "MyLib_UpdateCounter_u8.h"
#include "mock_MyLib.h"
#include "unity.h"
#include <string.h>
#include "MyLib.h"
#include "MyLib_UpdateCounter_u8.h"




// ============================================================================
// CALLBACKS
// ============================================================================

// No callbacks required for this unit test suite.

// ============================================================================
// SETUP AND TEARDOWN
// ============================================================================

void setUp(void)
{
    g_counter_u32 = 0U;
    g_systemReady_b = false;
    SetCounterLimit_u32(0U);
    SetSaturationEn_b(false);
}

void tearDown(void)
{
}

// ============================================================================
// TEST FUNCTIONS
// ============================================================================

void test_system_not_ready_returns_1(void)
{
    uint8_t result;
    
    g_systemReady_b = false;
    g_counter_u32 = 10U;
    
    result = MyLib_UpdateCounter_u8(5U);
    
    TEST_ASSERT_EQUAL_UINT8(1U, result);
    TEST_ASSERT_EQUAL_UINT32(10U, g_counter_u32);
}

void test_ready_sat_disabled_add_zero_returns_0(void)
{
    uint8_t result;
    
    g_systemReady_b = true;
    g_counter_u32 = 50U;
    SetSaturationEn_b(false);
    SetCounterLimit_u32(100U);
    
    result = MyLib_UpdateCounter_u8(0U);
    
    TEST_ASSERT_EQUAL_UINT8(0U, result);
    TEST_ASSERT_EQUAL_UINT32(50U, g_counter_u32);
}

void test_ready_sat_disabled_add_small_returns_0(void)
{
    uint8_t result;
    
    g_systemReady_b = true;
    g_counter_u32 = 10U;
    SetSaturationEn_b(false);
    SetCounterLimit_u32(100U);
    
    result = MyLib_UpdateCounter_u8(15U);
    
    TEST_ASSERT_EQUAL_UINT8(0U, result);
    TEST_ASSERT_EQUAL_UINT32(25U, g_counter_u32);
}

void test_ready_sat_disabled_wrap_around_returns_0(void)
{
    uint8_t result;
    
    g_systemReady_b = true;
    g_counter_u32 = 0xFFFFFFFEU;
    SetSaturationEn_b(false);
    SetCounterLimit_u32(100U);
    
    result = MyLib_UpdateCounter_u8(5U);
    
    TEST_ASSERT_EQUAL_UINT8(0U, result);
    TEST_ASSERT_EQUAL_UINT32(3U, g_counter_u32);
}

void test_ready_sat_enabled_below_limit_returns_0(void)
{
    uint8_t result;
    
    g_systemReady_b = true;
    g_counter_u32 = 50U;
    SetSaturationEn_b(true);
    SetCounterLimit_u32(100U);
    
    result = MyLib_UpdateCounter_u8(20U);
    
    TEST_ASSERT_EQUAL_UINT8(0U, result);
    TEST_ASSERT_EQUAL_UINT32(70U, g_counter_u32);
}

void test_ready_sat_enabled_equals_limit_returns_0(void)
{
    uint8_t result;
    
    g_systemReady_b = true;
    g_counter_u32 = 80U;
    SetSaturationEn_b(true);
    SetCounterLimit_u32(100U);
    
    result = MyLib_UpdateCounter_u8(20U);
    
    TEST_ASSERT_EQUAL_UINT8(0U, result);
    TEST_ASSERT_EQUAL_UINT32(100U, g_counter_u32);
}

void test_ready_sat_enabled_exceeds_by_1_returns_2(void)
{
    uint8_t result;
    
    g_systemReady_b = true;
    g_counter_u32 = 100U;
    SetSaturationEn_b(true);
    SetCounterLimit_u32(100U);
    
    result = MyLib_UpdateCounter_u8(1U);
    
    TEST_ASSERT_EQUAL_UINT8(2U, result);
    TEST_ASSERT_EQUAL_UINT32(100U, g_counter_u32);
}

void test_ready_sat_enabled_exceeds_large_returns_2(void)
{
    uint8_t result;
    
    g_systemReady_b = true;
    g_counter_u32 = 50U;
    SetSaturationEn_b(true);
    SetCounterLimit_u32(100U);
    
    result = MyLib_UpdateCounter_u8(1000U);
    
    TEST_ASSERT_EQUAL_UINT8(2U, result);
    TEST_ASSERT_EQUAL_UINT32(100U, g_counter_u32);
}

void test_ready_sat_enabled_at_limit_add_zero_returns_0(void)
{
    uint8_t result;
    
    g_systemReady_b = true;
    g_counter_u32 = 100U;
    SetSaturationEn_b(true);
    SetCounterLimit_u32(100U);
    
    result = MyLib_UpdateCounter_u8(0U);
    
    TEST_ASSERT_EQUAL_UINT8(0U, result);
    TEST_ASSERT_EQUAL_UINT32(100U, g_counter_u32);
}

void test_ready_sat_enabled_at_limit_add_nonzero_returns_2(void)
{
    uint8_t result;
    
    g_systemReady_b = true;
    g_counter_u32 = 100U;
    SetSaturationEn_b(true);
    SetCounterLimit_u32(100U);
    
    result = MyLib_UpdateCounter_u8(5U);
    
    TEST_ASSERT_EQUAL_UINT8(2U, result);
    TEST_ASSERT_EQUAL_UINT32(100U, g_counter_u32);
}

void test_ready_sat_enabled_near_max_wrap_exceeds_limit(void)
{
    uint8_t result;
    
    g_systemReady_b = true;
    g_counter_u32 = 0xFFFFFFF0U;
    SetSaturationEn_b(true);
    SetCounterLimit_u32(100U);
    
    result = MyLib_UpdateCounter_u8(20U);
    
    TEST_ASSERT_EQUAL_UINT8(2U, result);
    TEST_ASSERT_EQUAL_UINT32(100U, g_counter_u32);
}

void test_cycle_toggle_after_16_calls(void)
{
    uint8_t i;
    bool initial_sat;
    bool final_sat;
    
    g_systemReady_b = true;
    g_counter_u32 = 0U;
    SetSaturationEn_b(false);
    SetCounterLimit_u32(1000U);
    
    initial_sat = GetSaturationEn_b();
    
    for (i = 0U; i < 15U; i++)
    {
        MyLib_UpdateCounter_u8(1U);
    }
    
    TEST_ASSERT_EQUAL(initial_sat, GetSaturationEn_b());
    
    MyLib_UpdateCounter_u8(1U);
    
    final_sat = GetSaturationEn_b();
    TEST_ASSERT_NOT_EQUAL(initial_sat, final_sat);
}

void test_cycle_toggle_after_32_calls(void)
{
    uint8_t i;
    bool initial_sat;
    bool after_16_sat;
    bool after_32_sat;
    
    g_systemReady_b = true;
    g_counter_u32 = 0U;
    SetSaturationEn_b(false);
    SetCounterLimit_u32(1000U);
    
    initial_sat = GetSaturationEn_b();
    
    for (i = 0U; i < 16U; i++)
    {
        MyLib_UpdateCounter_u8(1U);
    }
    
    after_16_sat = GetSaturationEn_b();
    TEST_ASSERT_NOT_EQUAL(initial_sat, after_16_sat);
    
    for (i = 0U; i < 15U; i++)
    {
        MyLib_UpdateCounter_u8(1U);
    }
    
    TEST_ASSERT_EQUAL(after_16_sat, GetSaturationEn_b());
    
    MyLib_UpdateCounter_u8(1U);
    
    after_32_sat = GetSaturationEn_b();
    TEST_ASSERT_NOT_EQUAL(after_16_sat, after_32_sat);
    TEST_ASSERT_EQUAL(initial_sat, after_32_sat);
}

void test_cycle_counter_persistence(void)
{
    uint8_t i;
    
    g_systemReady_b = true;
    g_counter_u32 = 0U;
    SetSaturationEn_b(false);
    SetCounterLimit_u32(1000U);
    
    for (i = 0U; i < 16U; i++)
    {
        MyLib_UpdateCounter_u8(1U);
    }
    
    bool sat_after_16 = GetSaturationEn_b();
    
    for (i = 0U; i < 16U; i++)
    {
        MyLib_UpdateCounter_u8(1U);
    }
    
    bool sat_after_32 = GetSaturationEn_b();
    
    TEST_ASSERT_NOT_EQUAL(sat_after_16, sat_after_32);
}

void test_ready_sat_disabled_max_add_1_wraps_to_0(void)
{
    uint8_t result;
    
    g_systemReady_b = true;
    g_counter_u32 = 0xFFFFFFFFU;
    SetSaturationEn_b(false);
    SetCounterLimit_u32(100U);
    
    result = MyLib_UpdateCounter_u8(1U);
    
    TEST_ASSERT_EQUAL_UINT8(0U, result);
    TEST_ASSERT_EQUAL_UINT32(0U, g_counter_u32);
}

void test_ready_sat_enabled_limit_0_clamps_to_0(void)
{
    uint8_t result;
    
    g_systemReady_b = true;
    g_counter_u32 = 0U;
    SetSaturationEn_b(true);
    SetCounterLimit_u32(0U);
    
    result = MyLib_UpdateCounter_u8(10U);
    
    TEST_ASSERT_EQUAL_UINT8(2U, result);
    TEST_ASSERT_EQUAL_UINT32(0U, g_counter_u32);
}

void test_ready_sat_enabled_limit_max_no_wrap_returns_0(void)
{
    uint8_t result;
    
    g_systemReady_b = true;
    g_counter_u32 = 100U;
    SetSaturationEn_b(true);
    SetCounterLimit_u32(0xFFFFFFFFU);
    
    result = MyLib_UpdateCounter_u8(50U);
    
    TEST_ASSERT_EQUAL_UINT8(0U, result);
    TEST_ASSERT_EQUAL_UINT32(150U, g_counter_u32);
}

void test_ready_sat_enabled_limit_max_at_max_minus_1_add_1(void)
{
    uint8_t result;
    
    g_systemReady_b = true;
    g_counter_u32 = 0xFFFFFFFEU;
    SetSaturationEn_b(true);
    SetCounterLimit_u32(0xFFFFFFFFU);
    
    result = MyLib_UpdateCounter_u8(1U);
    
    TEST_ASSERT_EQUAL_UINT8(0U, result);
    TEST_ASSERT_EQUAL_UINT32(0xFFFFFFFFU, g_counter_u32);
}

void test_ready_sat_enabled_limit_max_at_max_add_1_wraps(void)
{
    uint8_t result;
    
    g_systemReady_b = true;
    g_counter_u32 = 0xFFFFFFFFU;
    SetSaturationEn_b(true);
    SetCounterLimit_u32(0xFFFFFFFFU);
    
    result = MyLib_UpdateCounter_u8(1U);
    
    TEST_ASSERT_EQUAL_UINT8(0U, result);
    TEST_ASSERT_EQUAL_UINT32(0U, g_counter_u32);
}

void test_not_ready_then_ready(void)
{
    uint8_t result1;
    uint8_t result2;
    
    g_systemReady_b = false;
    g_counter_u32 = 10U;
    SetSaturationEn_b(false);
    SetCounterLimit_u32(100U);
    
    result1 = MyLib_UpdateCounter_u8(5U);
    TEST_ASSERT_EQUAL_UINT8(1U, result1);
    TEST_ASSERT_EQUAL_UINT32(10U, g_counter_u32);
    
    g_systemReady_b = true;
    
    result2 = MyLib_UpdateCounter_u8(5U);
    TEST_ASSERT_EQUAL_UINT8(0U, result2);
    TEST_ASSERT_EQUAL_UINT32(15U, g_counter_u32);
}

void test_combo_sat_enabled_mid_limit_exactly_at_limit(void)
{
    uint8_t result;
    
    g_systemReady_b = true;
    g_counter_u32 = 200U;
    SetSaturationEn_b(true);
    SetCounterLimit_u32(500U);
    
    result = MyLib_UpdateCounter_u8(300U);
    
    TEST_ASSERT_EQUAL_UINT8(0U, result);
    TEST_ASSERT_EQUAL_UINT32(500U, g_counter_u32);
}

void test_combo_sat_enabled_mid_limit_exceeds_limit(void)
{
    uint8_t result;
    
    g_systemReady_b = true;
    g_counter_u32 = 200U;
    SetSaturationEn_b(true);
    SetCounterLimit_u32(500U);
    
    result = MyLib_UpdateCounter_u8(350U);
    
    TEST_ASSERT_EQUAL_UINT8(2U, result);
    TEST_ASSERT_EQUAL_UINT32(500U, g_counter_u32);
}

void test_combo_sat_disabled_multiple_increments(void)
{
    uint8_t result;
    
    g_systemReady_b = true;
    g_counter_u32 = 0U;
    SetSaturationEn_b(false);
    SetCounterLimit_u32(1000U);
    
    result = MyLib_UpdateCounter_u8(10U);
    TEST_ASSERT_EQUAL_UINT8(0U, result);
    TEST_ASSERT_EQUAL_UINT32(10U, g_counter_u32);
    
    result = MyLib_UpdateCounter_u8(20U);
    TEST_ASSERT_EQUAL_UINT8(0U, result);
    TEST_ASSERT_EQUAL_UINT32(30U, g_counter_u32);
    
    result = MyLib_UpdateCounter_u8(30U);
    TEST_ASSERT_EQUAL_UINT8(0U, result);
    TEST_ASSERT_EQUAL_UINT32(60U, g_counter_u32);
}

void test_combo_sat_toggled_via_cycle_count(void)
{
    uint8_t i;
    uint8_t result;
    
    g_systemReady_b = true;
    g_counter_u32 = 0U;
    SetSaturationEn_b(true);
    SetCounterLimit_u32(50U);
    
    for (i = 0U; i < 15U; i++)
    {
        MyLib_UpdateCounter_u8(1U);
    }
    
    TEST_ASSERT_EQUAL(true, GetSaturationEn_b());
    
    result = MyLib_UpdateCounter_u8(100U);
    TEST_ASSERT_EQUAL_UINT8(2U, result);
    TEST_ASSERT_EQUAL_UINT32(50U, g_counter_u32);
    
    TEST_ASSERT_EQUAL(false, GetSaturationEn_b());
    
    result = MyLib_UpdateCounter_u8(100U);
    TEST_ASSERT_EQUAL_UINT8(0U, result);
    TEST_ASSERT_EQUAL_UINT32(150U, g_counter_u32);
}

void test_edge_counter_0_sat_limit_0_add_0(void)
{
    uint8_t result;
    
    g_systemReady_b = true;
    g_counter_u32 = 0U;
    SetSaturationEn_b(true);
    SetCounterLimit_u32(0U);
    
    result = MyLib_UpdateCounter_u8(0U);
    
    TEST_ASSERT_EQUAL_UINT8(0U, result);
    TEST_ASSERT_EQUAL_UINT32(0U, g_counter_u32);
}

void test_edge_counter_0_sat_limit_1_add_1(void)
{
    uint8_t result;
    
    g_systemReady_b = true;
    g_counter_u32 = 0U;
    SetSaturationEn_b(true);
    SetCounterLimit_u32(1U);
    
    result = MyLib_UpdateCounter_u8(1U);
    
    TEST_ASSERT_EQUAL_UINT8(0U, result);
    TEST_ASSERT_EQUAL_UINT32(1U, g_counter_u32);
}

void test_edge_counter_0_sat_limit_1_add_2(void)
{
    uint8_t result;
    
    g_systemReady_b = true;
    g_counter_u32 = 0U;
    SetSaturationEn_b(true);
    SetCounterLimit_u32(1U);
    
    result = MyLib_UpdateCounter_u8(2U);
    
    TEST_ASSERT_EQUAL_UINT8(2U, result);
    TEST_ASSERT_EQUAL_UINT32(1U, g_counter_u32);
}