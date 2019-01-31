#ifndef _eval_if_h_
#define _eval_if_h_

#include "env.h"
#include "value.h"

namespace le {

enum class IF { PRED = 1, THEN = 2, ALTER = 3 };

bool is_if(valp_t exp);
valp_t if_part(valp_t exp, IF part);
valp_t make_if(valp_t pred, valp_t then, valp_t alter);
valp_t eval_if(valp_t expr, env_t env);

bool is_cond(valp_t exp);
valp_t cond2if(valp_t exp);

bool is_and(valp_t exp);
valp_t and2if(valp_t exp);

bool is_or(valp_t exp);
valp_t or2if(valp_t exp);

}; // namespace le

#endif