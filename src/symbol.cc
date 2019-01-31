#include "../include/symbol.h"
#include "../include/error.h"
#include "../include/value.h"
#include <map>
#include <vector>

namespace le {

static std::vector<string_t> base_str{"define",
                                      "set!",
                                      "lambda",
                                      "begin",
                                      "if",
                                      "cond",
                                      "ok",
                                      "**procedure**",
                                      "quote",
                                      "**primitive-procedure**",
                                      "else",
                                      "and",
                                      "let",
                                      "or",
                                      "**or-test**",
                                      "while",
                                      "for",
                                      "let*",
                                      "**unassigned**"};
static std::map<string_t, symbol_t> str2sb;
static std::vector<string_t> sb2str;
static std::vector<valp_t> sb2val;
static valp_t bools[2];

void st_init() {
    str2sb.clear();
    sb2str.clear();
    sb2val.clear();
    bools[0] = make(false);
    bools[1] = make(true);
    for (auto s : base_str) {
        st_add(s);
    }
}

const symbol_t st_add(const string_t &s) {
    auto it = str2sb.find(s);
    if (it == str2sb.end()) {
        int len = sb2str.size();
        str2sb[s] = len;
        sb2str.push_back(s);
        sb2val.push_back(make(len));
        return len;
    } else {
        return it->second;
    }
}

const symbol_t st_getsb(const string_t &s) {
    auto it = str2sb.find(s);
    if (it == str2sb.end()) {
        normal_err("Cannot Find Symbol: " + s);
    } else {
        return it->second;
    }
    return -1;
}

const string_t st_getstr(symbol_t sb) {
    if (sb < 0 || sb >= (int)sb2str.size()) {
        normal_err("Cannnot Find Symbol With id: " + std::to_string(sb));
    } else {
        return sb2str[sb];
    }
    return "";
}

valp_t st_getval(symbol_t sb) {
    if (sb < 0 || sb >= (int)sb2str.size()) {
        normal_err("Cannnot Find Symbol With id: " + std::to_string(sb));
    } else {
        return sb2val[sb];
    }
    return nullptr;
}
valp_t st_getval(BASE sb) {
    return st_getval((symbol_t)sb);
}

valp_t st_getbool(bool bl) {
    return bools[bl ? 1 : 0];
}

}; // namespace le