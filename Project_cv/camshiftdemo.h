#ifndef CAMSHIFTDEMO_H
#define CAMSHIFTDEMO_H
#include <iostream>
#include <ctype.h>
#include "opencv.h"
using namespace cv;
using namespace std;

Mat image;
bool backprojMode = false;
bool selectObject = false;
int trackObject = 0;
bool showHist = true;
Point origin;
Rect selection;
int vmin = 10, vmax = 256, smin = 30;

static void onMouse( int event, int x, int y, int, void* )
{
    if( selectObject )
    {
        selection.x = MIN(x, origin.x);
        selection.y = MIN(y, origin.y);
        selection.width = std::abs(x - origin.x);
        selection.height = std::abs(y - origin.y);

        selection &= Rect(0, 0, image.cols, image.rows);
    }

    switch( event )
    {
    //此句代码的OpenCV2版为：
    //case CV_EVENT_LBUTTONDOWN:
    //此句代码的OpenCV3版为：
    case EVENT_LBUTTONDOWN:
        origin = Point(x,y);
        selection = Rect(x,y,0,0);
        selectObject = true;
        break;
    //此句代码的OpenCV2版为：
    //case CV_EVENT_LBUTTONUP:
    //此句代码的OpenCV3版为：
    case EVENT_LBUTTONUP:
        selectObject = false;
        if( selection.width > 0 && selection.height > 0 )
            trackObject = -1;
        break;
    }
}
const char* keys =
{
    "{1|  | 0 | camera number}"
};
#endif // CAMSHIFTDEMO_H
