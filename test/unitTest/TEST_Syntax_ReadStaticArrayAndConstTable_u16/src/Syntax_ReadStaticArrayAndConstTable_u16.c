#include "Syntax_ReadStaticArrayAndConstTable_u16_help.h"

/* FUNCTION TO TEST */
uint16_t Syntax_ReadStaticArrayAndConstTable_u16(uint8_t index_u8) {
  if(index_u8 < 3U) {
    return (uint16_t)(SyntaxStaticArray_au8[index_u8] + SyntaxConstTable_au16[index_u8]);
  }

  return 0U;
}