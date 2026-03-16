#include "MyLib_RunStateMachine_u8_help.h"

/* FUNCTION TO TEST */


uint8_t MyLib_RunStateMachine_u8(const MyLib_record_t *rec_pc, uint32_t add_u32, const uint16_t *delta_pc_u16) {
  /* Function-local static variables to preserve state machine context across calls */
  static uint8_t l_State_u8 = 0U;
  static MyLib_record_t l_LastRecord;
  static uint32_t l_LastAdjusted_u32 = 0U;

  /* Local variables */
  uint8_t l_ret_u8 = 0U;
  uint32_t l_UpdateValue_u32 = 0U;

  /* State machine execution */
  switch(l_State_u8) {
  case 0U: /* Init state */
    if(rec_pc == NULL) {
      l_ret_u8 = 1U;
    } else {
      MyLib_UpdateGlobalRecord(&l_LastRecord, rec_pc);
      l_State_u8 = 1U;
      l_ret_u8 = 0U;
    }
    break;

  case 1U: /* Process state */
    MyLib_ProcessRecord(&l_LastRecord, MYLIB_MULT_VALUE_U8);
    l_LastAdjusted_u32 = MyLib_ComputeAdjustedValue_u32(l_LastRecord.value_u32, delta_pc_u16);
    l_State_u8 = 2U;
    l_ret_u8 = 0U;
    break;

  case 2U: /* Update counter state */
    l_UpdateValue_u32 = add_u32 + l_LastAdjusted_u32;
    l_ret_u8 = MyLib_UpdateCounter_u8(l_UpdateValue_u32);
    l_State_u8 = 0U;
    break;

  default:
    /* Defensive: should not occur if state machine is correctly managed */
    l_ret_u8 = 0U;
    break;
  }

  return l_ret_u8;
}
