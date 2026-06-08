#ifndef TEST_SYNTAX_READSTATICARRAYANDCONSTTABLE_U16_H
#define TEST_SYNTAX_READSTATICARRAYANDCONSTTABLE_U16_H

#include "AleLib.h"

#include <stddef.h>
#include <string.h>

/**
 * @brief Function using static arrays declared at translation-unit scope.
 */
uint16_t Syntax_ReadStaticArrayAndConstTable_u16(uint8_t index_u8);

const uint16_t* get_SyntaxConstTable_au16_ptr(void);
size_t get_SyntaxConstTable_au16_size(void);
void set_SyntaxConstTable_au16(const const uint16_t* src, size_t n);
uint8_t* get_SyntaxStaticArray_au8_ptr(void);
size_t get_SyntaxStaticArray_au8_size(void);
void set_SyntaxStaticArray_au8(const uint8_t* src, size_t n);

#endif /* TEST_SYNTAX_READSTATICARRAYANDCONSTTABLE_U16_H */
