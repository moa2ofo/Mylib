#include "mock_MyLib.h"
#include "unity.h"
#include <ProcessRecord.h>

void setUp(void) {
}
void tearDown(void) {
}
void test_NULL_pointer_no_side_effects(void) {
  uint32_t initial_counter = g_counter_u32;

  ProcessRecord(NULL, 5U);

  TEST_ASSERT_EQUAL_UINT32(initial_counter, g_counter_u32);
}
void test_multiplier_zero_no_accumulation(void) {
  MyLib_record_t rec = {.id_u16 = 1U, .value_u32 = 1000U};
  uint32_t initial_counter = g_counter_u32;

  MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(0U, (const uint16_t *)&(uint8_t){0U}, 0U);
  MyLib_ComputeAdjustedValue_u32_IgnoreArg_delta_pc_u16();

  ProcessRecord(&rec, 0U);

  TEST_ASSERT_EQUAL_UINT32(initial_counter, g_counter_u32);
}
void test_multiplier_one_value_zero(void) {
  MyLib_record_t rec = {.id_u16 = 2U, .value_u32 = 0U};
  uint32_t initial_counter = g_counter_u32;

  MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(0U, (const uint16_t *)&(uint8_t){1U}, 0U);
  MyLib_ComputeAdjustedValue_u32_IgnoreArg_delta_pc_u16();

  ProcessRecord(&rec, 1U);

  TEST_ASSERT_EQUAL_UINT32(initial_counter, g_counter_u32);
}
void test_multiplier_one_value_midrange(void) {
  MyLib_record_t rec = {.id_u16 = 3U, .value_u32 = 50000U};
  uint32_t initial_counter = g_counter_u32;

  MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(50000U, (const uint16_t *)&(uint8_t){1U}, 0U);
  MyLib_ComputeAdjustedValue_u32_IgnoreArg_delta_pc_u16();

  ProcessRecord(&rec, 1U);

  TEST_ASSERT_EQUAL_UINT32(initial_counter + 50000U, g_counter_u32);
}
void test_multiplier_one_value_max(void) {
  MyLib_record_t rec = {.id_u16 = 4U, .value_u32 = UINT32_MAX};
  uint32_t initial_counter = g_counter_u32;

  MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(UINT32_MAX, (const uint16_t *)&(uint8_t){1U}, 0U);
  MyLib_ComputeAdjustedValue_u32_IgnoreArg_delta_pc_u16();

  ProcessRecord(&rec, 1U);

  TEST_ASSERT_EQUAL_UINT32(initial_counter + UINT32_MAX, g_counter_u32);
}
void test_multiplier_two_value_hundred(void) {
  MyLib_record_t rec = {.id_u16 = 5U, .value_u32 = 100U};
  uint32_t initial_counter = g_counter_u32;

  MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(200U, (const uint16_t *)&(uint8_t){2U}, 0U);
  MyLib_ComputeAdjustedValue_u32_IgnoreArg_delta_pc_u16();

  ProcessRecord(&rec, 2U);

  TEST_ASSERT_EQUAL_UINT32(initial_counter + 200U, g_counter_u32);
}
void test_multiplier_two_value_zero(void) {
  MyLib_record_t rec = {.id_u16 = 6U, .value_u32 = 0U};
  uint32_t initial_counter = g_counter_u32;

  MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(0U, (const uint16_t *)&(uint8_t){2U}, 0U);
  MyLib_ComputeAdjustedValue_u32_IgnoreArg_delta_pc_u16();

  ProcessRecord(&rec, 2U);

  TEST_ASSERT_EQUAL_UINT32(initial_counter, g_counter_u32);
}
void test_multiplier_midrange_128(void) {
  MyLib_record_t rec = {.id_u16 = 7U, .value_u32 = 1000U};
  uint32_t initial_counter = g_counter_u32;

  MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(128000U, (const uint16_t *)&(uint8_t){128U}, 0U);
  MyLib_ComputeAdjustedValue_u32_IgnoreArg_delta_pc_u16();

  ProcessRecord(&rec, 128U);

  TEST_ASSERT_EQUAL_UINT32(initial_counter + 128000U, g_counter_u32);
}
void test_multiplier_254_value_ten(void) {
  MyLib_record_t rec = {.id_u16 = 8U, .value_u32 = 10U};
  uint32_t initial_counter = g_counter_u32;

  MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(2540U, (const uint16_t *)&(uint8_t){254U}, 0U);
  MyLib_ComputeAdjustedValue_u32_IgnoreArg_delta_pc_u16();

  ProcessRecord(&rec, 254U);

  TEST_ASSERT_EQUAL_UINT32(initial_counter + 2540U, g_counter_u32);
}
void test_multiplier_max_255_value_ten(void) {
  MyLib_record_t rec = {.id_u16 = 9U, .value_u32 = 10U};
  uint32_t initial_counter = g_counter_u32;

  MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(2550U, (const uint16_t *)&(uint8_t){255U}, 0U);
  MyLib_ComputeAdjustedValue_u32_IgnoreArg_delta_pc_u16();

  ProcessRecord(&rec, 255U);

  TEST_ASSERT_EQUAL_UINT32(initial_counter + 2550U, g_counter_u32);
}
void test_multiplier_255_value_max_wraparound(void) {
  MyLib_record_t rec = {.id_u16 = 10U, .value_u32 = UINT32_MAX};
  uint32_t initial_counter = g_counter_u32;
  uint32_t expected_acc = 0U;

  for(uint8_t i = 0U; i < 255U; i++) {
    expected_acc += UINT32_MAX;
  }

  MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(expected_acc, (const uint16_t *)&(uint8_t){255U}, 0U);
  MyLib_ComputeAdjustedValue_u32_IgnoreArg_delta_pc_u16();

  ProcessRecord(&rec, 255U);

  TEST_ASSERT_EQUAL_UINT32(initial_counter + expected_acc, g_counter_u32);
}
void test_multiplier_10_intermediate_wraparound(void) {
  MyLib_record_t rec = {.id_u16 = 11U, .value_u32 = 0xFFFFFFFFU / 5U};
  uint32_t initial_counter = g_counter_u32;
  uint32_t expected_acc = 0U;

  for(uint8_t i = 0U; i < 10U; i++) {
    expected_acc += rec.value_u32;
  }

  MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(expected_acc, (const uint16_t *)&(uint8_t){10U}, 0U);
  MyLib_ComputeAdjustedValue_u32_IgnoreArg_delta_pc_u16();

  ProcessRecord(&rec, 10U);

  TEST_ASSERT_EQUAL_UINT32(initial_counter + expected_acc, g_counter_u32);
}
void test_counter_wraparound_at_max(void) {
  MyLib_record_t rec = {.id_u16 = 12U, .value_u32 = 1U};
  g_counter_u32 = UINT32_MAX;

  MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(1U, (const uint16_t *)&(uint8_t){1U}, 0U);
  MyLib_ComputeAdjustedValue_u32_IgnoreArg_delta_pc_u16();

  ProcessRecord(&rec, 1U);

  TEST_ASSERT_EQUAL_UINT32(0U, g_counter_u32);
}
