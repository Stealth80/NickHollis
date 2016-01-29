#ifndef FILLER_IMAGE
#define FILLER_IMAGE

#include "globals.h"
#include "image.h"

class fillerImage : public image {
public:
    fillerImage();  // constructor
    pixel getAverageColor();
    void increaseTimesUsed();
    int getTimesUsed();
private:
    int timesUsed;
    pixel avgPixel;
};

#endif