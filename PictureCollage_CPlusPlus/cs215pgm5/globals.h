#ifndef GLOBALS_H
#define GLOBALS_H

#include <string>
using namespace std;

typedef unsigned char uchar; //make it so we can use the shorthand "uchar" instead of unsigned char everywhere
const int COMPONENT_INCREASE_VALUE = 20; //The amount that we increase a RGB component with one click of the button. //TODOD delete this line

const int FIRST_FILLER_NUMBER = 0; //The first number used in the filenames of the filler images
const int LAST_FILLER_NUMBER = 905; //The last number used in the filenames of the filler images
const string FILLER_IMAGE_EXT = ".jpg"; //The extension at the end of the filler image filenames

const int FILLER_IMAGE_WIDTH = 80; //The width in pixels of each filler image
const int FILLER_IMAGE_HEIGHT = 60; //The height in pixels of each filler image
#endif

