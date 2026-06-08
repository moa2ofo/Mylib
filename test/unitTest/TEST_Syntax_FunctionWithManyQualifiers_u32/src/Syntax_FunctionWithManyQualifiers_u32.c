#include "Syntax_FunctionWithManyQualifiers_u32_help.h"

/* FUNCTION TO TEST */
uint32_t Syntax_FunctionWithManyQualifiers_u32(volatile uint32_t * volatile value_pvu32,
                                               const volatile uint32_t * const reference_pcvu32) {
  if((value_pvu32 == NULL) || (reference_pcvu32 == NULL)) {
    return 0U;
  }

  *value_pvu32 = *reference_pcvu32;
  return *value_pvu32;
}