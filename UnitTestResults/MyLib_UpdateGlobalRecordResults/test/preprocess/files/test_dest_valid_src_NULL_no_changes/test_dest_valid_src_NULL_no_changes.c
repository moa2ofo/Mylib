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

void test_MyLib_UpdateGlobalRecord_dest_valid_src_NULL_no_changes(void)
{
  MyLib_record_t dest = {999U, 888U};

  MyLib_UpdateGlobalRecord(&dest,
                                 ((void *)0)
                                     );

  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT16)((999U)), (UNITY_INT)(UNITY_UINT16)((dest.id_u16)), (
 ((void *)0)
 ), (UNITY_UINT)(30), UNITY_DISPLAY_STYLE_UINT16);
  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((888U)), (UNITY_INT)(UNITY_UINT32)((dest.value_u32)), (
 ((void *)0)
 ), (UNITY_UINT)(31), UNITY_DISPLAY_STYLE_UINT32);
  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT16)((0U)), (UNITY_INT)(UNITY_UINT16)((g_record.id_u16)), (
 ((void *)0)
 ), (UNITY_UINT)(32), UNITY_DISPLAY_STYLE_UINT16);
  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((0U)), (UNITY_INT)(UNITY_UINT32)((g_record.value_u32)), (
 ((void *)0)
 ), (UNITY_UINT)(33), UNITY_DISPLAY_STYLE_UINT32);
  do { if (!(g_systemReady_b))
{ } else { UnityFail( ((" Expected FALSE Was TRUE")), (UNITY_UINT)((34))); } } while (0);
}