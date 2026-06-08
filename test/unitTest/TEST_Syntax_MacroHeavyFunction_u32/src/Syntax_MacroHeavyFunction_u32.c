#include "Syntax_MacroHeavyFunction_u32_help.h"

/* FUNCTION TO TEST */
uint32_t Syntax_MacroHeavyFunction_u32(uint32_t a_u32, uint32_t b_u32) {
  uint32_t l_value_u32 = MYLIB_SYNTAX_MULTILINE_SUM(a_u32, b_u32);

  if(l_value_u32 > MYLIB_SYNTAX_BASE_LIMIT_U32) {
    return (MYLIB_SYNTAX_BASE_LIMIT_U32 * 2U);
  }

  return (l_value_u32 * 2U);
}