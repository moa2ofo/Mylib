// CEEDLING NOTICE: This generated file only to be consumed for test runner creation

#include "utExecutionAndResults/utUnderTest/src/MyLib_UpdateGlobalRecord.h"
#include "utExecutionAndResults/utUnderTest/build/vendor/unity/src/unity.h"
#include "mock_MyLib.h"

void setUp(void)
{
  g_counter_u32 = 0U;
  g_record.id_u16 = 0U;
  g_record.value_u32 = 0U;
  g_systemReady_b =
                   0
}

void tearDown(void)
{
}

void test_MyLib_UpdateGlobalRecord_both_valid_mid_range_values_updates_correctly(void)
{
  MyLib_record_t dest = {0U, 0U};
  MyLib_record_t src = {32767U, 2147483647U};

  MyLib_UpdateGlobalRecord(&dest, &src);

  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT16)((32767U)), (UNITY_INT)(UNITY_UINT16)((dest.id_u16)), (
 ((void *)0)
 ), (UNITY_UINT)(26), UNITY_DISPLAY_STYLE_UINT16);
  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((2147483647U)), (UNITY_INT)(UNITY_UINT32)((dest.value_u32)), (
 ((void *)0)
 ), (UNITY_UINT)(27), UNITY_DISPLAY_STYLE_UINT32);
  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT16)((32767U)), (UNITY_INT)(UNITY_UINT16)((g_record.id_u16)), (
 ((void *)0)
 ), (UNITY_UINT)(28), UNITY_DISPLAY_STYLE_UINT16);
  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((2147483647U)), (UNITY_INT)(UNITY_UINT32)((g_record.value_u32)), (
 ((void *)0)
 ), (UNITY_UINT)(29), UNITY_DISPLAY_STYLE_UINT32);
  do { if ((g_systemReady_b))
{ } else { UnityFail( ((" Expected TRUE Was FALSE")), (UNITY_UINT)((30))); } } while (0);
}