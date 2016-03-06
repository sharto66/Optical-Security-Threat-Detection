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
#include "InputImage.h"

InputImage thresholdImage(InputImage src);
InputImage edgeDetection(InputImage src);
InputImage barrelDetection(InputImage src);
InputImage magazineDetection(InputImage src);
InputImage blurImage(InputImage src);
InputImage detectFaces(InputImage src);
InputImage lineDetect(InputImage src);
InputImage colourThreshold(InputImage src);
InputImage detectPeople(InputImage src);
InputImage applyInterface(InputImage src);
void writeResultsToFile(InputImage input[]);
std::string getImageName(std::string imagePath);
char* getImageSet(int set);

#endif /* OPTICALSECURITY_H */

