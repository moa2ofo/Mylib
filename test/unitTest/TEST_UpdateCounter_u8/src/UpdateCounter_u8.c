#include "UpdateCounter_u8_help.h"

/* FUNCTION TO TEST */
uint8_t UpdateCounter_u8(uint32_t add_u32) {
  /*
   * Syntax edge case:
   * This wrapper intentionally reuses the MyLib-prefixed implementation.
   */
  return MyLib_UpdateCounter_u8(add_u32);
}