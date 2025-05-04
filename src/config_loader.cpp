#include "config_loader.h"
#include <fstream>
#include <sstream>
#include <iostream>

void loadConfig(
    const std::string& filename,
    int& read_delay,
    int& write_delay,
    int& shift_delay,
    size_t& memory_limit
) {

    read_delay = 10;
    write_delay = 10;
    shift_delay = 1;
    memory_limit = 10;

    std::ifstream config_file(filename);
    if (!config_file.is_open()) {
        std::cerr << "Warning: Config file not found. Using defaults.\n";
        return;
    }

    std::string line;
    while (std::getline(config_file, line)) {
        std::istringstream iss(line);
        std::string key;
        if (std::getline(iss, key, '=')) {
            if (key == "read_delay") iss >> read_delay;
            else if (key == "write_delay") iss >> write_delay;
            else if (key == "shift_delay") iss >> shift_delay;
            else if (key == "memory_limit") iss >> memory_limit;
        }
    }
}