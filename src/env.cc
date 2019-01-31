#include "../include/env.h"
#include "../include/error.h"
#include "../include/util.h"
#include <cassert>

namespace le {

valp_t lookup(env_t env, symbol_t var) {
    if (env == nullptr)
        normal_err("Unbound Variable", st_getval(var));
    auto &mp = GET(car(env), svmap_t);
    auto it = mp.find(var);
    if (it == mp.end()) {
        return lookup(cdr(env), var);
    } else {
        if (eq(it->second, st_getval(BASE::UNASS)))
            normal_err("Unassigned Variable", st_getval(var));
        return it->second;
    }
}

void set_var(env_t env, symbol_t var, valp_t val) {
    if (env == nullptr)
        normal_err("Unbound Variable", st_getval(var));
    auto &mp = GET(car(env), svmap_t);
    auto it = mp.find(var);
    if (it == mp.end()) {
        set_var(cdr(env), var, val);
    } else {
        it->second = val;
    }
}

void define_var(env_t env, symbol_t var, valp_t val) {
    GET(car(env), svmap_t)[var] = val;
}

valp_t extend_env(env_t env, valp_t vars, valp_t vals) {
    frame_t f = cons(make(svmap_t()), env);
    auto &mp = GET(car(f), svmap_t);
    while (vars && vals && CHECK(vars, PAIR)) {
        mp[GET(car(vars), symbol_t)] = car(vals);
        vars = cdr(vars), vals = cdr(vals);
    }
    if (vars != nullptr && !CHECK(vars, PAIR))
        mp[GET(vars, symbol_t)] = vals;
    else {
        if (vars != nullptr && vals == nullptr)
            normal_err("Too Few Arguments", vals);
        if (vals != nullptr && vars == nullptr)
            normal_err("Too Many Arguments", vals);
    }
    return f;
}

}; // namespace le