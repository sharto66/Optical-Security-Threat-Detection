#include <cstdio>
#include <iostream>
#include <fstream>
#include <string>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "InputImage.h"
#include "opticalsecurity.h"

using namespace std;
using namespace cv;

float borderPercent = 0.25;
int NUM;
std::string argument = "";
std::string threatArg = "-Threat";
std::string nonThreatArg = "-Non_Threat";

int main(int argc, char *argv[])
{
    char image_name[100];
    char* image_location;
    int imgSet;
    if(argc == 2){
        argument = argv[1];
    }
    else if(argc == 1)
    {
        cout << "Enter 1 for Threats" << endl;
        cout << "Enter 2 for Non Threats" << endl;
        cin >> imgSet;
    }
    if(argument == threatArg){
        imgSet = 1;
    }
    else if(argument == nonThreatArg){
        imgSet = 2;
    }
    else if(argument != nonThreatArg && argument != threatArg && argument != ""){
        Mat argTest = imread(argument);
        if(argTest.data){
            InputImage argImage(argTest, argument);
            argImage = analyseImage(argImage);
            argImage = applyInterface(argImage);
            namedWindow(string("Image window"), WINDOW_AUTOSIZE);
            imshow(string("Image window"), argImage.origImage);
            imgSet = 3;
        }
    }
    if(imgSet != 3){
        image_location = getImageSet(imgSet);
        InputImage input[NUM];
        for(int i=0;i < NUM; i++)
        {        
            sprintf(image_name, image_location, i+1);
            input[i] = InputImage(imread(image_name), image_name);
        }
        int size = sizeof(input)/sizeof(input[0]);
        for(int i=0;i < size; i++)
        {
            if(input[i].image.data)
            {
                input[i] = analyseImage(input[i]);
                input[i] = applyInterface(input[i]);
               if(argument != threatArg && argument != nonThreatArg){
                   namedWindow(string("Display window") + std::to_string(i+1), WINDOW_AUTOSIZE);
                   imshow(string("Display window") + std::to_string(i+1), input[i].origImage);
               }
            }
            else{
                cout << "Error in image data for " + input[i].imageName << endl;
            }
        }
        writeResultsToFile(input);
    }
    waitKey(0);
    cvDestroyAllWindows();
    return 0;
}

InputImage analyseImage(InputImage src)
{
    src = detectPeople(src);
    src = blurImage(src);
    src = edgeDetection(src);
    src = barrelDetection(src);
//    input[i] = magazineDetection(input[i]);
    return src;
}

char* getImageSet(int set)
{
    char* image_name;
    if(set == 1) {
        if(argument == threatArg){
            image_name = "..\\images\\Threat/image%d.jpg";
        }
        else image_name = "images\\Threat/image%d.jpg";
        NUM = 50;
    }
    else if(set == 2) {
        if(argument == nonThreatArg){
            image_name = "..\\images\\Non_Threat/image%d.jpg";
        }
        else image_name = "images\\Non_Threat/image%d.jpg";
        NUM = 50;
    }
    else cout << "Please enter valid option" << endl;
    return image_name;
}

InputImage applyInterface(InputImage src)
{
    int border = (int) (borderPercent * src.origImage.rows);
    copyMakeBorder(src.origImage, src.origImage, 0, border, 0, 0, BORDER_CONSTANT, Scalar(0,0,0));
    
    Point p1 = cvPoint(10, src.origImage.rows - 10);
    Point p2 = cvPoint(10, p1.y - 10);
    Point p3 = cvPoint(10, p2.y - 10);
    string threat = "";
    if(src.containsThreat) threat = "True";
    else threat = "False";
    
    putText(src.origImage, "Threat Detected: " + threat, p1,
            FONT_HERSHEY_COMPLEX_SMALL, 0.42, Scalar(255,255,255), 1, CV_AA);
    putText(src.origImage, "Num. of Persons: " + to_string(src.numPeople), p2,
            FONT_HERSHEY_COMPLEX_SMALL, 0.42, Scalar(255,255,255), 1, CV_AA);
    putText(src.origImage, "Threat Info: " + src.threatInfo, p3,
            FONT_HERSHEY_COMPLEX_SMALL, 0.42, Scalar(255,255,255), 1, CV_AA);
    return src;
}

void writeResultsToFile(InputImage input[])
{
    std::string filepath;
    if(argument == threatArg || argument == nonThreatArg){
        filepath = "opticalSecDetectResults.json";
    }
    else filepath = "Test_Eval\\opticalSecDetectResults.json";
    ofstream prefile(filepath, std::ios::out);
    prefile.close();
    ofstream file(filepath, std::ios::out | std::ios::app);
    std::string result, threat;
    file << "{";
    for(int i = 0; i < NUM; i++)
    {
        if(input[i].containsThreat) threat = "true";
        else threat = "false";
        result = "\"" + getImageName(input[i].imageName) + "\" : " + threat;
        if(i < NUM-1) result = result + ", ";
        file << result;
    }
    file << "}";
    file.close();
}

std::string getImageName(string imagePath)
{
    std::string name;
    int pos = imagePath.find_last_of('/');
    for(int i = pos+1; i < imagePath.capacity(); i++)
    {
        name += imagePath[i];
    }
    return name;
}