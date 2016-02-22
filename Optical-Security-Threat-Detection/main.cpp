#include <cstdio>
#include <iostream>
#include <string>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "InputImage.h"
#include "opticalsecurity.h"

#define NUM 10

using namespace std;
using namespace cv;

float borderPercent = 0.20;

int main()
{
    InputImage input[NUM];
    Mat image;
    char image_name[100];
    char* image_location;
    int imgSet;
    
    cout << "Enter 1 for pistols" << endl;
    cout << "Enter 2 for all guns" << endl;
    cout << "Enter 3 for test image in root" << endl;
    cout << "Enter 4 for OpenCV test images" << endl;
    cin >> imgSet;
    
    image_location = getImageSet(imgSet);
    
    for(int i=0;i < NUM; i++)
    {        
        sprintf(image_name, image_location, i+1);
        input[i].image = imread(image_name);
    }
    int size = sizeof(input)/sizeof(input[0]);
    cout << size << endl;
    for(int i=0;i < size; i++)
    {
        if(input[i].image.data)
        {
           input[i] = detectPeople(input[i]);
           //input[i] = blurImage(input[i]);
           //input[i] = colourThreshold(input[i]);
           //input[i] = thresholdImage(input[i]);
           //input[i] = edgeDetection(input[i]);
           //input[i] = barrelDetection(input[i]);
           //input[i] = magazineDetection(input[i]);
           //input[i] = lineDetect(input[i]);
           
           int bottom = (int) (borderPercent * input[i].image.rows);
           copyMakeBorder(input[i].image, input[i].image, 0, bottom, 0, 0, BORDER_CONSTANT, Scalar(0,0,0));
           Point p = cvPoint(10, input[i].image.rows - 20);
           putText(input[i].image, "Threat Detected: " + to_string(input[i].containsThreat), p,
                   FONT_HERSHEY_COMPLEX_SMALL, 0.5, Scalar(255,255,255), 1, CV_AA);
           //putText(input[i].image, "Num. of Persons: " + to_string(input[i].numPeople), );
           //putText(input[i].image, "Threat Info: " + input[i].threatInfo, );
           namedWindow(string("Display window") + std::to_string(i+1), WINDOW_AUTOSIZE);
           imshow(string("Display window") + std::to_string(i+1), input[i].image);
        }
        else
        {
            cout << "Something wrong" << endl;
        }
    }
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

