#include "MyLib_UpdateGlobalRecord.h"
#include <stddef.h>
#include <string.h>

/* non-static globals used by this function */
MyLib_record_t g_record = {0U, 0U};
bool g_systemReady_b = false;

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
