#ifndef USE_POINTER_ACCESS_PIXEL_H
#define USE_POINTER_ACCESS_PIXEL_H
#include "opencv.h"
#include <iostream>
using namespace std;
using namespace cv;

//描述：使用【指针访问：C操作符[ ]】方法版的颜色空间缩减函数
void colorReduce(Mat& inputImage, Mat& outputImage, int div)
{
    //参数准备
    outputImage = inputImage.clone();  //拷贝实参到临时变量
    int rowNumber = outputImage.rows;  //行数
    int colNumber = outputImage.cols*outputImage.channels();  //列数 x 通道数=每一行元素的个数

    //双重循环，遍历所有的像素值
    for(int i = 0;i < rowNumber;i++)  //行循环
    {
        uchar* data = outputImage.ptr<uchar>(i);  //获取第i行的首地址
        for(int j = 0;j < colNumber;j++)   //列循环
        {
            // ---------【开始处理每个像素】-------------
            data[j] = data[j]/div*div + div/2;
            // ----------【处理结束】---------------------
        }  //行处理结束
    }
}

#endif // USE_POINTER_ACCESS_PIXEL_H
