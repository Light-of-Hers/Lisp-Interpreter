#include "../include/running.h"

int main(int argc, char **argv) {
    le::env_t global = le::setup_env();
    if (argc == 2) {
        le::load_file(global, std::string(argv[1]));
    }
    driver(global);
}