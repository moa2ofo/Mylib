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

void test_MyLib_UpdateGlobalRecord_called_twice_second_call_overwrites_correctly(void)
{
  MyLib_record_t dest = {0U, 0U};
  MyLib_record_t src1 = {100U, 5000U};
  MyLib_record_t src2 = {200U, 10000U};

  MyLib_UpdateGlobalRecord(&dest, &src1);

  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT16)((100U)), (UNITY_INT)(UNITY_UINT16)((dest.id_u16)), (
 ((void *)0)
 ), (UNITY_UINT)(32), UNITY_DISPLAY_STYLE_UINT16);
  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((5000U)), (UNITY_INT)(UNITY_UINT32)((dest.value_u32)), (
 ((void *)0)
 ), (UNITY_UINT)(33), UNITY_DISPLAY_STYLE_UINT32);
  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT16)((100U)), (UNITY_INT)(UNITY_UINT16)((g_record.id_u16)), (
 ((void *)0)
 ), (UNITY_UINT)(34), UNITY_DISPLAY_STYLE_UINT16);
  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((5000U)), (UNITY_INT)(UNITY_UINT32)((g_record.value_u32)), (
 ((void *)0)
 ), (UNITY_UINT)(35), UNITY_DISPLAY_STYLE_UINT32);
  do { if ((g_systemReady_b))
{ } else { UnityFail( ((" Expected TRUE Was FALSE")), (UNITY_UINT)((36))); } } while (0);

  MyLib_UpdateGlobalRecord(&dest, &src2);

  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT16)((200U)), (UNITY_INT)(UNITY_UINT16)((dest.id_u16)), (
 ((void *)0)
 ), (UNITY_UINT)(40), UNITY_DISPLAY_STYLE_UINT16);
  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((10000U)), (UNITY_INT)(UNITY_UINT32)((dest.value_u32)), (
 ((void *)0)
 ), (UNITY_UINT)(41), UNITY_DISPLAY_STYLE_UINT32);
  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT16)((200U)), (UNITY_INT)(UNITY_UINT16)((g_record.id_u16)), (
 ((void *)0)
 ), (UNITY_UINT)(42), UNITY_DISPLAY_STYLE_UINT16);
  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((10000U)), (UNITY_INT)(UNITY_UINT32)((g_record.value_u32)), (
 ((void *)0)
 ), (UNITY_UINT)(43), UNITY_DISPLAY_STYLE_UINT32);
  do { if ((g_systemReady_b))
{ } else { UnityFail( ((" Expected TRUE Was FALSE")), (UNITY_UINT)((44))); } } while (0);
}