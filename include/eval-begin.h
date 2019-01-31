#ifndef _eval_begin_h_
#define _eval_begin_h_

#include "env.h"
#include "value.h"

namespace le {

bool is_begin(valp_t exp);
valp_t begin_actions(valp_t exp);
valp_t eval_seq(valp_t exps, env_t env);
valp_t seq2exp(valp_t seq);

bool is_while(valp_t exp);
valp_t eval_while(valp_t exp, env_t env);
valp_t make_while(valp_t pred, valp_t body);

bool is_for(valp_t exp);
valp_t for2while(valp_t exp);

}; // namespace le

#endif