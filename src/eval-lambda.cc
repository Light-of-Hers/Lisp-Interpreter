#include "../include/eval-lambda.h"
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
    return make_list(
        {st_getval(BASE::PROC), args, body, env});
}

bool is_let(valp_t exp) {
    return tag_list(exp, BASE::LET);
}
valp_t let2lambda(valp_t exp) {
    valp_t binds = ref(exp, 1);
    valp_t body = cdr(cdr(exp));
    valp_t vars = map(binds, car);
    valp_t vals =
        map(binds, [](valp_t x) { return car(cdr(x)); });

    return cons(make_lambda(vars, body), vals);
}
valp_t make_let(valp_t binds, valp_t body) {
    return cons(st_getval(BASE::LET), cons(binds, body));
}
valp_t make1let(valp_t var, valp_t val, valp_t body) {
    valp_t binds = make_list({make_list({var, val})});
    return make_let(binds, body);
}

}; // namespace le