#ifndef _eval_define_h_
#define _eval_define_h_

#include "value.h"

namespace le {

enum class DEFINE { VAR, VAL };

bool is_define(valp_t exp);
valp_t eval_define(valp_t exp, valp_t env);
valp_t define_part(valp_t exp, DEFINE part);
valp_t make_define(valp_t var, valp_t val);

}; // namespace le

#endif