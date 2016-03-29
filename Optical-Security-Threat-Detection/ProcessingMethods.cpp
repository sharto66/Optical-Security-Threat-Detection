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

int MAX_KERNEL_LENGTH = 31;
int GAUSSIAN_KERNEL = 6;
int threshold = 200;

InputImage blurImage(InputImage src)
{
    for (int i=1; i<GAUSSIAN_KERNEL; i=i+2)
    {
        GaussianBlur(src.image, src.image, Size(i, i), 0, 0);
    }
    return src;
}

InputImage thresholdImage(InputImage src)
{
    int threshold_value = 200;
    int const max_BINARY_value = 255;
    cvtColor(src.image, src.image, CV_BGR2GRAY);
    cv::threshold(src.image, src.image, threshold_value, max_BINARY_value, THRESH_BINARY_INV);
    return src;
}

Mat thresholdImage(Mat src)
{
    Mat channels[3];
    cvtColor(src, src, CV_BGR2HSV);
    split(src, channels);
    int low = 16;
    int high = 100;
    Mat val = (channels[2] < low) | (channels[2] > high);
    cv::threshold(val, val, 1, 255, THRESH_OTSU + CV_THRESH_BINARY);
    return val;
}

InputImage colourThreshold(InputImage src)
{
    Mat channels[3];
    cvtColor(src.image, src.image, CV_BGR2HSV);
    split(src.image, channels);
    int low = 16;
    int high = 100;
    Mat val = (channels[2] < low) | (channels[2] > high);
    cv::threshold(val, val, 1, 255, THRESH_OTSU + CV_THRESH_BINARY);
    src.image = val;
    return src;
}

InputImage lineDetect(InputImage src)
{
    Mat dst;
    cvtColor(src.image, dst, CV_GRAY2BGR);
    std::vector<Vec4i> lines;
    cv::HoughLinesP(src.image, lines, 1, CV_PI/180, 10, 1.75, 2);
    cout << lines.size() << endl;
    for(int i = 0; i < lines.size(); i++)
    {
        line(dst, Point(lines[i][0], lines[i][1]), Point(lines[i][2], lines[i][3]), Scalar(0,0,255), 1, 8);
    }
    src.image = dst;
    return src;
}

InputImage edgeDetection(InputImage src)
{
    Mat edge, dst;
    Canny(src.image, edge, 50, 150, 3);
    edge.convertTo(dst, CV_8U);
    src.image = dst;
    return src;
}