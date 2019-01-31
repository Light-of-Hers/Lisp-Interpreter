#ifndef _error_h_
#define _error_h_

#include "value.h"
#include <string>

namespace le {

enum class ERR_LV { NORMAL, FATAL };
struct error_t {
    ERR_LV lv;
    std::string msg;
};

void normal_err(const std::string &msg, valp_t exp);
void normal_err(const std::string &msg);
void fatal_err(const std::string &msg, valp_t exp);
void fatal_err(const std::string &msg);

}; // namespace le

#endif