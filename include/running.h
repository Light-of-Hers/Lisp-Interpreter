#ifndef _running_h_
#define _running_h_

#include "env.h"
#include <string>

namespace le {

env_t setup_env();
void driver(env_t env);
void load_file(env_t env, const std::string &filename);

}; // namespace le

#endif