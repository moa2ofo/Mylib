#include "MyLib_ProcessRecord_help.h"

/* FUNCTION TO TEST */

void MyLib_ProcessRecord(const MyLib_record_t *rec_pc, uint8_t multiplier_u8) {
  uint32_t l_acc_u32;
  uint8_t l_i_u8;

  /* Check if input pointer is NULL */
  if(rec_pc == NULL) {
    return;
  }

  /* Switch-case structure for bounded accumulation based on multiplier_u8 */
  switch(multiplier_u8) {
  case 0U:
    /* No accumulation */
    l_acc_u32 = 0U;
    break;

  case 1U:
    /* Single direct assignment */
    l_acc_u32 = rec_pc->value_u32;
    break;

  default:
    /* Bounded loop accumulation */
    l_acc_u32 = 0U;
    for(l_i_u8 = 0U; l_i_u8 < multiplier_u8; l_i_u8++) {
      l_acc_u32 += rec_pc->value_u32;
    }
    break;
  }

  /* Increment global counter by accumulated value */
  g_counter_u32 += l_acc_u32;

  /* Invoke library function with accumulated value and multiplier address */
  (void)MyLib_ComputeAdjustedValue_u32(l_acc_u32, (const uint16_t *)&multiplier_u8);
}
