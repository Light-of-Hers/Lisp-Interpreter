#ifndef _env_h_
#define _env_h_

#include "value.h"

namespace le {

typedef valp_t env_t, frame_t;
// frame : (svmap, outer-env)

valp_t lookup(env_t env, symbol_t var);
void set_var(env_t env, symbol_t var, valp_t val);
void define_var(env_t env, symbol_t var, valp_t val);
valp_t extend_env(env_t env, valp_t vars, valp_t vals);

}; // namespace le

#endif