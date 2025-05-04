#include "file_tape.h"
#include <sstream>
#include <stdexcept>
#include <chrono>
#include <thread>

FileTape::FileTape(const std::string& filename, const std::string& mode) 
    : filename(filename) {
    if (mode == "r") {
        std::ifstream file(filename);
        if (!file) throw std::runtime_error("Can't open file: " + filename);
        
        int value;
        while (file >> value) {
            data.push_back(value);
        }
    }
}

FileTape::~FileTape() {
    if (dirty) saveToFile();
}

void FileTape::applyDelay(int ms) const {
    std::this_thread::sleep_for(std::chrono::milliseconds(ms));
}

void FileTape::configureDelays(int read, int write, int shift) {
    read_delay = read;
    write_delay = write;
    shift_delay = shift;
}

int FileTape::read() {
    applyDelay(read_delay);
    if (pos >= data.size()) throw std::runtime_error("Read beyond end");
    return data[pos];
}

void FileTape::write(int value) {
    applyDelay(write_delay);
    if (pos >= data.size()) data.resize(pos + 1, 0);
    data[pos] = value;
    dirty = true;
}

void FileTape::saveToFile() {
    std::ofstream file(filename);
    for (size_t i = 0; i < data.size(); ++i) {
        file << data[i];
        if (i != data.size() - 1) file << " ";
    }
    dirty = false;
}

void FileTape::moveForward() {
    applyDelay(shift_delay);
    pos++;
}

void FileTape::moveBackward() {
    applyDelay(shift_delay);
    pos = (pos > 0) ? pos - 1 : 0;
}

void FileTape::rewind() {
    pos = 0;
}

bool FileTape::isEnd() {
    return pos >= data.size();
}