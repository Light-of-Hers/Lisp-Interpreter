#include "../include/eval-begin.h"
#include "../include/eval-lambda.h"
#include "../include/eval.h"
#include "../include/symbol.h"
#include "../include/util.h"

namespace le {

bool is_begin(valp_t exp) {
    return tag_list(exp, BASE::BEGIN);
}
valp_t begin_actions(valp_t exp) {
    return cdr(exp);
}
static valp_t make_begin(valp_t exps) {
    return cons(st_getval(BASE::BEGIN), exps);
}
valp_t eval_seq(valp_t exps, env_t env) {
    if (exps == nullptr) {
        return nullptr;
    } else {
        while (cdr(exps)) {
            (void)eval(car(exps), env);
            exps = cdr(exps);
        }
        return eval(car(exps), env);
    }
}
valp_t seq2exp(valp_t seq) {
    if (seq == nullptr) {
        return nullptr;
    } else if (cdr(seq) == nullptr) {
        return car(seq);
    } else {
        return make_begin(seq);
    }
}

bool is_while(valp_t exp) {
    return tag_list(exp, BASE::WHILE);
}
valp_t eval_while(valp_t exp, env_t env) {
    valp_t pred = ref(exp, 1);
    valp_t actions = cdr(cdr(exp));
    while (is_true(eval(pred, env))) {
        eval_seq(actions, env);
    }
    return st_getval(BASE::OK);
}
valp_t make_while(valp_t pred, valp_t body) {
    return cons(st_getval(BASE::WHILE), cons(pred, body));
}

bool is_for(valp_t exp) {
    return tag_list(exp, BASE::FOR);
}
valp_t for2while(valp_t exp) {
    valp_t binds = ref(exp, 1);
    valp_t pred = ref(exp, 2);
    valp_t updates = ref(exp, 3);
    valp_t body = cdr(cdr(cdr(cdr(exp))));
    body = append(body, updates);
    return make_let(binds, make_list({make_while(pred, body)}));
}

}; // namespace le