#include "MyLib_UpdateCounter_u8.h"

/* Global variables */
uint32_t g_counter_u32 = 0U;
MyLib_record_t g_record = {0U, 0U};
bool g_systemReady_b = false;
static uint32_t CounterLimit_u32 = MYLIB_MAX_COUNT_U32;
static bool SaturationEn_b = true;

uint32_t GetCounterLimit_u32(void) {
  return CounterLimit_u32;
}

void SetCounterLimit_u32(uint32_t value) {
  CounterLimit_u32 = value;
}

bool GetSaturationEn_b(void) {
  return SaturationEn_b;
}

void SetSaturationEn_b(bool enable) {
  SaturationEn_b = enable;
}

/* FUNCTION TO TEST */


uint8_t MyLib_UpdateCounter_u8(uint32_t add_u32) {
  /* Local (function-static) state: tracks how many times this API has been called. */
  static uint32_t l_CycleCnt_u32 = 0U;

  uint8_t l_ret_u8 = 0U;
  uint32_t l_new_u32 = 0U;

  l_CycleCnt_u32++;

  if(g_systemReady_b == false) {
    l_ret_u8 = 1U;
  } else {
    l_new_u32 = g_counter_u32 + add_u32;

    if((SaturationEn_b == true) && (l_new_u32 > CounterLimit_u32)) {
      g_counter_u32 = CounterLimit_u32;
      l_ret_u8 = 2U;
    } else {
      g_counter_u32 = l_new_u32;
      l_ret_u8 = 0U;
    }

    /* Periodically toggle saturation enable to exercise both internal static variables. */
    if((l_CycleCnt_u32 & 0x0FU) == 0U) {
      SaturationEn_b = (SaturationEn_b == true) ? false : true;
    }
  }

  return l_ret_u8;
}
