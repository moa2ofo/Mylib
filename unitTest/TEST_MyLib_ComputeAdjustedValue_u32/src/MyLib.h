/* MyLib.h */

#ifndef MYLIB_H
#define MYLIB_H

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

/* Numeric macros */
#define MYLIB_MAX_COUNT_U32   (100U)
#define MYLIB_MULT_VALUE_U8   (5U)

/* Typedef / struct */
typedef struct
{
  uint16_t id_u16;
  uint32_t value_u32;
} MyLib_record_t;

/* Global variables */
extern uint32_t g_counter_u32;
extern MyLib_record_t g_record;
extern bool g_systemReady_b;

/**
 * @brief Process one record with a bounded accumulation and update module globals.
 *
 * @details
 * **Goal of the function**
 *
 * Consume an input record and apply a deterministic accumulation based on
 * `multiplier_u8`. The accumulation logic is implemented using a switch-case
 * structure to optimize specific scenarios while keeping execution bounded.
 *
 * Processing behavior:
 * - If `rec_pc == NULL`, the function returns immediately (no side effects).
 * - Otherwise, a local accumulator (`l_acc_u32`) is computed as follows:
 *   - `multiplier_u8 == 0U`
 *       → No accumulation (`l_acc_u32 = 0U`).
 *   - `multiplier_u8 == 1U`
 *       → Single direct assignment (`l_acc_u32 = rec_pc->value_u32`).
 *   - `default`
 *       → Bounded loop accumulation:
 *         `l_acc_u32 += rec_pc->value_u32` repeated `multiplier_u8` times.
 *
 * After accumulation:
 * - `g_counter_u32` is incremented by `l_acc_u32`.
 * - `MyLib_ComputeAdjustedValue_u32()` is invoked.
 *
 * Wrap-around on `uint32_t` is permitted by design.
 *
 * @par Interface summary
 *
 * | Interface                      | In | Out | Type / Signature                        | Param | Factor | Offset | Size | Range              | Unit |
 * |--------------------------------|----|-----|-----------------------------------------|-------|--------|--------|------|--------------------|------|
 * | rec_pc                         | X  |     | const MyLib_record_t*                   |   X   |   1    |   0    |   1  | pointer / NULL     | [-]  |
 * | multiplier_u8                  | X  |     | uint8_t                                 |   X   |   1    |   0    |   1  | 0..255             | [-]  |
 * | MyLib_ComputeAdjustedValue_u32 | X  |  X  | uint32_t (uint32_t , const uint16_t *)  |       |   1    |   0    |   1  | -                  | [-]  |
 * | g_counter_u32                  |    |  X  | uint32_t (global)                       |       |   1    |   0    |   1  | 0..(wrap)          | [-]  |
 * | return val                     |    |     | void                                    |       |   1    |   0    |   1  | -                  | [-]  |
 *
 * @par Activity diagram (PlantUML)
 *
 * @startuml
 * start
 * if (rec_pc == NULL) then (yes)
 *   :return;
 * else (no)
 *   :switch(multiplier_u8);
 *     case (0U)
 *       :l_acc_u32 = 0U;
 *     case (1U)
 *       :l_acc_u32 = rec_pc->value_u32;
 *     case (default)
 *       :for l_i_u8 in [0..multiplier_u8-1];
 *         :l_acc_u32 += rec_pc->value_u32;
 *       :endfor;
 *   :endswitch;
 *   :g_counter_u32 += l_acc_u32;
 *   :return;
 * endif
 * stop
 * @enduml
 *
 * @param rec_pc
 * Pointer to the input record. If NULL, the function returns immediately.
 *
 * @param multiplier_u8
 * Accumulation selector:
 * - 0 → no accumulation
 * - 1 → single accumulation
 * - >1 → bounded loop accumulation
 *
 * @return void
 * No return value.
 */
void MyLib_ProcessRecord(const MyLib_record_t *rec_pc, uint8_t multiplier_u8);

/**
 * @brief Compute an adjusted value from a base value and an optional delta.
 *
 * @details
 * **Goal of the function**
 *
 * Multiply `base_u32` by a delta factor and apply a deterministic internal
 * post-processing step. If `delta_pc_u16` is NULL, a default delta of `1` is used.
 *
 * @par Interface summary
 *
 * | Interface           | In | Out | Type / Signature                 | Param | Factor | Offset | Size | Range              | Unit |
 * |---------------------|----|-----|----------------------------------|-------|--------|--------|------|--------------------|------|
 * | base_u32            | X  |     | uint32_t                         |   X   |   1    |   0    |   1  | 0..600             | [-]  |
 * | delta_pc_u16        | X  |     | const uint16_t*                  |   X   |   1    |   0    |   1  | pointer / NULL     | [-]  |
 * | InternalHelper_u32  | X  |  X  | uint32_t (uint32_t , uint16_t )  |       |   1    |   0    |   1  | -                  | [-]  |
 * | return val          |    |  X  | uint32_t                         |       |   1    |   0    |   1  | 0..500             | [-]  |
 *
 * @par Activity diagram (PlantUML)
 *
 * @startuml
 * start
 * if (delta_pc_u16 == NULL) then (yes)
 *   :l_d_u16 = 1;
 * else (no)
 *   :l_d_u16 = *delta_pc_u16;
 * endif
 * :l_val_u32 = base_u32 * l_d_u16;
 * :l_val_u32 = InternalHelper_u32(l_val_u32, (uint16_t)MYLIB_MULT_VALUE_U8);
 * :return l_val_u32;
 * stop
 * @enduml
 *
 * @param base_u32
 * Base input value.
 *
 * @param delta_pc_u16
 * Optional pointer to delta factor. If NULL, delta defaults to 1.
 *
 * @return uint32_t
 * Adjusted value after applying delta and internal post-processing.
 */

/**
 * @brief Scale an array in-place and return the sum of scaled elements.
 *
 * @details
 * **Goal of the function**
 *
 * Iterate over `values_pu16` for `len_u32` elements, multiply each element by
 * `factor_u16`, store the result back into the array, and compute the sum.
 * If the pointer is NULL or the length is 0, return 0.
 *
 * The function also invokes `MyLib_ComputeAdjustedValue_u32()` to trigger a
 * secondary deterministic computation (its return value is not used).
 *
 * @par Interface summary
 *
 * | Interface                      | In | Out | Type / Signature                        | Param | Factor | Offset | Size | Range              | Unit |
 * |--------------------------------|----|-----|-----------------------------------------|-------|--------|--------|------|--------------------|------|
 * | values_pu16                    | X  |  X  | uint16_t*                               |   X   |   1    |   0    |   1  | pointer / NULL     | [-]  |
 * | len_u32                        | X  |     | size_t                                  |   X   |   1    |   0    |   1  | 0..600             | [-]  |
 * | factor_u16                     | X  |     | uint16_t                                |   X   |   1    |   0    |   1  | 0..65535           | [-]  |
 * | MyLib_ComputeAdjustedValue_u32 | X  |  X  | uint32_t (uint32_t , const uint16_t *)  |       |   1    |   0    |   1  | -                  | [-]  |
 * | return val                     |    |  X  | uint32_t                                |       |   1    |   0    |   1  | 0..500             | [-]  |
 *
 * @par Activity diagram (PlantUML)
 *
 * @startuml
 * start
 * if (values_pu16 == NULL or len_u32 == 0) then (yes)
 *   :return 0;
 * else (no)
 *   :l_sum_u32 = 0;
 *   :for l_i_u32 in [0..len_u32-1];
 *     :values_pu16[l_i_u32] *= factor_u16;
 *     :l_sum_u32 += values_pu16[l_i_u32];
 *   :endfor;
 *   :return l_sum_u32;
 * endif
 * stop
 * @enduml
 *
 * @param values_pu16
 * Pointer to the array to be scaled in-place. If NULL, the function returns 0.
 *
 * @param len_u32
 * Number of elements in the array. If 0, the function returns 0.
 *
 * @param factor_u16
 * Scaling factor applied to each element.
 *
 * @return uint32_t
 * Sum of the scaled array elements (wrap-around possible on overflow).
 */
uint32_t MyLib_AnalyzeArray_u32(uint16_t *values_pu16, size_t len_u32, uint16_t factor_u16);

/**
 * @brief Copy a record into a destination and update module global state.
 *
 * @details
 * **Goal of the function**
 *
 * Copy the content of `src_pc` into `dest_p`. On success, mirror the copied
 * record to the module global record and mark the system as ready.
 * If any pointer is NULL, the function returns immediately without changes.
 *
 * @par Interface summary
 *
 * | Interface         | In | Out | Type / Signature       | Param | Factor | Offset | Size | Range              | Unit |
 * |-------------------|----|-----|------------------------|-------|--------|--------|------|--------------------|------|
 * | dest_p            | X  |  X  | MyLib_record_t*        |   X   |   1    |   0    |   1  | pointer / NULL     | [-]  |
 * | src_pc            | X  |     | const MyLib_record_t*  |   X   |   1    |   0    |   1  | pointer / NULL     | [-]  |
 * | g_record          |    |  X  | MyLib_record_t         |       |   1    |   0    |   1  | -                  | [-]  |
 * | g_systemReady_b   |    |  X  | bool                   |       |   1    |   0    |   1  | false/true         | [-]  |
 * | return val        |    |     | void                   |       |   1    |   0    |   1  | -                  | [-]  |
 *
 * @par Activity diagram (PlantUML)
 *
 * @startuml
 * start
 * if (dest_p == NULL or src_pc == NULL) then (yes)
 *   :return;
 * else (no)
 *   :dest_p->id_u16 = src_pc->id_u16;
 *   :dest_p->value_u32 = src_pc->value_u32;
 *   :g_record = *dest_p;
 *   :g_systemReady_b = true;
 *   :return;
 * endif
 * stop
 * @enduml
 *
 * @param dest_p
 * Destination record pointer. Updated if not NULL and `src_pc` is not NULL.
 *
 * @param src_pc
 * Source record pointer. Read-only. If NULL, nothing is updated.
 *
 * @return void
 * No return value.
 */
void MyLib_UpdateGlobalRecord(MyLib_record_t * dest_p, const MyLib_record_t *src_pc);

/**
 * @brief Run an orchestration sequence and return a combined result.
 *
 * @details
 * **Goal of the function**
 *
 * Execute a deterministic sequence:
 * - Derive a delta (`l_d_u16`) from `delta_pc_u16` (default 0 if NULL)
 * - Compute a base using an internal helper
 * - Build a temporary record derived from the base
 * - Process the record via `MyLib_ProcessRecord()`
 * - Return `l_base_u32 + g_counter_u32`
 *
 * @par Interface summary
 *
 * | Interface              | In | Out | Type / Signature                         | Param | Factor | Offset | Size | Range              | Unit |
 * |------------------------|----|-----|------------------------------------------|-------|--------|--------|------|--------------------|------|
 * | start_u32              | X  |     | uint32_t                                 |   X   |   1    |   0    |   1  | 0..200             | [-]  |
 * | delta_pc_u16           | X  |     | const uint16_t*                          |   X   |   1    |   0    |   1  | pointer / NULL     | [-]  |
 * | InternalHelper_u32     |    |  X  | uint32_t (uint32_t x_u32, uint16_t y_u16)|       |   1    |   0    |   1  | -                  | [-]  |
 * | MyLib_ProcessRecord    |    |  X  | void (const MyLib_record_t *, uint8_t )  |       |   1    |   0    |   1  | -                  | [-]  |
 * | g_counter_u32          |    |  X  | uint32_t (global)                        |       |   1    |   0    |   1  | 0..500             | [-]  |
 * | return val             |    |  X  | uint32_t                                 |       |   1    |   0    |   1  | 0..400             | [-]  |
 *
 * @par Activity diagram (PlantUML)
 *
 * @startuml
 * start
 * if (delta_pc_u16 == NULL) then (yes)
 *   :l_d_u16 = 0;
 * else (no)
 *   :l_d_u16 = *delta_pc_u16;
 * endif
 * :l_base_u32 = InternalHelper_u32(start_u32, l_d_u16);
 * :l_r.id_u16 = (l_base_u32 & 0xFFFF);
 * :l_r.value_u32 = l_base_u32 / 2;
 * :call MyLib_ProcessRecord(&l_r, MYLIB_MULT_VALUE_U8);
 * :return (l_base_u32 + g_counter_u32);
 * stop
 * @enduml
 *
 * @param start_u32
 * Input start value used to derive the orchestration base.
 *
 * @param delta_pc_u16
 * Optional pointer to delta. If NULL, delta defaults to 0.
 *
 * @return uint32_t
 * Combined result: computed base plus the current global counter.
 */
uint32_t MyLib_Orchestrate_u32(uint32_t start_u32, const uint16_t *delta_pc_u16);

/**
 * @brief Compute a deterministic accumulated value based on an input seed and loop bound.
 *
 * @details
 * **Goal of the function**
 *
 * Provide a small, deterministic arithmetic helper that starts from `x_u32` and
 * accumulates an even-step sequence for `y_u16` iterations:
 * - Initialize `l_acc_u32` with `x_u32`
 * - For each `l_i_u16` in `[0 .. y_u16-1]`, add `(l_i_u16 * 2)` to `l_acc_u32`
 * - Return the final accumulated value
 *
 * This function is typically used as an internal building block to apply a
 * bounded and predictable post-processing step.
 *
 * @par Interface summary
 *
 * | Interface   | In | Out | Type / Signature | Param | Factor | Offset | Size | Range      | Unit |
 * |-------------|----|-----|------------------|-------|--------|--------|------|------------|------|
 * | x_u32       | X  |     | uint32_t         |   X   |   1    |   0    |   1  | 0..60535   | [-]  |
 * | y_u16       | X  |     | uint16_t         |   X   |   1    |   0    |   1  | 0..60535   | [-]  |
 * | return val  |    |  X  | uint32_t         |       |   1    |   0    |   1  | 0..700     | [-]  |
 *
 * @par Activity diagram (PlantUML)
 *
 * @startuml
 * start
 * :l_acc_u32 = x_u32;
 * :l_i_u16 = 0;
 * while (l_i_u16 < y_u16) is (yes)
 *   :l_acc_u32 += (l_i_u16 * 2);
 *   :l_i_u16++;
 * endwhile (no)
 * :return l_acc_u32;
 * stop
 * @enduml
 *
 * @param x_u32
 * Seed value used to initialize the accumulator.
 *
 * @param y_u16
 * Number of loop iterations. The accumulation adds `2*l_i_u16` for each
 * `l_i_u16` from 0 to `y_u16-1`.
 *
 * @return uint32_t
 * Final accumulated value (wrap-around possible on 32-bit overflow).
 */
uint32_t InternalHelper_u32(uint32_t x_u32, uint16_t y_u16);


#endif /* MYLIB_H */
