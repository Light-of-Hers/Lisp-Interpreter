#include "../include/eval-comb.h"
#include "../include/eval.h"
#include "../include/symbol.h"
#include "../include/util.h"

namespace le {

bool is_comb(valp_t exp) {
    return CHECK(exp, PAIR);
}
valp_t comb_part(valp_t exp, COMB part) {
    if (part == COMB::OPT) {
        return car(exp);
    } else {
        return cdr(exp);
    }
}
valp_t eval_comb(valp_t exp, env_t env) {
    auto opt = comb_part(exp, COMB::OPT);
    auto oprs = comb_part(exp, COMB::OPRS);
    return apply(eval(opt, env),
                 map(oprs, [=](valp_t x) { return eval(x, env); }));
}

}; // namespace le
