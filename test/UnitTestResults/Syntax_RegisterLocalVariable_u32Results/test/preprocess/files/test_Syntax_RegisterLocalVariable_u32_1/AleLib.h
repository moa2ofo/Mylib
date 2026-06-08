// CEEDLING NOTICE: This generated file only to be consumed by CMock

#ifndef _ALELIB_H_ // Ceedling-generated include guard
#define _ALELIB_H_

typedef struct {
  uint16_t id_u16;
  uint32_t value_u32;
} MyLib_record_t;

extern uint32_t g_counter_u32;
extern MyLib_record_t g_record;
extern
      _Bool
           g_systemReady_b;
void ProcessRecord(const MyLib_record_t *rec_pc, uint8_t multiplier_u8);
void MyLib_ProcessRecord(const MyLib_record_t *rec_pc, uint8_t multiplier_u8);
uint32_t MyLib_ComputeAdjustedValue_u32(uint32_t base_u32, const uint16_t *delta_pc_u16);
uint32_t MyLib_AnalyzeArray_u32(uint16_t *values_pu16, size_t len_u32, uint16_t factor_u16);
uint32_t AnalyzeArray_u32(uint16_t *values_pu16, size_t len_u32, uint16_t factor_u16);
void MyLib_UpdateGlobalRecord(MyLib_record_t *dest_p, const MyLib_record_t *src_pc);
uint32_t MyLib_Orchestrate_u32(uint32_t start_u32, const uint16_t *delta_pc_u16);
uint32_t InternalHelper_u32(uint32_t x_u32, uint16_t y_u16);
uint8_t MyLib_UpdateCounter_u8(uint32_t add_u32);
uint8_t UpdateCounter_u8(uint32_t add_u32);
uint8_t MyLib_RunStateMachine_u8(const MyLib_record_t *rec_pc, uint32_t add_u32, const uint16_t *delta_pc_u16);

typedef enum {
  MYLIB_SYNTAX_OK = 0U,
  MYLIB_SYNTAX_NOT_OK = 1U
} MyLib_SyntaxStatus_t;

typedef void (*MyLib_Callback_t)(uint8_t id_u8, uint32_t value_u32);
typedef uint32_t (*MyLib_Transform_t)(uint32_t value_u32);

typedef union {
  uint32_t raw_u32;
  struct {
    uint32_t low_u32 : 16;
    uint32_t high_u32 : 16;
  } bits;
} MyLib_PackedWord_t;

typedef enum {
  MYLIB_LOCAL_STATE_INIT = 0,
  MYLIB_LOCAL_STATE_READY = 1,
  MYLIB_LOCAL_STATE_ERROR = 2
} MyLib_LocalState_t;

typedef uint32_t MyLib_Vector3_u32[3];

uint32_t Syntax_InlineFunction_u32(uint32_t value_u32);

uint32_t
Syntax_MultilineReturnAndParams_u32(
  uint32_t a_u32,
  uint32_t b_u32,
  uint32_t c_u32
);

const MyLib_record_t *
Syntax_FindRecordById(
  const MyLib_record_t *records_pc,
  uint32_t count_u32,
  uint16_t id_u16
);

MyLib_SyntaxStatus_t Syntax_UpdateOutputPointer(uint32_t **out_ppu32, uint32_t *storage_pu32);

uint32_t Syntax_ConstPointerMix_u32(const uint32_t * const input_pcu32, uint32_t * const output_pu32);

uint32_t *Syntax_ReturnPointer(uint32_t *value_pu32);

uint32_t Syntax_ApplyTransform_u32(uint32_t value_u32, MyLib_Transform_t transform_pf);

void Syntax_NotifyWithCallback(uint8_t id_u8, uint32_t value_u32, void (*callback_pf)(uint8_t, uint32_t));

uint32_t Syntax_UseLocalFunctionPointer_u32(uint32_t value_u32);

uint32_t Syntax_SumFixedArray_u32(uint32_t values_au32[3]);

uint32_t Syntax_SumMatrix2x2_u32(uint32_t matrix_aau32[2][2]);

uint16_t Syntax_ReadStaticArrayAndConstTable_u16(uint8_t index_u8);

uint32_t Syntax_ProcessRecordByValue_u32(MyLib_record_t record);

uint32_t Syntax_ReadPackedHigh_u32(MyLib_PackedWord_t word);

MyLib_LocalState_t Syntax_AdvanceLocalState(
                                           _Bool
                                                error_b);

uint32_t Syntax_MacroHeavyFunction_u32(uint32_t a_u32, uint32_t b_u32);

uint32_t Syntax_CommentAndStringKeywords_u32(void);

uint32_t Syntax_ConditionalCompileFunction_u32(uint32_t value_u32);

uint32_t Syntax_SumVariadic_u32(uint32_t count_u32, ...);

uint32_t Syntax_NoInlineFunction_u32(uint32_t value_u32);

uint32_t Syntax_WeakFunction_u32(uint32_t value_u32);

uint32_t Syntax_ReadVectorElement_u32(uint8_t index_u8);

uint32_t Syntax_FunctionWithManyQualifiers_u32(volatile uint32_t * volatile value_pvu32,
                                               const volatile uint32_t * const reference_pcvu32);

uint32_t Syntax_ReusesMyLibServices_u32(MyLib_record_t *dest_p,
                                        const MyLib_record_t *src_pc,
                                        uint32_t add_u32);

#endif // _ALELIB_H_
