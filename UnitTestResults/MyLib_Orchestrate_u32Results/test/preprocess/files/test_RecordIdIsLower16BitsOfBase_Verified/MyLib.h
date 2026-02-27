// CEEDLING NOTICE: This generated file only to be consumed by CMock

#ifndef _MYLIB_H_ // Ceedling-generated include guard
#define _MYLIB_H_

typedef struct {
  uint16_t id_u16;
  uint32_t value_u32;
} MyLib_record_t;

extern uint32_t g_counter_u32;
extern MyLib_record_t g_record;
extern
      _Bool
           g_systemReady_b;
void MyLib_ProcessRecord(const MyLib_record_t *rec_pc, uint8_t multiplier_u8);
uint32_t MyLib_ComputeAdjustedValue_u32(uint32_t base_u32, const uint16_t *delta_pc_u16);
uint32_t MyLib_AnalyzeArray_u32(uint16_t *values_pu16, size_t len_u32, uint16_t factor_u16);
void MyLib_UpdateGlobalRecord(MyLib_record_t *dest_p, const MyLib_record_t *src_pc);
static uint32_t InternalHelper_u32(uint32_t x_u32, uint16_t y_u16);
uint8_t MyLib_UpdateCounter_u8(uint32_t add_u32);

#endif // _MYLIB_H_
