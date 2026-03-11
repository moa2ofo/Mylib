#ifndef TEST_MYLIB_ORCHESTRATE_U32_H
#define TEST_MYLIB_ORCHESTRATE_U32_H

#include "MyLib.h"

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
uint32_t MyLib_Orchestrate_u32(uint32_t start_u32, const uint16_t * delta_pc_u16);


#endif /* TEST_MYLIB_ORCHESTRATE_U32_H */
