#include "unity.h"
#include "MyLib_UpdateGlobalRecord.h"
#include "mock_MyLib.h"

/**
 * @file test_MyLib_UpdateGlobalRecord.c
 * @brief Unit tests for MyLib_UpdateGlobalRecord function
 *
 * This test suite validates the record update and global state management
 * functionality using CMock for dependency isolation.
 */

/* Test setup and teardown */

void setUp(void)
{
  /* Reset global variables before each test */
  g_counter_u32 = 0U;
  g_record.id_u16 = 0U;
  g_record.value_u32 = 0U;
  g_systemReady_b = false;
}

void tearDown(void)
{
  /* Cleanup after each test */
}

/**
 * @test MyLib_UpdateGlobalRecord_ValidInput_UpdatesDestinationAndGlobals
 * @brief Verify successful copy operation with valid pointers
 *
 * When: Both dest_p and src_pc point to valid MyLib_record_t structures
 * Then:
 *   - dest_p fields are updated with src_pc values
 *   - g_record is updated to match dest_p
 *   - g_systemReady_b is set to true
 */
void test_MyLib_UpdateGlobalRecord_ValidInput_UpdatesDestinationAndGlobals(void)
{
  /* Arrange */
  MyLib_record_t source = {0x1234U, 0x56789ABCU};
  MyLib_record_t destination = {0U, 0U};

  /* Precondition checks */
  TEST_ASSERT_EQUAL_UINT16(0U, destination.id_u16);
  TEST_ASSERT_EQUAL_UINT32(0U, destination.value_u32);
  TEST_ASSERT_EQUAL_UINT16(0U, g_record.id_u16);
  TEST_ASSERT_EQUAL_UINT32(0U, g_record.value_u32);
  TEST_ASSERT_FALSE(g_systemReady_b);

  /* Act */
  MyLib_UpdateGlobalRecord(&destination, &source);

  /* Assert - Destination record is updated */
  TEST_ASSERT_EQUAL_UINT16(0x1234U, destination.id_u16);
  TEST_ASSERT_EQUAL_UINT32(0x56789ABCU, destination.value_u32);

  /* Assert - Global record is synchronized */
  TEST_ASSERT_EQUAL_UINT16(0x1234U, g_record.id_u16);
  TEST_ASSERT_EQUAL_UINT32(0x56789ABCU, g_record.value_u32);

  /* Assert - System ready flag is set */
  TEST_ASSERT_TRUE(g_systemReady_b);
}

/**
 * @test MyLib_UpdateGlobalRecord_NullDestinationPointer_NoUpdate
 * @brief Verify function returns early when dest_p is NULL
 *
 * When: dest_p is NULL and src_pc points to valid data
 * Then:
 *   - No global state is modified
 *   - Function returns without side effects
 */
void test_MyLib_UpdateGlobalRecord_NullDestinationPointer_NoUpdate(void)
{
  /* Arrange */
  MyLib_record_t source = {0xABCDU, 0xDEADBEEFU};

  /* Precondition: globals are in known state (false, 0, 0) */
  TEST_ASSERT_FALSE(g_systemReady_b);
  TEST_ASSERT_EQUAL_UINT16(0U, g_record.id_u16);
  TEST_ASSERT_EQUAL_UINT32(0U, g_record.value_u32);

  /* Act */
  MyLib_UpdateGlobalRecord(NULL, &source);

  /* Assert - Global state remains unchanged */
  TEST_ASSERT_FALSE(g_systemReady_b);
  TEST_ASSERT_EQUAL_UINT16(0U, g_record.id_u16);
  TEST_ASSERT_EQUAL_UINT32(0U, g_record.value_u32);
}

/**
 * @test MyLib_UpdateGlobalRecord_NullSourcePointer_NoUpdate
 * @brief Verify function returns early when src_pc is NULL
 *
 * When: src_pc is NULL and dest_p points to valid memory
 * Then:
 *   - Destination record is not modified
 *   - Global state is not modified
 *   - Function returns without side effects
 */
void test_MyLib_UpdateGlobalRecord_NullSourcePointer_NoUpdate(void)
{
  /* Arrange */
  MyLib_record_t destination = {0x5555U, 0xAAAAAAAAU};

  /* Precondition: set destination to known values */
  TEST_ASSERT_EQUAL_UINT16(0x5555U, destination.id_u16);
  TEST_ASSERT_EQUAL_UINT32(0xAAAAAAAAU, destination.value_u32);
  TEST_ASSERT_FALSE(g_systemReady_b);

  /* Act */
  MyLib_UpdateGlobalRecord(&destination, NULL);

  /* Assert - Destination record is unchanged */
  TEST_ASSERT_EQUAL_UINT16(0x5555U, destination.id_u16);
  TEST_ASSERT_EQUAL_UINT32(0xAAAAAAAAU, destination.value_u32);

  /* Assert - Global state remains unchanged */
  TEST_ASSERT_FALSE(g_systemReady_b);
  TEST_ASSERT_EQUAL_UINT16(0U, g_record.id_u16);
  TEST_ASSERT_EQUAL_UINT32(0U, g_record.value_u32);
}

/**
 * @test MyLib_UpdateGlobalRecord_BothPointersNull_NoUpdate
 * @brief Verify function returns early when both pointers are NULL
 *
 * When: Both dest_p and src_pc are NULL
 * Then:
 *   - Global state remains unchanged
 *   - Function returns without side effects
 */
void test_MyLib_UpdateGlobalRecord_BothPointersNull_NoUpdate(void)
{
  /* Arrange */
  /* Pre-set some state to verify it is not modified */
  g_systemReady_b = true;
  g_record.id_u16 = 0x9999U;
  g_record.value_u32 = 0x11111111U;

  /* Precondition checks */
  TEST_ASSERT_TRUE(g_systemReady_b);
  TEST_ASSERT_EQUAL_UINT16(0x9999U, g_record.id_u16);
  TEST_ASSERT_EQUAL_UINT32(0x11111111U, g_record.value_u32);

  /* Act */
  MyLib_UpdateGlobalRecord(NULL, NULL);

  /* Assert - Global state remains exactly as it was */
  TEST_ASSERT_TRUE(g_systemReady_b);
  TEST_ASSERT_EQUAL_UINT16(0x9999U, g_record.id_u16);
  TEST_ASSERT_EQUAL_UINT32(0x11111111U, g_record.value_u32);
}

/**
 * @test MyLib_UpdateGlobalRecord_MultipleCallsWithDifferentValues_UpdatesCorrectly
 * @brief Verify that successive calls properly update state
 *
 * When: Function is called multiple times with different record values
 * Then:
 *   - Each call properly updates both destination and global state
 *   - Previous state is properly overwritten
 */
void test_MyLib_UpdateGlobalRecord_MultipleCallsWithDifferentValues_UpdatesCorrectly(void)
{
  /* Arrange */
  MyLib_record_t source1 = {100U, 1000U};
  MyLib_record_t source2 = {200U, 2000U};
  MyLib_record_t destination = {0U, 0U};

  /* Act - First call */
  MyLib_UpdateGlobalRecord(&destination, &source1);

  /* Assert - First update is correct */
  TEST_ASSERT_EQUAL_UINT16(100U, destination.id_u16);
  TEST_ASSERT_EQUAL_UINT32(1000U, destination.value_u32);
  TEST_ASSERT_EQUAL_UINT16(100U, g_record.id_u16);
  TEST_ASSERT_EQUAL_UINT32(1000U, g_record.value_u32);
  TEST_ASSERT_TRUE(g_systemReady_b);

  /* Act - Second call with different data */
  MyLib_UpdateGlobalRecord(&destination, &source2);

  /* Assert - Second update completely replaces first */
  TEST_ASSERT_EQUAL_UINT16(200U, destination.id_u16);
  TEST_ASSERT_EQUAL_UINT32(2000U, destination.value_u32);
  TEST_ASSERT_EQUAL_UINT16(200U, g_record.id_u16);
  TEST_ASSERT_EQUAL_UINT32(2000U, g_record.value_u32);
  TEST_ASSERT_TRUE(g_systemReady_b);
}

/**
 * @test MyLib_UpdateGlobalRecord_EdgeCaseZeroValues_UpdatesCorrectly
 * @brief Verify function handles zero values correctly
 *
 * When: Source record contains all zero values
 * Then:
 *   - Destination is updated with zero values
 *   - Global record reflects zero values
 *   - System ready flag is still set to true
 */
void test_MyLib_UpdateGlobalRecord_EdgeCaseZeroValues_UpdatesCorrectly(void)
{
  /* Arrange */
  MyLib_record_t source = {0U, 0U};
  MyLib_record_t destination = {0xFFFFU, 0xFFFFFFFFU};

  /* Precondition: destination has non-zero values */
  TEST_ASSERT_EQUAL_UINT16(0xFFFFU, destination.id_u16);
  TEST_ASSERT_EQUAL_UINT32(0xFFFFFFFFU, destination.value_u32);

  /* Act */
  MyLib_UpdateGlobalRecord(&destination, &source);

  /* Assert - Zero values are properly propagated */
  TEST_ASSERT_EQUAL_UINT16(0U, destination.id_u16);
  TEST_ASSERT_EQUAL_UINT32(0U, destination.value_u32);
  TEST_ASSERT_EQUAL_UINT16(0U, g_record.id_u16);
  TEST_ASSERT_EQUAL_UINT32(0U, g_record.value_u32);
  TEST_ASSERT_TRUE(g_systemReady_b);
}

/**
 * @test MyLib_UpdateGlobalRecord_EdgeCaseMaxValues_UpdatesCorrectly
 * @brief Verify function handles maximum type values correctly
 *
 * When: Source record contains maximum possible values
 * Then:
 *   - Destination is updated with max values
 *   - Global record reflects max values
 *   - System ready flag is set to true
 */
void test_MyLib_UpdateGlobalRecord_EdgeCaseMaxValues_UpdatesCorrectly(void)
{
  /* Arrange */
  MyLib_record_t source = {0xFFFFU, 0xFFFFFFFFU};
  MyLib_record_t destination = {0U, 0U};

  /* Act */
  MyLib_UpdateGlobalRecord(&destination, &source);

  /* Assert - Maximum values are properly propagated */
  TEST_ASSERT_EQUAL_UINT16(0xFFFFU, destination.id_u16);
  TEST_ASSERT_EQUAL_UINT32(0xFFFFFFFFU, destination.value_u32);
  TEST_ASSERT_EQUAL_UINT16(0xFFFFU, g_record.id_u16);
  TEST_ASSERT_EQUAL_UINT32(0xFFFFFFFFU, g_record.value_u32);
  TEST_ASSERT_TRUE(g_systemReady_b);
}


