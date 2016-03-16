#include <iostream>
#include <math.h>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "featureDetection.h"
#include "InputImage.h"

using namespace std;
using namespace cv;

std::vector<std::vector<cv::Point>> contours;
std::vector<std::vector<cv::Point>> curvedLines;

InputImage magazineDetection(InputImage src)
{
    Mat img, dst;
    img = src.image.clone();
    cvtColor(src.image, dst, CV_GRAY2BGR);
    std::vector<cv::Point> contour;
    cv::findContours(img, contours, CV_RETR_LIST, CV_CHAIN_APPROX_NONE);
    cout << "Test" << endl;
    for(int i = 0; i < 1; i++)
    {
        contour = contours.at(i);
        cout << src.imageName << "\n";
        cout << "Size = " + to_string(contour.size()) << "\n";
        curvedLines.push_back(getCurvedLine(contour));
        if(isNearOtherCurve(contour))
        {
            //cv::drawContours(dst, contour, 0, Scalar(0,255,0));
            //draw curves and store result to InputImage
        }
    }
    
    src.image = dst;
    return src;
}

vector<cv::Point> getCurvedLine(vector<cv::Point> contour)
{
    //This function will read in read in a vector of points
    //and then find if the line is suitably curved
    vector<cv::Point> matchSlopes;
    vector<float> slopes;
    Point p1, p2;
    Point first = contour.front();
    Point middle = contour.at(contour.size() / 2);
    Point last = contour.back();
    float A, B, C, X, Y;
    for(int i = 0; i < contour.size(); i++)
    {
        p1 = contour.at(i);
        p2 = contour.at(i+1);
        slopes.push_back(getSlope(p1, p2));
    }
    for(int i = 0; i < slopes.size(); i++)
    {
        if(slopes.at(i) == (slopes.at(slopes.size()-i))*-1 || -1*(slopes.at(i)) == slopes.at(slopes.size()-i))
        {
            if(matchSlopes.empty())
            {
                matchSlopes.push_back(contour.at(i));
                matchSlopes.push_back(contour.at(i+1));
            }
            else
            {
                matchSlopes.push_back(contour.at(i+1));
                matchSlopes.push_back(contour.at(i+2));
            }
        }
    }
    return matchSlopes;
}

bool isNearOtherCurve(std::vector<cv::Point> contour)
{
    Point p = contour.at(contour.size() / 2);
    Rect r = getRect(p);
    for(int i = 0; i < curvedLines.size(); i++)
    {
        for(int j = 0; j < curvedLines.at(i).size(); i++)
        {
            if(r.contains(curvedLines.at(i).at(j)) && curvedLines.at(i).at(j) != contour)
            {
                return true;
            }
        }
    }
    return false;
}

bool isSimilarCurve(std::vector<cv::Point> contour)
{
    //This function will check if curve is similar to any others
    return true;
}


//    vector<Vec3f> circles;
//    HoughCircles(img, circles, CV_HOUGH_GRADIENT, 2, dst.rows/20, 200, 100);
//    cout << "Size: " + to_string(circles.size()) << "\n";
//    for(int i = 0; i < circles.size(); i++)
//    {
//        Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
//        int radius = cvRound(circles[i][2]);
//        circle(dst, center, 3, Scalar(0,255,0), 1, 8, 0);
//        circle(dst, center, radius, Scalar(0,0,255), 1, 8, 0);
//    }