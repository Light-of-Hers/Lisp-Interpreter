#include "../include/eval-lambda.h"
#include "../include/error.h"
#include "../include/eval-assign.h"
#include "../include/eval-begin.h"
#include "../include/eval-define.h"
#include "../include/symbol.h"
#include "../include/util.h"

namespace le {

bool is_lambda(valp_t exp) {
    return tag_list(exp, BASE::LAMBDA);
}
valp_t lambda_part(valp_t exp, LAMBDA part) {
    if (part == LAMBDA::ARGS) {
        return ref(exp, 1);
    } else {
        return cdr(cdr(exp));
    }
}
valp_t make_lambda(valp_t args, valp_t body) {
    return cons(st_getval(BASE::LAMBDA), cons(args, body));
}
valp_t eval_lambda(valp_t exp, env_t env) {
    return make_proc(lambda_part(exp, LAMBDA::ARGS),
                     lambda_part(exp, LAMBDA::BODY), env);
}

bool is_proc(valp_t exp) {
    return tag_list(exp, BASE::PROC);
}
valp_t proc_part(valp_t exp, PROC part) {
    return ref(exp, (int)part);
}
valp_t make_proc(valp_t args, valp_t body, env_t env) {
    return make_list({st_getval(BASE::PROC), args, body_scan(body), env});
}

bool is_let(valp_t exp) {
    return tag_list(exp, BASE::LET);
}
static bool is_named_let(valp_t exp) {
    return CHECK(ref(exp, 1), SYMBOL);
}
static valp_t let_part(valp_t exp, LET part) {
    if (is_named_let(exp)) {
        if (part == LET::BINDS) {
            return ref(exp, 2);
        } else if (part == LET::BODY) {
            return cdr(cdr(cdr(exp)));
        } else {
            return ref(exp, 1);
        }
    } else {
        if (part == LET::BINDS) {
            return ref(exp, 1);
        } else if (part == LET::BODY) {
            return cdr(cdr(exp));
        } else {
            normal_err("Syntax Error", exp);
            return nullptr;
        }
    }
}
valp_t let2exp(valp_t exp) {
    auto binds = let_part(exp, LET::BINDS);
    auto body = let_part(exp, LET::BODY);
    auto vars = map(binds, car);
    auto vals = map(binds, [](valp_t x) { return car(cdr(x)); });
    if (is_named_let(exp)) {
        auto name = let_part(exp, LET::NAME);
        return seq2exp(make_list(
            {make_define(name, make_lambda(vars, body)), cons(name, vals)}));
    } else {
        if (vars == nullptr)
            return seq2exp(body);
        return cons(make_lambda(vars, body), vals);
    }
}
valp_t make_let(valp_t binds, valp_t body) {
    return cons(st_getval(BASE::LET), cons(binds, body));
}
valp_t make1let(valp_t var, valp_t val, valp_t body) {
    valp_t binds = make_list({make_list({var, val})});
    return make_let(binds, body);
}

bool is_let_(valp_t exp) {
    return tag_list(exp, BASE::LET_);
}
static valp_t let_2lets_aux(valp_t binds, valp_t body) {
    if (binds == nullptr) {
        return seq2exp(body);
    } else if (cdr(binds) == nullptr) {
        auto var = ref(car(binds), 0);
        auto val = ref(car(binds), 1);
        return make1let(var, val, body);
    } else {
        auto var = ref(car(binds), 0);
        auto val = ref(car(binds), 1);
        return make1let(var, val, make_list({let_2lets_aux(cdr(binds), body)}));
    }
}
valp_t let_2lets(valp_t exp) {
    auto binds = ref(exp, 1);
    auto body = cdr(cdr(exp));
    return let_2lets_aux(binds, body);
}

valp_t body_scan(valp_t body) {
    auto vvs = map(filter(body, is_define), [](valp_t x) {
        return cons(define_part(x, DEFINE::VAR), define_part(x, DEFINE::VAL));
    });
    auto others = filter(body, std::not_fn(is_define));
    auto binds = map(vvs, [](valp_t x) {
        return make_list({car(x), st_getval(BASE::UNASS)});
    });
    auto sets = map(vvs, [](valp_t x) { return make_assign(car(x), cdr(x)); });
    return make_list({make_let(binds, append(sets, others))});
}

}; // namespace le