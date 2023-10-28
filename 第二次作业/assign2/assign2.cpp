
#include<iostream>
#include<algorithm>
#include <opencv2/opencv.hpp>
//#include<opencv2/highgui/highgui.hpp>

using namespace std;
using namespace cv;

#define WINDOW_NAME_1 "初始图"
#define WINDOW_NAME_2 "结果图"


//手动的高斯核
double guss3[4][4]={
    0.05,0.1,0.05,
    0.1,0.4,0.1,
    0.05,0.1,0.05

};
double guss5[6][6]={
    1.0/56,1.0/56,2.0/56,1.0/56,1.0/56,
     1.0/56,3.0/56,4.0/56,3.0/56,1.0/56,
      2.0/56,4.0/56,8.0/56,4.0/56,2.0/56,
       1.0/56,3.0/56,4.0/56,3.0/56,1.0/56,
        1.0/56,1.0/56,2.0/56,1.0/56,1.0/56,
};


//初始化输入输出图
Mat src,output;

int main (){
    double scale;
    
    //读入缩放比例和原图像
    src=imread("/mnt/c/Users/86187/Desktop/rm/lesson2/assignment/assign2/test.png",1);
    printf("请输入缩放的比例：\n");
    scanf("%lf",&scale);

    //初始化输出图
    output=Mat(src.rows*scale,src.cols*scale,CV_8UC3);
    
    //转化过程

    //缩小图像，先模糊处理
    if(scale<1)
    for(int i=1;i<src.rows-1;i++){
            for(int j=1;j<src.cols-1;j++){
                double midb;
                midb=guss3[0][0]*src.at<Vec3b>(i-1,j-1)[0]+guss3[0][1]*src.at<Vec3b>(i-1,j)[0]+guss3[0][2]*src.at<Vec3b>(i-1,j+1)[0]
                +guss3[1][0]*src.at<Vec3b>(i,j-1)[0]+guss3[1][1]*src.at<Vec3b>(i,j)[0]+guss3[1][2]*src.at<Vec3b>(i,j+1)[0]
                +guss3[2][0]*src.at<Vec3b>(i,j-1)[0]+guss3[2][1]*src.at<Vec3b>(i,j)[0]+guss3[2][2]*src.at<Vec3b>(i,j+1)[0];
                double midg;
                midg=guss3[0][0]*src.at<Vec3b>(i-1,j-1)[1]+guss3[0][1]*src.at<Vec3b>(i-1,j)[1]+guss3[0][2]*src.at<Vec3b>(i-1,j+1)[1]
                +guss3[1][0]*src.at<Vec3b>(i,j-1)[1]+guss3[1][1]*src.at<Vec3b>(i,j)[1]+guss3[1][2]*src.at<Vec3b>(i,j+1)[1]
                +guss3[2][0]*src.at<Vec3b>(i,j-1)[1]+guss3[2][1]*src.at<Vec3b>(i,j)[1]+guss3[2][2]*src.at<Vec3b>(i,j+1)[1];
                double midr;
                midr=guss3[0][0]*src.at<Vec3b>(i-1,j-1)[2]+guss3[0][1]*src.at<Vec3b>(i-1,j)[2]+guss3[0][2]*src.at<Vec3b>(i-1,j+1)[2]
                +guss3[1][0]*src.at<Vec3b>(i,j-1)[2]+guss3[1][1]*src.at<Vec3b>(i,j)[2]+guss3[1][2]*src.at<Vec3b>(i,j+1)[2]
                +guss3[2][0]*src.at<Vec3b>(i,j-1)[2]+guss3[2][1]*src.at<Vec3b>(i,j)[2]+guss3[2][2]*src.at<Vec3b>(i,j+1)[2];
                src.at<Vec3b>(i,j-1)[0]=(uchar)midb;
                src.at<Vec3b>(i,j-1)[1]=(uchar)midg;
                src.at<Vec3b>(i,j-1)[2]=(uchar)midr;
            }
    }

    //根据缩放比例构造要输出的图
    for(int i=0;i<output.rows;i++){
            for(int j=0;j<output.cols;j++){
                int x=i/scale;
                int y=j/scale;
                output.at<Vec3b>(i,j)[0]=src.at<Vec3b>(x,y)[0];
                output.at<Vec3b>(i,j)[1]=src.at<Vec3b>(x,y)[1];
                output.at<Vec3b>(i,j)[2]=src.at<Vec3b>(x,y)[2];
            }
    }

    //放大图像 ，后模糊处理
    if(scale>1)
    for(int i=1;i<output.rows-1;i++){
            for(int j=1;j<output.cols-1;j++){
                double midb;
                midb=guss3[0][0]*output.at<Vec3b>(i-1,j-1)[0]+guss3[0][1]*output.at<Vec3b>(i-1,j)[0]+guss3[0][2]*output.at<Vec3b>(i-1,j+1)[0]
                +guss3[1][0]*output.at<Vec3b>(i,j-1)[0]+guss3[1][1]*output.at<Vec3b>(i,j)[0]+guss3[1][2]*output.at<Vec3b>(i,j+1)[0]
                +guss3[2][0]*output.at<Vec3b>(i,j-1)[0]+guss3[2][1]*output.at<Vec3b>(i,j)[0]+guss3[2][2]*output.at<Vec3b>(i,j+1)[0];
                double midg;
                midg=guss3[0][0]*output.at<Vec3b>(i-1,j-1)[1]+guss3[0][1]*output.at<Vec3b>(i-1,j)[1]+guss3[0][2]*output.at<Vec3b>(i-1,j+1)[1]
                +guss3[1][0]*output.at<Vec3b>(i,j-1)[1]+guss3[1][1]*output.at<Vec3b>(i,j)[1]+guss3[1][2]*output.at<Vec3b>(i,j+1)[1]
                +guss3[2][0]*output.at<Vec3b>(i,j-1)[1]+guss3[2][1]*output.at<Vec3b>(i,j)[1]+guss3[2][2]*output.at<Vec3b>(i,j+1)[1];
                double midr;
                midr=guss3[0][0]*output.at<Vec3b>(i-1,j-1)[2]+guss3[0][1]*output.at<Vec3b>(i-1,j)[2]+guss3[0][2]*output.at<Vec3b>(i-1,j+1)[2]
                +guss3[1][0]*output.at<Vec3b>(i,j-1)[2]+guss3[1][1]*output.at<Vec3b>(i,j)[2]+guss3[1][2]*output.at<Vec3b>(i,j+1)[2]
                +guss3[2][0]*output.at<Vec3b>(i,j-1)[2]+guss3[2][1]*output.at<Vec3b>(i,j)[2]+guss3[2][2]*output.at<Vec3b>(i,j+1)[2];
                output.at<Vec3b>(i,j-1)[0]=(uchar)midb;
                output.at<Vec3b>(i,j-1)[1]=(uchar)midg;
                output.at<Vec3b>(i,j-1)[2]=(uchar)midr;
            }
    }
    imshow(WINDOW_NAME_1,src);
    imshow(WINDOW_NAME_2,output);
    waitKey(0);
    return 0;

}
