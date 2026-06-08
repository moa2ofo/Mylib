#ifndef TEST_SYNTAX_ADVANCELOCALSTATE_HELP_H
#define TEST_SYNTAX_ADVANCELOCALSTATE_HELP_H

#include "Syntax_AdvanceLocalState.h"
#include <stddef.h>
#include <string.h>

/* static globals (copied) */
static MyLib_LocalState_t SyntaxCurrentState = MYLIB_LOCAL_STATE_INIT;
MyLib_LocalState_t get_SyntaxCurrentState(void) { return SyntaxCurrentState; }
void set_SyntaxCurrentState(MyLib_LocalState_t val) { SyntaxCurrentState = val; }

#endif /* TEST_SYNTAX_ADVANCELOCALSTATE_HELP_H */
