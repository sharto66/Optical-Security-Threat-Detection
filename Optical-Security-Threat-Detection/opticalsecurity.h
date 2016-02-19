/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   opticalsecurity.h
 * Author: Sean
 *
 * Created on 06 February 2016, 14:02
 */

#ifndef OPTICALSECURITY_H
#define OPTICALSECURITY_H

#include <opencv2/opencv.hpp>

cv::Mat thresholdImage(cv::Mat src);
cv::Mat filterImage(cv::Mat src);
cv::Mat blobDetection(cv::Mat src);
cv::Mat edgeDetection(cv::Mat src);
cv::Mat barrelDetection(cv::Mat src);
cv::Mat magazineDetection(cv::Mat src);
cv::Mat blurImage(cv::Mat src);
cv::Mat detectPeople(cv::Mat src);
cv::Mat detectFaces(cv::Mat src);
cv::Mat cornerDetection(cv::Mat src);
cv::Mat lineDetect(cv::Mat src);
cv::Mat colourThreshold(cv::Mat src);
char* getImageSet(int set);

#endif /* OPTICALSECURITY_H */

