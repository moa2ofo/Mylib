#include "Syntax_SumVariadic_u32_help.h"

/* FUNCTION TO TEST */
uint32_t Syntax_SumVariadic_u32(uint32_t count_u32, ...) {
  va_list args;
  uint32_t l_i_u32;
  uint32_t l_sum_u32 = 0U;

  va_start(args, count_u32);

  for(l_i_u32 = 0U; l_i_u32 < count_u32; l_i_u32++) {
    l_sum_u32 += (uint32_t)va_arg(args, uint32_t);
  }

  va_end(args);

  return l_sum_u32;
}