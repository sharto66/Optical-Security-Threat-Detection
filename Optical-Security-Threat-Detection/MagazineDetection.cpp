#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "InputImage.h"

using namespace std;
using namespace cv;

InputImage magazineDetection(InputImage src)
{
    Mat img, dst, dstCopy;
    cvtColor(src.image, dst, CV_GRAY2BGR);
    img = src.image.clone();
    
    std::vector<std::vector<cv::Point>> contours;
    cv::findContours(img, contours, CV_RETR_LIST, CV_CHAIN_APPROX_NONE);
    
    for(int i = 0; i < contours.size(); i++)
    {
        //function needed here to check if contour is curved
        //Perhaps HoughLines() could be used here instead?
        cv::drawContours(dst, contours, i, Scalar(0,255,0));
    }
    
    src.image = dst;
    
//    for(int i = 0; i < contours.size(); i++)
//    {
//        Point p1 = Point(contours[i][0], contours[i][1]);
//        Point p2 = Point(contours[i][2], contours[i][3]);
//        for(int j = i+1; j < contours.size(); j++)
//        {
//            Point p3 = Point(contours[j][0], contours[j][1]);
//            Point p4 = Point(contours[j][2], contours[j][3]);
//        }
//    }
    
//    vector<Vec4f> position;
//    Ptr<GeneralizedHoughGuil> hough = createGeneralizedHoughGuil();
//
//    hough->setMinDist(100);
//    hough->setLevels(360);
//    hough->setDp(2);
//    hough->setMaxBufferSize(1000);
//    hough->setMinAngle(0);
//    hough->setMaxAngle(90);
//    hough->setMinScale(0.05);
//    hough->setMaxScale(2);
//    hough->setAngleStep(1);
//    hough->setAngleThresh(50);
//    hough->setScaleStep(0.05);
//    hough->setScaleThresh(50);
//    hough->setPosThresh(80);
//    
//    Mat templ = imread("C:\\Users\\Sean\\Pictures\\OpenCV Tests/magazine2.jpg", IMREAD_GRAYSCALE);
//    //namedWindow("Template", WINDOW_AUTOSIZE);
//    //imshow("Template", templ);
//    hough->setTemplate(templ);
//    
//    hough->detect(src.image, position);
//    
//    cout << "Found : " << position.size() << " objects" << endl;
    
    return src;
}

bool curvedLine(std::vector<cv::Point> contour)
{
    
}