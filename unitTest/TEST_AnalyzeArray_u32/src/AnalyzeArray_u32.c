#include "AnalyzeArray_u32_help.h"

/* FUNCTION TO TEST */
uint32_t AnalyzeArray_u32(uint16_t *values_pu16, size_t len_u32, uint16_t factor_u16) {
  uint32_t l_sum_u32 = 0U;
  uint32_t l_i_u32;
  uint8_t l_inNull_b = 0U;

  /* Check for NULL pointer or zero length */
  if((values_pu16 == NULL) || (len_u32 == 0U)) {
    l_inNull_b = 1U;
  }

  if(l_inNull_b == 0U) {
    for(l_i_u32 = 0U; l_i_u32 < len_u32; l_i_u32++) {
      /* Scale each element in-place */
      values_pu16[l_i_u32] = (uint16_t)(values_pu16[l_i_u32] * factor_u16);
      /* Accumulate the sum of scaled elements */
      l_sum_u32 += values_pu16[l_i_u32];
    }

    /* Call internal adjustment function with NULL pointer as per header */
    l_sum_u32 = MyLib_ComputeAdjustedValue_u32(l_sum_u32, NULL);
  }

  return l_sum_u32;
}