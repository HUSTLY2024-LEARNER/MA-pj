#include<iostream>
#include<algorithm>
#include <opencv2/opencv.hpp>
#include<opencv2/highgui/highgui.hpp>

using namespace std;
using namespace cv;

#define WINDOW_NAME_1 "bgr"
#define WINDOW_NAME_2 "hsv"

// 由b，g，r三个元素求得v
double getv(double b,double g,double r){
       double v=-1;
        v=max(b,g);
        v=max(v,r);
        return v;
}

// 由b，g，r三个元素求得s
double getss(double b,double g,double r){
       double v=getv(b,g,r);
        double s;
        if(v==0) s=0;
        else {
            double mi=255;
            mi=min(b,g);
            mi=min(mi,r);
            s=(v-mi)/v;
        }
        return s;

}

// 由b，g，r三个元素求得h
double geth(double b,double g,double r){
        double v=getv(b,g,r);
        double h;
        double mi=255;
        mi=min(b,g);
        mi=min(mi,r);
        if(v==r){
            h=60*(g-b)/(v-mi);
        }else if(v==g){
            h=120+60*(b-r)/(v-mi);
        }else if(v==b){
            h=240+60*(r-g)/(v-mi);
        }
        if(h<0) h+=360;
        return h;
}


int main (){

    //读取图像，并初始化hsv图
    Mat src,output;
    src=imread("/mnt/c/Users/86187/Desktop/rm/lesson2/assignment/assign1/test.png",1);
    //src=imread("/mnt/c/Users/86187/Desktop/rm/lesson2/assignment/assign1/车牌3.png",1);
    output=Mat(src.rows,src.cols,CV_8UC3);

    //命名窗口
    namedWindow(WINDOW_NAME_1,WINDOW_NORMAL);
    namedWindow(WINDOW_NAME_2,WINDOW_NORMAL);
    imshow(WINDOW_NAME_1,src);
    cout << src.rows << ' ' << src.cols << endl;
    
    //转化过程
    for(int i=0;i<src.rows;i++){
        for(int j=0;j<src.cols;j++){
            double b=src.at<Vec3b>(i,j)[0]/255.0;
            double g=src.at<Vec3b>(i,j)[1]/255.0;
            double r=src.at<Vec3b>(i,j)[2]/255.0; // 注意先要进行类型转换！！
                                                    //否则先计算出取整然后转double型
            double h=geth(b,g,r);
            double s=getss(b,g,r);
            double v=getv(b,g,r);
            output.at<Vec3b>(i,j)[0]=(uchar)(h/2);
            output.at<Vec3b>(i,j)[1]=(uchar)(s*255);
            output.at<Vec3b>(i,j)[2]=(uchar)(v*255);
        }
    }
    imshow(WINDOW_NAME_2,output);
    waitKey(0);
    return 0;

}