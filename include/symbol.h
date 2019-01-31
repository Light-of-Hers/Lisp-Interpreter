#ifndef _symbol_h_
#define _symbol_h_

#include "value.h"
#include <string>

namespace le {

enum class BASE {
    DEFINE = 0,
    SET,
    LAMBDA,
    BEGIN,
    IF,
    COND,
    OK,
    PROC,
    QUOTE,
    PRIM,
    ELSE,
    AND,
    LET,
    OR,
    OR_TEST,
    WHILE,
    FOR
};

void st_init();
const symbol_t st_add(const string_t &s);
const symbol_t st_getsb(const string_t &s);
const string_t st_getstr(symbol_t sb);
valp_t st_getval(symbol_t sb);
valp_t st_getval(BASE sb);

valp_t st_getbool(bool bl);

}; // namespace le

#endif