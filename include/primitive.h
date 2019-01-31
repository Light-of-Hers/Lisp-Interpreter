#ifndef _primitive_h_
#define _primitive_h_

#include "env.h"
#include "value.h"

namespace le {

void pp_init(env_t env);
bool is_pp(valp_t proc);
valp_t apply_pp(valp_t proc, valp_t args);

}; // namespace le

#endif