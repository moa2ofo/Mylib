#include "InternalHelper_u32.h"

/* Global variables */
uint32_t g_counter_u32 = 0U;
MyLib_record_t g_record = {0U, 0U};
bool g_systemReady_b = false;
static uint32_t CounterLimit_u32 = MYLIB_MAX_COUNT_U32;
static bool SaturationEn_b = true;

/* FUNCTION TO TEST */


uint32_t InternalHelper_u32(uint32_t x_u32, uint16_t y_u16) {
  uint32_t l_acc_u32 = x_u32;

  /* Accumulate even-step sequence: for each l_i_u16 in [0 .. y_u16-1],
     add (l_i_u16 * 2) to l_acc_u32 */
  for(uint16_t l_i_u16 = 0U; l_i_u16 < y_u16; l_i_u16++) {
    l_acc_u32 += (uint32_t)(l_i_u16 * 2U);
  }
  return l_acc_u32;
}
