#include "MyLib_AnalyzeArray_u32.h"
#include <stddef.h>
#include <string.h>

/* all non- globals from this TU (real definitions) */
uint32_t g_counter_u32 = 0U;
MyLib_record_t g_record = {0U, 0U};
bool g_systemReady_b = false;

/* FUNCTION TO TEST */


uint32_t MyLib_AnalyzeArray_u32(uint16_t *values_pu16, size_t len_u32, uint16_t factor_u16) {
  /* Check for NULL pointer or zero length input */
  if((values_pu16 == NULL) || (len_u32 == 0U)) {
    return 0U;
  }

  uint32_t l_sum_u32 = 0U;

  for(size_t l_i_u32 = 0U; l_i_u32 < len_u32; l_i_u32++) {
    values_pu16[l_i_u32] = (uint16_t)(values_pu16[l_i_u32] * factor_u16);
    l_sum_u32 += values_pu16[l_i_u32];
  }

  /* Invoke deterministic secondary computation; return value not used as per header */
  (void)MyLib_ComputeAdjustedValue_u32(l_sum_u32, NULL);

  return l_sum_u32;
}
