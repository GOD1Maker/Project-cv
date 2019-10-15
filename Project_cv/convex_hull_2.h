#ifndef CONVEX_HULL_2_H
#define CONVEX_HULL_2_H
#include "opencv.h"
#include <iostream>
#define WINDOW_NAME6 "【原始图窗口】"					//为窗口标题定义的宏
#define WINDOW_NAME7 "【效果图窗口】"					//为窗口标题定义的宏
Mat g_srcImage4; Mat g_grayImage2;
int g_nThresh = 50;
int g_maxThresh = 255;
RNG g_rng2(12345);
Mat srcImage_copy = g_srcImage4.clone();
Mat g_thresholdImage_output;
vector<vector<Point> > g_vContours;
vector<Vec4i> g_vHierarchy;

//      描述：回调函数
//----------------------------------------------------------------------------------------------
void on_ThreshChange(int, void* )
{
    // 对图像进行二值化，控制阈值
    threshold( g_grayImage2, g_thresholdImage_output, g_nThresh, 255, THRESH_BINARY );

    // 寻找轮廓
    findContours( g_thresholdImage_output, g_vContours, g_vHierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE, Point(0, 0) );

    // 遍历每个轮廓，寻找其凸包
    vector<vector<Point> >hull( g_vContours.size() );
    for( unsigned int i = 0; i < g_vContours.size(); i++ )
    {
        convexHull( Mat(g_vContours[i]), hull[i], false );
    }

    // 绘出轮廓及其凸包
    Mat drawing = Mat::zeros( g_thresholdImage_output.size(), CV_8UC3 );
    for(unsigned  int i = 0; i< g_vContours.size(); i++ )
    {
        Scalar color = Scalar( g_rng.uniform(0, 255), g_rng.uniform(0,255), g_rng.uniform(0,255) );
        drawContours( drawing, g_vContours, i, color, 1, 8, vector<Vec4i>(), 0, Point() );
        drawContours( drawing, hull, i, color, 1, 8, vector<Vec4i>(), 0, Point() );
    }

    // 显示效果图
    imshow( WINDOW_NAME7, drawing );
}
#endif // CONVEX_HULL_2_H
