#include "../include/primitive.h"
#include "../include/env.h"
#include "../include/error.h"
#include "../include/eval.h"
#include "../include/parse.h"
#include "../include/running.h"
#include "../include/scan.h"
#include "../include/symbol.h"
#include "../include/util.h"
#include <cassert>
#include <cmath>
#include <functional>
#include <iostream>
#include <sstream>
#include <utility>
#include <vector>

namespace le {

#define PP(body) ([](valp_t args) -> valp_t body)

static void argcnt_err(int expect, int real, valp_t exp) {
    std::ostringstream sout;
    sout << "Argument Count Error, Expect " << expect << ", But Given " << real;
    normal_err(sout.str(), exp);
}
static void expect(int n, valp_t args) {
    int len = length(args);
    if (len != n) argcnt_err(n, len, args);
}

static valp_t plus(valp_t args) {
    number_t res = 0;
    while (args) {
        res += GET(car(args), number_t);
        args = cdr(args);
    }
    return make(res);
}
static valp_t minus(valp_t args) {
    if (args == nullptr) normal_err("At Least 1 Argument");
    number_t res = GET(car(args), number_t);
    args = cdr(args);
    while (args) {
        res -= GET(car(args), number_t);
        args = cdr(args);
    }
    return make(res);
}
static valp_t mult(valp_t args) {
    number_t res = 1;
    while (args) {
        res *= GET(car(args), number_t);
        args = cdr(args);
    }
    return make(res);
}
static valp_t divide(valp_t args) {
    if (args == nullptr) normal_err("At Least 1 Argument");
    number_t res = GET(car(args), number_t);
    args = cdr(args);
    while (args) {
        res /= GET(car(args), number_t);
        args = cdr(args);
    }
    return make(res);
}
static valp_t rem(valp_t args) {
    expect(2, args);
    number_t a = GET(ref(args, 0), number_t);
    number_t b = GET(ref(args, 1), number_t);
    if (a != std::floor(a) || b != std::floor(b))
        normal_err("Argument Error, Expect 2 Integer");
    return make((number_t)((int)a % (int)b));
}
static valp_t cons_(valp_t args) {
    expect(2, args);
    return cons(ref(args, 0), ref(args, 1));
}
static valp_t car_(valp_t args) {
    expect(1, args);
    return car(ref(args, 0));
}
static valp_t cdr_(valp_t args) {
    expect(1, args);
    return cdr(ref(args, 0));
}
static valp_t set_car_(valp_t args) {
    expect(2, args);
    car(ref(args, 0)) = ref(args, 1);
    return st_getval(BASE::OK);
}
static valp_t set_cdr_(valp_t args) {
    expect(2, args);
    cdr(ref(args, 0)) = ref(args, 1);
    return st_getval(BASE::OK);
}
static valp_t list_(valp_t args) {
    return args;
}
#define EPS 1e-8
static int dcmp(double a, double b) {
    if (a - b > EPS) {
        return 1;
    } else if (b - a > EPS) {
        return -1;
    } else {
        return 0;
    }
}
static int nb_cmp(valp_t args) {
    expect(2, args);
    number_t a = GET(ref(args, 0), number_t);
    number_t b = GET(ref(args, 1), number_t);
    return dcmp(a, b);
}
static valp_t nb_l(valp_t args) {
    return st_getbool(nb_cmp(args) == -1);
}
static valp_t nb_g(valp_t args) {
    return st_getbool(nb_cmp(args) == 1);
}
static valp_t nb_e(valp_t args) {
    return st_getbool(nb_cmp(args) == 0);
}
static valp_t nb_le(valp_t args) {
    int res = nb_cmp(args);
    return st_getbool(res == 0 || res == -1);
}
static valp_t nb_ge(valp_t args) {
    int res = nb_cmp(args);
    return st_getbool(res == 0 || res == 1);
}

static valp_t sb_eq(valp_t args) {
    expect(2, args);
    valp_t a = ref(args, 0), b = ref(args, 1);
    return st_getbool(eq(a, b));
}

static valp_t check_(valp_t args, value_t::type_t t) {
    expect(1, args);
    return st_getbool(car(args) && car(args)->type == t);
}

typedef std::function<valp_t(valp_t)> pp_t;
std::vector<std::pair<string_t, pp_t>> pp_tab{
    {"+", plus},
    {"-", minus},
    {"*", mult},
    {"/", divide},
    {"\%", rem},
    {"cons", cons_},
    {"car", car_},
    {"cdr", cdr_},
    {"<", nb_l},
    {">", nb_g},
    {"=", nb_e},
    {"<=", nb_le},
    {">=", nb_ge},
    {"eq?", sb_eq},
    {"list", list_},
    {"symbol?", PP({ return check_(args, value_t::SYMBOL); })},
    {"number?", PP({ return check_(args, value_t::NUMBER); })},
    {"boolean?", PP({ return check_(args, value_t::BOOLEAN); })},
    {"string?", PP({ return check_(args, value_t::STRING); })},
    {"pair?", PP({ return check_(args, value_t::PAIR); })},
    {"not", PP({
         expect(1, args);
         return st_getbool(!is_true(car(args)));
     })},
    {"set-car!", set_car_},
    {"set-cdr!", set_cdr_},
    {"null?", PP({
         expect(1, args);
         return st_getbool(car(args) == nullptr);
     })},
    {"apply", PP({
         expect(2, args);
         return apply(ref(args, 0), ref(args, 1));
     })}};

static valp_t make_pp(int idx) {
    return make_list({st_getval(BASE::PRIM), make((double)idx)});
}
static int pp_idx(valp_t pp) {
    return (int)GET(ref(pp, 1), number_t);
}

bool is_pp(valp_t proc) {
    return tag_list(proc, BASE::PRIM);
}
void pp_init(env_t env) {
    int len = pp_tab.size();
    for (int i = 0; i < len; ++i) {
        define_var(env, st_add(pp_tab[i].first), make_pp(i));
    }
}
valp_t apply_pp(valp_t proc, valp_t args) {
    return pp_tab[pp_idx(proc)].second(args);
}
}; // namespace le