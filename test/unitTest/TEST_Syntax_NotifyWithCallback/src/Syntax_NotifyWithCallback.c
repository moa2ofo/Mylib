#include "Syntax_NotifyWithCallback_help.h"

/* FUNCTION TO TEST */
void Syntax_NotifyWithCallback(uint8_t id_u8, uint32_t value_u32, void (*callback_pf)(uint8_t, uint32_t)) {
  if(callback_pf != NULL) {
    callback_pf(id_u8, value_u32);
  }
}