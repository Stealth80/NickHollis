/*
        CS215Pgm5.cpp : main project file.  
        Author:  
        Completion Date: 

        This file should interface with the supplied Qt GUI interface to create photomosaics.
        Please read the included Project Specification for more detailed descriptions of the project.

        In this assignment we will be building on the work from Program 4 to create photomosaics.
        In the last assignment, we were able to break a photo up into smaller blocks and find the average color in each of those blocks.
        To create a photomosaic, we will further this idea by constructing a new image created from smaller images of the same average
        color as each of the blocks.

        Provided with the assignment is a folder of around 900 small 80x60 images.  These images are referred to as filler images.
        In the last assignment, you created a fillerImage class that extended the image class provided.  
        In this assignment we will start by reading in each of these small images into it's own fillerImage object.
        Each of these objects should be stored in a vector. 
        Note that you need to delete any dynamically allocated objects you have created when 
        the program closes.  Put this code in the programExiting() function.

        You should also extend your fillerImage class from Program 4 with the ability to store the number of times it has been used when
        creating the photomosaic.  Make this integer a private member of the class with getter and setter functions to access it.

        When loading in the filler images, you will be passed a string to a directory.  In this directory are images that are named
        a number followed by an extension.  You should open every image from FIRST_FILLER_NUMBER to LAST_FILLER_NUMBER.  These are global
        variables defined in globals.h.  Each file should therefore be of the name:  directory + "/" + number + FILLER_IMAGE_EXT.

        Once all of the filler images have been loaded, an image should be opened in the same manner as in Program 4.  Once this image
        is opened, the "Generate Mosaic" button can be pressed.  When pressed, a new image should be generated (much like in Program 4)
        but this time, instead of 1 pixel per block, each block will be represented by a new group of pixels FILLER_IMAGE_WIDTH by 
        FILLER_IMAGE_HEIGHT.

        The new image should consist of 1 filler image per block in the original image.  You should find the average color of the pixels in
        the block area and compare it to each of the filler images to produce a score.  The filler image with the lowest score should be used
        in the new image.  The metric to score a filler image is very similar to finding the euclidean distance between two 3D points.
        sqrt((blockAvg.red - fillerAvg.red)^2+(blockAvg.green - fillerAvg.green)^2+(blockAvg.blue - fillerAvg.blue)^2).
        This finds the image with the closest average color, however we also want to take into account the number of times we have already
        used the image.  If we have already used it several times before we want to penalize that image some.  Therefore the metric:
        sqrt((blockAvg.red - fillerAvg.red)^2+(blockAvg.green - fillerAvg.green)^2+(blockAvg.blue - fillerAvg.blue)^2)*(timesUsed+1)
        should provide a decent way to provide a score to each image.  Remember:  the image with the LOWEST score should be used!

        Now that we have selected a filler image to use, we need to apply a filter to the version of it that we will be using in the final
        image.  Because often the filler image selected will not have an average color that is completely like the original image block, we
        will apply a filter to adjust the RGB tint of the filler image used (like in Program 4).  You should copy all the pixels of the filler
        image to the appropriate location in the newly created image, with each pixel modified so that the red component is increased or decreased
        an amount corresponding to blockAvg.red - fillerAvg.red.  This should also be done for the green and blue components.  So once you have the
        average pixel colors for the image block and the filler image, find the difference between each component and add/subtract that difference
        to each pixel of the copied filler image. (REMEMBER: you MUST make sure the values stay between 0 and 255!  If a value goes negative, set
        it to 0.  Greater than 255, set it to 255.)
	
        Performance Analysis:
        We need to collect data to analyze the performance of two characteristics of the program
        1. Collect the time needed to generate mosaics using same base image and set of fillers
           using different block widths, like 10,11,12,.... Plot the time as a function of block area.
        2. Collect the average time of searching for the best icon for each block width as described above.
           Plot the average time as function of block area.
        Note: You can use other software to plot the diagram like Matlab or Excel.
 
        The functions in this file should be completed as follows:

bool loadImageFromFile(string filename)
                INPUTS: a string containing a path to a file to open.  This value is returned from the 
                user's selection in the open file dialog.
                OUTPUTS: a boolean indicating whether or not the image could be opened correctly.

void saveImageToFile(string filename)
                INPUTS: a string containing a path to save the current image out to.
                OUTPUTS: NONE

image* displayImage()
                INPUTS: NONE
                OUTPUTS: This function should return a pointer to the image object that is currently being viewed on the screen.  
                If a user has loaded an image correctly, you should return a pointer to an image object containing the base image.  
                If a user has used the Generate Mosaic button, you should of course return a pointer to an image object that 
                reflects these changes.

bool loadFillerImagesFromFolder(string folder)
                INPUTS:  a string containing a path to a directory containing all of the filler images.
                OUTPUTS:  A boolean indicating if all the images loaded correctly into the vector or not

void programExiting()
                INPUTS:  NONE
                OUTPUTS:  NONE
                You should call your dynamic memory deletion code in here.

bool imageLoaded()
                INPUTS:  NONE
                OUTPUTS:  a boolean indicating whether a base image has been loaded successfully.

void generateMosaic(int blockWidth, int blockHeight)
                INPUTS:  Integers indicating the width and height of the “blocks�?to be averaged
                OUTPUTS: NONE
                Generate the Mosaic as described above.

fillerImage* findBestFillerImage(pixel color)
		INPUTS: A pixel object indicating the average color of the image block to be matched by a filler image.
		OUTPUTS: A pointer to a filler image object (remember, these objects are going to be stored in an STL list) which is the result of the metric Distance-2 being applied to all the filler image objects in the STL list.  The returned pointer is a pointer to the filler image object with the minimum score using the metric.
		This function is a helper function, and should be invoked by generateMosaic().

 */

#include <cstdlib>
#include "globals.h"		//some global variables are included here
#include "pixel.h"			//includes the pixel class for storing individual pixels
#include "image.h"			//includes the image class we will be using.
#include "fillerImage.h"	//include the fillerImage class that is implemented by you
#include <time.h>
#include <cmath>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <iomanip>

using namespace std;

//declare your global variables here!
string convert_string(int);
image* img;
image* mosaic;

list<fillerImage*> images;

//load the image from a file and return the result
bool loadImageFromFile(string filename) 
{
    img = new image;
    return img->loadImage(filename);
}

//save an image to a file
void saveImageToFile(string filename) 
{
    img->saveImage(filename);    
}

//return a pointer to your image object!
image* displayImage() 
{
    return img;
}

//load the filler images from the given folder into a vector of fillerImage.
bool loadFillerImagesFromFolder(string folder) 
{

    string path;
    fillerImage* fill;
    //linked list 
    for (int i = FIRST_FILLER_NUMBER; i <= LAST_FILLER_NUMBER; i++)
    {
        path = folder + "/" + convert_string(i) + FILLER_IMAGE_EXT;
        fill = new fillerImage;
        if (fill->loadImage(path))
        {
            images.push_back(fill);
            if (i == LAST_FILLER_NUMBER)
                return true;
        }
    }
    return false;
}

//This function is called when the program is closing.  Make sure to delete any dynamically allocated memory here!
void programExiting()
{
    delete img;
    delete mosaic;
    return;
}

//This function should return true if an image has been successfully loaded to turn into a mosaic, and false if one has not.
bool imageLoaded() 
{
    if (img == NULL)
    {
        return false;
    }
    return true;
}

//This function is a helper function, and should be invoked by generateMosaic().
fillerImage* findBestFillerImage(pixel color)
{
        clock_t start, finish;  // clock for performance analysis
        double elapsed;
        start = clock();
        
        fillerImage* bestImage;
        double bestScore = 9999, score = 0;
        for(list<fillerImage*>::iterator iter = images.begin(); iter != images.end(); iter++)
        {                                               //compute score for comparison 
            int R = (color.red - (*iter)->getAverageColor().red);
            int G = (color.green - (*iter)->getAverageColor().green);
            int B = (color.blue - (*iter)->getAverageColor().blue);
            score = sqrt((R*R + G*G + B*B)) * ((*iter)->getTimesUsed()+1); 
            if (score < bestScore)
            {
                bestScore = score;
                bestImage = *iter;  //store pointer to best image to be returned
            }
        }
        bestImage->increaseTimesUsed();   //increment times used on the image that is selected
        finish = clock();
        elapsed = ((double) (finish - start)) / CLOCKS_PER_SEC;
        cout << "Time to find filler image:  " << setprecision(50) << elapsed << endl;
        return bestImage;
}

//This function should generate the photomosaic from the loaded image.  Each filler image should represent a section of the original image
//that is blockWidth by blockHeight big.
void generateMosaic(int blockWidth, int blockHeight) 
{
        
        clock_t begin, end;             // clock for performance analysis
        double total_elapsed;
        begin = clock();
        
        fillerImage* filler;
        pixel color;
        mosaic = new image;        //create new image for mosaic
       
        if (blockWidth < 4)  // error check if block size is smaller than 4 because ratio is 4:3
        {
            cout << "ERROR:  Invalid block size." << endl;
            return;
        }
        int R = 0;
        int G = 0;
        int B = 0;
        int pix = blockWidth*blockHeight;  //block size
        int NumofBHeight = img->getHeight()/blockHeight;
        int NumofBWidth = img->getWidth()/blockWidth;
        mosaic->createNewImage(NumofBWidth*FILLER_IMAGE_WIDTH, NumofBHeight*FILLER_IMAGE_HEIGHT);
        pixel** Mapiexl = mosaic->getPixels();
        int avgRed, avgBlue, avgGreen;
        
        for (int i = 0; i < NumofBHeight; i++)        //generate filler image for each block 
        {       
            for (int j = 0; j < NumofBWidth; j++) 
            {        
                R = 0; G = 0; B = 0; 
                for(int H=0;H<blockHeight;H++)
                {
                    for(int W=0;W<blockWidth;W++)       //sum pixels in each block
                    {
                        R += static_cast<int>(img->getPixels()[i*blockHeight+H][j*blockWidth+W].red);
                        G += static_cast<int>(img->getPixels()[i*blockHeight+H][j*blockWidth+W].green);
                        B += static_cast<int>(img->getPixels()[i*blockHeight+H][j*blockWidth+W].blue);
                    }
                }      
                //assign pixel average to create new image
                color.red = static_cast<unsigned char>(R/pix);
                color.green = static_cast<unsigned char>(G/pix);
                color.blue = static_cast<unsigned char>(B/pix);
                
                filler = findBestFillerImage(color);  //find best filler image to replace block in image
                
                //find difference in averages
                avgRed = color.red - filler->getAverageColor().red;
                avgBlue = color.blue - filler->getAverageColor().blue;
                avgGreen = color.green - filler->getAverageColor().green;
                
                //assign filler image to mosaic image block
                for (int h = 0; h < FILLER_IMAGE_HEIGHT; h++)
                {
                    for (int w = 0; w < FILLER_IMAGE_WIDTH; w++)
                    {   //
                        //tint filler image pixels as they are copied into to mosaic image
                        
                        //Red
                        int RR = (filler->getPixels()[h][w]).red + avgRed;
                        if(RR<0){
                            RR =0;
                        }
                        if(RR>255){
                            RR=255;
                        }
                        Mapiexl[i*FILLER_IMAGE_HEIGHT+h][j*FILLER_IMAGE_WIDTH+w].red = (uchar)RR;
                        
                        //green
                        int GG = (filler->getPixels()[h][w]).green + avgGreen;
                        if(GG<0){
                            GG =0;
                        }
                        if(GG>255){
                            GG=255;
                        }
                       Mapiexl[i*FILLER_IMAGE_HEIGHT+h][j*FILLER_IMAGE_WIDTH+w].green = (uchar)GG;
                       
                        //blue
                        int BB = (filler->getPixels()[h][w]).blue + avgBlue;
                        if(BB<0){
                            BB =0;
                        }
                        if(BB>255){
                            BB=255;
                        }
                        Mapiexl[i*FILLER_IMAGE_HEIGHT+h][j*FILLER_IMAGE_WIDTH+w].blue = (uchar)BB;
                    }
                }
            }
        }
        
        img = mosaic;
        end = clock();
	total_elapsed = ((double) (end - begin)) / CLOCKS_PER_SEC;
        cout << "Total elapsed time for generate mosaic:  " << total_elapsed << endl;
        return;
}

string convert_string(int num)
{                               //convert filler image number to a string
    stringstream int_to_string;
    int_to_string << num;
    return int_to_string.str();
}