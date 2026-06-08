#include "Syntax_ProcessRecordByValue_u32_help.h"

/* FUNCTION TO TEST */
uint32_t Syntax_ProcessRecordByValue_u32(MyLib_record_t record) {
  return ((uint32_t)record.id_u16) + record.value_u32;
}