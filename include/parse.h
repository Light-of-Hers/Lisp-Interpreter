#ifndef _parse_h_
#define _parse_h_

#include "scan.h"
#include "value.h"

namespace le {
valp_t parse(const vtoken_t &tks);
};

#endif