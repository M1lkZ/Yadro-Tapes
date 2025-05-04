#pragma once
#include <cstdint>

class Tape {
public:
    virtual ~Tape() = default;
    virtual int read() = 0;
    virtual void write(int value) = 0;
    virtual void moveForward() = 0;
    virtual void moveBackward() = 0;
    virtual void rewind() = 0;
    virtual bool isEnd() = 0;
};