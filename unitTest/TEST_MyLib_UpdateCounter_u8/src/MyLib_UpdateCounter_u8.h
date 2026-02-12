#ifndef MYLIB_UPDATECOUNTER_U8_H
#define MYLIB_UPDATECOUNTER_U8_H

#include "MyLib.h"


uint32_t GetCounterLimit_u32(void);
void     SetCounterLimit_u32(uint32_t value);

bool GetSaturationEn_b(void);
void SetSaturationEn_b(bool enable);


uint8_t MyLib_UpdateCounter_u8(uint32_t add_u32);

#endif
