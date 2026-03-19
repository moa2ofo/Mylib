#include "MyLib_UpdateCounter_u8_help.h"

/* FUNCTION TO TEST */
uint8_t MyLib_UpdateCounter_u8(uint32_t add_u32) {
  /* Function-local static cycle counter, persistent across calls */
  static uint32_t l_CycleCnt_u32 = 0U;

  uint32_t l_new_u32;
  uint8_t l_ret_u8;

  /* Step 1: Increment the function-static cycle counter */
  l_CycleCnt_u32++;

  /* Step 2: Check module readiness */
  if(g_systemReady_b == false) {
    /* System not ready, return error code 1 and perform no update */
    return 1U;
  }

  /* Step 3: Compute tentative new counter value */
  l_new_u32 = g_counter_u32 + add_u32;

  /* Step 4: Apply saturation if enabled */
  if((SaturationEn_b == true) && (l_new_u32 > CounterLimit_u32)) {
    /* Saturation condition met: clamp to limit */
    g_counter_u32 = CounterLimit_u32;
    l_ret_u8 = 2U;
  } else {
    /* No saturation: store new value */
    g_counter_u32 = l_new_u32;
    l_ret_u8 = 0U;
  }

  /* Step 5: Periodically toggle SaturationEn_b every 16 calls */
  if((l_CycleCnt_u32 & 0x0FU) == 0U) {
    SaturationEn_b = !SaturationEn_b;
  }

  /* Return status code */
  return l_ret_u8;
}