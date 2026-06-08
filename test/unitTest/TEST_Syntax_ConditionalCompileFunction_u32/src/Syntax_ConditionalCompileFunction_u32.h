#ifndef TEST_SYNTAX_CONDITIONALCOMPILEFUNCTION_U32_H
#define TEST_SYNTAX_CONDITIONALCOMPILEFUNCTION_U32_H

#include "AleLib.h"

#define MYLIB_FEATURE_SCALE_FACTOR (2U)
#define MYLIB_SPECIAL_OFFSET_U32 (5U)

/**
 * @brief Function affected by preprocessor conditionals.
 */
uint32_t Syntax_ConditionalCompileFunction_u32(uint32_t value_u32);


#endif /* TEST_SYNTAX_CONDITIONALCOMPILEFUNCTION_U32_H */
