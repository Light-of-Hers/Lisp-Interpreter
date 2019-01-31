#include "../include/error.h"

namespace le {

static void error(ERR_LV lv, const std::string &msg, valp_t exp) {
    throw error_t({lv, "Error: " + msg + " : " + val2str(exp)});
}
static void error(ERR_LV lv, const std::string &msg) {
    throw error_t({lv, msg});
}

void normal_err(const std::string &msg, valp_t exp) {
    error(ERR_LV::NORMAL, msg, exp);
}
void normal_err(const std::string &msg) {
    error(ERR_LV::NORMAL, msg);
}

void fatal_err(const std::string &msg, valp_t exp) {
    error(ERR_LV::FATAL, msg, exp);
}
void fatal_err(const std::string &msg) {
    error(ERR_LV::FATAL, msg);
}

}; // namespace le