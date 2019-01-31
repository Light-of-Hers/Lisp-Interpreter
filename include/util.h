#ifndef _util_h_
#define _util_h_

#include "symbol.h"
#include "value.h"
#include <functional>
#include <vector>

namespace le {

valp_t make_list(std::vector<valp_t> lst);
valp_t ref(valp_t lst, int n);
valp_t map(valp_t lst, std::function<valp_t(valp_t)> proc);
int length(valp_t lst);
valp_t append(valp_t lst1, valp_t lst2);

bool is_true(valp_t atom);
bool is_false(valp_t atom);

bool eq(valp_t a, valp_t b);
bool equal(valp_t a, valp_t b);

bool tag_list(valp_t lst, symbol_t tag);
bool tag_list(valp_t lst, BASE tag);

}; // namespace le

#endif