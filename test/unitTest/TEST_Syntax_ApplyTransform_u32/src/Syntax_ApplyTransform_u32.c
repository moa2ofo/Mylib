#include "Syntax_ApplyTransform_u32_help.h"

/* FUNCTION TO TEST */
uint32_t Syntax_ApplyTransform_u32(uint32_t value_u32, MyLib_Transform_t transform_pf) {
  if(transform_pf == NULL) {
    return value_u32;
  }

  return transform_pf(value_u32);
}