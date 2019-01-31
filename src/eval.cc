#include "../include/eval.h"
#include "../include/env.h"
#include "../include/error.h"
#include "../include/eval-assign.h"
#include "../include/eval-begin.h"
#include "../include/eval-comb.h"
#include "../include/eval-define.h"
#include "../include/eval-if.h"
#include "../include/eval-lambda.h"
#include "../include/primitive.h"
#include "../include/symbol.h"
#include "../include/util.h"
#include <cassert>
#include <iostream>

namespace le {

static bool is_self_eval(valp_t exp) {
    return CHECK(exp, NUMBER) || CHECK(exp, STRING) || CHECK(exp, BOOLEAN) ||
           eq(exp, st_getval(BASE::UNASS));
}
static bool is_var(valp_t exp) {
    return CHECK(exp, SYMBOL);
}
static bool is_quote(valp_t exp) {
    return tag_list(exp, BASE::QUOTE);
}
static valp_t quote_text(valp_t exp) {
    return car(cdr(exp));
}

valp_t eval(valp_t exp, env_t env) {
    if (is_self_eval(exp)) {
        return exp;
    } else if (is_var(exp)) {
        return lookup(env, GET(exp, symbol_t));
    } else if (is_quote(exp)) {
        return quote_text(exp);
    } else if (is_define(exp)) {
        return eval_define(exp, env);
    } else if (is_assign(exp)) {
        return eval_assign(exp, env);
    } else if (is_begin(exp)) {
        return eval_seq(begin_actions(exp), env);
    } else if (is_lambda(exp)) {
        return eval_lambda(exp, env);
    } else if (is_if(exp)) {
        return eval_if(exp, env);
    } else if (is_let(exp)) {
        return eval(let2exp(exp), env);
    } else if (is_let_(exp)) {
        return eval(let_2lets(exp), env);
    } else if (is_cond(exp)) {
        return eval(cond2if(exp), env);
    } else if (is_and(exp)) {
        return eval(and2if(exp), env);
    } else if (is_or(exp)) {
        return eval(or2if(exp), env);
    } else if (is_while(exp)) {
        return eval_while(exp, env);
    } else if (is_for(exp)) {
        return eval(for2while(exp), env);
    } else if (is_comb(exp)) {
        return eval_comb(exp, env);
    } else {
        normal_err("Unknown Expression", exp);
    }
    return nullptr;
}

valp_t apply(valp_t proc, valp_t args) {
    if (is_pp(proc)) {
        return apply_pp(proc, args);
    } else {
        auto body = proc_part(proc, PROC::BODY);
        auto vars = proc_part(proc, PROC::ARGS);
        auto env = proc_part(proc, PROC::ENV);
        return eval_seq(body, extend_env(env, vars, args));
    }
}

}; // namespace le