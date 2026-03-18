// CEEDLING NOTICE: This generated file only to be consumed for test runner creation

#include "mock_MyLib.h"
#include "utExecutionAndResults/utUnderTest/build/vendor/unity/src/unity.h"
#include "utExecutionAndResults/utUnderTest/src/MyLib_UpdateGlobalRecord.h"

void setUp(void) {
}

void tearDown(void) {
}

void test_SrcNull_AfterSuccessfulCall(void) {
  MyLib_record_t dest1 = {0U, 0U};
  MyLib_record_t dest2 = {777U, 888999U};
  MyLib_record_t src = {111U, 222333U};

  MyLib_UpdateGlobalRecord(&dest1, &src);

  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT16)((111U)), (UNITY_INT)(UNITY_UINT16)((g_record.id_u16)), (((void *)0)), (UNITY_UINT)(18), UNITY_DISPLAY_STYLE_UINT16);
  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((222333U)), (UNITY_INT)(UNITY_UINT32)((g_record.value_u32)), (((void *)0)), (UNITY_UINT)(19), UNITY_DISPLAY_STYLE_UINT32);
  do {
    if((g_systemReady_b)) {
    } else {
      UnityFail(((" Expected TRUE Was FALSE")), (UNITY_UINT)((20)));
    }
  } while(0);

  MyLib_UpdateGlobalRecord(&dest2, ((void *)0));

  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT16)((777U)), (UNITY_INT)(UNITY_UINT16)((dest2.id_u16)), (((void *)0)), (UNITY_UINT)(24), UNITY_DISPLAY_STYLE_UINT16);
  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((888999U)), (UNITY_INT)(UNITY_UINT32)((dest2.value_u32)), (((void *)0)), (UNITY_UINT)(25), UNITY_DISPLAY_STYLE_UINT32);
  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT16)((111U)), (UNITY_INT)(UNITY_UINT16)((g_record.id_u16)), (((void *)0)), (UNITY_UINT)(26), UNITY_DISPLAY_STYLE_UINT16);
  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((222333U)), (UNITY_INT)(UNITY_UINT32)((g_record.value_u32)), (((void *)0)), (UNITY_UINT)(27), UNITY_DISPLAY_STYLE_UINT32);
  do {
    if((g_systemReady_b)) {
    } else {
      UnityFail(((" Expected TRUE Was FALSE")), (UNITY_UINT)((28)));
    }
  } while(0);
}