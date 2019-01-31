#ifndef _value_h_
#define _value_h_

#include <map>
#include <memory>
#include <string>
#include <variant>

namespace le {

struct value_t;
typedef std::shared_ptr<value_t> valp_t;

struct pair_t;
typedef int symbol_t;
typedef double number_t;
typedef std::string string_t;
typedef bool boolean_t;
typedef std::map<symbol_t, valp_t> svmap_t;

struct pair_t {
    valp_t chld[2];
};
struct value_t {
    enum type_t { SYMBOL, PAIR, NUMBER, STRING, BOOLEAN, SVMAP } type;
    std::variant<symbol_t, pair_t, number_t, string_t, boolean_t, svmap_t> data;

    value_t(valp_t a, valp_t b) : type(PAIR), data(pair_t{a, b}) {
    }
    value_t(symbol_t x) : type(SYMBOL), data(x) {
    }
    value_t(number_t x) : type(NUMBER), data(x) {
    }
    value_t(const string_t &x) : type(STRING), data(x) {
    }
    value_t(boolean_t x) : type(BOOLEAN), data(x) {
    }
    value_t(svmap_t x) : type(SVMAP), data(x) {
    }
};
const string_t val2str(valp_t v);

valp_t cons(valp_t a, valp_t b);
valp_t &car(valp_t x);
valp_t &cdr(valp_t x);

template <class T> T &get_val(valp_t vp) {
    return std::get<T>(vp->data);
}
template <class T> valp_t make(const T &t) {
    return valp_t(new value_t(t));
}

#define GET(vp, t) (get_val<t>(vp))
#define CHECK(vp, t) ((vp) != nullptr && (vp)->type == (vp)->t)

}; // namespace le

#endif