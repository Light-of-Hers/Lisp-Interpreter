#include "../include/value.h"
#include "../include/error.h"
#include "../include/symbol.h"
#include <sstream>

namespace le {

valp_t cons(valp_t a, valp_t b) {
    return valp_t(new value_t(a, b));
}
valp_t &car(valp_t x) {
    if (x == nullptr || !CHECK(x, PAIR))
        normal_err("Not a pair", x);
    return GET(x, pair_t).chld[0];
}
valp_t &cdr(valp_t x) {
    if (x == nullptr || !CHECK(x, PAIR))
        normal_err("Not a pair", x);
    return GET(x, pair_t).chld[1];
}

const string_t val2str(valp_t v) {
    if (v == nullptr)
        return "()";
    std::ostringstream sout;
    if (CHECK(v, NUMBER)) {
        sout << GET(v, number_t);
    } else if (CHECK(v, STRING)) {
        sout << GET(v, string_t);
    } else if (CHECK(v, BOOLEAN)) {
        sout << (GET(v, boolean_t) ? "#t" : "#f");
    } else if (CHECK(v, SYMBOL)) {
        sout << st_getstr(GET(v, symbol_t));
    } else if (CHECK(v, SVMAP)) {
        sout << "**environment**";
        auto &mp = GET(v, svmap_t);
        for (auto e : mp) {
            sout << " (" << st_getstr(e.first) << ")";
        }
    } else {
        sout << "(";
        while (cdr(v) && CHECK(cdr(v), PAIR)) {
            sout << val2str(car(v)) << " ";
            v = cdr(v);
        }
        if (cdr(v)) {
            sout << val2str(car(v)) << " . " << val2str(cdr(v));
        } else {
            sout << val2str(car(v));
        }
        sout << ")";
    }
    return sout.str();
}

}; // namespace le