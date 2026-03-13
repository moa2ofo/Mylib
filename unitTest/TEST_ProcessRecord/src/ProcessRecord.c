#include "ProcessRecord_help.h"

/* FUNCTION TO TEST */


void ProcessRecord(const MyLib_record_t *rec_pc, uint8_t multiplier_u8) {
  uint32_t l_acc_u32 = 0U;

  if(rec_pc == NULL) {
    return;
  }

  switch(multiplier_u8) {
  case 0U:
    l_acc_u32 = 0U;
    break;
  case 1U:
    l_acc_u32 = rec_pc->value_u32;
    break;
  default:
    for(uint8_t l_i_u8 = 0U; l_i_u8 < multiplier_u8; l_i_u8++) {
      l_acc_u32 += rec_pc->value_u32;
    }
    break;
  }

  g_counter_u32 += l_acc_u32;

  /*
   * Call MyLib_ComputeAdjustedValue_u32 with l_acc_u32 and pointer to multiplier_u8
   * Cast multiplier_u8 pointer to const uint16_t* as required by the interface
   * This cast is safe because the function expects a pointer to uint16_t,
   * but multiplier_u8 is uint8_t, so we rely on the header specification.
   * If this is incorrect, the header is inconsistent.
   */
  (void)MyLib_ComputeAdjustedValue_u32(l_acc_u32, (const uint16_t *)&multiplier_u8);
}
