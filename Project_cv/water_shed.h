#ifndef WATER_SHED_H
#define WATER_SHED_H
#include "opencv.h"
#include <iostream>
using namespace cv;
using namespace std;

#define WINDOW_NAME_e "【程序窗口1】"
#define WINDOW_NAME_f "【分水岭算法效果图】"

Mat g_maskImage, g_srcImage_c;
Point prevPt(-1, -1);

static void on_Mouse3( int event, int x, int y, int flags, void* )
{
    //处理鼠标不在窗口中的情况
    if( x < 0 || x >= g_srcImage_c.cols || y < 0 || y >= g_srcImage_c.rows )
        return;

    //处理鼠标左键相关消息
    if( event == EVENT_LBUTTONUP || !(flags & EVENT_FLAG_LBUTTON) )
        prevPt = Point(-1,-1);
    else if( event == EVENT_LBUTTONDOWN )
        prevPt = Point(x,y);

    //鼠标左键按下并移动，绘制出白色线条
    else if( event == EVENT_MOUSEMOVE && (flags & EVENT_FLAG_LBUTTON) )
    {
        Point pt(x, y);
        if( prevPt.x < 0 )
            prevPt = pt;
        line( g_maskImage, prevPt, pt, Scalar::all(255), 5, 8, 0 );
        line( g_srcImage_c, prevPt, pt, Scalar::all(255), 5, 8, 0 );
        prevPt = pt;
        imshow(WINDOW_NAME_e, g_srcImage_c);
    }
}
#endif // WATER_SHED_H
