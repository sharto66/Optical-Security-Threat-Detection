#include <cstdio>
#include <iostream>
#include <string>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace std;
using namespace cv;

int MAX_KERNEL_LENGTH = 31;
int GAUSSIAN_KERNEL = 6;

Mat filterImage(Mat src)
{
    Mat dst;
    for ( int j = 1; j < MAX_KERNEL_LENGTH; j = j + 2 )
    {
        bilateralFilter(src, dst, j, j*2, j/2);
    }
    return dst;
}

Mat blurImage(Mat src)
{
    Mat dst;
    for (int i=1; i<GAUSSIAN_KERNEL; i=i+2)
    {
        GaussianBlur(src, dst, Size(i, i), 0, 0);
    }
    return dst;
}

Mat blobDetection(Mat src)
{
    Mat dst;
    SimpleBlobDetector::Params params;

    // Filter by Area.
    params.filterByArea = true;
    params.minArea = 300;

    // Filter by Circularity
    params.filterByCircularity = false;
    params.minCircularity = 0.5;

    // Filter by Convexity
    params.filterByConvexity = false;
    params.maxConvexity = 0.87;

    // Filter by Inertia
    params.filterByInertia = true;
    params.minInertiaRatio = 0.01;
    params.maxInertiaRatio = 0.3;
    
    cv::Ptr<cv::SimpleBlobDetector> detector = cv::SimpleBlobDetector::create(params);
    std::vector<KeyPoint> keypoints;
    detector->detect(src, keypoints);
    drawKeypoints(src, keypoints, dst, Scalar(0,0,255), DrawMatchesFlags::DRAW_RICH_KEYPOINTS);
    return dst;
}

Mat barrelDetection(Mat src)
{
    Mat dst;
    cvtColor(src, dst, CV_GRAY2BGR);
    std::vector<Vec2f> lines;
    cv::HoughLines(src, lines, 1, CV_PI/180, 70, 0, 10);
    cout << lines.size() << endl;
    for(int i = 0; i < lines.size(); i++)
    {
        float r = lines[i][0];
        float theta = lines[i][1];
        cv::Point p1, p2;
        double a = cos(theta), b = sin(theta);
        double x0 = a*r, y0 = b*r;
        p1.x = cvRound(x0 + 1000*(-b)); //the first point
        p1.y = cvRound(y0 + 1000*(a)); //the first point
        p2.x = cvRound(x0 - 1000*(-b)); //the second point
        p2.y = cvRound(y0 - 1000*(a)); //the second point
        line(dst, p1, p2, Scalar(255,100,0), 1, 4, 0);
    }
    return dst;
}

Mat edgeDetection(Mat src)
{
    Mat edge, dst;
    Canny(src, edge, 50, 150, 3);
    edge.convertTo(dst, CV_8U);
    return dst;
}