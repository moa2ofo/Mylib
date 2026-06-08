#include "Syntax_UpdateOutputPointer_help.h"

/* FUNCTION TO TEST */
MyLib_SyntaxStatus_t Syntax_UpdateOutputPointer(uint32_t **out_ppu32, uint32_t *storage_pu32) {
  if((out_ppu32 == NULL) || (storage_pu32 == NULL)) {
    return MYLIB_SYNTAX_NOT_OK;
  }

  *out_ppu32 = storage_pu32;
  return MYLIB_SYNTAX_OK;
}