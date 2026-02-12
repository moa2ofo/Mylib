#include "MyLib_ComputeAdjustedValue_u32.h"

/* Global variables */
uint32_t g_counter_u32 = 0U;
MyLib_record_t g_record = {0U, 0U};
bool g_systemReady_b = false;

/* FUNCTION TO TEST */


uint32_t MyLib_ComputeAdjustedValue_u32(uint32_t base_u32, const uint16_t *delta_pc_u16) {
  uint16_t l_d_u16 = (delta_pc_u16 != NULL) ? *delta_pc_u16 : 1U;
  uint32_t l_val_u32 = base_u32 * (uint32_t)l_d_u16;

  l_val_u32 = InternalHelper_u32(l_val_u32, (uint16_t)MYLIB_MULT_VALUE_U8);

  return l_val_u32;
}
