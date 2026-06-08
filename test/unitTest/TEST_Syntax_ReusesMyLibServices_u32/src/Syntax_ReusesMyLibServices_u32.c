#include "Syntax_ReusesMyLibServices_u32_help.h"

/* FUNCTION TO TEST */
uint32_t Syntax_ReusesMyLibServices_u32(MyLib_record_t *dest_p, const MyLib_record_t *src_pc, uint32_t add_u32) {
  MyLib_UpdateGlobalRecord(dest_p, src_pc);

  if(g_systemReady_b == false) {
    return 0U;
  }

  (void)MyLib_UpdateCounter_u8(add_u32);

  return MyLib_Orchestrate_u32(add_u32, NULL);
}