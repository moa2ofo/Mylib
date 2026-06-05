#ifndef TEST_UNIT_BF679415_MYLIB_UPDATEGLOBALRECORD_HELP_H
#define TEST_UNIT_BF679415_MYLIB_UPDATEGLOBALRECORD_HELP_H

#include "unit_bf679415_MyLib_UpdateGlobalRecord.h"
#include <stddef.h>
#include <string.h>

/* non-static globals used by the function under test */
MyLib_record_t g_record = {0U, 0U};
bool g_systemReady_b = false;

#endif /* TEST_UNIT_BF679415_MYLIB_UPDATEGLOBALRECORD_HELP_H */
