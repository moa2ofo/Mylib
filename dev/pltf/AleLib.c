/* MyLib.c */

#include "MyLib.h"

/* Global variables */
uint32_t g_counter_u32 = 0U;
MyLib_record_t g_record = {0U, 0U};
bool g_systemReady_b = false;
static uint32_t CounterLimit_u32 = MYLIB_MAX_COUNT_U32;
static bool SaturationEn_b = true;

/* Local (c-file static) function */
static uint32_t InternalHelper_u32(uint32_t x_u32, uint16_t y_u16) {
  uint32_t l_acc_u32 = x_u32;

  /* Accumulate even-step sequence: for each l_i_u16 in [0 .. y_u16-1],
     add (l_i_u16 * 2) to l_acc_u32 */
  /* Loop counter l_i_u16 complies with interface and naming rules */
  for(uint16_t l_i_u16 = 0U; l_i_u16 < y_u16; l_i_u16++) {
    l_acc_u32 += ((uint32_t)l_i_u16 * 2U);
  }
  return l_acc_u32;
}
void MyLib_ProcessRecord(const MyLib_record_t *rec_pc, uint8_t multiplier_u8) {
  uint32_t l_acc_u32;
  uint8_t l_i_u8;

  /* Check if input pointer is NULL */
  if(rec_pc == NULL) {
    return;
  }

  /* Switch-case structure for bounded accumulation based on multiplier_u8 */
  switch(multiplier_u8) {
  case 0U:
    /* No accumulation */
    l_acc_u32 = 0U;
    break;

  case 1U:
    /* Single direct assignment */
    l_acc_u32 = rec_pc->value_u32;
    break;

  default:
    /* Bounded loop accumulation */
    l_acc_u32 = 0U;
    for(l_i_u8 = 0U; l_i_u8 < multiplier_u8; l_i_u8++) {
      l_acc_u32 += rec_pc->value_u32;
    }
    break;
  }

  /* Increment global counter by accumulated value */
  g_counter_u32 += l_acc_u32;

  /* Invoke library function with accumulated value and multiplier address */
  (void)MyLib_ComputeAdjustedValue_u32(l_acc_u32, (const uint16_t *)&multiplier_u8);
}
uint32_t MyLib_ComputeAdjustedValue_u32(uint32_t base_u32, const uint16_t *delta_pc_u16) {
  uint16_t l_d_u16;
  uint32_t l_val_u32;

  /* Check if delta pointer is NULL and assign default or dereferenced value */
  if(delta_pc_u16 == NULL) {
    l_d_u16 = 1U;
  } else {
    l_d_u16 = *delta_pc_u16;
  }

  /* Multiply base by delta factor */
  l_val_u32 = base_u32 * l_d_u16;

  /* Apply internal post-processing step */
  /* NOTE: MYLIB_MULT_VALUE_U8 macro is not defined in the [HEADER] but is referenced in the activity diagram */
  l_val_u32 = InternalHelper_u32(l_val_u32, (uint16_t)MYLIB_MULT_VALUE_U8);

  return l_val_u32;
}
uint32_t MyLib_AnalyzeArray_u32(uint16_t *values_pu16, size_t len_u32, uint16_t factor_u16) {
  /* Check for NULL pointer or zero length input */
  if((values_pu16 == NULL) || (len_u32 == 0U)) {
    return 0U;
  }

  uint32_t l_sum_u32 = 0U;

  for(size_t l_i_u32 = 0U; l_i_u32 < len_u32; l_i_u32++) {
    values_pu16[l_i_u32] = (uint16_t)(values_pu16[l_i_u32] * factor_u16);
    l_sum_u32 += values_pu16[l_i_u32];
  }

  /* Invoke deterministic secondary computation; return value not used as per header */
  (void)MyLib_ComputeAdjustedValue_u32(l_sum_u32, NULL);

  return l_sum_u32;
}
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
uint32_t MyLib_Orchestrate_u32(uint32_t start_u32, const uint16_t *delta_pc_u16) {
  uint16_t l_d_u16;
  uint32_t l_base_u32;
  MyLib_record_t l_r;

  /* Check if delta_pc_u16 is NULL and set l_d_u16 accordingly */
  if(delta_pc_u16 == NULL) {
    l_d_u16 = 0U;
  } else {
    l_d_u16 = *delta_pc_u16;
  }

  /* Compute base using internal helper */
  l_base_u32 = InternalHelper_u32(start_u32, l_d_u16);

  /* Build temporary record derived from the base */
  l_r.id_u16 = (uint16_t)(l_base_u32 & 0xFFFFU);
  l_r.value_u32 = l_base_u32 / 2U;

  /* Process the record via MyLib_ProcessRecord */
  MyLib_ProcessRecord(&l_r, MYLIB_MULT_VALUE_U8);

  /* Return combined result: base plus global counter */
  return (l_base_u32 + g_counter_u32);
}
uint8_t MyLib_UpdateCounter_u8(uint32_t add_u32) {
  /* Function-local static cycle counter, persistent across calls */
  static uint32_t l_CycleCnt_u32 = 0U;

  uint32_t l_new_u32;
  uint8_t l_ret_u8;

  /* Step 1: Increment the function-static cycle counter */
  l_CycleCnt_u32++;

  /* Step 2: Check module readiness */
  if(g_systemReady_b == false) {
    /* System not ready, return error code 1 and perform no update */
    return 1U;
  }

  /* Step 3: Compute tentative new counter value */
  l_new_u32 = g_counter_u32 + add_u32;

  /* Step 4: Apply saturation if enabled */
  if((SaturationEn_b == true) && (l_new_u32 > CounterLimit_u32)) {
    /* Saturation condition met: clamp to limit */
    g_counter_u32 = CounterLimit_u32;
    l_ret_u8 = 2U;
  } else {
    /* No saturation: store new value */
    g_counter_u32 = l_new_u32;
    l_ret_u8 = 0U;
  }

  /* Step 5: Periodically toggle SaturationEn_b every 16 calls */
  if((l_CycleCnt_u32 & 0x0FU) == 0U) {
    SaturationEn_b = !SaturationEn_b;
  }

  /* Return status code */
  return l_ret_u8;
}
int main() {
  return 0;
}
void ProcessRecord(const MyLib_record_t *rec_pc, uint8_t multiplier_u8) {
  /*
   * Syntax edge case:
   * This public wrapper reuses another function from the same library.
   * It is useful to verify that the generator detects intra-library calls.
   */
  MyLib_ProcessRecord(rec_pc, multiplier_u8);
}

uint32_t AnalyzeArray_u32(uint16_t *values_pu16, size_t len_u32, uint16_t factor_u16) {
  /*
   * Syntax edge case:
   * This wrapper intentionally reuses the MyLib-prefixed implementation.
   */
  return MyLib_AnalyzeArray_u32(values_pu16, len_u32, factor_u16);
}

uint8_t UpdateCounter_u8(uint32_t add_u32) {
  /*
   * Syntax edge case:
   * This wrapper intentionally reuses the MyLib-prefixed implementation.
   */
  return MyLib_UpdateCounter_u8(add_u32);
}


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

/* ==========================================================================
 * C syntax edge-case functions for generator validation
 * ========================================================================== */

/* Additional typedefs used only by the syntax edge-case functions. */
typedef enum {
  MYLIB_SYNTAX_OK = 0U,
  MYLIB_SYNTAX_NOT_OK = 1U
} MyLib_SyntaxStatus_t;

typedef void (*MyLib_Callback_t)(uint8_t id_u8, uint32_t value_u32);
typedef uint32_t (*MyLib_Transform_t)(uint32_t value_u32);

typedef union {
  uint32_t raw_u32;
  struct {
    uint32_t low_u32  : 16;
    uint32_t high_u32 : 16;
  } bits;
} MyLib_PackedWord_t;

typedef enum {
  MYLIB_LOCAL_STATE_INIT = 0,
  MYLIB_LOCAL_STATE_READY = 1,
  MYLIB_LOCAL_STATE_ERROR = 2
} MyLib_LocalState_t;

typedef uint32_t MyLib_Vector3_u32[3];

#define MYLIB_SYNTAX_BASE_LIMIT_U32    (100U)
#define MYLIB_SYNTAX_WARNING_LIMIT_U32 (MYLIB_SYNTAX_BASE_LIMIT_U32 - 10U)
#define MYLIB_SYNTAX_ERROR_LIMIT_U32   (MYLIB_SYNTAX_BASE_LIMIT_U32 + 20U)

#define MYLIB_SYNTAX_IS_WARNING_RANGE(x) \
  (((x) >= MYLIB_SYNTAX_WARNING_LIMIT_U32) && ((x) < MYLIB_SYNTAX_ERROR_LIMIT_U32))

#define MYLIB_SYNTAX_MULTILINE_SUM(a, b) \
  ((a) + \
   (b))

#ifndef MYLIB_FEATURE_SCALE_FACTOR
#define MYLIB_FEATURE_SCALE_FACTOR (2U)
#endif

#ifdef MYLIB_ENABLE_SPECIAL_BRANCH
#define MYLIB_SPECIAL_OFFSET_U32 (50U)
#else
#define MYLIB_SPECIAL_OFFSET_U32 (5U)
#endif

#if defined(__GNUC__)
#define MYLIB_NOINLINE __attribute__((noinline))
#define MYLIB_WEAK_SYMBOL __attribute__((weak))
#else
#define MYLIB_NOINLINE
#define MYLIB_WEAK_SYMBOL
#endif

static uint8_t SyntaxStaticCounter_u8 = 0U;
static uint8_t SyntaxStaticArray_au8[5] = {1U, 2U, 3U, 4U, 5U};
static const uint16_t SyntaxConstTable_au16[] = {10U, 20U, 30U};
static MyLib_LocalState_t SyntaxCurrentState = MYLIB_LOCAL_STATE_INIT;
static MyLib_Vector3_u32 SyntaxStaticVector = {1U, 2U, 3U};
static const char * const SyntaxTextWithKeywords = "static inline must not be changed here";

/**
 * @brief Static function definition used to validate static handling.
 */
static uint8_t Syntax_StaticFunction_u8(uint8_t value_u8) {
  SyntaxStaticCounter_u8 += value_u8;
  return SyntaxStaticCounter_u8;
}

/**
 * @brief Inline function definition used to validate inline handling.
 */
inline uint32_t Syntax_InlineFunction_u32(uint32_t value_u32) {
  return value_u32 + 1U;
}

/**
 * @brief Static inline function definition used to validate static inline handling.
 */
static inline uint32_t Syntax_StaticInlineFunction_u32(uint32_t value_u32) {
  return value_u32 * 2U;
}

/**
 * @brief Function with return type and parameters split across lines.
 */
uint32_t
Syntax_MultilineReturnAndParams_u32(
  uint32_t a_u32,
  uint32_t b_u32,
  uint32_t c_u32
)
{
  return a_u32 + b_u32 + c_u32;
}

/**
 * @brief Function with pointer and const qualifiers split across lines.
 */
const MyLib_record_t *
Syntax_FindRecordById(
  const MyLib_record_t *records_pc,
  uint32_t count_u32,
  uint16_t id_u16
)
{
  uint32_t l_i_u32;

  if(records_pc == NULL) {
    return NULL;
  }

  for(l_i_u32 = 0U; l_i_u32 < count_u32; l_i_u32++) {
    if(records_pc[l_i_u32].id_u16 == id_u16) {
      return &records_pc[l_i_u32];
    }
  }

  return NULL;
}

/**
 * @brief Function with pointer-to-pointer parameter.
 */
MyLib_SyntaxStatus_t Syntax_UpdateOutputPointer(uint32_t **out_ppu32, uint32_t *storage_pu32) {
  if((out_ppu32 == NULL) || (storage_pu32 == NULL)) {
    return MYLIB_SYNTAX_NOT_OK;
  }

  *out_ppu32 = storage_pu32;
  return MYLIB_SYNTAX_OK;
}

/**
 * @brief Function with const pointer variations.
 */
uint32_t Syntax_ConstPointerMix_u32(const uint32_t * const input_pcu32, uint32_t * const output_pu32) {
  if((input_pcu32 == NULL) || (output_pu32 == NULL)) {
    return 0U;
  }

  *output_pu32 = *input_pcu32 + 10U;
  return *output_pu32;
}

/**
 * @brief Function returning a pointer.
 */
uint32_t *Syntax_ReturnPointer(uint32_t *value_pu32) {
  return value_pu32;
}

/**
 * @brief Local static helper reused by function-pointer syntax tests.
 */
static uint32_t Syntax_LocalDouble_u32(uint32_t value_u32) {
  return value_u32 * 2U;
}

/**
 * @brief Function receiving a function pointer typedef.
 */
uint32_t Syntax_ApplyTransform_u32(uint32_t value_u32, MyLib_Transform_t transform_pf) {
  if(transform_pf == NULL) {
    return value_u32;
  }

  return transform_pf(value_u32);
}

/**
 * @brief Function receiving a raw function pointer parameter.
 */
void Syntax_NotifyWithCallback(uint8_t id_u8, uint32_t value_u32, void (*callback_pf)(uint8_t, uint32_t)) {
  if(callback_pf != NULL) {
    callback_pf(id_u8, value_u32);
  }
}

/**
 * @brief Function calling a static helper through a function pointer.
 */
uint32_t Syntax_UseLocalFunctionPointer_u32(uint32_t value_u32) {
  MyLib_Transform_t transform_pf = Syntax_LocalDouble_u32;

  return transform_pf(value_u32);
}

/**
 * @brief Function with fixed-size array parameter.
 */
uint32_t Syntax_SumFixedArray_u32(uint32_t values_au32[3]) {
  return values_au32[0] + values_au32[1] + values_au32[2];
}

/**
 * @brief Function with multidimensional array parameter.
 */
uint32_t Syntax_SumMatrix2x2_u32(uint32_t matrix_aau32[2][2]) {
  return matrix_aau32[0][0] + matrix_aau32[0][1] + matrix_aau32[1][0] + matrix_aau32[1][1];
}

/**
 * @brief Function using static arrays declared at translation-unit scope.
 */
uint16_t Syntax_ReadStaticArrayAndConstTable_u16(uint8_t index_u8) {
  if(index_u8 < 3U) {
    return (uint16_t)(SyntaxStaticArray_au8[index_u8] + SyntaxConstTable_au16[index_u8]);
  }

  return 0U;
}

/**
 * @brief Function using struct by value.
 */
uint32_t Syntax_ProcessRecordByValue_u32(MyLib_record_t record) {
  return ((uint32_t)record.id_u16) + record.value_u32;
}

/**
 * @brief Function using union and bitfields.
 */
uint32_t Syntax_ReadPackedHigh_u32(MyLib_PackedWord_t word) {
  return word.bits.high_u32;
}

/**
 * @brief Function using a local enum stored in a static global.
 */
MyLib_LocalState_t Syntax_AdvanceLocalState(bool error_b) {
  if(error_b) {
    SyntaxCurrentState = MYLIB_LOCAL_STATE_ERROR;
  } else {
    SyntaxCurrentState = MYLIB_LOCAL_STATE_READY;
  }

  return SyntaxCurrentState;
}

/*
 * These tokens must not be modified by strip_function_keywords_in_header:
 * static inline FakeFunction(void);
 * "static inline StringText(void);"
 */

/**
 * @brief Function using function-like macro and multiline macro.
 */
uint32_t Syntax_MacroHeavyFunction_u32(uint32_t a_u32, uint32_t b_u32) {
  uint32_t l_value_u32 = MYLIB_SYNTAX_MULTILINE_SUM(a_u32, b_u32);

  if(l_value_u32 > MYLIB_SYNTAX_BASE_LIMIT_U32) {
    return (MYLIB_SYNTAX_BASE_LIMIT_U32 * 2U);
  }

  return (l_value_u32 * 2U);
}

/**
 * @brief Function containing words static and inline in comments and strings.
 */
uint32_t Syntax_CommentAndStringKeywords_u32(void) {
  const char *l_localText_pc = "inline static text";

  /* static inline should remain unchanged in comments. */
  if((l_localText_pc[0] == 'i') && (SyntaxTextWithKeywords[0] == 's')) {
    return 1U;
  }

  return 0U;
}

/**
 * @brief Function affected by preprocessor conditionals.
 */
uint32_t Syntax_ConditionalCompileFunction_u32(uint32_t value_u32) {
#if MYLIB_FEATURE_SCALE_FACTOR > 1
  value_u32 = value_u32 * MYLIB_FEATURE_SCALE_FACTOR;
#else
  value_u32 = value_u32 + 1U;
#endif

#ifdef MYLIB_ENABLE_SPECIAL_BRANCH
  value_u32 += MYLIB_SPECIAL_OFFSET_U32;
#else
  value_u32 -= MYLIB_SPECIAL_OFFSET_U32;
#endif

  return value_u32;
}

/**
 * @brief Variadic function that validates ellipsis handling.
 */
uint32_t Syntax_SumVariadic_u32(uint32_t count_u32, ...) {
  va_list args;
  uint32_t l_i_u32;
  uint32_t l_sum_u32 = 0U;

  va_start(args, count_u32);

  for(l_i_u32 = 0U; l_i_u32 < count_u32; l_i_u32++) {
    l_sum_u32 += (uint32_t)va_arg(args, uint32_t);
  }

  va_end(args);

  return l_sum_u32;
}

/**
 * @brief Function using a register local variable.
 */
uint32_t Syntax_RegisterLocalVariable_u32(uint32_t input_u32) {
  register uint32_t l_local_u32 = input_u32;

  return l_local_u32 + 1U;
}

/**
 * @brief Function with compiler attribute before the function name.
 */
MYLIB_NOINLINE uint32_t Syntax_NoInlineFunction_u32(uint32_t value_u32) {
  return value_u32 + 1U;
}

/**
 * @brief Weak function.
 */
MYLIB_WEAK_SYMBOL uint32_t Syntax_WeakFunction_u32(uint32_t value_u32) {
  return value_u32 + 2U;
}

/**
 * @brief Function returning a typedef array element.
 */
uint32_t Syntax_ReadVectorElement_u32(uint8_t index_u8) {
  if(index_u8 >= 3U) {
    return 0U;
  }

  return SyntaxStaticVector[index_u8];
}

/**
 * @brief Function with volatile and const volatile pointer qualifiers.
 */
uint32_t Syntax_FunctionWithManyQualifiers_u32(volatile uint32_t * volatile value_pvu32,
                                               const volatile uint32_t * const reference_pcvu32) {
  if((value_pvu32 == NULL) || (reference_pcvu32 == NULL)) {
    return 0U;
  }

  *value_pvu32 = *reference_pcvu32;
  return *value_pvu32;
}

/**
 * @brief Function that reuses existing MyLib services from the same library.
 */
uint32_t Syntax_ReusesMyLibServices_u32(MyLib_record_t *dest_p,
                                        const MyLib_record_t *src_pc,
                                        uint32_t add_u32) {
  MyLib_UpdateGlobalRecord(dest_p, src_pc);

  if(g_systemReady_b == false) {
    return 0U;
  }

  (void)MyLib_UpdateCounter_u8(add_u32);

  return MyLib_Orchestrate_u32(add_u32, NULL);
}

