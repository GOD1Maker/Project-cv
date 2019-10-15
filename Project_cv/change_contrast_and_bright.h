#ifndef CHANGE_CONTRAST_AND_BRIGHT_H
#define CHANGE_CONTRAST_AND_BRIGHT_H
#include "opencv.h"
#include <iostream>
using namespace std;
using namespace cv;
int g_nContrastValue; //对比度值
int g_nBrightValue;  //亮度值
Mat g_srcImage,g_dstImage1;
//	描述：改变图像对比度和亮度值的回调函数
static void ContrastAndBright(int, void *)
{

    // 创建窗口
    namedWindow("【原始图窗口】", 1);

    // 三个for循环，执行运算 g_dstImage(i,j) = a*g_srcImage(i,j) + b
    for( int y = 0; y < g_srcImage.rows; y++ )
    {
        for( int x = 0; x < g_srcImage.cols; x++ )
        {
            for( int c = 0; c < 3; c++ )
            {
                g_dstImage1.at<Vec3b>(y,x)[c] = saturate_cast<uchar>( (g_nContrastValue*0.01)*( g_srcImage.at<Vec3b>(y,x)[c] ) + g_nBrightValue );
            }
        }
    }

    // 显示图像
    imshow("【原始图窗口】", g_srcImage);
    imshow("【效果图窗口】", g_dstImage1);
}
#endif // CHANGE_CONTRAST_AND_BRIGHT_H
