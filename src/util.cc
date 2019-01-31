#include "../include/util.h"

namespace le {

#define GUARD (cons(nullptr, nullptr))

valp_t make_list(std::vector<valp_t> lst) {
    valp_t head = GUARD;
    valp_t cur = head;
    for (auto e : lst) {
        cdr(cur) = cons(e, nullptr);
        cur = cdr(cur);
    }
    return cdr(head);
}

valp_t ref(valp_t lst, int n) {
    while (n--)
        lst = cdr(lst);
    return car(lst);
}

valp_t map(valp_t lst, std::function<valp_t(valp_t)> proc) {
    valp_t head = GUARD;
    valp_t cur = head;
    while (lst) {
        cdr(cur) = cons(proc(car(lst)), nullptr);
        cur = cdr(cur);
        lst = cdr(lst);
    }
    return cdr(head);
}

bool tag_list(valp_t lst, symbol_t tag) {
    return CHECK(lst, PAIR) && CHECK(car(lst), SYMBOL) &&
           GET(car(lst), symbol_t) == tag;
}
bool tag_list(valp_t lst, BASE tag) {
    return tag_list(lst, (symbol_t)tag);
}

bool is_true(valp_t atom) {
    return !is_false(atom);
}
bool is_false(valp_t atom) {
    return CHECK(atom, BOOLEAN) && !GET(atom, boolean_t);
}

int length(valp_t lst) {
    int len = 0;
    while (lst)
        lst = cdr(lst), len++;
    return len;
}

bool eq(valp_t a, valp_t b) {
    return a == b;
}

valp_t append(valp_t lst1, valp_t lst2) {
    if (lst1 == nullptr) {
        return lst2;
    } else {
        while (cdr(lst1))
            lst1 = cdr(lst1);
        cdr(lst1) = lst2;
        return lst1;
    }
}

}; // namespace le