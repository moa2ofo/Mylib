#include "MyLib_ComputeAdjustedValue_u32_help.h"

/* FUNCTION TO TEST */


uint32_t MyLib_ComputeAdjustedValue_u32(uint32_t base_u32, const uint16_t *delta_pc_u16) {
  uint16_t l_d_u16;
  uint32_t l_val_u32;

  /* Check if delta pointer is NULL and assign default or dereferenced value */
  if(delta_pc_u16 == NULL) {
    l_d_u16 = 1U;
  } else {
    l_d_u16 = *delta_pc_u16;
  }

  /* Multiply base by delta factor */
  l_val_u32 = base_u32 * l_d_u16;

  /* Apply internal post-processing step */
  /* NOTE: MYLIB_MULT_VALUE_U8 macro is not defined in the [HEADER] but is referenced in the activity diagram */
  l_val_u32 = InternalHelper_u32(l_val_u32, (uint16_t)MYLIB_MULT_VALUE_U8);

  return l_val_u32;
}
