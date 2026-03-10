#include "MyLib_UpdateGlobalRecord.h"
#include "mock_MyLib.h"
#include "unity.h"




void setUp(void)
{
}
void tearDown(void)
{
}
void test_BothPointersNull_NoChange(void)
{
    MyLib_UpdateGlobalRecord(NULL, NULL);

    TEST_ASSERT_EQUAL_UINT16(0U, g_record.id_u16);
    TEST_ASSERT_EQUAL_UINT32(0U, g_record.value_u32);
    TEST_ASSERT_FALSE(g_systemReady_b);
}
void test_DestNullSrcValid_NoChange(void)
{
    MyLib_record_t src = {123U, 456789U};

    MyLib_UpdateGlobalRecord(NULL, &src);

    TEST_ASSERT_EQUAL_UINT16(0U, g_record.id_u16);
    TEST_ASSERT_EQUAL_UINT32(0U, g_record.value_u32);
    TEST_ASSERT_FALSE(g_systemReady_b);
}
void test_DestValidSrcNull_NoChange(void)
{
    MyLib_record_t dest = {999U, 888777U};

    MyLib_UpdateGlobalRecord(&dest, NULL);

    TEST_ASSERT_EQUAL_UINT16(999U, dest.id_u16);
    TEST_ASSERT_EQUAL_UINT32(888777U, dest.value_u32);
    TEST_ASSERT_EQUAL_UINT16(0U, g_record.id_u16);
    TEST_ASSERT_EQUAL_UINT32(0U, g_record.value_u32);
    TEST_ASSERT_FALSE(g_systemReady_b);
}
void test_BothValid_CopyAndUpdate(void)
{
    MyLib_record_t dest = {0U, 0U};
    MyLib_record_t src = {100U, 200300U};

    MyLib_UpdateGlobalRecord(&dest, &src);

    TEST_ASSERT_EQUAL_UINT16(100U, dest.id_u16);
    TEST_ASSERT_EQUAL_UINT32(200300U, dest.value_u32);
    TEST_ASSERT_EQUAL_UINT16(100U, g_record.id_u16);
    TEST_ASSERT_EQUAL_UINT32(200300U, g_record.value_u32);
    TEST_ASSERT_TRUE(g_systemReady_b);
}
void test_BothValid_BoundaryZero(void)
{
    MyLib_record_t dest = {999U, 999999U};
    MyLib_record_t src = {0U, 0U};

    MyLib_UpdateGlobalRecord(&dest, &src);

    TEST_ASSERT_EQUAL_UINT16(0U, dest.id_u16);
    TEST_ASSERT_EQUAL_UINT32(0U, dest.value_u32);
    TEST_ASSERT_EQUAL_UINT16(0U, g_record.id_u16);
    TEST_ASSERT_EQUAL_UINT32(0U, g_record.value_u32);
    TEST_ASSERT_TRUE(g_systemReady_b);
}
void test_BothValid_BoundaryMax(void)
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
void test_BothValid_MidRange(void)
{
    MyLib_record_t dest = {0U, 0U};
    MyLib_record_t src = {32768U, 2147483648U};

    MyLib_UpdateGlobalRecord(&dest, &src);

    TEST_ASSERT_EQUAL_UINT16(32768U, dest.id_u16);
    TEST_ASSERT_EQUAL_UINT32(2147483648U, dest.value_u32);
    TEST_ASSERT_EQUAL_UINT16(32768U, g_record.id_u16);
    TEST_ASSERT_EQUAL_UINT32(2147483648U, g_record.value_u32);
    TEST_ASSERT_TRUE(g_systemReady_b);
}
void test_DestNull_AfterSuccessfulCall(void)
{
    MyLib_record_t dest = {0U, 0U};
    MyLib_record_t src1 = {111U, 222333U};
    MyLib_record_t src2 = {444U, 555666U};

    MyLib_UpdateGlobalRecord(&dest, &src1);

    TEST_ASSERT_EQUAL_UINT16(111U, g_record.id_u16);
    TEST_ASSERT_EQUAL_UINT32(222333U, g_record.value_u32);
    TEST_ASSERT_TRUE(g_systemReady_b);

    MyLib_UpdateGlobalRecord(NULL, &src2);

    TEST_ASSERT_EQUAL_UINT16(111U, g_record.id_u16);
    TEST_ASSERT_EQUAL_UINT32(222333U, g_record.value_u32);
    TEST_ASSERT_TRUE(g_systemReady_b);
}
void test_SrcNull_AfterSuccessfulCall(void)
{
    MyLib_record_t dest1 = {0U, 0U};
    MyLib_record_t dest2 = {777U, 888999U};
    MyLib_record_t src = {111U, 222333U};

    MyLib_UpdateGlobalRecord(&dest1, &src);

    TEST_ASSERT_EQUAL_UINT16(111U, g_record.id_u16);
    TEST_ASSERT_EQUAL_UINT32(222333U, g_record.value_u32);
    TEST_ASSERT_TRUE(g_systemReady_b);

    MyLib_UpdateGlobalRecord(&dest2, NULL);

    TEST_ASSERT_EQUAL_UINT16(777U, dest2.id_u16);
    TEST_ASSERT_EQUAL_UINT32(888999U, dest2.value_u32);
    TEST_ASSERT_EQUAL_UINT16(111U, g_record.id_u16);
    TEST_ASSERT_EQUAL_UINT32(222333U, g_record.value_u32);
    TEST_ASSERT_TRUE(g_systemReady_b);
}
