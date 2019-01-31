#include "../include/scan.h"
#include "../include/symbol.h"
#include <sstream>

namespace le {

static const string_t split(const string_t &code) {
    using namespace std;
    string res;
    int len = code.size();
    for (int i = 0; i < len; ++i) {
        char ch = code[i];
        switch (ch) {
            case '"': {
                int j;
                (res += '\n') += code[i];
                for (j = i + 1; j < len && code[j] != '"'; ++j)
                    res += code[j];
                (res += code[j]) += '\n';
                i = j;
                break;
            }
            case '\'':
            case '(':
            case ')': {
                res += string(" ") + ch + string(" ");
                break;
            }
            default: {
                res += ch;
                break;
            }
        }
    }
    return res;
}

vtoken_t scan(const string_t &code) {
    using namespace std;
    vtoken_t tks;
    tks.push_back(token_t::LEFT_BRACKET);
    tks.push_back(st_add("begin"));

    istringstream input(split(code));
    string line;
    while (getline(input, line)) {
        if (!line.empty()) {
            if (line.front() == '"' && line.back() == '"') {
                tks.push_back(line);
            } else {
                string tk;
                istringstream strin(line);
                while (strin >> tk) {
                    if (tk == "'") {
                        tks.push_back(token_t::QUOTE);
                    } else if (tk == ".") {
                        tks.push_back(token_t::DOT);
                    } else if (tk == "(") {
                        tks.push_back(token_t::LEFT_BRACKET);
                    } else if (tk == ")") {
                        tks.push_back(token_t::RIGHT_BRACKET);
                    } else if (tk == "#t" || tk == "#f") {
                        tks.push_back((bool)(tk == "#t"));
                    } else {
                        try {
                            tks.push_back(stod(tk));
                        } catch (std::invalid_argument) {
                            tks.push_back(st_add(tk));
                        }
                    }
                }
            }
        }
    }
    tks.push_back(token_t::RIGHT_BRACKET);
    return tks;
}

const std::string token_t::str() const {
    using namespace std;
    ostringstream sout;
    if (type == LEFT_BRACKET) {
        sout << "<(>";
    } else if (type == RIGHT_BRACKET) {
        sout << "<)>";
    } else if (type == QUOTE) {
        sout << "<'>";
    } else if (type == DOT) {
        sout << "<.>";
    } else if (type == NUMBER) {
        sout << "<number, " << get<double>(attr) << ">";
    } else if (type == STRING) {
        sout << "<string, " << get<string>(attr) << ">";
    } else if (type == SYMBOL) {
        sout << "<symbol, " << get<int>(attr) << ">";
    } else if (type == BOOLEAN) {
        sout << "<boolean, " << get<bool>(attr) << ">";
    } else {
        return "";
    }
    return sout.str();
}

}; // namespace le