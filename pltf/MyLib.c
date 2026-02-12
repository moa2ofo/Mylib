/* MyLib.c */

#include "MyLib.h"

/* Global variables */
uint32_t g_counter_u32 = 0U;
MyLib_record_t g_record = {0U, 0U};
bool g_systemReady_b = false;
static uint32_t CounterLimit_u32 = MYLIB_MAX_COUNT_U32;
static bool SaturationEn_b = true;

/* Local (c-file static) function */
static uint32_t InternalHelper_u32(uint32_t x_u32, uint16_t y_u16) {
  uint32_t l_acc_u32 = x_u32;

  /* Accumulate even-step sequence: for each l_i_u16 in [0 .. y_u16-1],
     add (l_i_u16 * 2) to l_acc_u32 */
  for (uint16_t l_i_u16 = 0U; l_i_u16 < y_u16; l_i_u16++) {
    l_acc_u32 += (uint32_t)(l_i_u16 * 2U);
  }

  return l_acc_u32;
}
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

uint32_t MyLib_ComputeAdjustedValue_u32(uint32_t base_u32, const uint16_t *delta_pc_u16) {
  uint16_t l_d_u16 = (delta_pc_u16 != NULL) ? *delta_pc_u16 : 1U;
  uint32_t l_val_u32 = base_u32 * (uint32_t)l_d_u16;

  l_val_u32 = InternalHelper_u32(l_val_u32, (uint16_t)MYLIB_MULT_VALUE_U8);

  return l_val_u32;
}
uint32_t MyLib_AnalyzeArray_u32(uint16_t *values_pu16, size_t len_u32, uint16_t factor_u16) {
  bool l_inNull_b = false;
  if((values_pu16 == NULL) || (len_u32 == 0U)) {
    l_inNull_b = true;
  }

  uint32_t l_sum_u32 = 0U;

  if(l_inNull_b == false) {
    for(size_t l_i_u32 = 0U; l_i_u32 < len_u32; l_i_u32++) {
      values_pu16[l_i_u32] = (uint16_t)(values_pu16[l_i_u32] * factor_u16);
      l_sum_u32 += values_pu16[l_i_u32];
    }

    /* Call another function */
    (void)MyLib_ComputeAdjustedValue_u32(l_sum_u32, NULL);
  }

  return l_sum_u32;
}

void MyLib_UpdateGlobalRecord(MyLib_record_t *dest_p, const MyLib_record_t *src_pc) {
  if ((dest_p == NULL) || (src_pc == NULL)) {
    return;
  }

  dest_p->id_u16 = src_pc->id_u16;
  dest_p->value_u32 = src_pc->value_u32;

  g_record = *dest_p;
  g_systemReady_b = true;
}
uint32_t MyLib_Orchestrate_u32(uint32_t start_u32, const uint16_t *delta_pc_u16) {
  uint16_t l_d_u16 = (delta_pc_u16 != NULL) ? *delta_pc_u16 : 0U;

  uint32_t l_base_u32 = InternalHelper_u32(start_u32, l_d_u16);

  MyLib_record_t l_r;
  l_r.id_u16 = (uint16_t)(l_base_u32 & 0xFFFFU);
  l_r.value_u32 = l_base_u32 / 2U;

  MyLib_ProcessRecord(&l_r, MYLIB_MULT_VALUE_U8);

  return (l_base_u32 + g_counter_u32);
}

uint8_t MyLib_UpdateCounter_u8(uint32_t add_u32) {
  /* Local (function-static) state: tracks how many times this API has been called. */
  static uint32_t l_CycleCnt_u32 = 0U;

  uint8_t l_ret_u8 = 0U;
  uint32_t l_new_u32 = 0U;

  l_CycleCnt_u32++;

  if(g_systemReady_b == false) {
    l_ret_u8 = 1U;
  } else {
    l_new_u32 = g_counter_u32 + add_u32;

    if((SaturationEn_b == true) && (l_new_u32 > CounterLimit_u32)) {
      g_counter_u32 = CounterLimit_u32;
      l_ret_u8 = 2U;
    } else {
      g_counter_u32 = l_new_u32;
      l_ret_u8 = 0U;
    }

    /* Periodically toggle saturation enable to exercise both internal static variables. */
    if((l_CycleCnt_u32 & 0x0FU) == 0U) {
      SaturationEn_b = (SaturationEn_b == true) ? false : true;
    }
  }

  return l_ret_u8;
}

int main() { return 0; }