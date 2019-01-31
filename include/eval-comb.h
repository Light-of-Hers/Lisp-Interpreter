#ifndef _eval_comb_h_
#define _eval_comb_h_

#include "env.h"
#include "value.h"

namespace le {

enum class COMB { OPT, OPRS };

bool is_comb(valp_t exp);
valp_t comb_part(valp_t exp, COMB part);
valp_t eval_comb(valp_t exp, env_t env);

}; // namespace le

#endif