#include "AnalyzeArray_u32_help.h"

/* FUNCTION TO TEST */
uint32_t AnalyzeArray_u32(uint16_t *values_pu16, size_t len_u32, uint16_t factor_u16) {
  /*
   * Syntax edge case:
   * This wrapper intentionally reuses the MyLib-prefixed implementation.
   */
  return MyLib_AnalyzeArray_u32(values_pu16, len_u32, factor_u16);
}