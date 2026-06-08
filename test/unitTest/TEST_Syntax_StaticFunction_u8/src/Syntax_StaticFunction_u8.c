#include "Syntax_StaticFunction_u8_help.h"

/* FUNCTION TO TEST */
uint8_t Syntax_StaticFunction_u8(uint8_t value_u8) {
  SyntaxStaticCounter_u8 += value_u8;
  return SyntaxStaticCounter_u8;
}