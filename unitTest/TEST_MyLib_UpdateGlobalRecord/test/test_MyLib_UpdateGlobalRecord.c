#include "MyLib_UpdateGlobalRecord.h"
#include "mock_MyLib.h"
#include "unity.h"




/* SECTION 1 — Mock callbacks */
/* No mock callbacks required for this unit test */

/* SECTION 2 — setUp() and tearDown() */
void setUp(void)
{
    g_counter_u32 = 0U;
    g_record.id_u16 = 0U;
    g_record.value_u32 = 0U;
    g_systemReady_b = false;
}

void tearDown(void)
{
}

/* SECTION 3 — Test functions */

/**
 * @brief Test: Both dest_p and src_pc are NULL – function returns immediately without modifying any global state or output; g_record and g_systemReady_b remain unchanged.
 */
void test_MyLib_UpdateGlobalRecord_both_pointers_null_no_changes(void)
{
    MyLib_record_t initial_record = g_record;
    bool initial_ready = g_systemReady_b;

    MyLib_UpdateGlobalRecord(NULL, NULL);

    TEST_ASSERT_EQUAL_UINT16(initial_record.id_u16, g_record.id_u16);
    TEST_ASSERT_EQUAL_UINT32(initial_record.value_u32, g_record.value_u32);
    TEST_ASSERT_EQUAL(initial_ready, g_systemReady_b);
}

/**
 * @brief Test: dest_p is NULL and src_pc is valid – function returns immediately without modifying g_record, g_systemReady_b, or dest_p.
 */
void test_MyLib_UpdateGlobalRecord_dest_null_src_valid_no_changes(void)
{
    MyLib_record_t src = {123U, 456789U};
    MyLib_record_t initial_record = g_record;
    bool initial_ready = g_systemReady_b;

    MyLib_UpdateGlobalRecord(NULL, &src);

    TEST_ASSERT_EQUAL_UINT16(initial_record.id_u16, g_record.id_u16);
    TEST_ASSERT_EQUAL_UINT32(initial_record.value_u32, g_record.value_u32);
    TEST_ASSERT_EQUAL(initial_ready, g_systemReady_b);
}

/**
 * @brief Test: dest_p is valid and src_pc is NULL – function returns immediately without modifying dest_p, g_record, or g_systemReady_b.
 */
void test_MyLib_UpdateGlobalRecord_dest_valid_src_null_no_changes(void)
{
    MyLib_record_t dest = {999U, 888888U};
    MyLib_record_t initial_dest = dest;
    MyLib_record_t initial_record = g_record;
    bool initial_ready = g_systemReady_b;

    MyLib_UpdateGlobalRecord(&dest, NULL);

    TEST_ASSERT_EQUAL_UINT16(initial_dest.id_u16, dest.id_u16);
    TEST_ASSERT_EQUAL_UINT32(initial_dest.value_u32, dest.value_u32);
    TEST_ASSERT_EQUAL_UINT16(initial_record.id_u16, g_record.id_u16);
    TEST_ASSERT_EQUAL_UINT32(initial_record.value_u32, g_record.value_u32);
    TEST_ASSERT_EQUAL(initial_ready, g_systemReady_b);
}

/**
 * @brief Test: Both dest_p and src_pc are valid with id_u16=0 and value_u32=0 – dest_p is updated with src_pc content, g_record mirrors dest_p, and g_systemReady_b is set to true.
 */
void test_MyLib_UpdateGlobalRecord_both_valid_zero_values_updates_correctly(void)
{
    MyLib_record_t dest = {0U, 0U};
    MyLib_record_t src = {0U, 0U};

    MyLib_UpdateGlobalRecord(&dest, &src);

    TEST_ASSERT_EQUAL_UINT16(0U, dest.id_u16);
    TEST_ASSERT_EQUAL_UINT32(0U, dest.value_u32);
    TEST_ASSERT_EQUAL_UINT16(0U, g_record.id_u16);
    TEST_ASSERT_EQUAL_UINT32(0U, g_record.value_u32);
    TEST_ASSERT_TRUE(g_systemReady_b);
}

/**
 * @brief Test: Both dest_p and src_pc are valid with id_u16=1 and value_u32=1 – dest_p is updated with src_pc content, g_record mirrors dest_p, and g_systemReady_b is set to true.
 */
void test_MyLib_UpdateGlobalRecord_both_valid_one_values_updates_correctly(void)
{
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
 * @brief Test: Both dest_p and src_pc are valid with id_u16=32767 and value_u32=2147483647 – dest_p is updated with src_pc content, g_record mirrors dest_p, and g_systemReady_b is set to true.
 */
void test_MyLib_UpdateGlobalRecord_both_valid_mid_range_values_updates_correctly(void)
{
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
 * @brief Test: Both dest_p and src_pc are valid with id_u16=65534 and value_u32=4294967294 – dest_p is updated with src_pc content, g_record mirrors dest_p, and g_systemReady_b is set to true.
 */
void test_MyLib_UpdateGlobalRecord_both_valid_near_max_values_updates_correctly(void)
{
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
 * @brief Test: Both dest_p and src_pc are valid with id_u16=65535 and value_u32=4294967295 – dest_p is updated with src_pc content, g_record mirrors dest_p, and g_systemReady_b is set to true.
 */
void test_MyLib_UpdateGlobalRecord_both_valid_max_values_updates_correctly(void)
{
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
 * @brief Test: Both dest_p and src_pc are valid with id_u16=100 and value_u32=500000 – dest_p is updated with src_pc content, g_record mirrors dest_p, and g_systemReady_b is set to true.
 */
void test_MyLib_UpdateGlobalRecord_both_valid_typical_values_updates_correctly(void)
{
    MyLib_record_t dest = {0U, 0U};
    MyLib_record_t src = {100U, 500000U};

    MyLib_UpdateGlobalRecord(&dest, &src);

    TEST_ASSERT_EQUAL_UINT16(100U, dest.id_u16);
    TEST_ASSERT_EQUAL_UINT32(500000U, dest.value_u32);
    TEST_ASSERT_EQUAL_UINT16(100U, g_record.id_u16);
    TEST_ASSERT_EQUAL_UINT32(500000U, g_record.value_u32);
    TEST_ASSERT_TRUE(g_systemReady_b);
}

/**
 * @brief Test: g_systemReady_b is initially false – after successful copy with valid pointers, g_systemReady_b transitions to true.
 */
void test_MyLib_UpdateGlobalRecord_systemReady_initially_false_transitions_to_true(void)
{
    MyLib_record_t dest = {0U, 0U};
    MyLib_record_t src = {50U, 250000U};
    g_systemReady_b = false;

    MyLib_UpdateGlobalRecord(&dest, &src);

    TEST_ASSERT_EQUAL_UINT16(50U, dest.id_u16);
    TEST_ASSERT_EQUAL_UINT32(250000U, dest.value_u32);
    TEST_ASSERT_EQUAL_UINT16(50U, g_record.id_u16);
    TEST_ASSERT_EQUAL_UINT32(250000U, g_record.value_u32);
    TEST_ASSERT_TRUE(g_systemReady_b);
}

/**
 * @brief Test: g_systemReady_b is initially true – after successful copy with valid pointers, g_systemReady_b remains true and g_record is updated.
 */
void test_MyLib_UpdateGlobalRecord_systemReady_initially_true_remains_true(void)
{
    MyLib_record_t dest = {0U, 0U};
    MyLib_record_t src = {75U, 375000U};
    g_systemReady_b = true;

    MyLib_UpdateGlobalRecord(&dest, &src);

    TEST_ASSERT_EQUAL_UINT16(75U, dest.id_u16);
    TEST_ASSERT_EQUAL_UINT32(375000U, dest.value_u32);
    TEST_ASSERT_EQUAL_UINT16(75U, g_record.id_u16);
    TEST_ASSERT_EQUAL_UINT32(375000U, g_record.value_u32);
    TEST_ASSERT_TRUE(g_systemReady_b);
}

/**
 * @brief Test: dest_p initially contains id_u16=999 and value_u32=888 – after successful copy from src_pc with id_u16=111 and value_u32=222, dest_p is overwritten with src_pc values, g_record mirrors the new dest_p, and g_systemReady_b is set to true.
 */
void test_MyLib_UpdateGlobalRecord_dest_overwritten_with_src_values(void)
{
    MyLib_record_t dest = {999U, 888U};
    MyLib_record_t src = {111U, 222U};

    MyLib_UpdateGlobalRecord(&dest, &src);

    TEST_ASSERT_EQUAL_UINT16(111U, dest.id_u16);
    TEST_ASSERT_EQUAL_UINT32(222U, dest.value_u32);
    TEST_ASSERT_EQUAL_UINT16(111U, g_record.id_u16);
    TEST_ASSERT_EQUAL_UINT32(222U, g_record.value_u32);
    TEST_ASSERT_TRUE(g_systemReady_b);
}