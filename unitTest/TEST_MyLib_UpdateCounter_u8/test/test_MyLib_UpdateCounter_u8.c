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
    
    g_systemReady_b = false;
    g_counter_u32 = 50U;
    
    result = MyLib_UpdateCounter_u8(10U);
    
    TEST_ASSERT_EQUAL_UINT8(1U, result);
    TEST_ASSERT_EQUAL_UINT32(50U, g_counter_u32);
}
void test_ready_sat_off_zero_inc_returns_0(void)
{
    uint8_t result;
    
    g_systemReady_b = true;
    g_counter_u32 = 100U;
    set_SaturationEn_b(false);
    
    result = MyLib_UpdateCounter_u8(0U);
    
    TEST_ASSERT_EQUAL_UINT8(0U, result);
    TEST_ASSERT_EQUAL_UINT32(100U, g_counter_u32);
}
void test_ready_sat_off_normal_inc_returns_0(void)
{
    uint8_t result;
    
    g_systemReady_b = true;
    g_counter_u32 = 50U;
    set_SaturationEn_b(false);
    
    result = MyLib_UpdateCounter_u8(25U);
    
    TEST_ASSERT_EQUAL_UINT8(0U, result);
    TEST_ASSERT_EQUAL_UINT32(75U, g_counter_u32);
}
void test_ready_sat_off_wrap_returns_0(void)
{
    uint8_t result;
    
    g_systemReady_b = true;
    g_counter_u32 = UINT32_MAX;
    set_SaturationEn_b(false);
    
    result = MyLib_UpdateCounter_u8(1U);
    
    TEST_ASSERT_EQUAL_UINT8(0U, result);
    TEST_ASSERT_EQUAL_UINT32(0U, g_counter_u32);
}
void test_ready_sat_on_below_limit_returns_0(void)
{
    uint8_t result;
    
    g_systemReady_b = true;
    g_counter_u32 = 50U;
    set_SaturationEn_b(true);
    set_CounterLimit_u32(100U);
    
    result = MyLib_UpdateCounter_u8(30U);
    
    TEST_ASSERT_EQUAL_UINT8(0U, result);
    TEST_ASSERT_EQUAL_UINT32(80U, g_counter_u32);
}
void test_ready_sat_on_reach_limit_returns_0(void)
{
    uint8_t result;
    
    g_systemReady_b = true;
    g_counter_u32 = 50U;
    set_SaturationEn_b(true);
    set_CounterLimit_u32(100U);
    
    result = MyLib_UpdateCounter_u8(50U);
    
    TEST_ASSERT_EQUAL_UINT8(0U, result);
    TEST_ASSERT_EQUAL_UINT32(100U, g_counter_u32);
}
void test_ready_sat_on_exceed_by_one_returns_2(void)
{
    uint8_t result;
    
    g_systemReady_b = true;
    g_counter_u32 = 50U;
    set_SaturationEn_b(true);
    set_CounterLimit_u32(100U);
    
    result = MyLib_UpdateCounter_u8(51U);
    
    TEST_ASSERT_EQUAL_UINT8(2U, result);
    TEST_ASSERT_EQUAL_UINT32(100U, g_counter_u32);
}
void test_ready_sat_on_exceed_large_returns_2(void)
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
void test_ready_sat_on_max_wrap_returns_2(void)
{
    uint8_t result;
    
    g_systemReady_b = true;
    g_counter_u32 = UINT32_MAX;
    set_SaturationEn_b(true);
    set_CounterLimit_u32(100U);
    
    result = MyLib_UpdateCounter_u8(1U);
    
    TEST_ASSERT_EQUAL_UINT8(2U, result);
    TEST_ASSERT_EQUAL_UINT32(100U, g_counter_u32);
}
void test_cycle_counter_toggle_at_16(void)
{
    uint8_t i;
    bool initial_sat;
    bool final_sat;
    
    g_systemReady_b = true;
    g_counter_u32 = 0U;
    set_SaturationEn_b(false);
    set_CounterLimit_u32(1000U);
    
    initial_sat = get_SaturationEn_b();
    
    for (i = 0U; i < 16U; i++)
    {
        MyLib_UpdateCounter_u8(1U);
    }
    
    final_sat = get_SaturationEn_b();
    
    TEST_ASSERT_NOT_EQUAL(initial_sat, final_sat);
}
void test_cycle_counter_no_toggle_before_16(void)
{
    uint8_t i;
    bool initial_sat;
    bool final_sat;
    
    g_systemReady_b = true;
    g_counter_u32 = 0U;
    set_SaturationEn_b(false);
    set_CounterLimit_u32(1000U);
    
    initial_sat = get_SaturationEn_b();
    
    for (i = 0U; i < 15U; i++)
    {
        MyLib_UpdateCounter_u8(1U);
    }
    
    final_sat = get_SaturationEn_b();
    
    TEST_ASSERT_EQUAL(initial_sat, final_sat);
}
void test_sat_limit_zero_positive_inc_returns_2(void)
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
void test_sat_limit_max_no_wrap_returns_0(void)
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
void test_state_transition_not_ready_to_ready(void)
{
    uint8_t result1;
    uint8_t result2;
    
    g_systemReady_b = false;
    g_counter_u32 = 50U;
    set_SaturationEn_b(false);
    
    result1 = MyLib_UpdateCounter_u8(10U);
    TEST_ASSERT_EQUAL_UINT8(1U, result1);
    TEST_ASSERT_EQUAL_UINT32(50U, g_counter_u32);
    
    g_systemReady_b = true;
    
    result2 = MyLib_UpdateCounter_u8(10U);
    TEST_ASSERT_EQUAL_UINT8(0U, result2);
    TEST_ASSERT_EQUAL_UINT32(60U, g_counter_u32);
}
void test_multiple_saturations_maintain_limit(void)
{
    uint8_t result1;
    uint8_t result2;
    uint8_t result3;
    
    g_systemReady_b = true;
    g_counter_u32 = 90U;
    set_SaturationEn_b(true);
    set_CounterLimit_u32(100U);
    
    result1 = MyLib_UpdateCounter_u8(20U);
    TEST_ASSERT_EQUAL_UINT8(2U, result1);
    TEST_ASSERT_EQUAL_UINT32(100U, g_counter_u32);
    
    result2 = MyLib_UpdateCounter_u8(50U);
    TEST_ASSERT_EQUAL_UINT8(2U, result2);
    TEST_ASSERT_EQUAL_UINT32(100U, g_counter_u32);
    
    result3 = MyLib_UpdateCounter_u8(100U);
    TEST_ASSERT_EQUAL_UINT8(2U, result3);
    TEST_ASSERT_EQUAL_UINT32(100U, g_counter_u32);
}
void test_inc_one_from_limit_minus_one_returns_0(void)
{
    uint8_t result;
    
    g_systemReady_b = true;
    g_counter_u32 = 99U;
    set_SaturationEn_b(true);
    set_CounterLimit_u32(100U);
    
    result = MyLib_UpdateCounter_u8(1U);
    
    TEST_ASSERT_EQUAL_UINT8(0U, result);
    TEST_ASSERT_EQUAL_UINT32(100U, g_counter_u32);
}
void test_inc_one_from_limit_returns_2(void)
{
    uint8_t result;
    
    g_systemReady_b = true;
    g_counter_u32 = 100U;
    set_SaturationEn_b(true);
    set_CounterLimit_u32(100U);
    
    result = MyLib_UpdateCounter_u8(1U);
    
    TEST_ASSERT_EQUAL_UINT8(2U, result);
    TEST_ASSERT_EQUAL_UINT32(100U, g_counter_u32);
}
void test_max_add_from_zero_sat_off_returns_0(void)
{
    uint8_t result;
    
    g_systemReady_b = true;
    g_counter_u32 = 0U;
    set_SaturationEn_b(false);
    
    result = MyLib_UpdateCounter_u8(UINT32_MAX);
    
    TEST_ASSERT_EQUAL_UINT8(0U, result);
    TEST_ASSERT_EQUAL_UINT32(UINT32_MAX, g_counter_u32);
}
void test_max_add_from_one_sat_off_wraps_to_zero(void)
{
    uint8_t result;
    
    g_systemReady_b = true;
    g_counter_u32 = 1U;
    set_SaturationEn_b(false);
    
    result = MyLib_UpdateCounter_u8(UINT32_MAX);
    
    TEST_ASSERT_EQUAL_UINT8(0U, result);
    TEST_ASSERT_EQUAL_UINT32(0U, g_counter_u32);
}
void test_cycle_counter_increments_on_not_ready(void)
{
    uint8_t i;
    bool initial_sat;
    bool final_sat;
    
    g_systemReady_b = false;
    g_counter_u32 = 0U;
    set_SaturationEn_b(false);
    
    initial_sat = get_SaturationEn_b();
    
    for (i = 0U; i < 16U; i++)
    {
        MyLib_UpdateCounter_u8(1U);
    }
    
    final_sat = get_SaturationEn_b();
    
    TEST_ASSERT_NOT_EQUAL(initial_sat, final_sat);
}
