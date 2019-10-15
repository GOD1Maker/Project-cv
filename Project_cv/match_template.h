#ifndef MATCH_TEMPLATE_H
#define MATCH_TEMPLATE_H
#include "opencv.h"
#include <iostream>
#define WINDOW_NAME_k "【原始图片】"
#define WINDOW_NAME_l "【匹配窗口】"
Mat g_srcImage_e; Mat g_templateImage; Mat g_resultImage;
int g_nMatchMethod;
int g_nMaxTrackbarNum = 5;

void on_Matching( int, void* )
{
    //【1】给局部变量初始化
    Mat srcImage;
    g_srcImage_e.copyTo( srcImage );

    //【2】初始化用于结果输出的矩阵
    int resultImage_rows = g_srcImage_e.rows - g_templateImage.rows + 1;
    int resultImage_cols =  g_srcImage_e.cols - g_templateImage.cols + 1;
    g_resultImage.create(resultImage_rows,resultImage_cols, CV_32FC1);

    //【3】进行匹配和标准化
    matchTemplate( g_srcImage_e, g_templateImage, g_resultImage, g_nMatchMethod );
    normalize( g_resultImage, g_resultImage, 0, 1, NORM_MINMAX, -1, Mat() );

    //【4】通过函数 minMaxLoc 定位最匹配的位置
    double minValue; double maxValue; Point minLocation; Point maxLocation;
    Point matchLocation;
    minMaxLoc( g_resultImage, &minValue, &maxValue, &minLocation, &maxLocation, Mat() );

    //【5】对于方法 SQDIFF 和 SQDIFF_NORMED, 越小的数值有着更高的匹配结果. 而其余的方法, 数值越大匹配效果越好：
    if( g_nMatchMethod  == TM_SQDIFF || g_nMatchMethod == TM_SQDIFF_NORMED )
    { matchLocation = minLocation; }
    else
    { matchLocation = maxLocation; }

    //【6】绘制出矩形，并显示最终结果
    rectangle( srcImage, matchLocation, Point( matchLocation.x + g_templateImage.cols , matchLocation.y + g_templateImage.rows ), Scalar(0,0,255), 2, 8, 0 );
    rectangle( g_resultImage, matchLocation, Point( matchLocation.x + g_templateImage.cols , matchLocation.y + g_templateImage.rows ), Scalar(0,0,255), 2, 8, 0 );

    imshow( WINDOW_NAME_k, srcImage );
    imshow( WINDOW_NAME_l, g_resultImage );

}


#endif // MATCH_TEMPLATE_H
