#ifndef TEST_SYNTAX_READVECTORELEMENT_U32_HELP_H
#define TEST_SYNTAX_READVECTORELEMENT_U32_HELP_H

#include "Syntax_ReadVectorElement_u32.h"
#include <stddef.h>
#include <string.h>

/* static globals (copied) */
static MyLib_Vector3_u32 SyntaxStaticVector = {1U, 2U, 3U};
MyLib_Vector3_u32 get_SyntaxStaticVector(void) { return SyntaxStaticVector; }
void set_SyntaxStaticVector(MyLib_Vector3_u32 val) { SyntaxStaticVector = val; }

#endif /* TEST_SYNTAX_READVECTORELEMENT_U32_HELP_H */
