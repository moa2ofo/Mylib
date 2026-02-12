#include "MyLib_UpdateGlobalRecord.h"

/* Global variables */
uint32_t g_counter_u32 = 0U;
MyLib_record_t g_record = {0U, 0U};
bool g_systemReady_b = false;

/* FUNCTION TO TEST */


void MyLib_UpdateGlobalRecord(MyLib_record_t *dest_p, const MyLib_record_t *src_pc) {
  if((dest_p == NULL) || (src_pc == NULL)) {
    return;
  }

  dest_p->id_u16 = src_pc->id_u16;
  dest_p->value_u32 = src_pc->value_u32;

  g_record = *dest_p;
  g_systemReady_b = true;
}
