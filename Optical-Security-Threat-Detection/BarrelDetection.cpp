#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "InputImage.h"
#include "opticalsecurity.h"
#include "featureDetection.h"

using namespace std;
using namespace cv;

std::vector<int> rotDegrees;

InputImage barrelDetection(InputImage src)
{
    Mat img, harris, dst, dstCopy;
    cvtColor(src.image, dst, CV_GRAY2BGR);
    cvtColor(src.image, dstCopy, CV_GRAY2BGR);
    std::vector<Vec4i> lines;
    Point p1, p2, p3, p4;
    Rect r1, r2;
    for(int i = 0; i < 45; i++)
    {
        img = rotate(src.image, i);
        dst = rotate(dstCopy, i);
        HoughLinesP(img, lines, 0.1, CV_PI/180, 20, 5, 0.00);
        cornerHarris(img, harris, 3, 5, 0.1, BORDER_DEFAULT);
        normalize(harris, harris, 0, 255, NORM_MINMAX, CV_32FC1, Mat());
        for(int k = 0; k < lines.size(); k++)
        {
            p1 = Point(lines[k][0], lines[k][1]);
            p2 = Point(lines[k][2], lines[k][3]);
            r1 = getRect(p1);
            r2 = getRect(p2);
            float slope1 = getSlope(p1, p2);
            for(int j = k+1; j < lines.size(); j++)
            {
                p3 = Point(lines[j][0], lines[j][1]);
                p4 = Point(lines[j][2], lines[j][3]);
                float slope2 = getSlope(p3, p4);
                if(slopeMatch(slope1, slope2) && endToEnd(p1, p2, p3, p4)){
                    if(p3.inside(r1) || p3.inside(r2) && p4.inside(r1) || p4.inside(r2)){
                        if(cornerDetected(harris, p1) || cornerDetected(harris, p2)){
                            if(isGunColour(src.origImage, p1, p2, p3, p4)){
//                                if(src.barrelPoints.size() < 100){
//                                src.barrelPoints.push_back(p1);
//                                src.barrelPoints.push_back(p2);
//                                src.barrelPoints.push_back(p3);
//                                src.barrelPoints.push_back(p4);
//                                rotDegrees.push_back(i);
//                                }
                                src.containsThreat = true;
                                src.threatInfo = "Gun barrel";
                                cv::line(dst, p1, p2, Scalar(0,0,255), 1, 8);
                                cv::line(dst, p3, p4, Scalar(0,255,0), 1, 8);
//                                return src;
                            }
                        }
                    }
                }
            }
        }
    }
//    src = drawLines(src);
    cv::flip(dst.t(), dst, 1);
    src.origImage = dst;
    return src;
}

bool isGunColour(Mat src, Point p1, Point p2, Point p3, Point p4)
{
    try{
        Mat img;
        Rect r = getROIrectangle(p1, p2, p3, p4);
        img = src(r).clone();
        img = thresholdImage(img);
        int total = img.rows * img.cols;
        float percent = 0;
        if(countBlackPixels(img) > 0){
            float black = countBlackPixels(img);
            percent = (black / total) * 100.00f;
        }
        if(percent < 70){
            return false;
        }
        else{
            return true;
        }
    }
    catch(cv::Exception e){
        return false;
    }
    catch(std::exception e){
        return false;
    }
}

Rect getROIrectangle1(Point p1, Point p2, Point p3, Point p4)
{
//    Rect r;
//    float height, width, len;
//    float len1 = norm(p1-p2);
//    float len2 = norm(p3-p4);
//    float len3 = norm(p1-p3);
//    float len4 = norm(p2-p4);
//    if(len1 >= len2){
//        len = len1;
//    }
//    else len = len2;
//    if(p1.y > p2.y || p1.y < p2.y){
//        
//    }
//    else if(p1.x > p2.x || p1.x < p2.x){
//        
//    }
//    r = Rect(p1.x, p1.y, 30, 30);
//    return r;
    float height, width;
    Rect r;
    Point center = (p1 + p2 + p3 + p4) / 4;
    float len1 = norm(p1-p2);
    float len2 = norm(p3-p4);
    if(p1.y > p2.y || p1.y < p2.y){
        if(len1 >= len2){
            height = len1;
        }
        else height = len2;
        width = 10;
    }
    else if(p1.x > p2.x || p1.x < p2.x){
        if(len1 >= len2){
            width = len1; 
        }
        else width = len2;
        height = 10;
    }
    else return r;
    r.height = height;
    r.width = width;
    r.x = center.x - r.width/2;
    r.y = center.y - r.height/2;
    return r;
}

Rect getROIrectangle(Point p1, Point p2, Point p3, Point p4)
{
    Point tl, br;
    float len1, len2, len3, len4;
    len1 = norm(p1-p3);
    len2 = norm(p1-p4);
    len3 = norm(p2-p3);
    len4 = norm(p2-p4);
    if(len1 > len2 && len1 > len3 && len1 > len4){
        if(norm(p3-p1) > len1){
            tl = p3;
            br = p2;
        }
        else{
            tl = p1;
            br = p3;
        }
    }
    else if(len2 > len1 && len2 > len3 && len2 > len4){
        if(norm(p4-p1) > len2){
            tl = p4;
            br = p1;
        }
        else{
            tl = p1;
            br = p4;
        }
    }
    else if(len3 > len1 && len3 > len2 && len3 > len4){
        if(norm(p3-p2) > len3){
            tl = p3;
            br = p2;
        }
        else{
            tl = p2;
            br = p3;
        }
    }
    else if(len4 > len1 && len4 > len2 && len4 > len3){
        if(norm(p4-p2) > len4){
            tl = p4;
            br = p2;
        }
        else{
            tl = p2;
            br = p4;
        }
    }
    Rect r = Rect(tl, br);
    return r;
}

int countBlackPixels(Mat img)
{
    int count = 0;
    for(int i = 0; i < img.rows; i++)
    {
        for( int j = 0; j < img.cols; j++)
        {
            if (img.at<uchar>(i,j) == 0)
            {
                count++;
            } 
        }
    }
    return count;
}

bool cornerDetected(Mat src, Point p1)
{
    for(int j = 0; j < src.rows ; j++)
    {
        for(int i = 0; i < src.cols; i++ )
        {
            if((int) src.at<float>(j,i) > 120)
            {
                Point p2 = Point(i, j);
                Rect r = getRect(p2);
                if(r.contains(p1)) return true;
            }
        }
    }
    return false;
}

float getSlope(Point p1, Point p2)
{
    float x1 = p1.x;
    float y1 = p1.y;
    float x2 = p2.x;
    float y2 = p2.y;
    float slope = (y2 - y1) / (x2 - x1);
    return slope;
}

bool slopeMatch(float s1, float s2)
{
    float var = 0.04;
    if(s1 == s2) return true;
    else if(s1 > s2){
        float diff = s1 - s2;
        if(diff <= var && diff >= -var) return true;
    }
    else if(s2 > s1){
        float diff = s2 - s1;
        if(diff <= var && diff >= -var) return true;
    }
    else return false;
}

bool lengthMatch(Point p1, Point p2, Point p3, Point p4)
{
    float minLength = 5;
    float len1, len2;
    
    len1 = norm(p1-p2);
    len2 = norm(p3-p4);
    
    if(len1 >= minLength && len2 >= minLength) return true;
    else return false;
}

Rect getRect(Point p)
{
    Rect r;
    int pad = 25;
    
    r.width = pad;
    r.height = pad;
    r.x = p.x - r.width/2;
    r.y = p.y - r.height/2;
    
    return r;
}

Mat rotate(Mat src, float angle)
{
    angle *= 2;
    Point2f center = Point2f(src.cols/2.0, src.rows/2.0);
    Rect bbox = RotatedRect(center,src.size(), angle).boundingRect();
    Mat rot = getRotationMatrix2D(center, angle, 1.0);
    rot.at<double>(0,2) += bbox.width/2.0 - center.x;
    rot.at<double>(1,2) += bbox.height/2.0 - center.y;
    cv::warpAffine(src, src, rot, bbox.size());
    rot.release();
    return src;
}

bool endToEnd(Point p1, Point p2, Point p3, Point p4)
{
    if(p1.x == p3.x || p1.x == p4.x || p2.x == p3.x || p2.x == p4.x){
        return false;
    }
    else if(p1.y == p3.y || p1.y == p4.y || p2.y == p3.y || p2.y == p4.y){
        return false;
    }
    else return true;
}

InputImage drawLines(InputImage img)
{
    cout << "Size: " +  to_string(img.barrelPoints.size()) << endl;
    if(img.barrelPoints.size() < 4){
        return img;
    }
    int rotCount = 0;
    for(int i = 0; i < img.barrelPoints.size()-4; i=i+4)
    {
        Point p1 = img.barrelPoints.at(i);
        Point p2 = img.barrelPoints.at(i+1);
        Point p3 = img.barrelPoints.at(i+2);
        Point p4 = img.barrelPoints.at(i+3);
        img.origImage = rotate(img.origImage, rotDegrees.at(rotCount));
        rotCount++;
        cv::line(img.origImage, p1, p2, Scalar(0,0,255), 1, 8);
        cv::line(img.origImage, p3, p4, Scalar(0,255,0), 1, 8);
    }
    img.origImage = rotate(img.origImage, 0);
    rotDegrees.clear();
    cout << "out" << endl;
    return img;
}