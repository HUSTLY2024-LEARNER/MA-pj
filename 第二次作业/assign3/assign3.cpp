#include <opencv2/opencv.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<iostream>

using namespace std;
using namespace cv;

#define widname_1 "src"
#define widname_2 "out"
#define widname_3 "out1"
#define widname_4 "out2"
#define widname_5 "out3"

int main() {
    // 图像加载
    Mat image = imread("/mnt/c/Users/86187/Desktop/rm/lesson2/assignment/assign3/车牌3.png");

    if (image.empty()) {
        std::cerr << "Could not open or find the image." << std::endl;
        return -1;
    }

    // 图像预处理，转成hsv图像
    Mat hsvImage,erodeimage,dilateimage;
    Mat element=getStructuringElement(MORPH_RECT,Size(7,7),Point(3,3));
    vector<Vec4i> g_vHierarchy;
    cvtColor(image, hsvImage, COLOR_BGR2HSV);
    imshow(widname_1, image);

    //二值化，只保留蓝色部分 
    inRange(hsvImage, Scalar(100, 223, 40), Scalar(130, 255, 255), hsvImage);
    imshow(widname_2, hsvImage);

    //膨胀
    dilate(hsvImage,dilateimage,element);    
    imshow(widname_3, dilateimage);

    //腐蚀
    erode(dilateimage,erodeimage,element);
    imshow(widname_4, erodeimage);
    GaussianBlur(erodeimage, erodeimage, Size(5, 5), 0);
    
    //寻找轮廓
    vector<vector<Point>> contours;
    findContours(erodeimage, contours, g_vHierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE, Point(0, 0));
    
    //寻找图中轮廓面积最大值，即车牌的轮廓
    double maxarea=-1;
    int aim=0;
    for(int i=0;i<contours.size();i++){
        double area = contourArea(contours[i]);
        if(area>maxarea){
            aim=i;
            maxarea=area;
        }
    }

    //求该轮廓的最小外接矩形并输出在原图
    Rect rect = boundingRect(contours[aim]);
     rectangle(image, rect, Scalar(0, 255, 0), 2);
     imshow(widname_5, image);
    waitKey(0);
    return 0;
}
