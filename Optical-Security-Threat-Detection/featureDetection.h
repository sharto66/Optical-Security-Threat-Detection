/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   featureDetection.h
 * Author: Sean
 *
 * Created on 08 March 2016, 18:25
 */

#ifndef FEATUREDETECTION_H
#define FEATUREDETECTION_H

#include <opencv2/opencv.hpp>
#include "InputImage.h"

using namespace cv;

float getSlope(Point p1, Point p2);
Rect getRect(Point p);
Rect getROIrectangle(Point p1, Point p2, Point p3, Point p4);
Mat rotate(Mat src, float angle);
bool cornerDetected(Mat harris, Point p);
bool slopeMatch(float s1, float s2);
bool lengthMatch(Point p1, Point p2, Point p3, Point p4);
bool endToEnd(Point p1, Point p2, Point p3, Point p4);
bool isGunColour(InputImage src, Point p1, Point p2, Point p3, Point p4);
std::vector<cv::Point> getCurvedLine(std::vector<cv::Point> contour);
bool isNearOtherCurve(std::vector<cv::Point> contour);
bool isSimilarCurve(std::vector<cv::Point> contour);

#endif /* FEATUREDETECTION_H */

