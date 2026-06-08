#include "Syntax_AdvanceLocalState_help.h"

/* FUNCTION TO TEST */
MyLib_LocalState_t Syntax_AdvanceLocalState(bool error_b) {
  if(error_b) {
    SyntaxCurrentState = MYLIB_LOCAL_STATE_ERROR;
  } else {
    SyntaxCurrentState = MYLIB_LOCAL_STATE_READY;
  }

  return SyntaxCurrentState;
}