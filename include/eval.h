#ifndef _eval_h_
#define _eval_h_

#include "env.h"
#include "value.h"

namespace le {

valp_t eval(valp_t exp, env_t env);
valp_t apply(valp_t proc, valp_t args);

}; // namespace le

#endif