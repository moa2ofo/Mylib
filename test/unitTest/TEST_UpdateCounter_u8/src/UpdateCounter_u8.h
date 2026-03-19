#ifndef TEST_UPDATECOUNTER_U8_H
#define TEST_UPDATECOUNTER_U8_H

#include "MyLib.h"

/**
 * @brief Update the module global counter with optional saturation handling.
 *
 * @details
 * **Goal of the function**
 *
 * Executes a deterministic update: increments a static cycle counter, 
 * checks system readiness, computes a new counter with optional saturation, updates `g_counter_u32` accordingly, and returns a status code.
 * Toggles `SaturationEn_b` every 16 cycles and clamps the counter when enabled and limits are exceeded.
 *
 * @par Interface summary
 *
 * | Interface         | In | Out | Type / Signature           | Param | Factor | Offset | Size | Range              | Unit |
 * |-------------------|----|-----|----------------------------|-------|--------|--------|------|--------------------|------|
 * | add_u32           | X  |     | uint32_t                   |   X   |   1    |   0    |   1  | 0..(wrap)          | [-]  |
 * | g_systemReady_b   |    |  X  | bool                       |       |   1    |   0    |   1  | false/true         | [-]  |
 * | g_counter_u32     |    |  X  | uint32_t                   |       |   1    |   0    |   1  | 0..(wrap)          | [-]  |
 * | CounterLimit_u32  |    |  X  | uint32_t                   |       |   1    |   0    |   1  | 0..(wrap)          | [-]  |
 * | SaturationEn_b    |    |  X  | bool                       |       |   1    |   0    |   1  | false/true         | [-]  |
 * | return val        |    |  X  | uint8_t                    |       |   1    |   0    |   1  | 0..2               | [-]  |
 *
 * @par Activity diagram (PlantUML)
 *
 * @startuml
 * start
 * :l_CycleCnt_u32++;
 * if (g_systemReady_b == false) then (yes)
 *   :return 1;
 * else (no)
 *   :l_new_u32 = g_counter_u32 + add_u32;
 *   if ((SaturationEn_b == true) && (l_new_u32 > CounterLimit_u32)) then (yes)
 *     :g_counter_u32 = CounterLimit_u32;
 *     :l_ret_u8 = 2;
 *   else (no)
 *     :g_counter_u32 = l_new_u32;
 *     :l_ret_u8 = 0;
 *   endif
 *   if ((l_CycleCnt_u32 & 0x0F) == 0) then (yes)
 *     :SaturationEn_b = !SaturationEn_b;
 *   endif
 *   :return l_ret_u8;
 * endif
 * stop
 * @enduml
 *
 * @param add_u32
 * Unsigned increment added to `g_counter_u32` (wrap-around may occur before saturation check).
 *
 * @return uint8_t
 * Status code:
 * - 0: Update applied (no saturation clamp)
 * - 1: Rejected because `g_systemReady_b == false`
 * - 2: Saturation applied and `g_counter_u32` clamped to `CounterLimit_u32`
 */
uint8_t UpdateCounter_u8(uint32_t add_u32);

uint32_t get_CounterLimit_u32(void);
void set_CounterLimit_u32(uint32_t val);
_Bool get_SaturationEn_b(void);
void set_SaturationEn_b(_Bool val);

#endif /* TEST_UPDATECOUNTER_U8_H */
