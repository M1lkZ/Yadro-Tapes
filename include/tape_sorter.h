#pragma once
#include "tape.h"
#include <vector>
#include <string>

class TapeSorter {
    Tape& input;
    Tape& output;
    size_t memory_limit;
    std::string tmp_dir;

    void splitAndSort(std::vector<std::string>& temp_files);

    void merge(const std::vector<std::string>& temp_files);

public:
    TapeSorter(Tape& in, Tape& out, size_t mem_limit, const std::string& tmp);
    void sort();
};