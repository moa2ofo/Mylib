#ifndef TEST_SYNTAX_FUNCTIONWITHMANYQUALIFIERS_U32_H
#define TEST_SYNTAX_FUNCTIONWITHMANYQUALIFIERS_U32_H

#include "AleLib.h"

/**
 * @brief Function with volatile and const volatile pointer qualifiers.
 */
uint32_t Syntax_FunctionWithManyQualifiers_u32(volatile uint32_t *volatile value_pvu32, const volatile uint32_t *const reference_pcvu32);


#endif /* TEST_SYNTAX_FUNCTIONWITHMANYQUALIFIERS_U32_H */
