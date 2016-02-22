#include <cstdio>
#include <iostream>
#include <string>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/objdetect.hpp>

#include "InputImage.h"

using namespace std;
using namespace cv;

cv::String cascades[3] = {"haarcascades/haarcascade_frontalface_default.xml",
                          "haarcascades/haarcascade_frontalface_alt.xml",
                          "haarcascades/haarcascade_frontalface_alt2.xml"};

cv::String body_cascade_name = "haarcascades/haarcascade_upperbody.xml";
CascadeClassifier cascade;

int size = sizeof(cascades)/sizeof(cascades[0]);

InputImage detectPeople(InputImage src)
{
    for(int k = 0; k < size; k++)
    {
        std::vector<Rect> human, human_filtered;
        if (!cascade.load(cascades[k])){
            cout << "Error loading cascade file" << endl;
            return src;
        }
        else{
            cascade.detectMultiScale(src.image, human, 1.1, 2, 0 | CV_HAAR_SCALE_IMAGE, Size(30, 30));
        }
        int i, j;
        for (i=0; i < human.size(); i++) 
        {
            cout << "Human detected" << endl;
            src.numPeople += 1;
            Rect r = human[i];
            for (j=0; j < human.size(); j++)
            {
                if (j!=i && (r & human[j]) == r) break;
            }
            if (j== human.size())
                human_filtered.push_back(r);
        }
        for (i=0; i < human_filtered.size(); i++) 
        {
            Rect r = human_filtered[i];
            r.x += cvRound(r.width*0.1);
            r.width = cvRound(r.width*0.8);
            r.y += cvRound(r.height*0.07);
            r.height = cvRound(r.height*0.8);
            rectangle(src.image, r.tl(), r.br(), Scalar(0,255,0), 1);   
        }
    }
    return src;
}

