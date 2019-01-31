#include "../include/running.h"
#include "../include/env.h"
#include "../include/error.h"
#include "../include/eval.h"
#include "../include/parse.h"
#include "../include/primitive.h"
#include "../include/scan.h"
#include "../include/symbol.h"
#include <cstdlib>
#include <exception>
#include <fstream>
#include <iostream>

namespace le {

std::istream &read(std::istream &is, std::string &code) {
    code.clear();
    int lb = 0, rb = 0;
    char ch;
    while (is.get(ch)) {
        code.push_back(ch);
        if (ch == '(') {
            lb++;
        } else if (ch == ')') {
            rb++;
        } else if (ch == '\n') {
            if (lb == rb)
                break;
        }
    }
    return is;
}

env_t setup_env() {
    st_init();
    env_t global = extend_env(nullptr, nullptr, nullptr);
    pp_init(global);
    return global;
}

void driver(env_t global) {
    static std::string inppt = ">> ";
    static std::string outppt = "<< ";
    std::string code;
    std::cout << inppt;
    while (read(std::cin, code)) {
        try {
            valp_t res = eval(parse(scan(code)), global);
            std::cout << outppt << val2str(res) << std::endl;
        } catch (error_t err) {
            if (err.lv == ERR_LV::NORMAL)
                std::cout << err.msg << std::endl;
            else
                exit(0);
        }
        std::cout << inppt;
    }
    std::cout << std::endl;
}

void load_file(env_t env, const std::string &filename) {
    std::ifstream fin(filename);
    std::string code, line;
    while (getline(fin, line))
        code += line + '\n';
    try {
        eval(parse(scan(code)), env);
    } catch (error_t err) {
        if (err.lv == ERR_LV::NORMAL)
            std::cout << err.msg << std::endl;
        else
            exit(0);
    }
}

}; // namespace le