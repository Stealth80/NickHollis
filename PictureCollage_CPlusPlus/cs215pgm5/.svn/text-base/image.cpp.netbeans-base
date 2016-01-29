#include <iostream>
#include "image.h"
#include <QColor>

image::image() {
    pixels = NULL;
    width = 0;
    height = 0;
}

image::image(string filename) {
    pixels = NULL;
    width = 0;
    height = 0;
    loadImage(filename);
}

image::~image() {
    if (pixels) {
        for (int i = 0; i < height; i++)
            delete [] pixels[i];
        delete [] pixels;
        pixels = NULL;
        width = 0;
        height = 0;
    }
}

int image::getWidth() {
    return width;
}

int image::getHeight() {
    return height;
}

pixel** image::getPixels() {
    return pixels;
}

void image::createNewImage(int width, int height) {
    if (this->pixels) {
        for (int i = 0; i<this->height; i++)
            delete [] this->pixels[i];
        delete [] this->pixels;
        this->pixels = NULL;
        this->width = 0;
        this->height = 0;
    }

    this->width = width;
    this->height = height;

    pixels = new pixel*[height];
    for (int j = 0; j < height; j++)
        pixels[j] = new pixel[width];
}

void image::viewImage(QImage* myImage) {
    pixelsToQImage(myImage);
    return;
}

bool image::loadImage(string filename) {
    if (pixels) {
        for (int i = 0; i < height; i++)
            delete [] pixels[i];
        delete [] pixels;
        pixels = NULL;
        width = 0;
        height = 0;
    }

    QImage myImage;
    myImage.load(QString::fromStdString(filename));

    if (myImage.isNull()) {
        cout << "The requested image could not be loaded." << endl;
        return false;
    }

    if (myImage.depth() != 32) {
        cout << "The input image must be stored in the 8 bit RGB (32 bpp) colorspace." << endl;
        return false;
    }

    width = myImage.width();
    height = myImage.height();

    pixels = new pixel*[height];

    for (int j = 0; j < height; j++) {
        pixels[j] = new pixel[width];
        for (int i = 0; i < width; i++) {
            QColor color = QColor::fromRgba(myImage.pixel(i, j));

            pixels[j][i].red = color.red();
            pixels[j][i].green = color.green();
            pixels[j][i].blue = color.blue();
        }
    }

    return true;
}

void image::pixelsToQImage(QImage* myImage) {
    if (myImage->isNull()) {
        cout << "An error occured when creating a new image!" << endl;
        return;
    }

    for (int j = 0; j < height; j++)
        for (int i = 0; i < width; i++) {
            QRgb value;

            value = qRgb(pixels[j][i].red, pixels[j][i].green, pixels[j][i].blue);
            myImage->setPixel(i, j, value);
        }
}

void image::saveImage(string filename) {
    if (!pixels) {
        cout << "No image data has been created to save! (The pixel buffer is empty)" << endl;
        return;
    }

    QImage myImage(width, height, QImage::Format_RGB32);
    pixelsToQImage(&myImage);
    myImage.save(QString::fromStdString(filename));

    return;
}