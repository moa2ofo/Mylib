#include "MyLib_UpdateCounter_u8_help.h"

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

    /* Periodically toggle saturation enable every 16 calls. */
    if((l_CycleCnt_u32 & 0x0FU) == 0U) {
      SaturationEn_b = !SaturationEn_b;
    }
  }

  return l_ret_u8;
}
