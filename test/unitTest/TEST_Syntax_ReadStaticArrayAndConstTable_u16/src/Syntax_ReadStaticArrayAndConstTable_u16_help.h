#ifndef TEST_SYNTAX_READSTATICARRAYANDCONSTTABLE_U16_HELP_H
#define TEST_SYNTAX_READSTATICARRAYANDCONSTTABLE_U16_HELP_H

#include "Syntax_ReadStaticArrayAndConstTable_u16.h"
#include <stddef.h>
#include <string.h>

/* static globals (copied) */
static const uint16_t SyntaxConstTable_au16[] = {10U, 20U, 30U};
const uint16_t* get_SyntaxConstTable_au16_ptr(void) { return SyntaxConstTable_au16; }
size_t get_SyntaxConstTable_au16_size(void) { return (size_t)3; }
void set_SyntaxConstTable_au16(const const uint16_t* src, size_t n) {
    size_t m = (n < (size_t)3) ? n : (size_t)3;
    memcpy(SyntaxConstTable_au16, src, m * sizeof(const uint16_t));
}
static uint8_t SyntaxStaticArray_au8[5] = {1U, 2U, 3U, 4U, 5U};
uint8_t* get_SyntaxStaticArray_au8_ptr(void) { return SyntaxStaticArray_au8; }
size_t get_SyntaxStaticArray_au8_size(void) { return (size_t)5; }
void set_SyntaxStaticArray_au8(const uint8_t* src, size_t n) {
    size_t m = (n < (size_t)5) ? n : (size_t)5;
    memcpy(SyntaxStaticArray_au8, src, m * sizeof(uint8_t));
}

#endif /* TEST_SYNTAX_READSTATICARRAYANDCONSTTABLE_U16_HELP_H */
