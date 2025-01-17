#ifndef OPTICFLOW_H
#define OPTICFLOW_H
#include "opencv.h"
#include <iostream>
#include <cstdio>

using namespace std;
using namespace cv;

void tracking(Mat &frame, Mat &output);//跟踪
bool addNewPoints();//检查新点是否被添加
bool acceptTrackedPoint(int i);//觉得哪些跟踪点被接受

//		描述：声明全局变量
string window_name = "optical flow tracking";
Mat gray;	// 当前图片
Mat gray_prev;	// 预测图片
vector<Point2f> points[2];	// point0为特征点的原来位置，point1为特征点的新位置
vector<Point2f> initial;	// 初始化跟踪点的位置
vector<Point2f> features;	// 检测的特征
int maxCount = 500;	// 检测的最大特征数
double qLevel = 0.01;	// 特征检测的等级
double minDist = 10.0;	// 两特征点之间的最小距离
vector<uchar> status;	// 跟踪特征的状态，特征的流发现为1，否则为0
vector<float> err;

void tracking(Mat &frame, Mat &output)
{

    //此句代码的OpenCV3版为：
    cvtColor(frame, gray, COLOR_BGR2GRAY);
    //此句代码的OpenCV2版为：
    //cvtColor(frame, gray, CV_BGR2GRAY);

    frame.copyTo(output);

    // 添加特征点
    if (addNewPoints())
    {
        goodFeaturesToTrack(gray, features, maxCount, qLevel, minDist);
        points[0].insert(points[0].end(), features.begin(), features.end());
        initial.insert(initial.end(), features.begin(), features.end());
    }

    if (gray_prev.empty())
    {
        gray.copyTo(gray_prev);
    }
    // l-k光流法运动估计
    calcOpticalFlowPyrLK(gray_prev, gray, points[0], points[1], status, err);
    // 去掉一些不好的特征点
    int k = 0;
    for (size_t i=0; i<points[1].size(); i++)
    {
        if (acceptTrackedPoint(i))
        {
            initial[k] = initial[i];
            points[1][k++] = points[1][i];
        }
    }
    points[1].resize(k);
    initial.resize(k);
    // 显示特征点和运动轨迹
    for (size_t i=0; i<points[1].size(); i++)
    {
        line(output, initial[i], points[1][i], Scalar(0, 0, 255));
        circle(output, points[1][i], 3, Scalar(0, 255, 0), -1);
    }

    // 把当前跟踪结果作为下一此参考
    swap(points[1], points[0]);
    swap(gray_prev, gray);

    imshow(window_name, output);
}

bool addNewPoints()
{
    return points[0].size() <= 10;
}

bool acceptTrackedPoint(int i)
{
    return status[i] && ((abs(points[0][i].x - points[1][i].x) + abs(points[0][i].y - points[1][i].y)) > 2);
}

#endif // OPTICFLOW_H
