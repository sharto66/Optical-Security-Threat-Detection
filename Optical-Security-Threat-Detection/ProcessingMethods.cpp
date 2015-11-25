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
int GAUSSIAN_KERNEL = 6;

CascadeClassifier face_cascade;
string face_cascade_name = "C:\\Projects\\Final Year Project\\Optical-Security-Threat-Detection\\Optical-Security-Threat-Detection/haarcascade_frontalface_alt2.xml";

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
    std::vector<Vec2f> lines;
    cv::HoughLines(src, lines, 5, CV_PI/180, 100, 0, 0);
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
    HOGDescriptor hog;
    hog.setSVMDetector(HOGDescriptor::getDefaultPeopleDetector());
 
    while (true)
    {
        if (src.empty())
            continue;
 
        vector<Rect> found, found_filtered;
        hog.detectMultiScale(src, found, 0, Size(8,8), Size(32,32), 1.05, 2);
        size_t i, j;
        for (i=0; i<found.size(); i++) 
        {
            Rect r = found[i];
            for (j=0; j<found.size(); j++) {
                if (j!=i && (r & found[j]) == r)
                    break;
                }
            if (j== found.size())
                found_filtered.push_back(r);
        }
 
        for (i=0; i<found_filtered.size(); i++) 
        {
            Rect r = found_filtered[i];
            r.x += cvRound(r.width*0.1);
		    r.width = cvRound(r.width*0.8);
		    r.y += cvRound(r.height*0.07);
		    r.height = cvRound(r.height*0.8);
		    rectangle(src, r.tl(), r.br(), Scalar(0,255,0), 3);        
        }
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
    face_cascade.detectMultiScale(src, faces, 1.1, 2, 0 | CASCADE_SCALE_IMAGE, Size(60, 60));
    int i, j;
    for (i=0; i<faces.size(); i++) 
    {
        Rect r = faces[i];
        for (j=0; j<faces.size(); j++) {
            if (j!=i && (r & faces[j]) == r)
                break;
            }
        if (j== faces.size())
            faces_filtered.push_back(r);
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