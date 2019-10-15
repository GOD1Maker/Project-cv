#ifndef POINTTRACKING_H
#define POINTTRACKING_H
#include <iostream>
#include <ctype.h>
#include "opencv.h"
using namespace cv;
using namespace std;

Point2f point;
bool addRemovePt = false;

//鼠标操作回调
static void on_Mouse( int event, int x, int y, int /*flags*/, void* /*param*/ )
{
    //此句代码的OpenCV2版为：
    //if( event == CV_EVENT_LBUTTONDOWN )
    //此句代码的OpenCV3版为：
    if( event == EVENT_LBUTTONDOWN )
    {
        point = Point2f((float)x, (float)y);
        addRemovePt = true;
    }
}
#endif // POINTTRACKING_H
