#ifndef TEST_SYNTAX_NOTIFYWITHCALLBACK_H
#define TEST_SYNTAX_NOTIFYWITHCALLBACK_H

#include "AleLib.h"

/**
 * @brief Function receiving a raw function pointer parameter.
 */
void Syntax_NotifyWithCallback(uint8_t id_u8, uint32_t value_u32, void (*)(uint8_t, uint32_t) callback_pf);


#endif /* TEST_SYNTAX_NOTIFYWITHCALLBACK_H */
