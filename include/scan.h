#ifndef _scan_h_
#define _scan_h_

#include "value.h"
#include <variant>
#include <vector>

namespace le {

struct token_t {
    enum type_t {
        LEFT_BRACKET,
        RIGHT_BRACKET,
        DOT,
        QUOTE,
        SYMBOL,
        NUMBER,
        STRING,
        BOOLEAN
    } type;
    std::variant<symbol_t, number_t, string_t, boolean_t> attr;

    token_t() = default;
    token_t(type_t t) : type(t) {}
    token_t(number_t x) : type(NUMBER), attr(x) {}
    token_t(const string_t &x) : type(STRING), attr(x) {}
    token_t(symbol_t x) : type(SYMBOL), attr(x) {}
    token_t(boolean_t x) : type(BOOLEAN), attr(x) {}

    const string_t str() const;
};

typedef std::vector<token_t> vtoken_t;

vtoken_t scan(const string_t &code);

}; // namespace le

#endif