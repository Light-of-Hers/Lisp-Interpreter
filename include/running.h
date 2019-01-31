#ifndef _running_h_
#define _running_h_

#include "env.h"
#include <iostream>
#include <string>

namespace le {

std::istream &read(std::istream &is, std::string &code);
env_t setup_env();
void driver(env_t env);
void load_file(env_t env, const std::string &filename);

}; // namespace le

#endif