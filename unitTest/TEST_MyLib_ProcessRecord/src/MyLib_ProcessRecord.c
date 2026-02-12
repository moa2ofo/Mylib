#include "MyLib_ProcessRecord.h"

/* Global variables */
uint32_t g_counter_u32 = 0U;
MyLib_record_t g_record = {0U, 0U};
bool g_systemReady_b = false;

/* FUNCTION TO TEST */


void MyLib_ProcessRecord(const MyLib_record_t *rec_pc, uint8_t multiplier_u8) {
  if(rec_pc == NULL) {
    return;
  }

  uint32_t l_acc_u32 = 0U;

  /* Fast paths / special cases for deterministic and efficient execution. */
  switch(multiplier_u8) {
  case 0U:
    /* No accumulation requested. */
    l_acc_u32 = 0U;
    break;

  case 1U:
    /* Single accumulation without loop overhead. */
    l_acc_u32 = rec_pc->value_u32;
    break;

  default:
    /* Bounded accumulation: wrap-around is acceptable by design. */
    for(uint8_t l_i_u8 = 0U; l_i_u8 < multiplier_u8; l_i_u8++) {
      l_acc_u32 += rec_pc->value_u32;
    }
    break;
  }

  g_counter_u32 += l_acc_u32;

  /* Call another function */
  (void)MyLib_ComputeAdjustedValue_u32(l_acc_u32, (const uint16_t *)&multiplier_u8);
}
