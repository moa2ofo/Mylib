#include "MyLib_RunStateMachine_u8.h"
#include <stddef.h>
#include <string.h>

/* all non- globals from this TU (real definitions) */
uint32_t g_counter_u32 = 0U;
MyLib_record_t g_record = {0U, 0U};
bool g_systemReady_b = false;

/* FUNCTION TO TEST */


uint8_t MyLib_RunStateMachine_u8(const MyLib_record_t *rec_pc, uint32_t add_u32, const uint16_t *delta_pc_u16) {
  /* Function-static state variables preserve the state machine context. */
  static uint8_t l_State_u8 = 0U;
  static MyLib_record_t l_LastRecord = {0U, 0U};
  static uint32_t l_LastAdjusted_u32 = 0U;

  uint8_t l_ret_u8 = 0U;
  uint32_t l_UpdateValue_u32 = 0U;

  switch(l_State_u8) {
  case 0U:
    if(rec_pc == NULL) {
      l_ret_u8 = 1U;
    } else {
      MyLib_UpdateGlobalRecord(&l_LastRecord, rec_pc);
      l_State_u8 = 1U;
      l_ret_u8 = 0U;
    }
    break;

  case 1U:
    MyLib_ProcessRecord(&l_LastRecord, MYLIB_MULT_VALUE_U8);
    l_LastAdjusted_u32 = MyLib_ComputeAdjustedValue_u32(l_LastRecord.value_u32, delta_pc_u16);
    l_State_u8 = 2U;
    l_ret_u8 = 0U;
    break;

  case 2U:
    l_UpdateValue_u32 = add_u32 + l_LastAdjusted_u32;
    l_ret_u8 = MyLib_UpdateCounter_u8(l_UpdateValue_u32);
    l_State_u8 = 0U;
    break;

  default:
    l_State_u8 = 0U;
    l_LastAdjusted_u32 = 0U;
    l_ret_u8 = 3U;
    break;
  }

  return l_ret_u8;
}
