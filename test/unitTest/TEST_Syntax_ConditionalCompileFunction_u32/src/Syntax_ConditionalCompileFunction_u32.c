#include "Syntax_ConditionalCompileFunction_u32_help.h"

/* FUNCTION TO TEST */
uint32_t Syntax_ConditionalCompileFunction_u32(uint32_t value_u32) {
#if MYLIB_FEATURE_SCALE_FACTOR > 1
  value_u32 = value_u32 * MYLIB_FEATURE_SCALE_FACTOR;
#else
  value_u32 = value_u32 + 1U;
#endif

#ifdef MYLIB_ENABLE_SPECIAL_BRANCH
  value_u32 += MYLIB_SPECIAL_OFFSET_U32;
#else
  value_u32 -= MYLIB_SPECIAL_OFFSET_U32;
#endif

  return value_u32;
}