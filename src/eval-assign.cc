#include "../include/eval-assign.h"
#include "../include/env.h"
#include "../include/eval.h"
#include "../include/symbol.h"
#include "../include/util.h"

namespace le {

bool is_assign(valp_t exp) {
    return tag_list(exp, BASE::SET);
}

valp_t assign_part(valp_t exp, ASSIGN part) {
    return ref(exp, (int)part);
}

valp_t eval_assign(valp_t exp, valp_t env) {
    auto var = assign_part(exp, ASSIGN::VAR);
    auto val = assign_part(exp, ASSIGN::VAL);
    set_var(env, GET(var, symbol_t), eval(val, env));
    return st_getval(BASE::OK);
}

valp_t make_assign(valp_t var, valp_t val) {
    return make_list({st_getval(BASE::SET), var, val});
}

}; // namespace le