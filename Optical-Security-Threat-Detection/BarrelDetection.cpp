#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace std;
using namespace cv;

float getSlope(Point p1, Point p2);
Rect getRect(Point p);
Mat rotate(Mat src);
bool cornerDetected(Mat harris, Point p);
bool slopeMatch(float s1, float s2);
bool lengthMatch(Point p1, Point p2, Point p3, Point p4);
bool endToEnd(Point p1, Point p2, Point p3, Point p4);

Mat barrelDetection(Mat src)
{
    //src = rotate(src);
    Mat hough, harris, dst;
    cvtColor(src, dst, CV_GRAY2BGR);
    std::vector<Vec4i> lines;
    HoughLinesP(src, lines, 0.1, CV_PI/180, 20, 1, 0.00);
    cornerHarris(src, harris, 3, 5, 0.1, BORDER_DEFAULT);
    normalize(harris, harris, 0, 255, NORM_MINMAX, CV_32FC1, Mat());
    for(int i = 0; i < lines.size(); i++)
    {
        Point p1 = Point(lines[i][0], lines[i][1]);
        Point p2 = Point(lines[i][2], lines[i][3]);
        Rect r1 = getRect(p1);
        Rect r2 = getRect(p2);
        float slope1 = getSlope(p1, p2);
        for(int j = i+1; j < lines.size(); j++)
        {
            Point p3 = Point(lines[j][0], lines[j][1]);
            Point p4 = Point(lines[j][2], lines[j][3]);
            float slope2 = getSlope(p3, p4);
            if(slopeMatch(slope1, slope2) && lengthMatch(p1, p2, p3, p4)){
                if(p3.inside(r1) || p3.inside(r2) && p4.inside(r1) || p4.inside(r2)){
                    if(cornerDetected(harris, p1) || cornerDetected(harris, p2) && endToEnd(p1, p2, p3, p4)){
//                        rectangle(dst, r1.tl(), r1.br(), Scalar(0,255,0), 1);
//                        rectangle(dst, r2.tl(), r2.br(), Scalar(0,255,0), 1);
                        line(dst, p1, p2, Scalar(0,0,255), 1, 8);
                        line(dst, p3, p4, Scalar(0,255,0), 1, 8);
                    }
                }
            }
        }
    }
    return dst;
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
    int pad = 20;
    
    r.width = pad;
    r.height = pad;
    r.x = p.x - r.width/2;
    r.y = p.y - r.height/2;
    
    return r;
}

Mat rotate(Mat src)
{
    double angle = -20.00f;
    Point2f center(src.cols/2.0, src.rows/2.0);
    Mat rot = getRotationMatrix2D(center, angle, 1.0);
    Rect bbox = RotatedRect(center,src.size(), angle).boundingRect();
    rot.at<double>(0,2) += bbox.width/2.0 - center.x;
    rot.at<double>(1,2) += bbox.height/2.0 - center.y;
    cv::warpAffine(src, src, rot, bbox.size());
    return src;
}

//function needs to be be re implemented to allow variances
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