#include "MyLib_AnalyzeArray_u32.h"
#include <stddef.h>
#include <string.h>

/* FUNCTION TO TEST */


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
