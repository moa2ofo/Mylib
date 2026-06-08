#include "Syntax_ConstPointerMix_u32_help.h"

/* FUNCTION TO TEST */
uint32_t Syntax_ConstPointerMix_u32(const uint32_t *const input_pcu32, uint32_t *const output_pu32) {
  if((input_pcu32 == NULL) || (output_pu32 == NULL)) {
    return 0U;
  }

  *output_pu32 = *input_pcu32 + 10U;
  return *output_pu32;
}