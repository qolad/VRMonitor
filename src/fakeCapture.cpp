#include "fakeCapture.h"

bool FakeCapture::start(){
    pixels.resize(width * height * 4);

    for (int y = 0; y < height; ++y){
        for (int x = 0; x < width; ++x){
            int index = (y * width + x) * 4;

            // r, g, b, a
            pixels[index + 0] = 255;
            pixels[index + 1] = 0;
            pixels[index + 2] = 0;
            pixels[index + 3] = 255;
        }
    }
    return true;
}

bool FakeCapture::getFrame(Frame& frame){
    frame.data = pixels.data();
    frame.width = width;
    frame.height = height;
    frame.stride = width * 4;

    return true;
}

void FakeCapture::stop(){
    pixels.clear();
}