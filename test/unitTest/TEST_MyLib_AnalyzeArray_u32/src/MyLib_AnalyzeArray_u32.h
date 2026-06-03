#ifndef TEST_MYLIB_ANALYZEARRAY_U32_H
#define TEST_MYLIB_ANALYZEARRAY_U32_H

#include "MyLib.h"

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
 * : l_inNull_b = false;
 * 
 * if (values_pu16 == NULL or len_u32 == 0) then (yes)
 *   : l_inNull_b = true;
 * endif
 * :l_sum_u32 = 0;
 * 
 * if (l_inNull_b == false) then (process)
 *   :for l_i_u32 in [0 .. len_u32-1];
 *     :values_pu16[l_i_u32] = values_pu16[l_i_u32] * factor_u16;
 *     :l_sum_u32 += values_pu16[l_i_u32];
 *   :endfor;
 * 
 *   :call MyLib_ComputeAdjustedValue_u32(l_sum_u32, NULL);
 * endif
 * :return l_sum_u32;
 * 
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

#endif /* TEST_MYLIB_ANALYZEARRAY_U32_H */
