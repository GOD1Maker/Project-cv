#ifndef USE_AT_ACCESS_PIXEL_H
#define USE_AT_ACCESS_PIXEL_H
#include "opencv.h"
#include <iostream>
using namespace std;
using namespace cv;

//描述：使用【动态地址运算配合at】方法版本的颜色空间缩减函数
void colorReduce3(Mat& inputImage, Mat& outputImage, int div)
{
    //参数准备
    outputImage = inputImage.clone();  //拷贝实参到临时变量
    int rowNumber = outputImage.rows;  //行数
    int colNumber = outputImage.cols;  //列数

    //存取彩色图像像素
    for(int i = 0;i < rowNumber;i++)
    {
        for(int j = 0;j < colNumber;j++)
        {
            // ------------------------【开始处理每个像素】--------------------
            outputImage.at<Vec3b>(i,j)[0] =  outputImage.at<Vec3b>(i,j)[0]/div*div + div/2;  //蓝色通道
            outputImage.at<Vec3b>(i,j)[1] =  outputImage.at<Vec3b>(i,j)[1]/div*div + div/2;  //绿色通道
            outputImage.at<Vec3b>(i,j)[2] =  outputImage.at<Vec3b>(i,j)[2]/div*div + div/2;  //红是通道
            // -------------------------【处理结束】----------------------------
        }  // 行处理结束
    }
}

#endif // USE_AT_ACCESS_PIXEL_H
