#include "UpdateCounter_u8_help.h"

/* FUNCTION TO TEST */
uint8_t UpdateCounter_u8(uint32_t add_u32) {
  static uint32_t l_CycleCnt_u32 = 0u;
  uint32_t l_new_u32;
  uint8_t l_ret_u8;

  l_CycleCnt_u32++;

  if(g_systemReady_b == false) {
    return 1u;
  }

  l_new_u32 = g_counter_u32 + add_u32;

  if((SaturationEn_b == true) && (l_new_u32 > CounterLimit_u32)) {
    g_counter_u32 = CounterLimit_u32;
    l_ret_u8 = 2u;
  } else {
    g_counter_u32 = l_new_u32;
    l_ret_u8 = 0u;
  }

  if((l_CycleCnt_u32 & 0x0Fu) == 0u) {
    SaturationEn_b = !SaturationEn_b;
  }
  return l_ret_u8;
}