#ifndef _eval_assign_h_
#define _eval_assign_h_

#include "value.h"

namespace le {

enum class ASSIGN { VAR = 1, VAL = 2 };

bool is_assign(valp_t exp);
valp_t eval_assign(valp_t exp, valp_t env);
valp_t assign_part(valp_t exp, ASSIGN part);
valp_t make_assign(valp_t var, valp_t val);

}; // namespace le

#endif