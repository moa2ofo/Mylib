#include "mock_MyLib.h"
#include "unity.h"
#include <ProcessRecord.h>

void setUp(void) {
  g_counter_u32 = 0U;
}
void tearDown(void) {
}
void test_NULL_ptr_no_side_effects(void) {
  uint32_t initial_counter = g_counter_u32;

  ProcessRecord(NULL, 5U);

  TEST_ASSERT_EQUAL_UINT32(initial_counter, g_counter_u32);
}
void test_mult_0_no_accumulation(void) {
  MyLib_record_t rec = {.id_u16 = 1U, .value_u32 = 100U};
  uint32_t initial_counter = g_counter_u32;
  uint8_t mult = 0U;

  MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(0U, (const uint16_t *)&mult, 0U);

  ProcessRecord(&rec, mult);

  TEST_ASSERT_EQUAL_UINT32(initial_counter, g_counter_u32);
}
void test_mult_1_single_accumulation(void) {
  MyLib_record_t rec = {.id_u16 = 2U, .value_u32 = 50U};
  uint32_t initial_counter = g_counter_u32;
  uint8_t mult = 1U;

  MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(50U, (const uint16_t *)&mult, 0U);

  ProcessRecord(&rec, mult);

  TEST_ASSERT_EQUAL_UINT32(initial_counter + 50U, g_counter_u32);
}
void test_mult_2_bounded_loop_twice(void) {
  MyLib_record_t rec = {.id_u16 = 3U, .value_u32 = 75U};
  uint32_t initial_counter = g_counter_u32;
  uint8_t mult = 2U;
  uint32_t expected_acc = 2U * 75U;

  MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(expected_acc, (const uint16_t *)&mult, 0U);

  ProcessRecord(&rec, mult);

  TEST_ASSERT_EQUAL_UINT32(initial_counter + expected_acc, g_counter_u32);
}
void test_mult_128_mid_range(void) {
  MyLib_record_t rec = {.id_u16 = 4U, .value_u32 = 1000U};
  uint32_t initial_counter = g_counter_u32;
  uint8_t mult = 128U;
  uint32_t expected_acc = 128U * 1000U;

  MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(expected_acc, (const uint16_t *)&mult, 0U);

  ProcessRecord(&rec, mult);

  TEST_ASSERT_EQUAL_UINT32(initial_counter + expected_acc, g_counter_u32);
}
void test_mult_254_near_upper_boundary(void) {
  MyLib_record_t rec = {.id_u16 = 5U, .value_u32 = 500U};
  uint32_t initial_counter = g_counter_u32;
  uint8_t mult = 254U;
  uint32_t expected_acc = 254U * 500U;

  MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(expected_acc, (const uint16_t *)&mult, 0U);

  ProcessRecord(&rec, mult);

  TEST_ASSERT_EQUAL_UINT32(initial_counter + expected_acc, g_counter_u32);
}
void test_mult_255_upper_boundary(void) {
  MyLib_record_t rec = {.id_u16 = 6U, .value_u32 = 200U};
  uint32_t initial_counter = g_counter_u32;
  uint8_t mult = 255U;
  uint32_t expected_acc = 255U * 200U;

  MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(expected_acc, (const uint16_t *)&mult, 0U);

  ProcessRecord(&rec, mult);

  TEST_ASSERT_EQUAL_UINT32(initial_counter + expected_acc, g_counter_u32);
}
void test_value_0_mult_10(void) {
  MyLib_record_t rec = {.id_u16 = 7U, .value_u32 = 0U};
  uint32_t initial_counter = g_counter_u32;
  uint8_t mult = 10U;

  MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(0U, (const uint16_t *)&mult, 0U);

  ProcessRecord(&rec, mult);

  TEST_ASSERT_EQUAL_UINT32(initial_counter, g_counter_u32);
}
void test_value_1_mult_10(void) {
  MyLib_record_t rec = {.id_u16 = 8U, .value_u32 = 1U};
  uint32_t initial_counter = g_counter_u32;
  uint8_t mult = 10U;

  MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(10U, (const uint16_t *)&mult, 0U);

  ProcessRecord(&rec, mult);

  TEST_ASSERT_EQUAL_UINT32(initial_counter + 10U, g_counter_u32);
}
void test_value_max_mult_1(void) {
  MyLib_record_t rec = {.id_u16 = 9U, .value_u32 = 0xFFFFFFFFU};
  uint32_t initial_counter = g_counter_u32;
  uint8_t mult = 1U;

  MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(0xFFFFFFFFU, (const uint16_t *)&mult, 0U);

  ProcessRecord(&rec, mult);

  TEST_ASSERT_EQUAL_UINT32(initial_counter + 0xFFFFFFFFU, g_counter_u32);
}
void test_value_max_mult_2_wraparound(void) {
  MyLib_record_t rec = {.id_u16 = 10U, .value_u32 = 0xFFFFFFFFU};
  uint32_t initial_counter = g_counter_u32;
  uint8_t mult = 2U;
  uint32_t expected_acc = 0xFFFFFFFEU;

  MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(expected_acc, (const uint16_t *)&mult, 0U);

  ProcessRecord(&rec, mult);

  TEST_ASSERT_EQUAL_UINT32(initial_counter + expected_acc, g_counter_u32);
}
void test_counter_near_max_wraparound(void) {
  MyLib_record_t rec = {.id_u16 = 11U, .value_u32 = 0x20U};
  g_counter_u32 = 0xFFFFFFF0U;
  uint8_t mult = 1U;

  MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(0x20U, (const uint16_t *)&mult, 0U);

  ProcessRecord(&rec, mult);

  TEST_ASSERT_EQUAL_UINT32(0x10U, g_counter_u32);
}
void test_mult_255_large_value_wraparound(void) {
  MyLib_record_t rec = {.id_u16 = 12U, .value_u32 = 0x01000000U};
  uint32_t initial_counter = g_counter_u32;
  uint8_t mult = 255U;
  uint32_t expected_acc = (uint32_t)(255ULL * 0x01000000ULL);

  MyLib_ComputeAdjustedValue_u32_ExpectAndReturn(expected_acc, (const uint16_t *)&mult, 0U);

  ProcessRecord(&rec, mult);

  TEST_ASSERT_EQUAL_UINT32(initial_counter + expected_acc, g_counter_u32);
}
