#include "../include/parse.h"
#include "../include/error.h"
#include "../include/symbol.h"

namespace le {

static int step;
static valp_t aux(const vtoken_t &tks);
valp_t parse(const vtoken_t &tks) {
    step = 0;
    return aux(tks);
}
valp_t aux(const vtoken_t &tks) {
    token_t tk = tks[step++];
    if (tk.type == token_t::NUMBER) {
        return make(std::get<double>(tk.attr));
    } else if (tk.type == token_t::STRING) {
        return make(std::get<std::string>(tk.attr));
    } else if (tk.type == token_t::BOOLEAN) {
        return st_getbool(std::get<bool>(tk.attr));
    } else if (tk.type == token_t::SYMBOL) {
        return st_getval(std::get<int>(tk.attr));
    } else if (tk.type == token_t::LEFT_BRACKET) {
        valp_t head = cons(nullptr, nullptr);
        valp_t cur = head;
        while (tks[step].type != token_t::RIGHT_BRACKET) {
            if (tks[step].type == token_t::DOT) {
                step++;
                cdr(cur) = aux(tks);
                if (tks[step].type != token_t::RIGHT_BRACKET)
                    normal_err("Syntax Error");
            }
            cdr(cur) = cons(aux(tks), nullptr);
            cur = cdr(cur);
        }
        step++;
        return cdr(head);
    } else if (tk.type == token_t::QUOTE) {
        return cons(st_getval(BASE::QUOTE), cons(aux(tks), nullptr));
    } else {
        return nullptr;
    }
}

}; // namespace le