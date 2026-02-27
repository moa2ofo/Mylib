#ifndef TEST_MYLIB_PROCESSRECORD_H
#define TEST_MYLIB_PROCESSRECORD_H

#include "MyLib.h"

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
 *   :call MyLib_ComputeAdjustedValue_u32(l_acc_u32, (const uint16_t *)&multiplier_u8);
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
void MyLib_ProcessRecord(const MyLib_record_t * rec_pc, uint8_t multiplier_u8);


#endif /* TEST_MYLIB_PROCESSRECORD_H */
