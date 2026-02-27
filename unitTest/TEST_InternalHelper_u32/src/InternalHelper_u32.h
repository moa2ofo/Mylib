#ifndef TEST_INTERNALHELPER_U32_H
#define TEST_INTERNALHELPER_U32_H

#include "MyLib.h"

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


#endif /* TEST_INTERNALHELPER_U32_H */
