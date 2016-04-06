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

bool sameDetectedPerson(Rect r1, Rect r2);

cv::String cascades[3] = {"haarcascades/haarcascade_frontalface_default.xml",
                          "haarcascades/haarcascade_frontalface_alt.xml",
                          "haarcascades/haarcascade_frontalface_alt2.xml"};

cv::String body_cascade_name = "haarcascades/haarcascade_upperbody.xml";

InputImage detectPeople(InputImage src)
{
    CascadeClassifier cascade;
    int size = sizeof(cascades)/sizeof(cascades[0]);
    std::vector<Rect> human, human_filtered;
    
    for(int k = 0; k < size; k++)
    {
        if(!cascade.load(cascades[k])){
            cout << "Error loading cascade file" << endl;
            return src;
        }
        else{
            cascade.detectMultiScale(src.image, human, 1.1, 2, 0 | CV_HAAR_SCALE_IMAGE, Size(10, 10));
        }
        int i, j;
        for(i=0; i < human.size(); i++)
        {
            Rect r = human[i];
            for(j=0; j < human.size(); j++)
            {
                if(j != i && (r & human[j]) == r) break;
            }
            if(j == human.size()){
                if(human_filtered.size() == 0){
                    human_filtered.push_back(r);
                }
                else{
                    for(int l = 0; l < human_filtered.size(); l++)
                    {
                        if((human_filtered[l] & r) != r){
                            human_filtered.push_back(r);
                            src.numPeople += 1;
                            break;
                        }
                    }
                }
            }
        }
        for(i=0; i < human_filtered.size(); i++) 
        {
            Rect r = human_filtered[i];
            r.x += cvRound(r.width*0.1);
            r.width = cvRound(r.width*0.8);
            r.y += cvRound(r.height*0.07);
            r.height = cvRound(r.height*0.8);
            //rectangle(src.image, r.tl(), r.br(), Scalar(0,255,0), 1);   
        }
    }
    return src;
}