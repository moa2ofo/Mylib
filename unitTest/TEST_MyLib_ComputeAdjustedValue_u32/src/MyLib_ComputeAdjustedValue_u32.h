#ifndef TEST_MYLIB_COMPUTEADJUSTEDVALUE_U32_H
#define TEST_MYLIB_COMPUTEADJUSTEDVALUE_U32_H

#include "MyLib.h"

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
uint32_t MyLib_ComputeAdjustedValue_u32(uint32_t base_u32, const uint16_t * delta_pc_u16);


#endif /* TEST_MYLIB_COMPUTEADJUSTEDVALUE_U32_H */
