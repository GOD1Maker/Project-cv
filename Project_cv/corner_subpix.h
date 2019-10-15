#ifndef CORNER_SUBPIX_H
#define CORNER_SUBPIX_H
#include "opencv.h"
#include <iostream>
#define WINDOW_NAME_4 "【亚像素级角点检测】"

Mat g_srcImage_g, g_grayImage_d;
int g_maxCornerNumber2 = 33;
int g_maxTrackbarNumber2 = 500;
RNG g_rng6(12345);//初始化随机数生成器

void on_GoodFeaturesToTrack2( int, void* )
{
    //【1】对变量小于等于1时的处理
    if( g_maxCornerNumber2 <= 1 ) { g_maxCornerNumber2 = 1; }

    //【2】Shi-Tomasi算法（goodFeaturesToTrack函数）的参数准备
    vector<Point2f> corners;
    double qualityLevel = 0.01;//角点检测可接受的最小特征值
    double minDistance = 15;//角点之间的最小距离
    int blockSize = 3;//计算导数自相关矩阵时指定的邻域范围
    double k = 0.04;//权重系数
    Mat copy = g_srcImage_g.clone();	//复制源图像到一个临时变量中，作为感兴趣区域

    //【3】进行Shi-Tomasi角点检测
    goodFeaturesToTrack( g_grayImage_d,//输入图像
        corners,//检测到的角点的输出向量
        g_maxCornerNumber2,//角点的最大数量
        qualityLevel,//角点检测可接受的最小特征值
        minDistance,//角点之间的最小距离
        Mat(),//感兴趣区域
        blockSize,//计算导数自相关矩阵时指定的邻域范围
        false,//不使用Harris角点检测
        k );//权重系数

    //【4】输出文字信息
    cout<<"\n\t>-------------此次检测到的角点数量为："<<corners.size()<<endl;

    //【5】绘制检测到的角点
    int r = 4;
    for( unsigned int i = 0; i < corners.size(); i++ )
    {
        //以随机的颜色绘制出角点
        circle( copy, corners[i], r, Scalar(g_rng6.uniform(0,255), g_rng6.uniform(0,255),
            g_rng6.uniform(0,255)), -1, 8, 0 );
    }

    //【6】显示（更新）窗口
    imshow( WINDOW_NAME_4, copy );

    //【7】亚像素角点检测的参数设置
    Size winSize = Size( 5, 5 );
    Size zeroZone = Size( -1, -1 );
    TermCriteria criteria = TermCriteria( TermCriteria::EPS + TermCriteria::MAX_ITER, 40, 0.001 );

    //【8】计算出亚像素角点位置
    cornerSubPix( g_grayImage_d, corners, winSize, zeroZone, criteria );

    //【9】输出角点信息
    for( int i = 0; i < corners.size(); i++ )
        { cout<<" \t>>精确角点坐标["<<i<<"]  ("<<corners[i].x<<","<<corners[i].y<<")"<<endl; }


}
#endif // CORNER_SUBPIX_H
