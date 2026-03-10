#include "MyLib_UpdateGlobalRecord.h"
#include "mock_MyLib.h"
#include "unity.h"

void setUp(void) {
  g_counter_u32 = 0U;
  g_record.id_u16 = 0U;
  g_record.value_u32 = 0U;
  g_systemReady_b = false;
}
void tearDown(void) {
}
void test_BothPointersNull_NoChange(void) {
  MyLib_record_t initial_record = g_record;
  bool initial_ready = g_systemReady_b;

  MyLib_UpdateGlobalRecord(NULL, NULL);

  TEST_ASSERT_EQUAL_UINT16(initial_record.id_u16, g_record.id_u16);
  TEST_ASSERT_EQUAL_UINT32(initial_record.value_u32, g_record.value_u32);
  TEST_ASSERT_EQUAL(initial_ready, g_systemReady_b);
}
void test_DestNullSrcValid_NoChange(void) {
  MyLib_record_t src = {100U, 200U};
  MyLib_record_t initial_record = g_record;
  bool initial_ready = g_systemReady_b;

  MyLib_UpdateGlobalRecord(NULL, &src);

  TEST_ASSERT_EQUAL_UINT16(initial_record.id_u16, g_record.id_u16);
  TEST_ASSERT_EQUAL_UINT32(initial_record.value_u32, g_record.value_u32);
  TEST_ASSERT_EQUAL(initial_ready, g_systemReady_b);
}
void test_DestValidSrcNull_NoChange(void) {
  MyLib_record_t dest = {50U, 75U};
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
void test_BothValidZeroValues_UpdateSuccess(void) {
  MyLib_record_t src = {0U, 0U};
  MyLib_record_t dest = {999U, 999U};

  MyLib_UpdateGlobalRecord(&dest, &src);

  TEST_ASSERT_EQUAL_UINT16(0U, dest.id_u16);
  TEST_ASSERT_EQUAL_UINT32(0U, dest.value_u32);
  TEST_ASSERT_EQUAL_UINT16(0U, g_record.id_u16);
  TEST_ASSERT_EQUAL_UINT32(0U, g_record.value_u32);
  TEST_ASSERT_TRUE(g_systemReady_b);
}
void test_BothValidMinValues_UpdateSuccess(void) {
  MyLib_record_t src = {1U, 1U};
  MyLib_record_t dest = {0U, 0U};

  MyLib_UpdateGlobalRecord(&dest, &src);

  TEST_ASSERT_EQUAL_UINT16(1U, dest.id_u16);
  TEST_ASSERT_EQUAL_UINT32(1U, dest.value_u32);
  TEST_ASSERT_EQUAL_UINT16(1U, g_record.id_u16);
  TEST_ASSERT_EQUAL_UINT32(1U, g_record.value_u32);
  TEST_ASSERT_TRUE(g_systemReady_b);
}
void test_BothValidMidRangeValues_UpdateSuccess(void) {
  MyLib_record_t src = {32767U, 2147483647U};
  MyLib_record_t dest = {0U, 0U};

  MyLib_UpdateGlobalRecord(&dest, &src);

  TEST_ASSERT_EQUAL_UINT16(32767U, dest.id_u16);
  TEST_ASSERT_EQUAL_UINT32(2147483647U, dest.value_u32);
  TEST_ASSERT_EQUAL_UINT16(32767U, g_record.id_u16);
  TEST_ASSERT_EQUAL_UINT32(2147483647U, g_record.value_u32);
  TEST_ASSERT_TRUE(g_systemReady_b);
}
void test_BothValidNearMaxValues_UpdateSuccess(void) {
  MyLib_record_t src = {65534U, 4294967294U};
  MyLib_record_t dest = {0U, 0U};

  MyLib_UpdateGlobalRecord(&dest, &src);

  TEST_ASSERT_EQUAL_UINT16(65534U, dest.id_u16);
  TEST_ASSERT_EQUAL_UINT32(4294967294U, dest.value_u32);
  TEST_ASSERT_EQUAL_UINT16(65534U, g_record.id_u16);
  TEST_ASSERT_EQUAL_UINT32(4294967294U, g_record.value_u32);
  TEST_ASSERT_TRUE(g_systemReady_b);
}
void test_BothValidMaxValues_UpdateSuccess(void) {
  MyLib_record_t src = {65535U, 4294967295U};
  MyLib_record_t dest = {0U, 0U};

  MyLib_UpdateGlobalRecord(&dest, &src);

  TEST_ASSERT_EQUAL_UINT16(65535U, dest.id_u16);
  TEST_ASSERT_EQUAL_UINT32(4294967295U, dest.value_u32);
  TEST_ASSERT_EQUAL_UINT16(65535U, g_record.id_u16);
  TEST_ASSERT_EQUAL_UINT32(4294967295U, g_record.value_u32);
  TEST_ASSERT_TRUE(g_systemReady_b);
}
void test_BothValidArbitraryValues_UpdateSuccess(void) {
  MyLib_record_t src = {12345U, 987654321U};
  MyLib_record_t dest = {0U, 0U};

  MyLib_UpdateGlobalRecord(&dest, &src);

  TEST_ASSERT_EQUAL_UINT16(12345U, dest.id_u16);
  TEST_ASSERT_EQUAL_UINT32(987654321U, dest.value_u32);
  TEST_ASSERT_EQUAL_UINT16(12345U, g_record.id_u16);
  TEST_ASSERT_EQUAL_UINT32(987654321U, g_record.value_u32);
  TEST_ASSERT_TRUE(g_systemReady_b);
}
void test_SystemReadyFalseToTrue_Transition(void) {
  MyLib_record_t src = {100U, 200U};
  MyLib_record_t dest = {0U, 0U};
  g_systemReady_b = false;

  MyLib_UpdateGlobalRecord(&dest, &src);

  TEST_ASSERT_EQUAL_UINT16(100U, dest.id_u16);
  TEST_ASSERT_EQUAL_UINT32(200U, dest.value_u32);
  TEST_ASSERT_EQUAL_UINT16(100U, g_record.id_u16);
  TEST_ASSERT_EQUAL_UINT32(200U, g_record.value_u32);
  TEST_ASSERT_TRUE(g_systemReady_b);
}
void test_SystemReadyTrueToTrue_RemainsTrue(void) {
  MyLib_record_t src = {300U, 400U};
  MyLib_record_t dest = {0U, 0U};
  g_systemReady_b = true;

  MyLib_UpdateGlobalRecord(&dest, &src);

  TEST_ASSERT_EQUAL_UINT16(300U, dest.id_u16);
  TEST_ASSERT_EQUAL_UINT32(400U, dest.value_u32);
  TEST_ASSERT_EQUAL_UINT16(300U, g_record.id_u16);
  TEST_ASSERT_EQUAL_UINT32(400U, g_record.value_u32);
  TEST_ASSERT_TRUE(g_systemReady_b);
}
void test_GlobalRecordOverwritten_NewContent(void) {
  MyLib_record_t src = {555U, 777U};
  MyLib_record_t dest = {0U, 0U};
  g_record.id_u16 = 999U;
  g_record.value_u32 = 888U;

  MyLib_UpdateGlobalRecord(&dest, &src);

  TEST_ASSERT_EQUAL_UINT16(555U, dest.id_u16);
  TEST_ASSERT_EQUAL_UINT32(777U, dest.value_u32);
  TEST_ASSERT_EQUAL_UINT16(555U, g_record.id_u16);
  TEST_ASSERT_EQUAL_UINT32(777U, g_record.value_u32);
  TEST_ASSERT_TRUE(g_systemReady_b);
}
