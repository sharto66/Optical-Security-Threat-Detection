#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace std;
using namespace cv;

Mat magazineDetection(Mat src)
{
    Mat img, dst, dstCopy;
    cvtColor(src, dst, CV_GRAY2BGR);
    
    vector<Vec4f> position;
    
    Ptr<GeneralizedHoughGuil> hough = createGeneralizedHoughGuil();

    hough->setMinDist(100);
    hough->setLevels(360);
    hough->setDp(2);
    hough->setMaxBufferSize(1000);
    hough->setMinAngle(0);
    hough->setMaxAngle(360);
    hough->setMinScale(0.2);
    hough->setMaxScale(3);
    hough->setAngleStep(1);
    hough->setAngleThresh(10000);
    hough->setScaleStep(0.05);
    hough->setScaleThresh(1000);
    hough->setPosThresh(100);
    
    hough->detect(src, position);
    
    cout << "Found : " << position.size() << " objects" << endl;
    
    return dst;
}