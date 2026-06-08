#include "Syntax_ReadPackedHigh_u32_help.h"

/* FUNCTION TO TEST */
uint32_t Syntax_ReadPackedHigh_u32(MyLib_PackedWord_t word) {
  return word.bits.high_u32;
}