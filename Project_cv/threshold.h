#ifndef THRESHOLD_H
#define THRESHOLD_H

#define WINDOW_NAME5 "【程序窗口】"
#include "opencv.h"
#include <iostream>
using namespace std;
using namespace cv;

int g_nThresholdValue = 100;
int g_nThresholdType = 3;
Mat g_srcImage3, g_grayImage, g_dstImage3;

//描述：自定义的阈值回调函数
void on_Threshold( int, void* )
{
    //调用阈值函数
    threshold(g_grayImage,g_dstImage3,g_nThresholdValue,255,g_nThresholdType);

    //更新效果图
    imshow( WINDOW_NAME5, g_dstImage3 );
}

#endif // THRESHOLD_H
