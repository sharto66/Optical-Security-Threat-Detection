#include <cstdio>
#include <iostream>
#include <string>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace std;
using namespace cv;

int MAX_KERNEL_LENGTH = 31;

Mat filterImage(Mat src){
    Mat dst;
    for ( int j = 1; j < MAX_KERNEL_LENGTH; j = j + 2 )
    {
        bilateralFilter(src, dst, j, j*2, j/2);
    }
    return dst;
}

Mat blobDetection(Mat src){
           Mat dst;
           cv::Ptr<cv::SimpleBlobDetector> detector = cv::SimpleBlobDetector::create();
           std::vector<KeyPoint> keypoints;
           detector->detect(src, keypoints);
           drawKeypoints(src, keypoints, dst, Scalar(0,0,255), DrawMatchesFlags::DRAW_RICH_KEYPOINTS );
           return dst;
}


