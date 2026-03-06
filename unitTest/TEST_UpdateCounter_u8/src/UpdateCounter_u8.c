#include "UpdateCounter_u8.h"
#include <stddef.h>
#include <string.h>

/* all non-static globals from this TU (real definitions) */
uint32_t g_counter_u32 = 0U;
MyLib_record_t g_record = {0U, 0U};
bool g_systemReady_b = false;

/* static globals (copied) */
 uint32_t CounterLimit_u32 = MYLIB_MAX_COUNT_U32;
uint32_t get_CounterLimit_u32(void) { return CounterLimit_u32; }
void set_CounterLimit_u32(uint32_t val) { CounterLimit_u32 = val; }
 bool SaturationEn_b = true;
_Bool get_SaturationEn_b(void) { return SaturationEn_b; }
void set_SaturationEn_b(_Bool val) { SaturationEn_b = val; }

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
