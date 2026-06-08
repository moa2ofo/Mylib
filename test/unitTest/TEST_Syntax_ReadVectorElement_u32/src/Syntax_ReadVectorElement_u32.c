#include "Syntax_ReadVectorElement_u32_help.h"

/* FUNCTION TO TEST */
uint32_t Syntax_ReadVectorElement_u32(uint8_t index_u8) {
  if(index_u8 >= 3U) {
    return 0U;
  }

  return SyntaxStaticVector[index_u8];
}