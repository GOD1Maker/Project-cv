#ifndef HARRIS_CORNER_DETECTION_H
#define HARRIS_CORNER_DETECTION_H
#include "opencv.h"
#include <iostream>
#define WINDOW_NAME_1 "【程序窗口1】"
#define WINDOW_NAME_2 "【程序窗口2】"

Mat g_srcImage_j, g_srcImage_k,g_grayImage_c;
int thresh = 30; //当前阈值
int max_thresh = 175; //最大阈值

void on_CornerHarris( int, void* )
{
    //---------------------------【1】定义一些局部变量-----------------------------
    Mat dstImage;//目标图
    Mat normImage;//归一化后的图
    Mat scaledImage;//线性变换后的八位无符号整型的图

    //---------------------------【2】初始化---------------------------------------
    //置零当前需要显示的两幅图，即清除上一次调用此函数时他们的值
    dstImage = Mat::zeros( g_srcImage_j.size(), CV_32FC1 );
    g_srcImage_k=g_srcImage_j.clone( );

    //---------------------------【3】正式检测-------------------------------------
    //进行角点检测
    cornerHarris( g_grayImage_c, dstImage, 2, 3, 0.04, BORDER_DEFAULT );

    // 归一化与转换
    normalize( dstImage, normImage, 0, 255, NORM_MINMAX, CV_32FC1, Mat() );
    convertScaleAbs( normImage, scaledImage );//将归一化后的图线性变换成8位无符号整型

    //---------------------------【4】进行绘制-------------------------------------
    // 将检测到的，且符合阈值条件的角点绘制出来
    for( int j = 0; j < normImage.rows ; j++ )
    { for( int i = 0; i < normImage.cols; i++ )
    {
        if( (int) normImage.at<float>(j,i) > thresh+80 )
        {
            circle( g_srcImage_k, Point( i, j ), 5,  Scalar(10,10,255), 2, 8, 0 );
            circle( scaledImage, Point( i, j ), 5,  Scalar(0,10,255), 2, 8, 0 );
        }
    }
    }
    //---------------------------【4】显示最终效果---------------------------------
    imshow( WINDOW_NAME_1, g_srcImage_k );
    imshow( WINDOW_NAME_2, scaledImage );

}


#endif // HARRIS_CORNER_DETECTION_H
