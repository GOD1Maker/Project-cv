#ifndef CALC_BACK_PROJECT_H
#define CALC_BACK_PROJECT_H
#include "opencv.h"
#include <iostream>
#define WINDOW_NAME_j "【原始图】"

Mat g_srcImage_d; Mat g_hsvImage; Mat g_hueImage;
int g_bins = 30;//直方图组距

void on_BinChange(int, void* )
{
    //【1】参数准备
    MatND hist;
    int histSize = MAX( g_bins, 2 );
    float hue_range[] = { 0, 180 };
    const float* ranges = { hue_range };

    //【2】计算直方图并归一化
    calcHist( &g_hueImage, 1, 0, Mat(), hist, 1, &histSize, &ranges, true, false );
    normalize( hist, hist, 0, 255, NORM_MINMAX, -1, Mat() );

    //【3】计算反向投影
    MatND backproj;
    calcBackProject( &g_hueImage, 1, 0, hist, backproj, &ranges, 1, true );

    //【4】显示反向投影
    imshow( "反向投影图", backproj );

    //【5】绘制直方图的参数准备
    int w = 400; int h = 400;
    int bin_w = cvRound( (double) w / histSize );
    Mat histImg = Mat::zeros( w, h, CV_8UC3 );

    //【6】绘制直方图
    for( int i = 0; i < g_bins; i ++ )
    { rectangle( histImg, Point( i*bin_w, h ), Point( (i+1)*bin_w, h - cvRound( hist.at<float>(i)*h/255.0 ) ), Scalar( 100, 123, 255 ), -1 ); }

    //【7】显示直方图窗口
    imshow( "直方图", histImg );
}

#endif // CALC_BACK_PROJECT_H
