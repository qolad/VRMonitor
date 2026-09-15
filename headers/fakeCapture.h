#pragma once 

#include "capture.h"

#include <vector>

class FakeCapture : public Capture {
    public:
        bool start() override;
        bool getFrame(Frame& frame) override;
        void stop() override;
    private:
        std::vector<uint8_t> pixels;
        
        int width = 800;
        int height = 600;
};