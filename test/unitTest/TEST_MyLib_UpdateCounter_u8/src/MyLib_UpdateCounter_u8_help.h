#ifndef TEST_MYLIB_UPDATECOUNTER_U8_HELP_H
#define TEST_MYLIB_UPDATECOUNTER_U8_HELP_H

#include "MyLib_UpdateCounter_u8.h"
#include <stddef.h>
#include <string.h>

/* non-static globals used by this function */
uint32_t g_counter_u32 = 0U;
bool g_systemReady_b = false;

/* static globals (copied) */
static uint32_t CounterLimit_u32 = MYLIB_MAX_COUNT_U32;
uint32_t get_CounterLimit_u32(void) { return CounterLimit_u32; }
void set_CounterLimit_u32(uint32_t val) { CounterLimit_u32 = val; }
static bool SaturationEn_b = true;
_Bool get_SaturationEn_b(void) { return SaturationEn_b; }
void set_SaturationEn_b(_Bool val) { SaturationEn_b = val; }

#endif /* TEST_MYLIB_UPDATECOUNTER_U8_HELP_H */
