#include <cstdio>
#include <iostream>
#include <fstream>
#include <string>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "InputImage.h"
#include "opticalsecurity.h"

#define NUM 15

using namespace std;
using namespace cv;

float borderPercent = 0.25;

int main(int argc, char *argv[])
{
    InputImage input[NUM];
    char image_name[100];
    char* image_location;
    int imgSet;
    if(argc == 0)
    {
        cout << "Enter 1 for pistols" << endl;
        cout << "Enter 2 for all guns" << endl;
        cout << "Enter 3 for test image in root" << endl;
        cout << "Enter 4 for OpenCV test images" << endl;
        cin >> imgSet;
    }
    else if(argv[0] == "-test")
    {
        imgSet == 1;
    }
    else {
        cout << "Usage: No arguments or -test" << "\n";
    }
    
    image_location = getImageSet(imgSet);
    
    for(int i=0;i < NUM; i++)
    {        
        sprintf(image_name, image_location, i+1);
        input[i] = InputImage(imread(image_name), image_name);
    }
    int size = sizeof(input)/sizeof(input[0]);
    cout << size << endl;
    for(int i=0;i < size; i++)
    {
        if(input[i].image.data)
        {
           //input[i] = detectPeople(input[i]);
           input[i] = blurImage(input[i]);
           input[i] = colourThreshold(input[i]);
           input[i] = edgeDetection(input[i]);
           //input[i] = thresholdImage(input[i]);
           //input[i] = barrelDetection(input[i]);
           input[i] = magazineDetection(input[i]);
           
           input[i] = applyInterface(input[i]);
           
           namedWindow(string("Display window") + std::to_string(i+1), WINDOW_AUTOSIZE);
           imshow(string("Display window") + std::to_string(i+1), input[i].image);
        }
        else
        {
            cout << "Something wrong" << endl;
        }
    }
    writeResultsToFile(input);
    waitKey(0);
    cvDestroyAllWindows();
    return 0;
}

char* getImageSet(int set)
{
    char* image_name;
    if(set == 1) {
        image_name = "C:\\Users\\Sean\\Pictures\\guns\\handguns/image%d.jpg";
    }
    else if(set == 2) {
        image_name = "C:\\Users\\Sean\\Pictures\\guns/image%d.jpg";
    }
    else if(set == 3) {
        image_name = "me_eating_cereal.jpg";
    }
    else if(set == 4) {
        image_name = "C:\\Users\\Sean\\Pictures\\OpenCV Tests/image%d.jpg";
    }
    return image_name;
}

InputImage applyInterface(InputImage src)
{
    int border = (int) (borderPercent * src.image.rows);
    copyMakeBorder(src.image, src.image, 0, border, 0, 0, BORDER_CONSTANT, Scalar(0,0,0));
    
    Point p1 = cvPoint(10, src.image.rows - 10);
    Point p2 = cvPoint(10, p1.y - 10);
    Point p3 = cvPoint(10, p2.y - 10);
    string threat = "";
    if(src.containsThreat) threat = "True";
    else threat = "False";
    
    putText(src.image, "Threat Detected: " + threat, p1,
            FONT_HERSHEY_COMPLEX_SMALL, 0.42, Scalar(255,255,255), 1, CV_AA);
    putText(src.image, "Num. of Persons: " + to_string(src.numPeople), p2,
            FONT_HERSHEY_COMPLEX_SMALL, 0.42, Scalar(255,255,255), 1, CV_AA);
    putText(src.image, "Threat Info: " + src.threatInfo, p3,
            FONT_HERSHEY_COMPLEX_SMALL, 0.42, Scalar(255,255,255), 1, CV_AA);
    return src;
}

void writeResultsToFile(InputImage input[])
{
    ofstream file("Test_Eval\\opticalSecDetectResults.json", std::ios::out);
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
    cout << "Successfully written to file!" << endl;
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