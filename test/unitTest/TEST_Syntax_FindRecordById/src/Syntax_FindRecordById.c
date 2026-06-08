#include "Syntax_FindRecordById_help.h"

/* FUNCTION TO TEST */
const MyLib_record_t *Syntax_FindRecordById(const MyLib_record_t *records_pc, uint32_t count_u32, uint16_t id_u16) {
  uint32_t l_i_u32;

  if(records_pc == NULL) {
    return NULL;
  }

  for(l_i_u32 = 0U; l_i_u32 < count_u32; l_i_u32++) {
    if(records_pc[l_i_u32].id_u16 == id_u16) {
      return &records_pc[l_i_u32];
    }
  }

  return NULL;
}