// CEEDLING NOTICE: This generated file only to be consumed for test runner creation

#include "mock_MyLib.h"
#include "utExecutionAndResults/utUnderTest/build/vendor/unity/src/unity.h"
#include "utExecutionAndResults/utUnderTest/src/MyLib.h"
#include "utExecutionAndResults/utUnderTest/src/MyLib_UpdateCounter_u8.h"

void setUp(void) {
}

void tearDown(void) {
}

void test_cycle_counter_increments_on_not_ready(void) {
  uint8_t i;

  _Bool initial_sat;

  _Bool final_sat;

  g_systemReady_b = 0

      g_counter_u32 = 0U;
  set_SaturationEn_b(0);

  initial_sat = get_SaturationEn_b();

  for(i = 0U; i < 16U; i++) {
    MyLib_UpdateCounter_u8(1U);
  }

  final_sat = get_SaturationEn_b();

  do {
    if(((initial_sat) != (final_sat))) {
    } else {
      UnityFail(((" Expected Not-Equal")), (UNITY_UINT)((30)));
    }
  } while(0);
}