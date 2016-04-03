#include <iostream>
#include <string>
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
    cout << to_string(contours.size()) << endl;
    for(int i = 0; i < contours.size()-1; i++)
    {
        contour = contours.at(i);
        if(contour.size() > 12)
        {
            curvedLines.push_back(getCurvedLine(contour));
            if(curvedLines.size() > 1 && isNearOtherCurve(contour))
            {
                cout << "IN" << endl;
                //cv::drawContours(dst, contour, 0, Scalar(0,255,0));
                //draw curves and store result to InputImage
            }
        }
    }
    src.image = dst;
    return src;
}

std::vector<cv::Point> getCurvedLine(std::vector<cv::Point> contour)
{
    std::vector<cv::Point> matchSlopes;
    std::vector<float> slopes;
    Point p1, p2;
    for(int i = 0; i < contour.size()-4; i=i+4)
    {
        p1 = contour.at(i);
        p2 = contour.at(i+4);
        slopes.push_back(getSlope(p1, p2));
    }
    cout << "Size = " + to_string(slopes.size()) << endl;
    if(slopes.size()-1 % 2 != 0){
        slopes.pop_back();
    }
    for(int i = 0; i < slopes.size()-1; i++)
    {
        for(int j = slopes.size()-1; j > i+1; j--)
        {
            try{
                if(slopes.at(i) * (slopes.at(j)) == -1 && slopes.at(i+1) * (slopes.at(j-1)) == -1)
                {
                    if(matchSlopes.empty())
                    {
                        matchSlopes.push_back(contour.at(i));
                        matchSlopes.push_back(contour.at(i+4));
                    }
                    else
                    {
                        matchSlopes.push_back(contour.at(i+4));
                        matchSlopes.push_back(contour.at(i+8));
                    }
                }
            }
            catch(cv::Exception e){
                cout << "Exception cv" << endl;
                break;
            }
            catch(std::exception e){
                cout << "Exception std" << endl;
                break;
            }
        }
    }
    cout << "Test at end" << endl;
    return matchSlopes;
}

bool isNearOtherCurve(std::vector<cv::Point> contour)
{
    Point p = contour.at(contour.size() / 2);
    Rect r = getRect(p);
    cout << "curvedLines size = " + to_string(curvedLines.size()) << endl;
    int size;
    
    if(curvedLines.size() == 1){
        size = 1;
    }
    else{
        size = curvedLines.size()-1;
    }
    cout << "before double loop" << endl;
    for(int i = 0; i < size; i++)
    {
        cout << "in loop 1" << endl;
        for(int j = 0; j < curvedLines.at(i).size(); j++)
        {
            cout << "in loop 2" << endl;
            try{
                if(r.contains(curvedLines.at(i).at(j)) && curvedLines.at(i) != contour)
                {
                    cout << "in if" << endl;
//                    if(isSimilarCurve(contour, curvedLines.at(i)))
//                    {
                        return true;
//                    }
                }
            }
            catch(std::exception e){
                cout << "STD ERROR" << endl;
            }
        }
    }
    return false;
}

bool isSimilarCurve(std::vector<cv::Point> line1, std::vector<cv::Point> line2)
{
    if(getCurvedLine(line1) == getCurvedLine(line2))
    {
        return true;
    }
    else return false;
}

//std::vector<float> getSlopesOfCurve(std::vector<cv::Point> line)
//{
//    std::vector<float> slopes;
//    
//}