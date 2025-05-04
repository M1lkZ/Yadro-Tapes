#include "tape_sorter.h"
#include "file_tape.h"
#include <queue>
#include <vector>
#include <filesystem>
#include <algorithm>

namespace fs = std::filesystem;

struct TapeElement {
    int value;
    FileTape* tape;

    TapeElement(int v, FileTape* t) : value(v), tape(t) {}

    bool operator<(const TapeElement& other) const {
        return value > other.value;
    }
};


TapeSorter::TapeSorter(Tape& in, Tape& out, size_t mem_limit, const std::string& tmp)
    : input(in), output(out), memory_limit(mem_limit), tmp_dir(tmp) {}

void TapeSorter::splitAndSort(std::vector<std::string>& temp_files) {
    std::vector<int> buffer;
    input.rewind();

    while (!input.isEnd()) {
        buffer.clear();

        for (size_t i = 0; i < memory_limit && !input.isEnd(); ++i) {
            buffer.push_back(input.read());
            input.moveForward();
        }

        std::sort(buffer.begin(), buffer.end());

        std::string temp_name = tmp_dir + "/temp_" + std::to_string(temp_files.size()) + ".txt";
        temp_files.push_back(temp_name);

        FileTape temp_tape(temp_name, "w");
        for (int val : buffer) {
            temp_tape.write(val);
            temp_tape.moveForward();
        }
        temp_tape.saveToFile();
    }
}

void TapeSorter::merge(const std::vector<std::string>& temp_files) {
    std::priority_queue<TapeElement> min_heap;
    std::vector<FileTape*> open_tapes;

    for (const auto& file : temp_files) {
        FileTape* tape = new FileTape(file, "r");
        tape->rewind();
        if (!tape->isEnd()) {
            min_heap.emplace(tape->read(), tape);
        }
        open_tapes.push_back(tape);
    }


    output.rewind();
    while (!min_heap.empty()) {
        TapeElement top = min_heap.top();
        min_heap.pop();

        output.write(top.value);
        output.moveForward();

        top.tape->moveForward();
        if (!top.tape->isEnd()) {
            min_heap.emplace(top.tape->read(), top.tape);
        }
    }


    for (const auto& file : temp_files) {
        fs::remove(file);
    }

    for (auto* tape : open_tapes) {
        delete tape;
    }
}

void TapeSorter::sort() {
    std::vector<std::string> temp_files;
    splitAndSort(temp_files);
    merge(temp_files);
}