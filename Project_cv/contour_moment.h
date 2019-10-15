#ifndef CONTOUR_MOMENT_H
#define CONTOUR_MOMENT_H
#include "opencv.h"
#include <iostream>
using namespace cv;
using namespace std;

#define WINDOW_NAME_c "【原始图】"
#define WINDOW_NAME_d "【图像轮廓】"

Mat g_srcImage_b; Mat g_grayImage_b;
int g_nThresh3 = 100;
int g_nMaxThresh2 = 255;
RNG g_rng4(12345);
Mat g_cannyMat_output;
vector<vector<Point> > g_vContours2;
vector<Vec4i> g_vHierarchy2;

void on_ThreshChange2(int, void* )
{
    // 使用Canndy检测边缘
    Canny( g_grayImage_b, g_cannyMat_output, g_nThresh3, g_nThresh3*2, 3 );

    // 找到轮廓
    findContours( g_cannyMat_output, g_vContours2, g_vHierarchy2, RETR_TREE, CHAIN_APPROX_SIMPLE, Point(0, 0) );

    // 计算矩
    vector<Moments> mu(g_vContours2.size() );
    for(unsigned int i = 0; i < g_vContours2.size(); i++ )
    { mu[i] = moments( g_vContours2[i], false ); }

    //  计算中心矩
    vector<Point2f> mc( g_vContours2.size() );
    for( unsigned int i = 0; i < g_vContours.size(); i++ )
    { mc[i] = Point2f( static_cast<float>(mu[i].m10/mu[i].m00), static_cast<float>(mu[i].m01/mu[i].m00 )); }

    // 绘制轮廓
    Mat drawing = Mat::zeros( g_cannyMat_output.size(), CV_8UC3 );
    for( unsigned int i = 0; i< g_vContours2.size(); i++ )
    {
        Scalar color = Scalar( g_rng4.uniform(0, 255), g_rng4.uniform(0,255), g_rng4.uniform(0,255) );//随机生成颜色值
        drawContours( drawing, g_vContours2, i, color, 2, 8, g_vHierarchy2, 0, Point() );//绘制外层和内层轮廓
        circle( drawing, mc[i], 4, color, -1, 8, 0 );;//绘制圆
    }

    // 显示到窗口中
    namedWindow( WINDOW_NAME_d, WINDOW_AUTOSIZE );
    imshow( WINDOW_NAME_d, drawing );

    // 通过m00计算轮廓面积并且和OpenCV函数比较
    printf("\t 输出内容: 面积和轮廓长度\n");
    for(unsigned  int i = 0; i< g_vContours2.size(); i++ )
    {
        printf(" >通过m00计算出轮廓[%d]的面积: (M_00) = %.2f \n OpenCV函数计算出的面积=%.2f , 长度: %.2f \n\n", i, mu[i].m00, contourArea(g_vContours2[i]), arcLength( g_vContours2[i], true ) );
        Scalar color = Scalar( g_rng4.uniform(0, 255), g_rng4.uniform(0,255), g_rng4.uniform(0,255) );
        drawContours( drawing, g_vContours2, i, color, 2, 8, g_vHierarchy2, 0, Point() );
        circle( drawing, mc[i], 4, color, -1, 8, 0 );
    }
}

#endif // CONTOUR_MOMENT_H
