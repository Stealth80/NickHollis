#include "fillerImage.h"

// implement your functions here
fillerImage::fillerImage()  // constructor
{
    timesUsed = 0;
    int R = 0;
    int G = 0;
    int B = 0;
    int Height = getHeight();
    int Width = getWidth();
    int pix = Width * Height;
    
    //pixel object[Height][Width];
    for (int i = 0; i < Height; i++)
    {   
      for (int j = 0; j < Width; j++) 
      {  
         R = 0; G = 0; B = 0; 
         for(int H=0;H<Height;H++)
         {
             for(int W=0;W<Width;W++)
             {
                 R += static_cast<int>(getPixels()[i+H][j+W].red);
                 G += static_cast<int>(getPixels()[i+H][j+W].green);
                 B += static_cast<int>(getPixels()[i+H][j+W].blue);
             }
         }      
         //assign pixel average to created new image
         avgPixel.red = static_cast<unsigned char>(R/pix);
         avgPixel.green = static_cast<unsigned char>(G/pix);
         avgPixel.blue = static_cast<unsigned char>(B/pix);
      }
    }
}

pixel fillerImage::getAverageColor()
{
    return avgPixel;
}

void fillerImage::increaseTimesUsed()
{
    timesUsed++;
    return;
}

int fillerImage::getTimesUsed()
{
    return timesUsed;
}