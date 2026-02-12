#include "MyLib_Orchestrate_u32.h"

/* Global variables */
uint32_t      g_counter_u32 = 0U;
MyLib_record_t g_record     = {0U, 0U};
bool          g_systemReady_b = false;

/* FUNCTION TO TEST */


uint32_t MyLib_Orchestrate_u32(uint32_t start_u32, const uint16_t *delta_pc_u16) {
  uint16_t l_d_u16 = (delta_pc_u16 != NULL) ? *delta_pc_u16 : 0U;

  uint32_t l_base_u32 = InternalHelper_u32(start_u32, l_d_u16);

  MyLib_record_t l_r;
  l_r.id_u16 = (uint16_t)(l_base_u32 & 0xFFFFU);
  l_r.value_u32 = l_base_u32 / 2U;

  MyLib_ProcessRecord(&l_r, MYLIB_MULT_VALUE_U8);

  return (l_base_u32 + g_counter_u32);
}
