#include "ProcessRecord_help.h"

/* FUNCTION TO TEST */
void ProcessRecord(const MyLib_record_t *rec_pc, uint8_t multiplier_u8) {
  /*
   * Syntax edge case:
   * This public wrapper reuses another function from the same library.
   * It is useful to verify that the generator detects intra-library calls.
   */
  MyLib_ProcessRecord(rec_pc, multiplier_u8);
}