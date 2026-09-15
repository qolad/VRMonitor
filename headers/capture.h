#pragma once

#include <cstdint>

struct Frame
{
    const uint8_t* data = nullptr;

    int width = 0;
    int height = 0;

    int stride = 0;
};

class Capture
{
public:
    virtual ~Capture() = default;

    virtual bool start() = 0;
    virtual bool getFrame(Frame& frame) = 0;
    virtual void stop() = 0;
};