#include "../include/eval-if.h"
#include "../include/error.h"
#include "../include/eval-begin.h"
#include "../include/eval-lambda.h"
#include "../include/eval.h"
#include "../include/symbol.h"
#include "../include/util.h"

namespace le {

bool is_if(valp_t exp) {
    return tag_list(exp, BASE::IF);
}
valp_t if_part(valp_t exp, IF part) {
    return ref(exp, (int)part);
}
valp_t make_if(valp_t pred, valp_t then, valp_t alter) {
    return make_list({st_getval(BASE::IF), pred, then, alter});
}
valp_t eval_if(valp_t exp, env_t env) {
    if (is_true(eval(if_part(exp, IF::PRED), env))) {
        return eval(if_part(exp, IF::THEN), env);
    } else {
        return eval(if_part(exp, IF::ALTER), env);
    }
}

bool is_cond(valp_t exp) {
    return tag_list(exp, BASE::COND);
}
static valp_t cond_clss(valp_t exp) {
    return cdr(exp);
}
static valp_t cls_pred(valp_t cls) {
    return car(cls);
}
static valp_t cls_actions(valp_t cls) {
    return cdr(cls);
}
static valp_t cond2if_aux(valp_t clss) {
    if (clss == nullptr)
        return st_getbool(false);
    valp_t cls = car(clss);
    valp_t pred = cls_pred(cls);
    if (eq(pred, st_getval(BASE::ELSE))) {
        if (cdr(clss) != nullptr)
            normal_err("Else's Not the Last", clss);
        return seq2exp(cls_actions(cls));
    } else {
        return make_if(pred, seq2exp(cls_actions(cls)), cond2if_aux(cdr(clss)));
    }
}
valp_t cond2if(valp_t exp) {
    return cond2if_aux(cond_clss(exp));
}

bool is_and(valp_t exp) {
    return tag_list(exp, BASE::AND);
}
static valp_t and2if_aux(valp_t exps) {
    if (exps == nullptr) {
        return st_getbool(true);
    } else if (cdr(exps) == nullptr) {
        return car(exps);
    } else {
        return make_if(car(exps), and2if_aux(cdr(exps)), st_getbool(false));
    }
}
valp_t and2if(valp_t exp) {
    return and2if_aux(cdr(exp));
}

bool is_or(valp_t exp) {
    return tag_list(exp, BASE::OR);
}
static valp_t or2if_aux(valp_t exps) {
    valp_t or_test = st_getval(BASE::OR_TEST);
    if (exps == nullptr) {
        return st_getbool(false);
    } else {
        return make1let(
            or_test, car(exps),
            make_list({make_if(or_test, or_test, or2if_aux(cdr(exps)))}));
    }
}
valp_t or2if(valp_t exp) {
    return or2if_aux(cdr(exp));
}

}; // namespace le