#ifndef MYLIB_UPDATECOUNTER_U8_H
#define MYLIB_UPDATECOUNTER_U8_H

#include "MyLib.h"

uint32_t GetCounterLimit_u32(void);
void SetCounterLimit_u32(uint32_t value);

bool GetSaturationEn_b(void);
void SetSaturationEn_b(bool enable);

/**
 * @brief Update the module global counter with optional saturation handling.
 *
 * @details
 * **Goal of the function**
 *
 * Execute a deterministic sequence:
 * - Increment a function-static cycle counter (`l_CycleCnt_u32`)
 * - Check module readiness via `g_systemReady_b`
 *   - If not ready, return error code 1 and perform no update
 * - Compute a tentative new counter value (`l_new_u32 = g_counter_u32 + add_u32`)
 * - Apply saturation (if enabled):
 *   - If `SaturationEn_b == true` and `l_new_u32 > CounterLimit_u32`, clamp `g_counter_u32` and return code 2
 *   - Otherwise store `l_new_u32` into `g_counter_u32` and return code 0
 * - Periodically toggle `SaturationEn_b` every 16 calls (when `(l_CycleCnt_u32 & 0x0FU) == 0U`)
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
 * :static l_CycleCnt_u32++;
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
uint8_t MyLib_UpdateCounter_u8(uint32_t add_u32);

#endif
