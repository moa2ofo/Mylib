#ifndef TEST_MYLIB_UPDATEGLOBALRECORD_H
#define TEST_MYLIB_UPDATEGLOBALRECORD_H

#include "MyLib.h"

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
void MyLib_UpdateGlobalRecord(MyLib_record_t *dest_p, const MyLib_record_t *src_pc);

#endif /* TEST_MYLIB_UPDATEGLOBALRECORD_H */
