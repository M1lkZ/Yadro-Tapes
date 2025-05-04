#pragma once
#include "tape.h"
#include <vector>
#include <fstream>
#include <string>

class FileTape : public Tape {
    std::vector<int> data;
    size_t pos = 0;
    std::string filename;
    bool dirty = false;


    int read_delay = 0;
    int write_delay = 0;
    int shift_delay = 0;

    void applyDelay(int ms) const;

public:
    FileTape(const std::string& filename, const std::string& mode);
    ~FileTape();

    void configureDelays(int read, int write, int shift);
    const std::string& getFileName() const { return filename; }

    int read() override;
    void write(int value) override;
    void moveForward() override;
    void moveBackward() override;
    void rewind() override;
    bool isEnd() override;

    void saveToFile();
};