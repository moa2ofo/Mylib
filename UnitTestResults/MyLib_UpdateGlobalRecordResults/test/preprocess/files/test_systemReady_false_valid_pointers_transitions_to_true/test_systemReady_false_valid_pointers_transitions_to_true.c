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

void test_MyLib_UpdateGlobalRecord_systemReady_false_valid_pointers_transitions_to_true(void)
{
  MyLib_record_t dest = {0U, 0U};
  MyLib_record_t src = {300U, 7000U};

  g_systemReady_b =
                   

  MyLib_UpdateGlobalRecord(&dest, &src);

  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT16)((300U)), (UNITY_INT)(UNITY_UINT16)((dest.id_u16)), (
 ((void *)0)
 ), (UNITY_UINT)(33), UNITY_DISPLAY_STYLE_UINT16);
  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((7000U)), (UNITY_INT)(UNITY_UINT32)((dest.value_u32)), (
 ((void *)0)
 ), (UNITY_UINT)(34), UNITY_DISPLAY_STYLE_UINT32);
  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT16)((300U)), (UNITY_INT)(UNITY_UINT16)((g_record.id_u16)), (
 ((void *)0)
 ), (UNITY_UINT)(35), UNITY_DISPLAY_STYLE_UINT16);
  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((7000U)), (UNITY_INT)(UNITY_UINT32)((g_record.value_u32)), (
 ((void *)0)
 ), (UNITY_UINT)(36), UNITY_DISPLAY_STYLE_UINT32);
  do { if ((g_systemReady_b))
{ } else { UnityFail( ((" Expected TRUE Was FALSE")), (UNITY_UINT)((37))); } } while (0);
}