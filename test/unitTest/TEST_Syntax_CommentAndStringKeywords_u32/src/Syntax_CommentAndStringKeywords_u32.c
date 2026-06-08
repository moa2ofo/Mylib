#include "Syntax_CommentAndStringKeywords_u32_help.h"

/* FUNCTION TO TEST */
uint32_t Syntax_CommentAndStringKeywords_u32(void) {
  const char *l_localText_pc = "inline static text";

  /* static inline should remain unchanged in comments. */
  if((l_localText_pc[0] == 'i') && (SyntaxTextWithKeywords[0] == 's')) {
    return 1U;
  }

  return 0U;
}