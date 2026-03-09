#ifndef TEST_MYLIB_RUNSTATEMACHINE_U8_H
#define TEST_MYLIB_RUNSTATEMACHINE_U8_H

#include "MyLib.h"

/**
 * @brief Execute one step of an internal state machine operating on a record and updating the module counter.
 *
 * @details
 * **Goal of the function**
 *
 * Execute a lightweight internal state machine that processes a record
 * across multiple calls and updates the module counter accordingly.
 * The function preserves context using static variables and orchestrates
 * record initialization, processing, and counter update by invoking
 * existing module services.
 *
 * @par Interface summary
 *
 * | Interface                      | In | Out | Type / Signature                                 | Param | Factor | Offset | Size | Range                | Unit |
 * |--------------------------------|----|-----|--------------------------------------------------|-------|--------|--------|------|----------------------|------|
 * | rec_pc                         | X  |     | const MyLib_record_t*                            |   X   |   1    |   0    |   1  | pointer / NULL       | [-]  |
 * | add_u32                        | X  |     | uint32_t                                         |   X   |   1    |   0    |   1  | 0..(wrap)            | [-]  |
 * | delta_pc_u16                   | X  |     | const uint16_t*                                  |   X   |   1    |   0    |   1  | pointer / NULL       | [-]  |
 * | g_counter_u32                  |    |  X  | uint32_t                                         |       |   1    |   0    |   1  | 0..(wrap)            | [-]  |
 * | MyLib_UpdateGlobalRecord       |    |  X  | void (MyLib_record_t*, const MyLib_record_t*)    |       |   1    |   0    |   1  | -                    | [-]  |
 * | MyLib_ProcessRecord            |    |  X  | void (MyLib_record_t*, uint8_t)                  |       |   1    |   0    |   1  | -                    | [-]  |
 * | MyLib_ComputeAdjustedValue_u32 |    |  X  | uint32_t (uint32_t, const uint16_t*)             |       |   1    |   0    |   1  | 0..(wrap)            | [-]  |
 * | MyLib_UpdateCounter_u8         |    |  X  | uint8_t (uint32_t)                               |       |   1    |   0    |   1  | 0..2                 | [-]  |
 * | return val                     |    |  X  | uint8_t                                          |       |   1    |   0    |   1  | 0..3                 | [-]  |
 *
 * @par Activity diagram (PlantUML)
 *
 * @startuml
 * start
 *
 * :static uint8_t l_State_u8;
 * :static MyLib_record_t l_LastRecord;
 * :static uint32_t l_LastAdjusted_u32;
 * :uint8_t l_ret_u8 = 0;
 * :uint32_t l_UpdateValue_u32 = 0;
 *
 * switch (l_State_u8)
 *
 * case (0: Init)
 *   if (rec_pc == NULL) then (yes)
 *     :l_ret_u8 = 1;
 *   else (no)
 *     :MyLib_UpdateGlobalRecord(&l_LastRecord, rec_pc);
 *     :l_State_u8 = 1;
 *     :l_ret_u8 = 0;
 *   endif
 *   break
 *
 * case (1: Process)
 *   :MyLib_ProcessRecord(&l_LastRecord, MYLIB_MULT_VALUE_U8);
 *   :l_LastAdjusted_u32 =
 *   MyLib_ComputeAdjustedValue_u32(l_LastRecord.value_u32, delta_pc_u16);
 *   :l_State_u8 = 2;
 *   :l_ret_u8 = 0;
 *   break
 *
 * case (2: Update counter)
 *   :l_UpdateValue_u32 = add_u32 + l_LastAdjusted_u32;
 *   :l_ret_u8 = MyLib_UpdateCounter_u8(l_UpdateValue_u32);
 *   :l_State_u8 = 0;
 *   break
 *
 * endswitch
 *
 * :return l_ret_u8;
 * stop
 * @enduml
 *
 * @param rec_pc
 * Pointer to the input record used during the initialization state.
 * If NULL, the initialization step is rejected.
 *
 * @param add_u32
 * Increment applied to the module counter during the counter update state.
 *
 * @param delta_pc_u16
 * Optional pointer to a delta value used in the adjusted value computation.
 * If NULL, the adjustment routine applies its default behaviour.
 *
 * @return uint8_t
 * Status code:
 * - 0: Step executed successfully
 * - 1: Initialization rejected because `rec_pc == NULL`
 * - 2: Counter update routine reported saturation
 * - 3: Internal state recovery executed (invalid state detected)
 */
uint8_t MyLib_RunStateMachine_u8(const MyLib_record_t *rec_pc, uint32_t add_u32, const uint16_t *delta_pc_u16);

#endif /* TEST_MYLIB_RUNSTATEMACHINE_U8_H */
