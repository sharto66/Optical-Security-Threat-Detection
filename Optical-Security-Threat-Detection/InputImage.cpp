/* 
 * File:   InputImage.cpp
 * Author: Sean
 * 
 * Created on 13 November 2015, 15:16
 */

#include "InputImage.h"
#include <opencv2/opencv.hpp>

InputImage::InputImage()
{
    containsThreat = false;
    threatInfo = "";
    numPeople = 0;
}

InputImage::InputImage(cv::Mat image, std::string imageName)
{
    this->image = image;
    this->origImage = image;
    this->containsThreat = false;
    this->threatInfo = "";
    this->imageName = imageName;
    this->numPeople = 0;
}

InputImage::~InputImage() {
}

