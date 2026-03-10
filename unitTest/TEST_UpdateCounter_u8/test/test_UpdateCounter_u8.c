#include "mock_MyLib.h"
#include "unity.h"
#include <UpdateCounter_u8.h>

void setUp(void) {
}
void tearDown(void) {
}
void test_system_not_ready_returns_1_no_counter_change(void) {
  g_systemReady_b = false;
  g_counter_u32 = 42U;

  uint8_t result = UpdateCounter_u8(10U);

  TEST_ASSERT_EQUAL_UINT8(1, result);
  TEST_ASSERT_EQUAL_UINT32(42U, g_counter_u32);
}
void test_system_ready_add_zero_sat_disabled_no_change(void) {
  g_systemReady_b = true;
  g_counter_u32 = 100U;
  set_SaturationEn_b(false);

  uint8_t result = UpdateCounter_u8(0U);

  TEST_ASSERT_EQUAL_UINT8(0, result);
  TEST_ASSERT_EQUAL_UINT32(100U, g_counter_u32);
}
void test_system_ready_add_one_sat_disabled_increments(void) {
  g_systemReady_b = true;
  g_counter_u32 = 50U;
  set_SaturationEn_b(false);

  uint8_t result = UpdateCounter_u8(1U);

  TEST_ASSERT_EQUAL_UINT8(0, result);
  TEST_ASSERT_EQUAL_UINT32(51U, g_counter_u32);
}
void test_system_ready_add_midrange_sat_disabled_updates(void) {
  g_systemReady_b = true;
  g_counter_u32 = 100U;
  set_SaturationEn_b(false);

  uint8_t result = UpdateCounter_u8(0x7FFFFFFFU);

  TEST_ASSERT_EQUAL_UINT8(0, result);
  TEST_ASSERT_EQUAL_UINT32(100U + 0x7FFFFFFFU, g_counter_u32);
}
void test_system_ready_add_max_sat_disabled_wraps(void) {
  g_systemReady_b = true;
  g_counter_u32 = 10U;
  set_SaturationEn_b(false);

  uint8_t result = UpdateCounter_u8(0xFFFFFFFFU);

  TEST_ASSERT_EQUAL_UINT8(0, result);
  TEST_ASSERT_EQUAL_UINT32(9U, g_counter_u32);
}
void test_system_ready_sat_enabled_new_equals_limit_no_clamp(void) {
  g_systemReady_b = true;
  g_counter_u32 = 50U;
  set_CounterLimit_u32(100U);
  set_SaturationEn_b(true);

  uint8_t result = UpdateCounter_u8(50U);

  TEST_ASSERT_EQUAL_UINT8(0, result);
  TEST_ASSERT_EQUAL_UINT32(100U, g_counter_u32);
}
void test_system_ready_sat_enabled_new_one_over_limit_clamps(void) {
  g_systemReady_b = true;
  g_counter_u32 = 50U;
  set_CounterLimit_u32(100U);
  set_SaturationEn_b(true);

  uint8_t result = UpdateCounter_u8(51U);

  TEST_ASSERT_EQUAL_UINT8(2, result);
  TEST_ASSERT_EQUAL_UINT32(100U, g_counter_u32);
}
void test_system_ready_sat_enabled_new_far_exceeds_limit_clamps(void) {
  g_systemReady_b = true;
  g_counter_u32 = 50U;
  set_CounterLimit_u32(100U);
  set_SaturationEn_b(true);

  uint8_t result = UpdateCounter_u8(1000U);

  TEST_ASSERT_EQUAL_UINT8(2, result);
  TEST_ASSERT_EQUAL_UINT32(100U, g_counter_u32);
}
void test_system_ready_sat_disabled_new_exceeds_limit_no_clamp(void) {
  g_systemReady_b = true;
  g_counter_u32 = 50U;
  set_CounterLimit_u32(100U);
  set_SaturationEn_b(false);

  uint8_t result = UpdateCounter_u8(100U);

  TEST_ASSERT_EQUAL_UINT8(0, result);
  TEST_ASSERT_EQUAL_UINT32(150U, g_counter_u32);
}
void test_cycle_15_to_16_toggles_saturation(void) {
  g_systemReady_b = true;
  g_counter_u32 = 0U;
  set_SaturationEn_b(false);

  for(uint32_t i = 0; i < 15; i++) {
    UpdateCounter_u8(0U);
  }

  TEST_ASSERT_FALSE(get_SaturationEn_b());

  UpdateCounter_u8(0U);

  TEST_ASSERT_TRUE(get_SaturationEn_b());
}
void test_cycle_31_to_32_toggles_saturation_again(void) {
  g_systemReady_b = true;
  g_counter_u32 = 0U;
  set_SaturationEn_b(false);

  for(uint32_t i = 0; i < 31; i++) {
    UpdateCounter_u8(0U);
  }

  TEST_ASSERT_TRUE(get_SaturationEn_b());

  UpdateCounter_u8(0U);

  TEST_ASSERT_FALSE(get_SaturationEn_b());
}
void test_cycle_17_no_toggle(void) {
  g_systemReady_b = true;
  g_counter_u32 = 0U;
  set_SaturationEn_b(false);

  for(uint32_t i = 0; i < 16; i++) {
    UpdateCounter_u8(0U);
  }

  TEST_ASSERT_TRUE(get_SaturationEn_b());

  UpdateCounter_u8(0U);

  TEST_ASSERT_TRUE(get_SaturationEn_b());
}
void test_counter_zero_add_one_sat_disabled_increments(void) {
  g_systemReady_b = true;
  g_counter_u32 = 0U;
  set_SaturationEn_b(false);

  uint8_t result = UpdateCounter_u8(1U);

  TEST_ASSERT_EQUAL_UINT8(0, result);
  TEST_ASSERT_EQUAL_UINT32(1U, g_counter_u32);
}
void test_counter_near_max_add_one_sat_disabled_reaches_max(void) {
  g_systemReady_b = true;
  g_counter_u32 = 0xFFFFFFFEU;
  set_SaturationEn_b(false);

  uint8_t result = UpdateCounter_u8(1U);

  TEST_ASSERT_EQUAL_UINT8(0, result);
  TEST_ASSERT_EQUAL_UINT32(0xFFFFFFFFU, g_counter_u32);
}
void test_counter_max_add_one_sat_disabled_wraps_to_zero(void) {
  g_systemReady_b = true;
  g_counter_u32 = 0xFFFFFFFFU;
  set_SaturationEn_b(false);

  uint8_t result = UpdateCounter_u8(1U);

  TEST_ASSERT_EQUAL_UINT8(0, result);
  TEST_ASSERT_EQUAL_UINT32(0U, g_counter_u32);
}
void test_sat_enabled_wrap_result_below_limit_no_clamp(void) {
  g_systemReady_b = true;
  g_counter_u32 = 0xFFFFFFFFU;
  set_CounterLimit_u32(100U);
  set_SaturationEn_b(true);

  uint8_t result = UpdateCounter_u8(50U);

  TEST_ASSERT_EQUAL_UINT8(0, result);
  TEST_ASSERT_EQUAL_UINT32(49U, g_counter_u32);
}
void test_sat_enabled_wrap_result_exceeds_limit_clamps(void) {
  g_systemReady_b = true;
  g_counter_u32 = 0xFFFFFFFFU;
  set_CounterLimit_u32(100U);
  set_SaturationEn_b(true);

  uint8_t result = UpdateCounter_u8(200U);

  TEST_ASSERT_EQUAL_UINT8(2, result);
  TEST_ASSERT_EQUAL_UINT32(100U, g_counter_u32);
}
void test_limit_zero_sat_enabled_any_add_clamps_to_zero(void) {
  g_systemReady_b = true;
  g_counter_u32 = 0U;
  set_CounterLimit_u32(0U);
  set_SaturationEn_b(true);

  uint8_t result = UpdateCounter_u8(1U);

  TEST_ASSERT_EQUAL_UINT8(2, result);
  TEST_ASSERT_EQUAL_UINT32(0U, g_counter_u32);
}
void test_limit_max_sat_enabled_wrap_no_clamp_possible(void) {
  g_systemReady_b = true;
  g_counter_u32 = 0xFFFFFFFFU;
  set_CounterLimit_u32(0xFFFFFFFFU);
  set_SaturationEn_b(true);

  uint8_t result = UpdateCounter_u8(10U);

  TEST_ASSERT_EQUAL_UINT8(0, result);
  TEST_ASSERT_EQUAL_UINT32(9U, g_counter_u32);
}
void test_multiple_calls_sat_disabled_accumulates(void) {
  g_systemReady_b = true;
  g_counter_u32 = 0U;
  set_SaturationEn_b(false);

  uint8_t result1 = UpdateCounter_u8(10U);
  TEST_ASSERT_EQUAL_UINT8(0, result1);
  TEST_ASSERT_EQUAL_UINT32(10U, g_counter_u32);

  uint8_t result2 = UpdateCounter_u8(20U);
  TEST_ASSERT_EQUAL_UINT8(0, result2);
  TEST_ASSERT_EQUAL_UINT32(30U, g_counter_u32);

  uint8_t result3 = UpdateCounter_u8(5U);
  TEST_ASSERT_EQUAL_UINT8(0, result3);
  TEST_ASSERT_EQUAL_UINT32(35U, g_counter_u32);
}
void test_multiple_calls_sat_enabled_each_clamps(void) {
  g_systemReady_b = true;
  g_counter_u32 = 90U;
  set_CounterLimit_u32(100U);
  set_SaturationEn_b(true);

  uint8_t result1 = UpdateCounter_u8(20U);
  TEST_ASSERT_EQUAL_UINT8(2, result1);
  TEST_ASSERT_EQUAL_UINT32(100U, g_counter_u32);

  uint8_t result2 = UpdateCounter_u8(50U);
  TEST_ASSERT_EQUAL_UINT8(2, result2);
  TEST_ASSERT_EQUAL_UINT32(100U, g_counter_u32);

  uint8_t result3 = UpdateCounter_u8(1U);
  TEST_ASSERT_EQUAL_UINT8(2, result3);
  TEST_ASSERT_EQUAL_UINT32(100U, g_counter_u32);
}
void test_cross_cycle_16_sat_disabled_to_enabled(void) {
  g_systemReady_b = true;
  g_counter_u32 = 0U;
  set_CounterLimit_u32(50U);
  set_SaturationEn_b(false);

  for(uint32_t i = 0; i < 15; i++) {
    UpdateCounter_u8(1U);
  }

  TEST_ASSERT_FALSE(get_SaturationEn_b());
  TEST_ASSERT_EQUAL_UINT32(15U, g_counter_u32);

  uint8_t result = UpdateCounter_u8(100U);

  TEST_ASSERT_EQUAL_UINT8(0, result);
  TEST_ASSERT_EQUAL_UINT32(115U, g_counter_u32);
  TEST_ASSERT_TRUE(get_SaturationEn_b());

  uint8_t result2 = UpdateCounter_u8(10U);

  TEST_ASSERT_EQUAL_UINT8(2, result2);
  TEST_ASSERT_EQUAL_UINT32(50U, g_counter_u32);
}
void test_cross_cycle_16_sat_enabled_to_disabled(void) {
  g_systemReady_b = true;
  g_counter_u32 = 0U;
  set_CounterLimit_u32(50U);
  set_SaturationEn_b(true);

  for(uint32_t i = 0; i < 15; i++) {
    UpdateCounter_u8(1U);
  }

  TEST_ASSERT_TRUE(get_SaturationEn_b());
  TEST_ASSERT_EQUAL_UINT32(15U, g_counter_u32);

  uint8_t result = UpdateCounter_u8(100U);

  TEST_ASSERT_EQUAL_UINT8(2, result);
  TEST_ASSERT_EQUAL_UINT32(50U, g_counter_u32);
  TEST_ASSERT_FALSE(get_SaturationEn_b());

  uint8_t result2 = UpdateCounter_u8(100U);

  TEST_ASSERT_EQUAL_UINT8(0, result2);
  TEST_ASSERT_EQUAL_UINT32(150U, g_counter_u32);
}
void test_not_ready_then_ready_updates_only_second_call(void) {
  g_systemReady_b = false;
  g_counter_u32 = 10U;
  set_SaturationEn_b(false);

  uint8_t result1 = UpdateCounter_u8(5U);

  TEST_ASSERT_EQUAL_UINT8(1, result1);
  TEST_ASSERT_EQUAL_UINT32(10U, g_counter_u32);

  g_systemReady_b = true;

  uint8_t result2 = UpdateCounter_u8(5U);

  TEST_ASSERT_EQUAL_UINT8(0, result2);
  TEST_ASSERT_EQUAL_UINT32(15U, g_counter_u32);
}
