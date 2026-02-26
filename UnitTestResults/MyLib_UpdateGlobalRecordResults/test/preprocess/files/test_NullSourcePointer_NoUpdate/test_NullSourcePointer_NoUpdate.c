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

void test_MyLib_UpdateGlobalRecord_NullSourcePointer_NoUpdate(void)
{
  MyLib_record_t destination = {0x5555U, 0xAAAAAAAAU};

  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT16)((0x5555U)), (UNITY_INT)(UNITY_UINT16)((destination.id_u16)), (
 ((void *)0)
 ), (UNITY_UINT)(31), UNITY_DISPLAY_STYLE_UINT16);
  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((0xAAAAAAAAU)), (UNITY_INT)(UNITY_UINT32)((destination.value_u32)), (
 ((void *)0)
 ), (UNITY_UINT)(32), UNITY_DISPLAY_STYLE_UINT32);
  do { if (!(g_systemReady_b))
{ } else { UnityFail( ((" Expected FALSE Was TRUE")), (UNITY_UINT)((33))); } } while (0);

  MyLib_UpdateGlobalRecord(&destination,
                                        ((void *)0)
                                            );

  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT16)((0x5555U)), (UNITY_INT)(UNITY_UINT16)((destination.id_u16)), (
 ((void *)0)
 ), (UNITY_UINT)(39), UNITY_DISPLAY_STYLE_UINT16);
  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((0xAAAAAAAAU)), (UNITY_INT)(UNITY_UINT32)((destination.value_u32)), (
 ((void *)0)
 ), (UNITY_UINT)(40), UNITY_DISPLAY_STYLE_UINT32);

  do { if (!(g_systemReady_b))
{ } else { UnityFail( ((" Expected FALSE Was TRUE")), (UNITY_UINT)((43))); } } while (0);
  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT16)((0U)), (UNITY_INT)(UNITY_UINT16)((g_record.id_u16)), (
 ((void *)0)
 ), (UNITY_UINT)(44), UNITY_DISPLAY_STYLE_UINT16);
  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((0U)), (UNITY_INT)(UNITY_UINT32)((g_record.value_u32)), (
 ((void *)0)
 ), (UNITY_UINT)(45), UNITY_DISPLAY_STYLE_UINT32);
}