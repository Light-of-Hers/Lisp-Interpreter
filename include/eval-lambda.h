#ifndef _eval_lambda_h_
#define _eval_lambda_h_

#include "env.h"
#include "value.h"

namespace le {

enum class LAMBDA { ARGS, BODY };

bool is_lambda(valp_t exp);
valp_t lambda_part(valp_t exp, LAMBDA part);
valp_t make_lambda(valp_t args, valp_t body);
valp_t eval_lambda(valp_t exp, env_t env);

enum class PROC { ARGS = 1, BODY = 2, ENV = 3 };

bool is_proc(valp_t exp);
valp_t proc_part(valp_t exp, PROC part);
valp_t make_proc(valp_t args, valp_t body, env_t env);

bool is_let(valp_t exp);
valp_t let2lambda(valp_t exp);
valp_t make_let(valp_t binds, valp_t body);
valp_t make1let(valp_t var, valp_t val, valp_t body);

}; // namespace le

#endif