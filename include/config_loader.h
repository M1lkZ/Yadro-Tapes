#pragma once
#include <string>

void loadConfig(
    const std::string& filename,
    int& read_delay,
    int& write_delay,
    int& shift_delay,
    size_t& memory_limit
);