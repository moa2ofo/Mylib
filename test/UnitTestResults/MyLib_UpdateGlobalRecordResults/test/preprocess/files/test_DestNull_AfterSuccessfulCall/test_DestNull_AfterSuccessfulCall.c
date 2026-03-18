// CEEDLING NOTICE: This generated file only to be consumed for test runner creation

#include "mock_MyLib.h"
#include "utExecutionAndResults/utUnderTest/build/vendor/unity/src/unity.h"
#include "utExecutionAndResults/utUnderTest/src/MyLib_UpdateGlobalRecord.h"

void setUp(void) {
}

void tearDown(void) {
}

void test_DestNull_AfterSuccessfulCall(void) {
  MyLib_record_t dest = {0U, 0U};
  MyLib_record_t src1 = {111U, 222333U};
  MyLib_record_t src2 = {444U, 555666U};

  MyLib_UpdateGlobalRecord(&dest, &src1);

  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT16)((111U)), (UNITY_INT)(UNITY_UINT16)((g_record.id_u16)), (((void *)0)), (UNITY_UINT)(18), UNITY_DISPLAY_STYLE_UINT16);
  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((222333U)), (UNITY_INT)(UNITY_UINT32)((g_record.value_u32)), (((void *)0)), (UNITY_UINT)(19), UNITY_DISPLAY_STYLE_UINT32);
  do {
    if((g_systemReady_b)) {
    } else {
      UnityFail(((" Expected TRUE Was FALSE")), (UNITY_UINT)((20)));
    }
  } while(0);

  MyLib_UpdateGlobalRecord(((void *)0), &src2);

  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT16)((111U)), (UNITY_INT)(UNITY_UINT16)((g_record.id_u16)), (((void *)0)), (UNITY_UINT)(24), UNITY_DISPLAY_STYLE_UINT16);
  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((222333U)), (UNITY_INT)(UNITY_UINT32)((g_record.value_u32)), (((void *)0)), (UNITY_UINT)(25), UNITY_DISPLAY_STYLE_UINT32);
  do {
    if((g_systemReady_b)) {
    } else {
      UnityFail(((" Expected TRUE Was FALSE")), (UNITY_UINT)((26)));
    }
  } while(0);
}