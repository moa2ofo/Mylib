#ifndef TEST_SYNTAX_ADVANCELOCALSTATE_H
#define TEST_SYNTAX_ADVANCELOCALSTATE_H

#include "AleLib.h"

/**
 * @brief Function using a local enum stored in a static global.
 */
MyLib_LocalState_t Syntax_AdvanceLocalState(_Bool error_b);

MyLib_LocalState_t get_SyntaxCurrentState(void);
void set_SyntaxCurrentState(MyLib_LocalState_t val);

#endif /* TEST_SYNTAX_ADVANCELOCALSTATE_H */
