#include "../include/eval-define.h"
#include "../include/env.h"
#include "../include/eval-lambda.h"
#include "../include/eval.h"
#include "../include/symbol.h"
#include "../include/util.h"

namespace le {

static inline bool is_candy(valp_t exp) {
    return CHECK(ref(exp, 1), PAIR);
}

bool is_define(valp_t exp) {
    return tag_list(exp, BASE::DEFINE);
}

valp_t define_part(valp_t exp, DEFINE part) {
    if (part == DEFINE::VAR) {
        if (is_candy(exp)) {
            return car(ref(exp, 1));
        } else {
            return ref(exp, 1);
        }
    } else {
        if (is_candy(exp)) {
            return make_lambda(cdr(ref(exp, 1)), cdr(cdr(exp)));
        } else {
            return ref(exp, 2);
        }
    }
}

valp_t make_define(valp_t var, valp_t val) {
    return make_list({st_getval(BASE::DEFINE), var, val});
}

valp_t eval_define(valp_t exp, valp_t env) {
    auto var = define_part(exp, DEFINE::VAR);
    auto val = define_part(exp, DEFINE::VAL);
    define_var(env, GET(var, symbol_t), eval(val, env));
    return st_getval(BASE::OK);
}

}; // namespace le