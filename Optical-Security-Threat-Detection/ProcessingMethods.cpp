#include <cstdio>
#include <iostream>
#include <string>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/objdetect.hpp>


using namespace std;
using namespace cv;

int MAX_KERNEL_LENGTH = 31;
int GAUSSIAN_KERNEL = 7;

cv::String face_cascade_name = "haarcascades/haarcascade_frontalface_alt.xml";
cv::String body_cascade_name = "haarcascades/haarcascade_upperbody.xml";
CascadeClassifier face_cascade;
CascadeClassifier body_cascade;

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
    for (int i=1; i<GAUSSIAN_KERNEL; i=i+2)
    {
        GaussianBlur(src, src, Size(i, i), 0, 0);
    }
    return src;
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
    std::vector<Vec4i> lines;
    cv::HoughLinesP(src, lines, 1, CV_PI/180, 10, 5, 1);
    cout << lines.size() << endl;
    for(int i = 0; i < lines.size(); i++)
    {
        line(dst, Point(lines[i][0], lines[i][1]), Point(lines[i][2], lines[i][3]), Scalar(0,0,255), 1, 8);
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

Mat generalisedHough(Mat src)
{
    Mat templ = imread("C:\\Users\\Sean\\Pictures/pistol.jpg", IMREAD_GRAYSCALE);
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
    
    hough->setTemplate(templ);
    
    hough->detect(src, position);
    
    cout << "Found : " << position.size() << " objects" << endl;
    
    
}

Mat detectPeople(Mat src)
{
    std::vector<Rect> body, body_filtered;
    if (!body_cascade.load(body_cascade_name)){
        cout << "Error loading body cascade" << endl;
        return src;
    }
    body_cascade.detectMultiScale(src, body, 1.1, 2, 0 | CV_HAAR_SCALE_IMAGE, Size(30, 30));
    int i, j;
    for (i=0; i < body.size(); i++) 
    {
        cout << "Body detected" << endl;
        Rect r = body[i];
        for (j=0; j < body.size(); j++)
        {
            if (j!=i && (r & body[j]) == r) break;
        }
        if (j== body.size())
            body_filtered.push_back(r);
    }
    for (i=0; i < body_filtered.size(); i++) 
    {
        Rect r = body_filtered[i];
        r.x += cvRound(r.width*0.1);
        r.width = cvRound(r.width*0.8);
        r.y += cvRound(r.height*0.07);
        r.height = cvRound(r.height*0.8);
        rectangle(src, r.tl(), r.br(), Scalar(0,255,0), 2);   
    }
    return src;
}

Mat detectFaces(Mat src)
{
    std::vector<Rect> faces, faces_filtered;
    if (!face_cascade.load(face_cascade_name)){
        cout << "Error loading face cascade" << endl;
        return src;
    }
    face_cascade.detectMultiScale(src, faces, 1.1, 1, 1 | CV_HAAR_SCALE_IMAGE, Size(30, 30));
    int i, j;
    for (i=0; i<faces.size(); i++) 
    {
        cout << "Face detected" << endl;
        Rect r = faces[i];
        for (j=0; j<faces.size(); j++)
        {
            if (j!=i && (r & faces[j]) == r) break;
        }
        if (j== faces.size()) faces_filtered.push_back(r);
    }
    for (i=0; i<faces_filtered.size(); i++) 
    {
        Rect r = faces_filtered[i];
        r.x += cvRound(r.width*0.1);
        r.width = cvRound(r.width*0.8);
        r.y += cvRound(r.height*0.07);
        r.height = cvRound(r.height*0.8);
        rectangle(src, r.tl(), r.br(), Scalar(0,255,0), 3);   
    }
    return src;
}