#include "MyLib_UpdateGlobalRecord.h"
#include "mock_MyLib.h"
#include "unity.h"

/* ========================================================================
   SECTION 1 — Mock callbacks
   ======================================================================== */

/* No mock callbacks required for this unit test file. */

/* ========================================================================
   SECTION 2 — setUp() and tearDown()
   ======================================================================== */

void setUp(void) {
  g_counter_u32 = 0U;
  g_record.id_u16 = 0U;
  g_record.value_u32 = 0U;
  g_systemReady_b = false;
}

void tearDown(void) {
}

/* ========================================================================
   SECTION 3 — Test functions
   ======================================================================== */

/**
 * @brief Test: Both dest_p and src_pc are NULL – function returns immediately without modifying any global state or output; g_record and g_systemReady_b remain unchanged.
 */
void test_MyLib_UpdateGlobalRecord_both_pointers_NULL_no_changes(void) {
  MyLib_UpdateGlobalRecord(NULL, NULL);

  TEST_ASSERT_EQUAL_UINT16(0U, g_record.id_u16);
  TEST_ASSERT_EQUAL_UINT32(0U, g_record.value_u32);
  TEST_ASSERT_FALSE(g_systemReady_b);
}

/**
 * @brief Test: dest_p is NULL and src_pc is valid – function returns immediately without modifying g_record, g_systemReady_b, or dest_p.
 */
void test_MyLib_UpdateGlobalRecord_dest_NULL_src_valid_no_changes(void) {
  MyLib_record_t src = {100U, 5000U};

  MyLib_UpdateGlobalRecord(NULL, &src);

  TEST_ASSERT_EQUAL_UINT16(0U, g_record.id_u16);
  TEST_ASSERT_EQUAL_UINT32(0U, g_record.value_u32);
  TEST_ASSERT_FALSE(g_systemReady_b);
}

/**
 * @brief Test: dest_p is valid and src_pc is NULL – function returns immediately without modifying dest_p, g_record, or g_systemReady_b.
 */
void test_MyLib_UpdateGlobalRecord_dest_valid_src_NULL_no_changes(void) {
  MyLib_record_t dest = {999U, 888U};

  MyLib_UpdateGlobalRecord(&dest, NULL);

  TEST_ASSERT_EQUAL_UINT16(999U, dest.id_u16);
  TEST_ASSERT_EQUAL_UINT32(888U, dest.value_u32);
  TEST_ASSERT_EQUAL_UINT16(0U, g_record.id_u16);
  TEST_ASSERT_EQUAL_UINT32(0U, g_record.value_u32);
  TEST_ASSERT_FALSE(g_systemReady_b);
}

/**
 * @brief Test: Both dest_p and src_pc are valid with nominal values (id_u16 = 100, value_u32 = 5000) – dest_p is updated with src_pc content, g_record mirrors dest_p, and g_systemReady_b is set to true.
 */
void test_MyLib_UpdateGlobalRecord_both_valid_nominal_values_updates_all(void) {
  MyLib_record_t dest = {0U, 0U};
  MyLib_record_t src = {100U, 5000U};

  MyLib_UpdateGlobalRecord(&dest, &src);

  TEST_ASSERT_EQUAL_UINT16(100U, dest.id_u16);
  TEST_ASSERT_EQUAL_UINT32(5000U, dest.value_u32);
  TEST_ASSERT_EQUAL_UINT16(100U, g_record.id_u16);
  TEST_ASSERT_EQUAL_UINT32(5000U, g_record.value_u32);
  TEST_ASSERT_TRUE(g_systemReady_b);
}

/**
 * @brief Test: Both pointers valid, src_pc contains boundary values id_u16 = 0 and value_u32 = 0 – dest_p is updated, g_record mirrors dest_p, and g_systemReady_b is set to true.
 */
void test_MyLib_UpdateGlobalRecord_both_valid_boundary_zero_updates_all(void) {
  MyLib_record_t dest = {999U, 999U};
  MyLib_record_t src = {0U, 0U};

  MyLib_UpdateGlobalRecord(&dest, &src);

  TEST_ASSERT_EQUAL_UINT16(0U, dest.id_u16);
  TEST_ASSERT_EQUAL_UINT32(0U, dest.value_u32);
  TEST_ASSERT_EQUAL_UINT16(0U, g_record.id_u16);
  TEST_ASSERT_EQUAL_UINT32(0U, g_record.value_u32);
  TEST_ASSERT_TRUE(g_systemReady_b);
}

/**
 * @brief Test: Both pointers valid, src_pc contains boundary values id_u16 = 65535 and value_u32 = 4294967295 – dest_p is updated, g_record mirrors dest_p, and g_systemReady_b is set to true.
 */
void test_MyLib_UpdateGlobalRecord_both_valid_boundary_max_updates_all(void) {
  MyLib_record_t dest = {0U, 0U};
  MyLib_record_t src = {65535U, 4294967295U};

  MyLib_UpdateGlobalRecord(&dest, &src);

  TEST_ASSERT_EQUAL_UINT16(65535U, dest.id_u16);
  TEST_ASSERT_EQUAL_UINT32(4294967295U, dest.value_u32);
  TEST_ASSERT_EQUAL_UINT16(65535U, g_record.id_u16);
  TEST_ASSERT_EQUAL_UINT32(4294967295U, g_record.value_u32);
  TEST_ASSERT_TRUE(g_systemReady_b);
}

/**
 * @brief Test: Both pointers valid, src_pc contains mid-range values id_u16 = 32767 and value_u32 = 2147483647 – dest_p is updated, g_record mirrors dest_p, and g_systemReady_b is set to true.
 */
void test_MyLib_UpdateGlobalRecord_both_valid_midrange_values_updates_all(void) {
  MyLib_record_t dest = {0U, 0U};
  MyLib_record_t src = {32767U, 2147483647U};

  MyLib_UpdateGlobalRecord(&dest, &src);

  TEST_ASSERT_EQUAL_UINT16(32767U, dest.id_u16);
  TEST_ASSERT_EQUAL_UINT32(2147483647U, dest.value_u32);
  TEST_ASSERT_EQUAL_UINT16(32767U, g_record.id_u16);
  TEST_ASSERT_EQUAL_UINT32(2147483647U, g_record.value_u32);
  TEST_ASSERT_TRUE(g_systemReady_b);
}

/**
 * @brief Test: Both pointers valid, src_pc contains id_u16 = 1 and value_u32 = 1 (just inside lower boundary) – dest_p is updated, g_record mirrors dest_p, and g_systemReady_b is set to true.
 */
void test_MyLib_UpdateGlobalRecord_both_valid_just_inside_lower_boundary_updates_all(void) {
  MyLib_record_t dest = {0U, 0U};
  MyLib_record_t src = {1U, 1U};

  MyLib_UpdateGlobalRecord(&dest, &src);

  TEST_ASSERT_EQUAL_UINT16(1U, dest.id_u16);
  TEST_ASSERT_EQUAL_UINT32(1U, dest.value_u32);
  TEST_ASSERT_EQUAL_UINT16(1U, g_record.id_u16);
  TEST_ASSERT_EQUAL_UINT32(1U, g_record.value_u32);
  TEST_ASSERT_TRUE(g_systemReady_b);
}

/**
 * @brief Test: Both pointers valid, src_pc contains id_u16 = 65534 and value_u32 = 4294967294 (just inside upper boundary) – dest_p is updated, g_record mirrors dest_p, and g_systemReady_b is set to true.
 */
void test_MyLib_UpdateGlobalRecord_both_valid_just_inside_upper_boundary_updates_all(void) {
  MyLib_record_t dest = {0U, 0U};
  MyLib_record_t src = {65534U, 4294967294U};

  MyLib_UpdateGlobalRecord(&dest, &src);

  TEST_ASSERT_EQUAL_UINT16(65534U, dest.id_u16);
  TEST_ASSERT_EQUAL_UINT32(4294967294U, dest.value_u32);
  TEST_ASSERT_EQUAL_UINT16(65534U, g_record.id_u16);
  TEST_ASSERT_EQUAL_UINT32(4294967294U, g_record.value_u32);
  TEST_ASSERT_TRUE(g_systemReady_b);
}

/**
 * @brief Test: Function called twice with different valid records – verify that the second call correctly overwrites dest_p, g_record, and that g_systemReady_b remains true after both calls.
 */
void test_MyLib_UpdateGlobalRecord_called_twice_second_call_overwrites_correctly(void) {
  MyLib_record_t dest = {0U, 0U};
  MyLib_record_t src1 = {100U, 5000U};
  MyLib_record_t src2 = {200U, 10000U};

  MyLib_UpdateGlobalRecord(&dest, &src1);

  TEST_ASSERT_EQUAL_UINT16(100U, dest.id_u16);
  TEST_ASSERT_EQUAL_UINT32(5000U, dest.value_u32);
  TEST_ASSERT_EQUAL_UINT16(100U, g_record.id_u16);
  TEST_ASSERT_EQUAL_UINT32(5000U, g_record.value_u32);
  TEST_ASSERT_TRUE(g_systemReady_b);

  MyLib_UpdateGlobalRecord(&dest, &src2);

  TEST_ASSERT_EQUAL_UINT16(200U, dest.id_u16);
  TEST_ASSERT_EQUAL_UINT32(10000U, dest.value_u32);
  TEST_ASSERT_EQUAL_UINT16(200U, g_record.id_u16);
  TEST_ASSERT_EQUAL_UINT32(10000U, g_record.value_u32);
  TEST_ASSERT_TRUE(g_systemReady_b);
}

/**
 * @brief Test: g_systemReady_b is initially true; call function with both pointers NULL – verify g_systemReady_b remains true and g_record is unchanged.
 */
void test_MyLib_UpdateGlobalRecord_systemReady_true_both_NULL_no_changes(void) {
  g_systemReady_b = true;
  g_record.id_u16 = 123U;
  g_record.value_u32 = 456U;

  MyLib_UpdateGlobalRecord(NULL, NULL);

  TEST_ASSERT_EQUAL_UINT16(123U, g_record.id_u16);
  TEST_ASSERT_EQUAL_UINT32(456U, g_record.value_u32);
  TEST_ASSERT_TRUE(g_systemReady_b);
}

/**
 * @brief Test: g_systemReady_b is initially false; call function with valid pointers – verify g_systemReady_b transitions to true and g_record is updated.
 */
void test_MyLib_UpdateGlobalRecord_systemReady_false_valid_pointers_transitions_to_true(void) {
  MyLib_record_t dest = {0U, 0U};
  MyLib_record_t src = {300U, 7000U};

  g_systemReady_b = false;

  MyLib_UpdateGlobalRecord(&dest, &src);

  TEST_ASSERT_EQUAL_UINT16(300U, dest.id_u16);
  TEST_ASSERT_EQUAL_UINT32(7000U, dest.value_u32);
  TEST_ASSERT_EQUAL_UINT16(300U, g_record.id_u16);
  TEST_ASSERT_EQUAL_UINT32(7000U, g_record.value_u32);
  TEST_ASSERT_TRUE(g_systemReady_b);
}