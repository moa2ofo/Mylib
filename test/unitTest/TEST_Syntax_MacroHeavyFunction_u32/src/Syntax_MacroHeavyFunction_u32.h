#ifndef TEST_SYNTAX_MACROHEAVYFUNCTION_U32_H
#define TEST_SYNTAX_MACROHEAVYFUNCTION_U32_H

#include "AleLib.h"

#define MYLIB_SYNTAX_BASE_LIMIT_U32 (100U)
#define MYLIB_SYNTAX_MULTILINE_SUM(a, b) ((a) + (b))

/**
 * @brief Function using function-like macro and multiline macro.
 */
uint32_t Syntax_MacroHeavyFunction_u32(uint32_t a_u32, uint32_t b_u32);


#endif /* TEST_SYNTAX_MACROHEAVYFUNCTION_U32_H */
