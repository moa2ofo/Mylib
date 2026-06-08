#include "Syntax_SumMatrix2x2_u32_help.h"

/* FUNCTION TO TEST */
uint32_t Syntax_SumMatrix2x2_u32(uint32_t matrix_aau32[2][2]) {
  return matrix_aau32[0][0] + matrix_aau32[0][1] + matrix_aau32[1][0] + matrix_aau32[1][1];
}