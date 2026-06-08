#include "MyLib_Orchestrate_u32_help.h"

/* FUNCTION TO TEST */
uint32_t MyLib_Orchestrate_u32(uint32_t start_u32, const uint16_t *delta_pc_u16) {
  uint16_t l_d_u16;
  uint32_t l_base_u32;
  MyLib_record_t l_r;

  /* Check if delta_pc_u16 is NULL and set l_d_u16 accordingly */
  if(delta_pc_u16 == NULL) {
    l_d_u16 = 0U;
  } else {
    l_d_u16 = *delta_pc_u16;
  }

  /* Compute base using internal helper */
  l_base_u32 = InternalHelper_u32(start_u32, l_d_u16);

  /* Build temporary record derived from the base */
  l_r.id_u16 = (uint16_t)(l_base_u32 & 0xFFFFU);
  l_r.value_u32 = l_base_u32 / 2U;

  /* Process the record via MyLib_ProcessRecord */
  MyLib_ProcessRecord(&l_r, MYLIB_MULT_VALUE_U8);

  /* Return combined result: base plus global counter */
  return (l_base_u32 + g_counter_u32);
}