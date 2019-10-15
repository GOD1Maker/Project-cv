#ifndef INPAINT_H
#define INPAINT_H
#include "opencv.h"
#include <iostream>

using namespace cv;
using namespace std;
Mat srcImage0,srcImage1, inpaintMask;
Point previousPoint(-1,-1);//原来的点坐标
#define WINDOW_NAME_g "【原始图参考】"
#define WINDOW_NAME_h "【原始图】"
#define WINDOW_NAME_i "【修补后的效果图】"

static void On_Mouse2( int event, int x, int y, int flags, void* )
{
    //鼠标左键弹起消息
    if( event == EVENT_LBUTTONUP || !(flags & EVENT_FLAG_LBUTTON) )
        previousPoint = Point(-1,-1);
    //鼠标左键按下消息
    else if( event == EVENT_LBUTTONDOWN )
        previousPoint = Point(x,y);
    //鼠标按下并移动，进行绘制
    else if( event == EVENT_MOUSEMOVE && (flags & EVENT_FLAG_LBUTTON) )
    {
        Point pt(x,y);
        if( previousPoint.x < 0 )
            previousPoint = pt;
        //绘制白色线条
        line( inpaintMask, previousPoint, pt, Scalar::all(255), 5, 8, 0 );
        line( srcImage1, previousPoint, pt, Scalar::all(255), 5, 8, 0 );
        previousPoint = pt;
        imshow(WINDOW_NAME_h, srcImage1);
    }
}

#endif // INPAINT_H
