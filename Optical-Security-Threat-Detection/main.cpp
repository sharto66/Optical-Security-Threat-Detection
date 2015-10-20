#include <cstdio>
#include <iostream>
#include <string>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

#define NUM 5

using namespace std;
using namespace cv;

Mat filterImage(Mat src);
Mat blobDetection(Mat src);

int main()
{
    Mat images[NUM];
    Mat image, dst;
    Mat im_with_keypoints;
    char image_name[100];
    
    for(int i=0;i < NUM; i++)
    {
        sprintf(image_name, "C:\\Users\\Sean\\Pictures\\guns/image%d.jpg",i+1);
        image = imread(image_name, IMREAD_GRAYSCALE);
        images[i] = image;
    }
    int size = sizeof(images)/sizeof(images[0]);
    cout << size << endl;
    for(int i=0;i < size; i++)
    {
        if(images[i].data){
           images[i] = filterImage(images[i]);
           images[i] = blobDetection(images[i]);
           namedWindow(string("Display window") + std::to_string(i+1), WINDOW_AUTOSIZE);
           imshow(string("Display window") + std::to_string(i+1), images[i] );
        }
    }
    waitKey(0);
    cvDestroyAllWindows();
    return 0;
}


