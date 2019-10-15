#ifndef SHI_TOMASI_H
#define SHI_TOMASI_H
#include "opencv.h"
#include <iostream>
#define WINDOW_NAME_3 "【Shi-Tomasi角点检测】"

Mat g_srcImage_f, g_grayImage_e;
int g_maxCornerNumber = 33;
int g_maxTrackbarNumber = 500;
RNG g_rng5(12345);//初始化随机数生成器

void on_GoodFeaturesToTrack( int, void* )
{
    //【1】对变量小于等于1时的处理
    if( g_maxCornerNumber <= 1 ) { g_maxCornerNumber = 1; }

    //【2】Shi-Tomasi算法（goodFeaturesToTrack函数）的参数准备
    vector<Point2f> corners;
    double qualityLevel = 0.01;//角点检测可接受的最小特征值
    double minDistance = 10;//角点之间的最小距离
    int blockSize = 3;//计算导数自相关矩阵时指定的邻域范围
    double k = 0.04;//权重系数
    Mat copy = g_srcImage_f.clone();	//复制源图像到一个临时变量中，作为感兴趣区域

    //【3】进行Shi-Tomasi角点检测
    goodFeaturesToTrack( g_grayImage_e,//输入图像
        corners,//检测到的角点的输出向量
        g_maxCornerNumber,//角点的最大数量
        qualityLevel,//角点检测可接受的最小特征值
        minDistance,//角点之间的最小距离
        Mat(),//感兴趣区域
        blockSize,//计算导数自相关矩阵时指定的邻域范围
        false,//不使用Harris角点检测
        k );//权重系数


    //【4】输出文字信息
    cout<<"\t>此次检测到的角点数量为："<<corners.size()<<endl;

    //【5】绘制检测到的角点
    int r = 4;
    for( int i = 0; i < corners.size(); i++ )
    {
        //以随机的颜色绘制出角点
        circle( copy, corners[i], r, Scalar(g_rng.uniform(0,255), g_rng5.uniform(0,255),
            g_rng5.uniform(0,255)), -1, 8, 0 );
    }

    //【6】显示（更新）窗口
    imshow( WINDOW_NAME_3, copy );
}
#endif // SHI_TOMASI_H
