/* 
 * File:   InputImage.h
 * Author: Sean
 *
 * Created on 13 November 2015, 15:16
 */

#ifndef INPUTIMAGE_H
#define	INPUTIMAGE_H

#include <string>
#include <opencv2/opencv.hpp>

class InputImage {
public:
    cv::Mat image;
    cv::Mat origImage;
    bool containsThreat;
    std::string threatInfo;
    int numPeople;
    InputImage();
    InputImage(cv::Mat image);
    virtual ~InputImage();
private:

};

#endif	/* INPUTIMAGE_H */

