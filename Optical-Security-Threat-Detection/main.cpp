#include <cstdio>
#include <iostream>
#include <string>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "InputImage.h"
#include "opticalsecurity.h"

#define NUM 20

using namespace std;
using namespace cv;

int main()
{
    Mat images[NUM];
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
        image = imread(image_name);
        images[i] = image;
    }
    int size = sizeof(images)/sizeof(images[0]);
    cout << size << endl;
    for(int i=0;i < size; i++)
    {
        if(images[i].data)
        {
           images[i] = blurImage(images[i]);
           //images[i] = filterImage(images[i]);
           //images[i] = blobDetection(images[i]);
           //images[i] = colourThreshold(images[i]);
           //images[i] = thresholdImage(images[i]);
           images[i] = edgeDetection(images[i]);
           //images[i] = barrelDetection(images[i]);
           images[i] = magazineDetection(images[i]);
           //images[i] = lineDetect(images[i]);
           //images[i] = cornerDetection(images[i]);
           //images[i] = detectFaces(images[i]);
           //images[i] = detectPeople(images[i]);
           //generalisedHough(images[i]);
           namedWindow(string("Display window") + std::to_string(i+1), WINDOW_AUTOSIZE);
           imshow(string("Display window") + std::to_string(i+1), images[i]);
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

