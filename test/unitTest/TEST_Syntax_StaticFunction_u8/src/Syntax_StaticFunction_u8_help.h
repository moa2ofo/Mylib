#ifndef TEST_SYNTAX_STATICFUNCTION_U8_HELP_H
#define TEST_SYNTAX_STATICFUNCTION_U8_HELP_H

#include "Syntax_StaticFunction_u8.h"
#include <stddef.h>
#include <string.h>

/* static globals (copied) */
static uint8_t SyntaxStaticCounter_u8 = 0U;
uint8_t get_SyntaxStaticCounter_u8(void) { return SyntaxStaticCounter_u8; }
void set_SyntaxStaticCounter_u8(uint8_t val) { SyntaxStaticCounter_u8 = val; }

#endif /* TEST_SYNTAX_STATICFUNCTION_U8_HELP_H */
