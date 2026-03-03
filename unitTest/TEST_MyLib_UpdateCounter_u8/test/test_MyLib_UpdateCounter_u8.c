#include "MyLib.h"
#include "MyLib_UpdateCounter_u8.h"
#include "mock_MyLib.h"
#include "unity.h"
#include <string.h>




/**
 * @brief Test: System not ready – verify return code 1 and no counter update
 */
void test_system_not_ready_returns_error_code_1_and_no_counter_update(void)
{
    uint32_t initial_counter = 42U;
    g_counter_u32 = initial_counter;
    g_systemReady_b = false;

    uint8_t result = MyLib_UpdateCounter_u8(10U);

    TEST_ASSERT_EQUAL_UINT8(1U, result);
    TEST_ASSERT_EQUAL_UINT32(initial_counter, g_counter_u32);
}

/**
 * @brief Test: System ready, saturation disabled, zero increment – verify return code 0 and counter unchanged
 */
void test_system_ready_saturation_disabled_zero_increment_returns_0_counter_unchanged(void)
{
    uint32_t initial_counter = 50U;
    g_counter_u32 = initial_counter;
    g_systemReady_b = true;
    set_SaturationEn_b(false);

    uint8_t result = MyLib_UpdateCounter_u8(0U);

    TEST_ASSERT_EQUAL_UINT8(0U, result);
    TEST_ASSERT_EQUAL_UINT32(initial_counter, g_counter_u32);
}

/**
 * @brief Test: System ready, saturation disabled, small increment within limit – verify return code 0 and counter updated correctly
 */
void test_system_ready_saturation_disabled_small_increment_returns_0_counter_updated(void)
{
    g_counter_u32 = 10U;
    g_systemReady_b = true;
    set_SaturationEn_b(false);
    set_CounterLimit_u32(100U);

    uint8_t result = MyLib_UpdateCounter_u8(5U);

    TEST_ASSERT_EQUAL_UINT8(0U, result);
    TEST_ASSERT_EQUAL_UINT32(15U, g_counter_u32);
}

/**
 * @brief Test: System ready, saturation disabled, increment causing uint32_t wrap-around – verify return code 0 and counter wraps correctly
 */
void test_system_ready_saturation_disabled_increment_causing_wraparound_returns_0_counter_wraps(void)
{
    g_counter_u32 = UINT32_MAX - 5U;
    g_systemReady_b = true;
    set_SaturationEn_b(false);

    uint8_t result = MyLib_UpdateCounter_u8(10U);

    TEST_ASSERT_EQUAL_UINT8(0U, result);
    TEST_ASSERT_EQUAL_UINT32(4U, g_counter_u32);
}

/**
 * @brief Test: System ready, saturation enabled, increment below limit – verify return code 0 and counter updated correctly
 */
void test_system_ready_saturation_enabled_increment_below_limit_returns_0_counter_updated(void)
{
    g_counter_u32 = 20U;
    g_systemReady_b = true;
    set_SaturationEn_b(true);
    set_CounterLimit_u32(100U);

    uint8_t result = MyLib_UpdateCounter_u8(30U);

    TEST_ASSERT_EQUAL_UINT8(0U, result);
    TEST_ASSERT_EQUAL_UINT32(50U, g_counter_u32);
}

/**
 * @brief Test: System ready, saturation enabled, increment exactly at limit – verify return code 0 and counter equals limit
 */
void test_system_ready_saturation_enabled_increment_exactly_at_limit_returns_0_counter_equals_limit(void)
{
    g_counter_u32 = 50U;
    g_systemReady_b = true;
    set_SaturationEn_b(true);
    set_CounterLimit_u32(100U);

    uint8_t result = MyLib_UpdateCounter_u8(50U);

    TEST_ASSERT_EQUAL_UINT8(0U, result);
    TEST_ASSERT_EQUAL_UINT32(100U, g_counter_u32);
}

/**
 * @brief Test: System ready, saturation enabled, increment exceeding limit by one – verify return code 2 and counter clamped to limit
 */
void test_system_ready_saturation_enabled_increment_exceeding_limit_by_one_returns_2_counter_clamped(void)
{
    g_counter_u32 = 50U;
    g_systemReady_b = true;
    set_SaturationEn_b(true);
    set_CounterLimit_u32(100U);

    uint8_t result = MyLib_UpdateCounter_u8(51U);

    TEST_ASSERT_EQUAL_UINT8(2U, result);
    TEST_ASSERT_EQUAL_UINT32(100U, g_counter_u32);
}

/**
 * @brief Test: System ready, saturation enabled, large increment far exceeding limit – verify return code 2 and counter clamped to limit
 */
void test_system_ready_saturation_enabled_large_increment_far_exceeding_limit_returns_2_counter_clamped(void)
{
    g_counter_u32 = 10U;
    g_systemReady_b = true;
    set_SaturationEn_b(true);
    set_CounterLimit_u32(100U);

    uint8_t result = MyLib_UpdateCounter_u8(1000U);

    TEST_ASSERT_EQUAL_UINT8(2U, result);
    TEST_ASSERT_EQUAL_UINT32(100U, g_counter_u32);
}

/**
 * @brief Test: System ready, saturation enabled, increment causing wrap-around before saturation check – verify return code 2 and counter clamped to limit
 */
void test_system_ready_saturation_enabled_increment_causing_wraparound_before_saturation_returns_2_counter_clamped(void)
{
    g_counter_u32 = UINT32_MAX - 10U;
    g_systemReady_b = true;
    set_SaturationEn_b(true);
    set_CounterLimit_u32(100U);

    uint8_t result = MyLib_UpdateCounter_u8(20U);

    TEST_ASSERT_EQUAL_UINT8(2U, result);
    TEST_ASSERT_EQUAL_UINT32(100U, g_counter_u32);
}

/**
 * @brief Test: Cycle counter toggle – verify SaturationEn_b toggles after exactly 16 calls
 */
void test_cycle_counter_toggle_saturation_toggles_after_16_calls(void)
{
    g_systemReady_b = true;
    g_counter_u32 = 0U;
    set_SaturationEn_b(false);
    set_CounterLimit_u32(1000U);

    bool initial_saturation = get_SaturationEn_b();

    for (uint8_t i = 0U; i < 15U; i++)
    {
        MyLib_UpdateCounter_u8(1U);
    }

    TEST_ASSERT_EQUAL(initial_saturation, get_SaturationEn_b());

    MyLib_UpdateCounter_u8(1U);

    TEST_ASSERT_EQUAL(!initial_saturation, get_SaturationEn_b());
}

/**
 * @brief Test: Cycle counter toggle – verify SaturationEn_b does not toggle on call 15 (one before threshold)
 */
void test_cycle_counter_toggle_saturation_does_not_toggle_on_call_15(void)
{
    g_systemReady_b = true;
    g_counter_u32 = 0U;
    set_SaturationEn_b(true);
    set_CounterLimit_u32(1000U);

    bool initial_saturation = get_SaturationEn_b();

    for (uint8_t i = 0U; i < 15U; i++)
    {
        MyLib_UpdateCounter_u8(1U);
    }

    TEST_ASSERT_EQUAL(initial_saturation, get_SaturationEn_b());
}

/**
 * @brief Test: Cycle counter toggle – verify SaturationEn_b does not toggle on call 17 (one after threshold)
 */
void test_cycle_counter_toggle_saturation_does_not_toggle_on_call_17(void)
{
    g_systemReady_b = true;
    g_counter_u32 = 0U;
    set_SaturationEn_b(false);
    set_CounterLimit_u32(1000U);

    for (uint8_t i = 0U; i < 16U; i++)
    {
        MyLib_UpdateCounter_u8(1U);
    }

    bool saturation_after_16 = get_SaturationEn_b();

    MyLib_UpdateCounter_u8(1U);

    TEST_ASSERT_EQUAL(saturation_after_16, get_SaturationEn_b());
}

/**
 * @brief Test: Cycle counter toggle persistence – verify SaturationEn_b toggles again after next 16 calls (call 32)
 */
void test_cycle_counter_toggle_persistence_saturation_toggles_again_at_call_32(void)
{
    g_systemReady_b = true;
    g_counter_u32 = 0U;
    set_SaturationEn_b(false);
    set_CounterLimit_u32(1000U);

    bool initial_saturation = get_SaturationEn_b();

    for (uint8_t i = 0U; i < 16U; i++)
    {
        MyLib_UpdateCounter_u8(1U);
    }

    bool saturation_after_16 = get_SaturationEn_b();
    TEST_ASSERT_EQUAL(!initial_saturation, saturation_after_16);

    for (uint8_t i = 0U; i < 16U; i++)
    {
        MyLib_UpdateCounter_u8(1U);
    }

    TEST_ASSERT_EQUAL(initial_saturation, get_SaturationEn_b());
}

/**
 * @brief Test: System not ready after multiple ready calls – verify return code 1 and counter unchanged regardless of prior state
 */
void test_system_not_ready_after_multiple_ready_calls_returns_1_counter_unchanged(void)
{
    g_systemReady_b = true;
    g_counter_u32 = 10U;
    set_SaturationEn_b(false);
    set_CounterLimit_u32(100U);

    MyLib_UpdateCounter_u8(5U);
    MyLib_UpdateCounter_u8(5U);

    uint32_t counter_before_not_ready = g_counter_u32;

    g_systemReady_b = false;

    uint8_t result = MyLib_UpdateCounter_u8(10U);

    TEST_ASSERT_EQUAL_UINT8(1U, result);
    TEST_ASSERT_EQUAL_UINT32(counter_before_not_ready, g_counter_u32);
}

/**
 * @brief Test: Saturation boundary – counter at limit minus one, increment by one with saturation enabled – verify return code 0 and counter equals limit
 */
void test_saturation_boundary_counter_at_limit_minus_one_increment_by_one_returns_0_counter_equals_limit(void)
{
    g_systemReady_b = true;
    set_CounterLimit_u32(100U);
    g_counter_u32 = 99U;
    set_SaturationEn_b(true);

    uint8_t result = MyLib_UpdateCounter_u8(1U);

    TEST_ASSERT_EQUAL_UINT8(0U, result);
    TEST_ASSERT_EQUAL_UINT32(100U, g_counter_u32);
}

/**
 * @brief Test: Saturation boundary – counter at limit, increment by one with saturation enabled – verify return code 2 and counter remains at limit
 */
void test_saturation_boundary_counter_at_limit_increment_by_one_returns_2_counter_remains_at_limit(void)
{
    g_systemReady_b = true;
    set_CounterLimit_u32(100U);
    g_counter_u32 = 100U;
    set_SaturationEn_b(true);

    uint8_t result = MyLib_UpdateCounter_u8(1U);

    TEST_ASSERT_EQUAL_UINT8(2U, result);
    TEST_ASSERT_EQUAL_UINT32(100U, g_counter_u32);
}

/**
 * @brief Test: Saturation boundary – counter at zero, increment to exactly limit with saturation enabled – verify return code 0 and counter equals limit
 */
void test_saturation_boundary_counter_at_zero_increment_to_exactly_limit_returns_0_counter_equals_limit(void)
{
    g_systemReady_b = true;
    set_CounterLimit_u32(100U);
    g_counter_u32 = 0U;
    set_SaturationEn_b(true);

    uint8_t result = MyLib_UpdateCounter_u8(100U);

    TEST_ASSERT_EQUAL_UINT8(0U, result);
    TEST_ASSERT_EQUAL_UINT32(100U, g_counter_u32);
}

/**
 * @brief Test: Saturation boundary – counter at zero, increment to limit plus one with saturation enabled – verify return code 2 and counter clamped to limit
 */
void test_saturation_boundary_counter_at_zero_increment_to_limit_plus_one_returns_2_counter_clamped(void)
{
    g_systemReady_b = true;
    set_CounterLimit_u32(100U);
    g_counter_u32 = 0U;
    set_SaturationEn_b(true);

    uint8_t result = MyLib_UpdateCounter_u8(101U);

    TEST_ASSERT_EQUAL_UINT8(2U, result);
    TEST_ASSERT_EQUAL_UINT32(100U, g_counter_u32);
}

/**
 * @brief Test: Maximum uint32_t increment – counter at zero, add UINT32_MAX with saturation disabled – verify return code 0 and counter wraps to UINT32_MAX
 */
void test_maximum_uint32_increment_counter_at_zero_add_max_saturation_disabled_returns_0_counter_wraps_to_max(void)
{
    g_systemReady_b = true;
    g_counter_u32 = 0U;
    set_SaturationEn_b(false);

    uint8_t result = MyLib_UpdateCounter_u8(UINT32_MAX);

    TEST_ASSERT_EQUAL_UINT8(0U, result);
    TEST_ASSERT_EQUAL_UINT32(UINT32_MAX, g_counter_u32);
}

/**
 * @brief Test: Maximum uint32_t increment – counter at one, add UINT32_MAX with saturation disabled – verify return code 0 and counter wraps to zero
 */
void test_maximum_uint32_increment_counter_at_one_add_max_saturation_disabled_returns_0_counter_wraps_to_zero(void)
{
    g_systemReady_b = true;
    g_counter_u32 = 1U;
    set_SaturationEn_b(false);

    uint8_t result = MyLib_UpdateCounter_u8(UINT32_MAX);

    TEST_ASSERT_EQUAL_UINT8(0U, result);
    TEST_ASSERT_EQUAL_UINT32(0U, g_counter_u32);
}

/**
 * @brief Test: Saturation disabled, counter at maximum representable value, increment by one – verify return code 0 and counter wraps to zero
 */
void test_saturation_disabled_counter_at_max_increment_by_one_returns_0_counter_wraps_to_zero(void)
{
    g_systemReady_b = true;
    g_counter_u32 = UINT32_MAX;
    set_SaturationEn_b(false);

    uint8_t result = MyLib_UpdateCounter_u8(1U);

    TEST_ASSERT_EQUAL_UINT8(0U, result);
    TEST_ASSERT_EQUAL_UINT32(0U, g_counter_u32);
}

/**
 * @brief Test: Limit set to UINT32_MAX, saturation enabled, any increment – verify return code 0 because new value cannot exceed limit
 */
void test_limit_set_to_max_saturation_enabled_any_increment_returns_0_new_value_cannot_exceed_limit(void)
{
    g_systemReady_b = true;
    set_CounterLimit_u32(UINT32_MAX);
    g_counter_u32 = 100U;
    set_SaturationEn_b(true);

    uint8_t result = MyLib_UpdateCounter_u8(1000U);

    TEST_ASSERT_EQUAL_UINT8(0U, result);
    TEST_ASSERT_EQUAL_UINT32(1100U, g_counter_u32);
}

/**
 * @brief Test: Limit set to zero, saturation enabled, any non-zero increment – verify return code 2 and counter clamped to zero
 */
void test_limit_set_to_zero_saturation_enabled_any_nonzero_increment_returns_2_counter_clamped_to_zero(void)
{
    g_systemReady_b = true;
    set_CounterLimit_u32(0U);
    g_counter_u32 = 0U;
    set_SaturationEn_b(true);

    uint8_t result = MyLib_UpdateCounter_u8(1U);

    TEST_ASSERT_EQUAL_UINT8(2U, result);
    TEST_ASSERT_EQUAL_UINT32(0U, g_counter_u32);
}

/**
 * @brief Test: Cycle counter increments correctly across system not ready calls – verify l_CycleCnt_u32 increments even when returning error code 1
 */
void test_cycle_counter_increments_across_system_not_ready_calls(void)
{
    g_systemReady_b = true;
    g_counter_u32 = 0U;
    set_SaturationEn_b(false);
    set_CounterLimit_u32(1000U);

    for (uint8_t i = 0U; i < 8U; i++)
    {
        MyLib_UpdateCounter_u8(1U);
    }

    g_systemReady_b = false;

    for (uint8_t i = 0U; i < 8U; i++)
    {
        uint8_t result = MyLib_UpdateCounter_u8(1U);
        TEST_ASSERT_EQUAL_UINT8(1U, result);
    }

    g_systemReady_b = true;
    bool saturation_before = get_SaturationEn_b();

    MyLib_UpdateCounter_u8(1U);

    TEST_ASSERT_EQUAL(!saturation_before, get_SaturationEn_b());
}

void setUp(void)
{
    g_counter_u32 = 0U;
    g_systemReady_b = false;
    set_CounterLimit_u32(0U);
    set_SaturationEn_b(false);
}

void tearDown(void)
{
}