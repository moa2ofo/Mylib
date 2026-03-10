#include "MyLib_ProcessRecord.h"
#include "mock_MyLib.h"
#include "unity.h"

void setUp(void) {
  g_counter_u32 = 0U;
}
void tearDown(void) {
}
void test_NULL_pointer_no_side_effects(void) {
  uint32_t initial_counter = g_counter_u32;

  MyLib_ProcessRecord(NULL, 5U);

  TEST_ASSERT_EQUAL_UINT32(initial_counter, g_counter_u32);
}
void test_multiplier_zero_no_accumulation(void) {
  MyLib_record_t rec = {.id_u16 = 1U, .value_u32 = 100U};
  uint32_t initial_counter = g_counter_u32;

  MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(0U, (const uint16_t *)&(uint8_t){0U}, 0U);

  MyLib_ProcessRecord(&rec, 0U);

  TEST_ASSERT_EQUAL_UINT32(initial_counter, g_counter_u32);
}
void test_multiplier_one_single_assignment(void) {
  MyLib_record_t rec = {.id_u16 = 2U, .value_u32 = 50U};
  uint32_t initial_counter = g_counter_u32;
  uint8_t mult = 1U;

  MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(50U, (const uint16_t *)&mult, 0U);

  MyLib_ProcessRecord(&rec, mult);

  TEST_ASSERT_EQUAL_UINT32(initial_counter + 50U, g_counter_u32);
}
void test_multiplier_two_bounded_loop(void) {
  MyLib_record_t rec = {.id_u16 = 3U, .value_u32 = 75U};
  uint32_t initial_counter = g_counter_u32;
  uint8_t mult = 2U;
  uint32_t expected_acc = 150U;

  MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(expected_acc, (const uint16_t *)&mult, 0U);

  MyLib_ProcessRecord(&rec, mult);

  TEST_ASSERT_EQUAL_UINT32(initial_counter + expected_acc, g_counter_u32);
}
void test_multiplier_255_upper_boundary(void) {
  MyLib_record_t rec = {.id_u16 = 4U, .value_u32 = 0x01000000U};
  uint32_t initial_counter = g_counter_u32;
  uint8_t mult = 255U;
  uint32_t expected_acc = 0xFF000000U;

  MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(expected_acc, (const uint16_t *)&mult, 0U);

  MyLib_ProcessRecord(&rec, mult);

  TEST_ASSERT_EQUAL_UINT32(initial_counter + expected_acc, g_counter_u32);
}
void test_multiplier_128_mid_range(void) {
  MyLib_record_t rec = {.id_u16 = 5U, .value_u32 = 0x00010000U};
  uint32_t initial_counter = g_counter_u32;
  uint8_t mult = 128U;
  uint32_t expected_acc = 0x00800000U;

  MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(expected_acc, (const uint16_t *)&mult, 0U);

  MyLib_ProcessRecord(&rec, mult);

  TEST_ASSERT_EQUAL_UINT32(initial_counter + expected_acc, g_counter_u32);
}
void test_value_zero_multiplier_ten(void) {
  MyLib_record_t rec = {.id_u16 = 6U, .value_u32 = 0U};
  uint32_t initial_counter = g_counter_u32;
  uint8_t mult = 10U;

  MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(0U, (const uint16_t *)&mult, 0U);

  MyLib_ProcessRecord(&rec, mult);

  TEST_ASSERT_EQUAL_UINT32(initial_counter, g_counter_u32);
}
void test_value_max_multiplier_one(void) {
  MyLib_record_t rec = {.id_u16 = 7U, .value_u32 = 0xFFFFFFFFU};
  uint32_t initial_counter = g_counter_u32;
  uint8_t mult = 1U;

  MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(0xFFFFFFFFU, (const uint16_t *)&mult, 0U);

  MyLib_ProcessRecord(&rec, mult);

  TEST_ASSERT_EQUAL_UINT32(initial_counter + 0xFFFFFFFFU, g_counter_u32);
}
void test_value_max_multiplier_two_wraparound(void) {
  MyLib_record_t rec = {.id_u16 = 8U, .value_u32 = 0xFFFFFFFFU};
  uint32_t initial_counter = g_counter_u32;
  uint8_t mult = 2U;
  uint32_t expected_acc = 0xFFFFFFFEU;

  MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(expected_acc, (const uint16_t *)&mult, 0U);

  MyLib_ProcessRecord(&rec, mult);

  TEST_ASSERT_EQUAL_UINT32(initial_counter + expected_acc, g_counter_u32);
}
void test_counter_near_max_wraparound(void) {
  MyLib_record_t rec = {.id_u16 = 9U, .value_u32 = 0x20U};
  g_counter_u32 = 0xFFFFFFF0U;
  uint8_t mult = 1U;

  MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(0x20U, (const uint16_t *)&mult, 0U);

  MyLib_ProcessRecord(&rec, mult);

  TEST_ASSERT_EQUAL_UINT32(0x10U, g_counter_u32);
}
void test_value_one_multiplier_one_minimal(void) {
  MyLib_record_t rec = {.id_u16 = 10U, .value_u32 = 1U};
  uint32_t initial_counter = g_counter_u32;
  uint8_t mult = 1U;

  MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(1U, (const uint16_t *)&mult, 0U);

  MyLib_ProcessRecord(&rec, mult);

  TEST_ASSERT_EQUAL_UINT32(initial_counter + 1U, g_counter_u32);
}
void test_value_mid_range_multiplier_two_wraparound(void) {
  MyLib_record_t rec = {.id_u16 = 11U, .value_u32 = 0x80000000U};
  uint32_t initial_counter = g_counter_u32;
  uint8_t mult = 2U;
  uint32_t expected_acc = 0x00000000U;

  MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(expected_acc, (const uint16_t *)&mult, 0U);

  MyLib_ProcessRecord(&rec, mult);

  TEST_ASSERT_EQUAL_UINT32(initial_counter, g_counter_u32);
}
