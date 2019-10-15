#ifndef USE_ITERATOR_ACCESS_PIXEL_H
#define USE_ITERATOR_ACCESS_PIXEL_H
#include "opencv.h"
#include <iostream>
using namespace std;
using namespace cv;
//使用【迭代器】方法版的颜色空间缩减函数
void colorReduce2(Mat& inputImage, Mat& outputImage, int div)
{
    //参数准备
    outputImage = inputImage.clone();  //拷贝实参到临时变量
    //获取迭代器
    Mat_<Vec3b>::iterator it = outputImage.begin<Vec3b>();  //初始位置的迭代器
    Mat_<Vec3b>::iterator itend = outputImage.end<Vec3b>();  //终止位置的迭代器

    //存取彩色图像像素
    for(;it != itend;++it)
    {
        // ------------------------【开始处理每个像素】--------------------
        (*it)[0] = (*it)[0]/div*div + div/2;
        (*it)[1] = (*it)[1]/div*div + div/2;
        (*it)[2] = (*it)[2]/div*div + div/2;
        // ------------------------【处理结束】----------------------------
    }
}
#endif // USE_ITERATOR_ACCESS_PIXEL_H
