#include "MyLib_UpdateGlobalRecord_help.h"

/* FUNCTION TO TEST */
void MyLib_UpdateGlobalRecord(MyLib_record_t *dest_p, const MyLib_record_t *src_pc) {
  /* Check for NULL pointers to avoid invalid memory access */
  if((dest_p == NULL) || (src_pc == NULL)) {
    return;
  }

  /* Copy the content from source to destination record */
  dest_p->id_u16 = src_pc->id_u16;
  dest_p->value_u32 = src_pc->value_u32;

  /* Update the global record to mirror the destination record */
  g_record = *dest_p;

  /* Mark the system as ready */
  g_systemReady_b = true;
}