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

void test_MyLib_UpdateGlobalRecord_EdgeCaseZeroValues_UpdatesCorrectly(void)
{
  MyLib_record_t source = {0U, 0U};
  MyLib_record_t destination = {0xFFFFU, 0xFFFFFFFFU};

  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT16)((0xFFFFU)), (UNITY_INT)(UNITY_UINT16)((destination.id_u16)), (
 ((void *)0)
 ), (UNITY_UINT)(32), UNITY_DISPLAY_STYLE_UINT16);
  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((0xFFFFFFFFU)), (UNITY_INT)(UNITY_UINT32)((destination.value_u32)), (
 ((void *)0)
 ), (UNITY_UINT)(33), UNITY_DISPLAY_STYLE_UINT32);

  MyLib_UpdateGlobalRecord(&destination, &source);

  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT16)((0U)), (UNITY_INT)(UNITY_UINT16)((destination.id_u16)), (
 ((void *)0)
 ), (UNITY_UINT)(39), UNITY_DISPLAY_STYLE_UINT16);
  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((0U)), (UNITY_INT)(UNITY_UINT32)((destination.value_u32)), (
 ((void *)0)
 ), (UNITY_UINT)(40), UNITY_DISPLAY_STYLE_UINT32);
  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT16)((0U)), (UNITY_INT)(UNITY_UINT16)((g_record.id_u16)), (
 ((void *)0)
 ), (UNITY_UINT)(41), UNITY_DISPLAY_STYLE_UINT16);
  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((0U)), (UNITY_INT)(UNITY_UINT32)((g_record.value_u32)), (
 ((void *)0)
 ), (UNITY_UINT)(42), UNITY_DISPLAY_STYLE_UINT32);
  do { if ((g_systemReady_b))
{ } else { UnityFail( ((" Expected TRUE Was FALSE")), (UNITY_UINT)((43))); } } while (0);
}