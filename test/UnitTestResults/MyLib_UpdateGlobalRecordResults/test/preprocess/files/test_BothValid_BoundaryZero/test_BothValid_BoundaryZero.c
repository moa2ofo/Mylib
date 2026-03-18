// CEEDLING NOTICE: This generated file only to be consumed for test runner creation

#include "mock_MyLib.h"
#include "utExecutionAndResults/utUnderTest/build/vendor/unity/src/unity.h"
#include "utExecutionAndResults/utUnderTest/src/MyLib_UpdateGlobalRecord.h"

void setUp(void) {
}

void tearDown(void) {
}

void test_BothValid_BoundaryZero(void) {
  MyLib_record_t dest = {999U, 999999U};
  MyLib_record_t src = {0U, 0U};

  MyLib_UpdateGlobalRecord(&dest, &src);

  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT16)((0U)), (UNITY_INT)(UNITY_UINT16)((dest.id_u16)), (((void *)0)), (UNITY_UINT)(17), UNITY_DISPLAY_STYLE_UINT16);
  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((0U)), (UNITY_INT)(UNITY_UINT32)((dest.value_u32)), (((void *)0)), (UNITY_UINT)(18), UNITY_DISPLAY_STYLE_UINT32);
  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT16)((0U)), (UNITY_INT)(UNITY_UINT16)((g_record.id_u16)), (((void *)0)), (UNITY_UINT)(19), UNITY_DISPLAY_STYLE_UINT16);
  UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT32)((0U)), (UNITY_INT)(UNITY_UINT32)((g_record.value_u32)), (((void *)0)), (UNITY_UINT)(20), UNITY_DISPLAY_STYLE_UINT32);
  do {
    if((g_systemReady_b)) {
    } else {
      UnityFail(((" Expected TRUE Was FALSE")), (UNITY_UINT)((21)));
    }
  } while(0);
}